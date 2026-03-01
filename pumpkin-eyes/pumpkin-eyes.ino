/*
 * Animatronic Eyes Controller v0.1
 * 
 * This Arduino project controls animatronic eyes inspired by Will Cogley's design
 * (https://www.youtube.com/@WillCogley). The system uses 6 servo motors to create
 * realistic eye movements and expressions.
 * 
 * Hardware Setup:
 * - Arduino board (compatible with Servo library)
 * - 6 servo motors connected to digital pins 8, 9, 10, 11, 12, 13
 * 
 * Servo Pin Mapping:
 * - Pin 12: Eyes left/right movement servo
 * - Pin 13: Eyes up/down movement servo
 * - Pin 8: Right lower eyelid servo
 * - Pin 9: Right upper eyelid servo
 * - Pin 10: Left upper eyelid servo
 * - Pin 11: Left lower eyelid servo
 * 
 * Features:
 * - Independent control of left and right eyelids
 * - Coordinated eye movement (up/down and left/right)
 * - Blinking animation
 * - Individual eye winking
 * - Surprised expressions
 * - Mouth invasion behavior (triggered when someone reaches into mouth)
 * 
 * MEMORY OPTIMIZATION:
 * ====================
 * To save SRAM on Arduino Nano (2KB limit), most behaviors are disabled.
 * Currently only IDLE and MOUTH_INVASION behaviors are enabled.
 * 
 * TO CHANGE STARTUP BEHAVIOR:
 * 1. Find the setBehavior() call in setup() function
 * 2. Change BEHAVIOR_IDLE to your desired behavior:
 *    - BEHAVIOR_IDLE: Basic idle behavior
 *    - BEHAVIOR_MOUTH_INVASION: Mouth invasion behavior
 * 
 * TO ENABLE OTHER BEHAVIORS:
 * See Behaviors.ino for detailed instructions on enabling additional behaviors.
 * 
 * TODO LIST:
 * ==========
 * 
 * HIGH PRIORITY:
 * - Verify pin assignments work with specific Arduino board
 * - Test servo response on each pin to ensure proper operation
 * - Calibrate center positions for specific mechanical setup
 * - Test and adjust position values to ensure eyes are properly centered
 * - Calibrate movement ranges to prevent mechanical damage
 * 
 * MEDIUM PRIORITY:
 * - Add error checking for servo attachment
 * - Verify all servos are responding before proceeding
 * - Implement servo range testing to find min/max positions
 * - Add power supply voltage monitoring if using external power
 * - Adjust timing intervals based on desired behavior
 * - Add randomness to timing for more natural movement
 * - Test different blink speeds and positions
 * - Adjust blink duration based on testing
 * - Add variation in blink duration and intensity
 * - Consider asymmetric blinking for more realistic behavior
 * - Add partial blink variations
 * - Test different movement patterns and speeds
 * - Add smooth movement transitions
 * - Implement more realistic eye movement patterns (saccades, etc.)
 * - Add smooth return to center for random movements
 * - Adjust hold times based on desired behavior
 * 
 * LOW PRIORITY:
 * - Add watchdog timer to prevent servo jitter
 * - Implement power-saving mode when idle
 * - Add serial command interface for manual control
 * - Consider adding sensor input (light, motion, etc.) for reactive behavior
 * - Add function for manual servo control via serial commands
 * - Add function for testing individual servo ranges
 * - Add function for saving/loading calibrated positions
 * - Add function for different expressions (anger, sadness, etc.)
 * - Add function for coordinated eye and eyelid movements
 * - Add function for power management and servo shutdown
 * 
 * Based on design by: Will Cogley
 * 
 * Note: Ensure all servos are properly powered and calibrated before use.
 */

#include "Globals.h"



// Initialize current position tracking variables
uint8_t eyesLeftRightPos = (EyePos_Default::EYES_LEFT_POS + EyePos_Default::EYES_RIGHT_POS) / 2;
uint8_t eyesUpDownPos = (EyePos_Default::EYES_LEFT_POS + EyePos_Default::EYES_RIGHT_POS) / 2;
uint8_t leftUpperPos = EyePos_Default::LEFT_EYELID_UPPER_OPEN;
uint8_t leftLowerPos = EyePos_Default::LEFT_EYELID_LOWER_OPEN;
uint8_t rightUpperPos = EyePos_Default::RIGHT_EYELID_UPPER_OPEN;
uint8_t rightLowerPos = EyePos_Default::RIGHT_EYELID_LOWER_OPEN;

// Debug mode variables
bool debugMode = false;
String serialInput = "";


// Timing variables
unsigned long lastBlinkTime = 0;
unsigned long lastEyeMoveTime = 0;

/*
 * Handle serial commands for debug mode
 */
void handleSerialCommands() {
  while (Serial.available() > 0) {
    char inChar = Serial.read();
    
    if (inChar == '\n' || inChar == '\r') {
      // Process complete command
      serialInput.trim();
      serialInput.toLowerCase();
      
      if (serialInput == "debugmode") {
        debugMode = !debugMode;
        Serial.print("Debug mode: ");
        Serial.println(debugMode ? "ON" : "OFF");
        
        if (debugMode) {
          Serial.println("Behaviors paused. Available commands:");
          Serial.println("- 'debugmode' - Toggle debug mode");
          Serial.println("- 'center' - Move eyes to center");
          Serial.println("- 'left' - Move eyes left");
          Serial.println("- 'right' - Move eyes right");
          Serial.println("- 'up' - Move eyes up");
          Serial.println("- 'down' - Move eyes down");
          Serial.println("- 'blink' - Blink once");
          Serial.println("- 'open' - Open eyes");
          Serial.println("- 'close' - Close eyes");
          Serial.println("- 'speed <1-10>' - Set movement speed");
        } else {
          Serial.println("Behaviors resumed.");
        }
      } else if (debugMode) {
        // Handle debug commands
        if (serialInput == "center") {
          moveEyeTo(0.0, 0.0);
          Serial.println("Eyes moved to center");
        } else if (serialInput == "left") {
          moveEyeTo(-1.0, 0.0);
          Serial.println("Eyes moved left");
        } else if (serialInput == "right") {
          moveEyeTo(1.0, 0.0);
          Serial.println("Eyes moved right");
        } else if (serialInput == "up") {
          moveEyeTo(0.0, -1.0);
          Serial.println("Eyes moved up");
        } else if (serialInput == "down") {
          moveEyeTo(0.0, 1.0);
          Serial.println("Eyes moved down");
        } else if (serialInput == "blink") {
          blink();
          Serial.println("Blinked");
        } else if (serialInput == "open") {
          moveEyelids(1.0, 1.0);
          Serial.println("Eyes opened");
        } else if (serialInput == "surprised") {
          surprisedEyes();
          Serial.println("Eyes surprised");
        } else if (serialInput == "close") {
          moveEyelids(0.0, 0.0);
          Serial.println("Eyes closed");
        } else if (serialInput == "twitch") {
          eyelidTwitch(15, 150);
          Serial.println("Eyes twitched");
        } else if (serialInput.startsWith("speed")) {
          // Parse speed command: "speed 3" or "speed 7"
          int spaceIndex = serialInput.indexOf(' ');
          if (spaceIndex > 0) {
            int newSpeed = serialInput.substring(spaceIndex + 1).toInt();
            setSmoothMovementSpeed(newSpeed);
          } else {
            Serial.println("Usage: speed <1-10>");
          }
        } else {
          Serial.print("Unknown command: ");
          Serial.println(serialInput);
        }
      }
      
      serialInput = ""; // Clear input buffer
    } else {
      serialInput += inChar;
    }
  }
}

void setup() {
  
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Attach all servos using the centralized function
  attachServos();
  
  // Initialize sensor
  initializeSensor();
  
  // Set initial center position
  OpenLookForward();
  delay(8000);
  
  // Initialize behavior system
  // STARTUP BEHAVIOR: Change this to set the initial behavior
  // Available behaviors: BEHAVIOR_IDLE, BEHAVIOR_MOUTH_INVASION, BEHAVIOR_SLEEPING
  setBehavior(BEHAVIOR_SLEEPING); // Start with sleeping behavior
}

void loop() {
  // Always handle serial commands first
  handleSerialCommands();
  
  // Update sensor readings
  loopMovementSensor();
  
  // Update all smooth movements (non-blocking)
  smoothMovementLoop();
  
  // Only run behaviors if not in debug mode
  if (!debugMode) {
    // Call the behavior tick function to handle current behavior
    behaviorLoop();
  }
}
