/*
 * Globals.h
 * 
 * Header file for Animatronic Eyes Controller v0.1
 * Contains all declarations needed across the project
 */

#ifndef GLOBALS_H
#define GLOBALS_H

// #ignore: Servo.h is included in the Arduino IDE
#include <Servo.h>

// Servo objects for each motor
Servo leftUpperEyelid;    // Pin 10
Servo leftLowerEyelid;    // Pin 11
Servo rightUpperEyelid;   // Pin 9
Servo rightLowerEyelid;   // Pin 8 
Servo eyesUpDown;         // Pin 13
Servo eyesLeftRight;      // Pin 12

// Enum defining different eye behaviors
enum EyeBehavior {
  BEHAVIOR_IDLE,           // Default idle state - occasional blinks and small movements
  BEHAVIOR_ATTENTIVE,      // More active - looking around, following movement
  BEHAVIOR_SURPRISED,      // Wide eyes, quick movements, alert behavior
  BEHAVIOR_CURIOUS,        // Focused looking, head tilting simulation
  BEHAVIOR_PLAYFUL,        // Quick movements, winks, expressive behavior
  BEHAVIOR_TESTING,        // Test mode - runs through all movements
  BEHAVIOR_PUMPKIN,        // Pumpkin behavior with sequence-based states
  BEHAVIOR_MOUTH_INVASION, // Mouth invasion behavior - triggered when someone reaches into mouth
  BEHAVIOR_SLEEPING        // Sleeping behavior - tired blinking, half-closed, slow blinks, gradual closing
};

// Enum defining pumpkin behavior internal states
enum PumpkinState {
  PUMPKIN_IDLE,        // Resting, occasional blinks
  PUMPKIN_SCANNING,    // Looking around
  PUMPKIN_CURIOUS,     // Spotting something interesting
  PUMPKIN_PLAYFUL,     // Expressive reactions
  PUMPKIN_RETURN       // Returning to idle
};

// Enum defining mouth invasion behavior internal states
enum MouthInvasionState {
  MOUTH_INVASION_ENTRY,        // Transition from eyes closed
  MOUTH_INVASION_SURPRISED,    // Wide-eyed surprise (2s)
  MOUTH_INVASION_LOOK_FORWARD, // Look straight forward (1s)
  MOUTH_INVASION_SHUFFLING,    // Looking down with side-to-side movement
  MOUTH_INVASION_INVITING,     // Forward look with inviting eyelid twitch
  MOUTH_INVASION_QUICK_LOOK,   // Quick down/up/forward sequence
  MOUTH_INVASION_RANDOM_LOOP   // Continuous random forward/down looking
};

// Enum defining sleeping behavior internal states
enum SleepingState {
  SLEEPING_TIRED_BLINK,   // Blinking like tired
  SLEEPING_HALF_CLOSED,   // Eyes half-closed
  SLEEPING_SLOW_BLINKS,   // Slow blinks with half-closed eyes
  SLEEPING_CLOSING,       // Gradually closing eyes
  SLEEPING_CLOSED         // Fully closed
};

// Pin definitions
const int LEFT_UPPER_EYELID_PIN = 10;
const int LEFT_LOWER_EYELID_PIN = 11;
const int RIGHT_UPPER_EYELID_PIN = 9;
const int RIGHT_LOWER_EYELID_PIN = 8;
const int EYES_UP_DOWN_PIN = 13;
const int EYES_LEFT_RIGHT_PIN = 12;

// Eye position constants struct
struct EyePos_Default {
  // Eye movement position constants
  static const int EYES_LEFT_POS = 40;    // Maximum left position
  static const int EYES_RIGHT_POS = 140;  // Maximum right position
  // Center position calculated as: (EYES_LEFT_POS + EYES_RIGHT_POS) / 2 = 90

  // Eye up/down movement position constants
  static const int EYES_UP_POS = 90;     // Maximum up position
  static const int EYES_DOWN_POS = 10;    // Maximum down position

  // Left eye specific constants
  static const int LEFT_EYELID_UPPER_CLOSED = 160;
  static const int LEFT_EYELID_LOWER_CLOSED = 20;
  static const int LEFT_EYELID_UPPER_OPEN = 90;
  static const int LEFT_EYELID_LOWER_OPEN = 90;
  // Right eye specific constants
  static const int RIGHT_EYELID_UPPER_CLOSED = 90;
  static const int RIGHT_EYELID_LOWER_CLOSED = 90;
  static const int RIGHT_EYELID_UPPER_OPEN = 160;
  static const int RIGHT_EYELID_LOWER_OPEN = 20;
};

// Current position tracking variables (simplified)
extern uint8_t eyesLeftRightPos;
extern uint8_t eyesUpDownPos;
extern uint8_t leftUpperPos;
extern uint8_t leftLowerPos;
extern uint8_t rightUpperPos;
extern uint8_t rightLowerPos;

// Current eyelid position ratios (0.0 = closed, 1.0 = open, 1.2 = extra wide)
extern float currentLeftEyelidRatio;
extern float currentRightEyelidRatio;

// Smooth movement structure
struct SmoothMovement {
  bool isMoving = false;
  int currentPos = 0;
  int targetPos = 0;
  int stepSize = 1;
  unsigned long lastUpdate = 0;
  int stepDelay = 20; // ms between steps
};

// Global smooth movement speed (1-10, higher = faster)
extern int smoothMovementSpeed;

// Individual movement tracking for each servo
extern SmoothMovement leftUpperSmooth, leftLowerSmooth, rightUpperSmooth, rightLowerSmooth;
extern SmoothMovement eyesLeftRightSmooth, eyesUpDownSmooth;

// Timing constants
const unsigned long BLINK_INTERVAL = 3000;    // Blink every 3 seconds
const unsigned long EYE_MOVE_INTERVAL = 2000; // Move eyes every 2 seconds
const unsigned long BEHAVIOR_TICK_INTERVAL = 100; // 100ms tick rate
const unsigned long BEHAVIOR_CHANGE_INTERVAL = 10000; // 10 seconds between behavior changes

// Function declarations
void setBehavior(EyeBehavior behavior);
void behaviorLoop();
void handleBehaviorTesting();
void TestAllMovements();
void attachServos();
void OpenLookForward();
void initializeBehavior(EyeBehavior behavior);
void changeToRandomBehavior();
void handleBehaviorIdle();
void handleBehaviorMouthInvasion();
void initializeMouthInvasionBehavior();
void handleBehaviorSleeping();
void initializeSleepingBehavior();

// MEMORY OPTIMIZATION: Commented out unused behavior handlers
// Uncomment these when enabling the corresponding behaviors:
// void handleBehaviorAttentive();
// void handleBehaviorSurprised();
// void handleBehaviorCurious();
// void handleBehaviorPlayful();
  // void handleBehaviorPumpkin();
  // void initializePumpkinBehavior();
  String getBehaviorName(EyeBehavior behavior);
  String getMouthInvasionStateName(MouthInvasionState state);
  String getSleepingStateName(SleepingState state);
void blink(int holdDuration = 150);
void winkRightEye();
void winkLeftEye();
void moveEyeTo(float x, float y);
void moveEyeHorizontal(float position);
void moveEyeVertical(float position);
void wink(bool isLeftEye);
void surprisedEyes(bool holdWide = true);
void moveEyelids(float leftPosition, float rightPosition);
void refreshEyelidsWithGazeConstraint();
void eyelidTwitch(int intensity = 10, int duration = 200);
void startSmoothMovement(SmoothMovement &movement, int targetPos, bool isInverted = false);
void smoothMovementLoop();
void setSmoothMovementSpeed(int speed);

// Sensor function declarations
void initializeSensor();
void loopMovementSensor();
bool isMovementDetected();
bool getSensorValue();
void setSensorThreshold(int threshold);
int getSensorThreshold();
void resetMovementDetection();

#endif // GLOBALS_H 