/*
 * BaseMovements.ino
 * 
 * Core movement functions for animatronic eyes
 * This file contains the basic eye and eyelid movement functions
 */

#include "Globals.h"

// Eyelid-gaze coordination variable
// -1.0 (looking up) to 1.0 (looking down), 0.0 (center)
float eyelidGazeConstraint = 0.0;

// Current eyelid position ratios (0.0 = closed, 1.0 = open, 1.1 = extra wide)
float currentLeftEyelidRatio = 1.0;
float currentRightEyelidRatio = 1.0;

// Global smooth movement speed (1-10, higher = faster)
int smoothMovementSpeed = 5;

// Individual movement tracking for each servo
SmoothMovement leftUpperSmooth, leftLowerSmooth, rightUpperSmooth, rightLowerSmooth;
SmoothMovement eyesLeftRightSmooth, eyesUpDownSmooth;



/*
 * Attach all servos to their respective pins
 * This function centralizes servo attachment for easier management
 */
void attachServos() {
  // Attach left/right eye movement servo
  eyesLeftRight.attach(EYES_LEFT_RIGHT_PIN);
  
  // Attach up/down eye movement servo
  eyesUpDown.attach(EYES_UP_DOWN_PIN);
  
  // Attach left eyelid servos
  leftUpperEyelid.attach(LEFT_UPPER_EYELID_PIN);
  leftLowerEyelid.attach(LEFT_LOWER_EYELID_PIN);
  
  // Attach right eyelid servos
  rightUpperEyelid.attach(RIGHT_UPPER_EYELID_PIN);
  rightLowerEyelid.attach(RIGHT_LOWER_EYELID_PIN);
  
  // Immediately set all servos to safe positions to prevent unwanted movement
  
  // Calculate midpoint positions for all servos
  int leftUpperMid = (EyePos_Default::LEFT_EYELID_UPPER_OPEN + EyePos_Default::LEFT_EYELID_UPPER_CLOSED) / 2;
  int leftLowerMid = (EyePos_Default::LEFT_EYELID_LOWER_OPEN + EyePos_Default::LEFT_EYELID_LOWER_CLOSED) / 2;
  int rightUpperMid = (EyePos_Default::RIGHT_EYELID_UPPER_OPEN + EyePos_Default::RIGHT_EYELID_UPPER_CLOSED) / 2;
  int rightLowerMid = (EyePos_Default::RIGHT_EYELID_LOWER_OPEN + EyePos_Default::RIGHT_EYELID_LOWER_CLOSED) / 2;
  int eyesCenter = (EyePos_Default::EYES_LEFT_POS + EyePos_Default::EYES_RIGHT_POS) / 2;
  int eyesVerticalCenter = (EyePos_Default::EYES_UP_POS + EyePos_Default::EYES_DOWN_POS) / 2;
  
  // Set servos to midpoint positions directly
  leftUpperEyelid.write(leftUpperMid);
  leftLowerEyelid.write(leftLowerMid);
  rightUpperEyelid.write(rightUpperMid);
  rightLowerEyelid.write(rightLowerMid);
  eyesLeftRight.write(eyesCenter);
  eyesUpDown.write(eyesVerticalCenter);
  
  // Update position tracking variables with actual positions
  eyesLeftRightPos = eyesCenter;
  eyesUpDownPos = eyesVerticalCenter;
  leftUpperPos = leftUpperMid;
  leftLowerPos = leftLowerMid;
  rightUpperPos = rightUpperMid;
  rightLowerPos = rightLowerMid;
  
  // Initialize smooth movement structures with actual current positions
  leftUpperSmooth.currentPos = leftUpperMid;
  leftLowerSmooth.currentPos = leftLowerMid;
  rightUpperSmooth.currentPos = rightUpperMid;
  rightLowerSmooth.currentPos = rightLowerMid;
  eyesLeftRightSmooth.currentPos = eyesCenter;
  eyesUpDownSmooth.currentPos = eyesVerticalCenter;
  
}



/*
 * Move eyes to specific x,y coordinates
 * @param x: -1.0 (full left) to 1.0 (full right), 0.0 is center
 * @param y: -1.0 (full up) to 1.0 (full down), 0.0 is center
 */
void moveEyeTo(float x, float y) {
  // Move horizontally first
  moveEyeHorizontal(x);
  
  // Then move vertically
  moveEyeVertical(y);
}

/*
 * Move eyes horizontally with normalized input
 * @param position: -1.0 (full left) to 1.0 (full right), 0.0 is center
 */
void moveEyeHorizontal(float position) {
  // Clamp position to valid range
  if (position < -1.0) position = -1.0;
  if (position > 1.0) position = 1.0;
  
  // Map position from -1 to 1 range to servo position range
  int servoPosition;
  if (position <= 0) {
    // Map -1 to 0 range to LEFT_POS to CENTER_POS
    servoPosition = map(position * 100, -100, 0, EyePos_Default::EYES_LEFT_POS, (EyePos_Default::EYES_LEFT_POS + EyePos_Default::EYES_RIGHT_POS) / 2);
  } else {
    // Map 0 to 1 range to CENTER_POS to RIGHT_POS
    servoPosition = map(position * 100, 0, 100, (EyePos_Default::EYES_LEFT_POS + EyePos_Default::EYES_RIGHT_POS) / 2, EyePos_Default::EYES_RIGHT_POS);
  }
  
  // Start smooth movement to calculated position
  startSmoothMovement(eyesLeftRightSmooth, servoPosition, false);
}

/*
 * Move eyes vertically with normalized input
 * @param position: -1.0 (full up) to 1.0 (full down), 0.0 is center
 */
void moveEyeVertical(float position) {
  // Clamp position to valid range
  if (position < -1.0) position = -1.0;
  if (position > 1.0) position = 1.0;
  
  // Map position from -1 to 1 range to servo position range
  int servoPosition;
  int verticalCenter = (EyePos_Default::EYES_UP_POS + EyePos_Default::EYES_DOWN_POS) / 2;
  
  if (position <= 0) {
    // Map -1 to 0 range to UP_POS to CENTER_POS
    servoPosition = map(position * 100, -100, 0, EyePos_Default::EYES_UP_POS, verticalCenter);
  } else {
    // Map 0 to 1 range to CENTER_POS to DOWN_POS
    servoPosition = map(position * 100, 0, 100, verticalCenter, EyePos_Default::EYES_DOWN_POS);
  }
  
  // Start smooth movement to calculated position
  startSmoothMovement(eyesUpDownSmooth, servoPosition, false);
  
  // Update gaze constraint to match vertical position with intensity scaling
  eyelidGazeConstraint = position * 0.75;
  
  // Reapply current eyelid ratios with updated gaze constraint
  moveEyelids(currentLeftEyelidRatio, currentRightEyelidRatio);
}

/*
 * Blinking animation - closes and opens both eyes
 * @param holdDuration: Optional duration to hold the blink (default: 150ms)
 */
void blink(int holdDuration = 150) {
  
  // Close eyes using moveEyelids function
  moveEyelids(0.0, 0.0);
  
  delay(holdDuration); // Hold blink for specified duration
  
  // Open eyes using moveEyelids function
  moveEyelids(1.0, 1.0);
}

/*
 * Wink with specified eye
 * @param isLeftEye: true for left eye, false for right eye
 */
void wink(bool isLeftEye) {
  if (isLeftEye) {
    // Close left eye, keep right eye open
    moveEyelids(0.0, 1.0);
    delay(500);
    
    // Open left eye back to current position
    moveEyelids(currentLeftEyelidRatio, currentRightEyelidRatio);
  } else {
    // Close right eye, keep left eye open
    moveEyelids(1.0, 0.0);
    delay(500);
    
    // Open right eye back to current position
    moveEyelids(currentLeftEyelidRatio, currentRightEyelidRatio);
  }
  delay(500);
}


/*
 * Wink with right eye (close and open right eyelid)
 */
void winkRightEye() {
  wink(false); // false = right eye
}

/*
 * Wink with left eye (close and open left eyelid)
 */
void winkLeftEye() {
  wink(true); // true = left eye
}


/*
 * Open eyes and look straight forward
 * Sets all servos to their center/neutral positions
 */
void OpenLookForward() {
  // Set eyes to center position (looking straight ahead)
  moveEyeTo(0.0, 0.0);
  
  // Open eyes using the new centralized function
  moveEyelids(1.0, 1.0);
}

/*
 * Surprised eyes - opens eyes wider than normal
 * @param holdWide: Whether to hold the wide position
 */
void surprisedEyes(bool holdWide = true) {
  
  // Set eyes to center position (looking straight ahead)
  moveEyeTo(0.0, 0.0);
  
  // Open eyelids wider than normal for surprised expression
  // Use extra wide position (1.2) for both eyes to create dramatic wide-eyed surprise
  moveEyelids(1.2, 1.2);
}

/*
 * Central eyelid movement function using proportional scaling
 * @param leftPosition: Left eye position ratio (0.0 = fully closed, 1.0 = fully open, 1.2 = extra wide for effects)
 * @param rightPosition: Right eye position ratio (0.0 = fully closed, 1.0 = fully open, 1.2 = extra wide for effects)
 */
void moveEyelids(float leftPosition, float rightPosition) {
  // Clamp positions to valid range (allow up to 1.2 for effects like surprised/twitch)
  if (leftPosition < 0.0) leftPosition = 0.0;
  if (leftPosition > 1.2) leftPosition = 1.2;
  if (rightPosition < 0.0) rightPosition = 0.0;
  if (rightPosition > 1.2) rightPosition = 1.2;
  
  // Update tracked eyelid ratios
  currentLeftEyelidRatio = leftPosition;
  currentRightEyelidRatio = rightPosition;
  
  // Apply gaze constraint to upper and lower eyelids differently
  // Upper eyelids: more open when looking up (negative gaze), more closed when looking down
  float upperLeftRatio = leftPosition * (1.0 - eyelidGazeConstraint);
  float upperRightRatio = rightPosition * (1.0 - eyelidGazeConstraint);
  
  // Lower eyelids: more closed when looking up, more open when looking down
  float lowerLeftRatio = leftPosition * (1.0 + eyelidGazeConstraint);
  float lowerRightRatio = rightPosition * (1.0 + eyelidGazeConstraint);
  
  // Clamp ratios to valid range
  upperLeftRatio = constrain(upperLeftRatio, 0.0, 1.2);
  upperRightRatio = constrain(upperRightRatio, 0.0, 1.2);
  lowerLeftRatio = constrain(lowerLeftRatio, 0.0, 1.2);
  lowerRightRatio = constrain(lowerRightRatio, 0.0, 1.2);
  
  // Calculate left eye positions using gaze-modified ratios
  int leftUpperPosCalc = (int)(EyePos_Default::LEFT_EYELID_UPPER_CLOSED + 
                              (EyePos_Default::LEFT_EYELID_UPPER_OPEN - EyePos_Default::LEFT_EYELID_UPPER_CLOSED) * upperLeftRatio);
  int leftLowerPosCalc = (int)(EyePos_Default::LEFT_EYELID_LOWER_CLOSED + 
                              (EyePos_Default::LEFT_EYELID_LOWER_OPEN - EyePos_Default::LEFT_EYELID_LOWER_CLOSED) * lowerLeftRatio);
  
  // Calculate right eye positions using gaze-modified ratios
  int rightUpperPosCalc = (int)(EyePos_Default::RIGHT_EYELID_UPPER_CLOSED + 
                               (EyePos_Default::RIGHT_EYELID_UPPER_OPEN - EyePos_Default::RIGHT_EYELID_UPPER_CLOSED) * upperRightRatio);
  int rightLowerPosCalc = (int)(EyePos_Default::RIGHT_EYELID_LOWER_CLOSED + 
                               (EyePos_Default::RIGHT_EYELID_LOWER_OPEN - EyePos_Default::RIGHT_EYELID_LOWER_CLOSED) * lowerRightRatio);
  
  
  // Start smooth movement to calculated positions (all move simultaneously)
  // Left upper: inverted (160=closed, 90=open)
  startSmoothMovement(leftUpperSmooth, leftUpperPosCalc, true);
  // Left lower: normal (20=closed, 90=open)  
  startSmoothMovement(leftLowerSmooth, leftLowerPosCalc, false);
  // Right upper: normal (90=closed, 160=open)
  startSmoothMovement(rightUpperSmooth, rightUpperPosCalc, false);
  // Right lower: inverted (90=closed, 20=open)
  startSmoothMovement(rightLowerSmooth, rightLowerPosCalc, true);

}

/*
 * Eyelid twitch - quick, small movement of eyelids
 * @param intensity: How much to twitch (1-20, higher = more movement)
 * @param duration: How long to hold the twitch position (ms)
 */
void eyelidTwitch(int intensity = 10, int duration = 200) {

  // Calculate twitch effect (slightly more open)
  // Convert intensity (1-20) to ratio adjustment (0.01-0.2)
  float twitchAdjustment = (float)intensity / 100.0; // 0.01 to 0.2
  
  float twitchLeftRatio = currentLeftEyelidRatio + twitchAdjustment;
  float twitchRightRatio = currentRightEyelidRatio + twitchAdjustment;
  
  // Clamp twitch ratios to valid range (allow up to 1.2 for dramatic effects)
  if (twitchLeftRatio > 1.2) twitchLeftRatio = 1.2;
  if (twitchRightRatio > 1.2) twitchRightRatio = 1.2;
  
  float revertLeftEyelidRatio= currentLeftEyelidRatio;
  float revertRightEyelidRatio= currentRightEyelidRatio;

  // Apply twitch using centralized function
  moveEyelids(twitchLeftRatio, twitchRightRatio);
  
  delay(duration);  // Hold twitch position
  
  // Return to original positions using stored ratios
  moveEyelids(revertLeftEyelidRatio, revertRightEyelidRatio);
}


/*
 * Start smooth movement for a servo (non-blocking)
 * @param movement: Reference to the smooth movement structure
 * @param targetPos: Target servo position
 * @param isInverted: True if servo direction is inverted (higher position = more closed)
 */
void startSmoothMovement(SmoothMovement &movement, int targetPos, bool isInverted = false) {
  // Cancel any existing movement
  movement.isMoving = false;
  
  // Set up new movement
  movement.targetPos = targetPos;
  movement.stepDelay = map(smoothMovementSpeed, 1, 10, 50, 5); // 5ms to 50ms delay per step
  
  
  // Calculate step direction based on whether servo is inverted
  if (isInverted) {
    // For inverted servos: higher position = more closed, so step down to open
    movement.stepSize = (targetPos < movement.currentPos) ? -1 : 1;
  } else {
    // For normal servos: higher position = more open, so step up to open
    movement.stepSize = (targetPos > movement.currentPos) ? 1 : -1;
  }
  
  movement.isMoving = true;
  movement.lastUpdate = millis();
  
}

/*
 * Update smooth movement for a servo (non-blocking)
 * @param movement: Reference to the smooth movement structure
 * @param servo: Reference to the servo object
 * @param currentPos: Reference to current position variable
 * @param isInverted: True if servo direction is inverted
 */
void updateSmoothMovement(SmoothMovement &movement, Servo &servo, uint8_t &currentPos, bool isInverted = false) {
  if (!movement.isMoving) return;
  
  unsigned long currentTime = millis();
  if (currentTime - movement.lastUpdate >= movement.stepDelay) {
    movement.lastUpdate = currentTime;
    
    if (movement.currentPos != movement.targetPos) {
      movement.currentPos += movement.stepSize;
      
      // Check if we've reached the target
      bool reachedTarget = (movement.stepSize > 0 && movement.currentPos >= movement.targetPos) ||
                          (movement.stepSize < 0 && movement.currentPos <= movement.targetPos);
      
      if (reachedTarget) {
        movement.currentPos = movement.targetPos;
        movement.isMoving = false;
      }
      
      servo.write(movement.currentPos);
      currentPos = movement.currentPos;
      
    }
  }
}

/*
 * Update all smooth movements (call this in main loop)
 */
void smoothMovementLoop() {
  // Left upper: inverted (160=closed, 90=open)
  updateSmoothMovement(leftUpperSmooth, leftUpperEyelid, leftUpperPos, true);
  // Left lower: normal (20=closed, 90=open)
  updateSmoothMovement(leftLowerSmooth, leftLowerEyelid, leftLowerPos, false);
  // Right upper: normal (90=closed, 160=open)
  updateSmoothMovement(rightUpperSmooth, rightUpperEyelid, rightUpperPos, false);
  // Right lower: inverted (90=closed, 20=open)
  updateSmoothMovement(rightLowerSmooth, rightLowerEyelid, rightLowerPos, true);
  // Eye servos: normal
  updateSmoothMovement(eyesLeftRightSmooth, eyesLeftRight, eyesLeftRightPos, false);
  updateSmoothMovement(eyesUpDownSmooth, eyesUpDown, eyesUpDownPos, false);
}

/*
 * Set smooth movement speed for all servos
 * @param speed: Movement speed (1-10, higher = faster)
 */
void setSmoothMovementSpeed(int speed) {
  if (speed < 1) speed = 1;
  if (speed > 10) speed = 10;
  smoothMovementSpeed = speed;
}
