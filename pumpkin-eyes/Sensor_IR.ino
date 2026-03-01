/*
 * Sensor_IR.ino
 * 
 * IR sensor functionality for animatronic eyes
 * Contains sensor reading and movement detection functions
 * 
 * Hardware: HC-SR501 PIR motion sensor module
 * - Digital output: HIGH when motion detected, LOW when no motion
 * - Digital pin D3 used for reading sensor state
 * 
 * Author: AI Assistant
 * Date: 2024
 * Version: 0.1
 */

#include "Globals.h"

// Sensor pin definitions
const int MOVEMENT_SENSOR_PIN = 3;  // Digital pin for HC-SR501 PIR sensor

// Sensor state variables
bool movementDetected = false;
unsigned long lastMovementTime = 0;
bool sensorValue = false;

// Movement detection timing
const unsigned long MOVEMENT_DEBOUNCE_TIME = 100;  // 100ms debounce
const unsigned long MOVEMENT_TIMEOUT = 2000;       // 2s timeout for movement state

// Sensor reading timing - check frequently
unsigned long lastSensorCheckTime = 0;
const unsigned long SENSOR_CHECK_INTERVAL = 50;  // Check every 50ms

// Hand detection timing
unsigned long lowStateStartTime = 0;  // When sensor went LOW
const unsigned long HAND_LEFT_DURATION = 8000;  // 8 seconds HIGH = hand left (wait before post invasion)
bool handLeftMessageSent = false;  // Prevent spamming message
bool behaviorTriggeredForHandIn = false;  // Track if we've triggered mouth invasion
bool behaviorTriggeredForHandOut = false;  // Track if we've triggered post invasion

// Debugging - minimal
unsigned long sensorStartTime = 0;
const unsigned long SENSOR_WARMUP_TIME = 60000;  // 60 seconds warm-up period
bool sensorWarmedUp = false;
bool lastSensorState = false;

/**
 * Initialize sensor hardware
 * Call this in setup() function
 */
void initializeSensor() {
  pinMode(MOVEMENT_SENSOR_PIN, INPUT);
  sensorStartTime = millis();
  lastSensorState = digitalRead(MOVEMENT_SENSOR_PIN);
  Serial.println("PIR sensor init (warm-up: 60s)");
}

/**
 * Main sensor loop function
 * Reads sensor and detects movement
 * Call this in main loop() function
 */
void loopMovementSensor() {
  unsigned long currentTime = millis();
  
  // Check if sensor has warmed up
  if (!sensorWarmedUp && (currentTime - sensorStartTime >= SENSOR_WARMUP_TIME)) {
    sensorWarmedUp = true;
    Serial.println("PIR warm-up complete");
  }
  
  // Check sensor frequently (every 50ms or as fast as loop runs)
  if (currentTime - lastSensorCheckTime >= SENSOR_CHECK_INTERVAL) {
    lastSensorCheckTime = currentTime;
    
    // Read sensor value (LOW = motion detected, HIGH = no motion - inverted logic)
    sensorValue = digitalRead(MOVEMENT_SENSOR_PIN);
    
    // Detect HIGH to LOW transition (hand entered mouth - sensor goes LOW)
    if (!sensorValue && lastSensorState) {
      Serial.println("HAND IN MOUTH");
      handLeftMessageSent = false;  // Reset flag for next cycle
      lowStateStartTime = 0;  // Clear LOW timer
      behaviorTriggeredForHandOut = false;  // Reset hand out flag
      
      // Trigger mouth invasion behavior
      if (!behaviorTriggeredForHandIn) {
        Serial.println("Sensor: Triggering MOUTH_INVASION behavior");
        setBehavior(BEHAVIOR_MOUTH_INVASION);
        behaviorTriggeredForHandIn = true;
      }
    }
    
    // Detect LOW to HIGH transition (hand may be leaving - sensor goes HIGH)
    if (sensorValue && !lastSensorState) {
      lowStateStartTime = currentTime;  // Start timer for HIGH state (no motion)
      handLeftMessageSent = false;  // Reset message flag
    }
    
    // Check if HIGH (no motion) has persisted for 3 seconds (hand left mouth)
    if (sensorValue && lowStateStartTime > 0 && !handLeftMessageSent) {
      if (currentTime - lowStateStartTime >= HAND_LEFT_DURATION) {
        Serial.println("HAND LEFT MOUTH");
        handLeftMessageSent = true;  // Prevent spamming
        behaviorTriggeredForHandIn = false;  // Reset hand in flag
        
        // Trigger post invasion behavior
        if (!behaviorTriggeredForHandOut) {
          Serial.println("Sensor: Triggering POST_INVASION behavior");
          setBehavior(BEHAVIOR_POST_INVASION);
          behaviorTriggeredForHandOut = true;
        }
      }
    }
    
    // Update last state
    lastSensorState = sensorValue;
  }
  
  // Check for movement detection (HIGH = motion detected)
  bool currentMovement = sensorValue;
  
  // Debounce movement detection
  if (currentMovement && !movementDetected) {
    if (currentTime - lastMovementTime > MOVEMENT_DEBOUNCE_TIME) {
      movementDetected = true;
      lastMovementTime = currentTime;
    }
  }
  
  // Reset movement state after timeout
  if (movementDetected && (currentTime - lastMovementTime > MOVEMENT_TIMEOUT)) {
    movementDetected = false;
  }
}

/**
 * Check if movement is currently detected
 * @return true if movement is detected, false otherwise
 */
bool isMovementDetected() {
  return movementDetected;
}

/**
 * Get current sensor value
 * @return digital sensor reading (true = HIGH/motion, false = LOW/no motion)
 */
bool getSensorValue() {
  return sensorValue;
}

/**
 * Set movement detection threshold (not used for digital sensor)
 * @param threshold Not applicable for digital sensor
 */
void setSensorThreshold(int threshold) {
  Serial.println("Digital PIR sensor does not use threshold - HIGH/LOW only");
}

/**
 * Get current sensor threshold (not applicable for digital sensor)
 * @return always returns 0 for digital sensor
 */
int getSensorThreshold() {
  return 0;  // Digital sensor doesn't use threshold
}

/**
 * Reset movement detection state
 * Forces movement state to false
 */
void resetMovementDetection() {
  movementDetected = false;
  lastMovementTime = 0;
}
