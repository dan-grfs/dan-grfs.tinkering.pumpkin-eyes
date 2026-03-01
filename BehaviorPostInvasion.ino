/*
 * BehaviorPostInvasion.ino
 * 
 * Post invasion behavior implementation for animatronic eyes
 * Calm idle behavior after mouth invasion - occasional blinks and small movements
 * Based on idle behavior pattern
 */

#include "Globals.h"

// Timing variables for post invasion behavior
unsigned long postInvasionLastBlinkTime = 0;
unsigned long postInvasionLastMoveTime = 0;
unsigned long postInvasionStartTime = 0;  // When post invasion behavior started

// Timing constants for post invasion behavior
const unsigned long BLINK_INTERVAL_POST_INVASION = 3000;    // Blink every 3 seconds
const unsigned long EYE_MOVE_INTERVAL_POST_INVASION = 4000; // Move eyes every 4 seconds
const unsigned long POST_INVASION_TO_SLEEPING_DURATION = 6000;  // 6 seconds before switching to sleeping

/*
 * Post invasion behavior handler
 * Simple idle-like behavior with occasional blinks and small movements
 */
void handleBehaviorPostInvasion() {
  unsigned long currentTime = millis();
  
  // Check if 6 seconds have passed - switch to sleeping behavior
  if (postInvasionStartTime > 0 && (currentTime - postInvasionStartTime >= POST_INVASION_TO_SLEEPING_DURATION)) {
    setBehavior(BEHAVIOR_SLEEPING);
    return;  // Exit early after switching behavior
  }
  
  // Occasional blinks
  if (currentTime - postInvasionLastBlinkTime >= BLINK_INTERVAL_POST_INVASION) {
    postInvasionLastBlinkTime = currentTime;
    blink(200);  // Normal blink duration
  }
  
  // Small random eye movements
  if (currentTime - postInvasionLastMoveTime >= EYE_MOVE_INTERVAL_POST_INVASION) {
    postInvasionLastMoveTime = currentTime;
    
    // Small random movements around center (subtle, calm movements)
    float x = random(-30, 31) / 100.0;  // -0.3 to 0.3
    float y = random(-20, 21) / 100.0;  // -0.2 to 0.2
    moveEyeTo(x, y);
  }
}

/*
 * Initialize post invasion behavior
 * Sets up initial state and positions
 */
void initializePostInvasionBehavior() {
  // Reset timing variables
  postInvasionLastBlinkTime = 0;
  postInvasionLastMoveTime = 0;
  postInvasionStartTime = millis();  // Record when post invasion behavior started
  
  // Set smooth movement speed for calm behavior (moderate speed)
  setSmoothMovementSpeed(5);
  
  // Start with eyes open and looking forward
  OpenLookForward();
}
