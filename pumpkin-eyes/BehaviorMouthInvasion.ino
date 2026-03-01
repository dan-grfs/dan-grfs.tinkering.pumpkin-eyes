/*
 * BehaviorMouthInvasion.ino
 * 
 * Mouth invasion behavior implementation for animatronic eyes
 * Triggered when someone reaches into the pumpkin's mouth
 * Demonstrates sequence-based behavior with smooth state transitions
 */

#include "Globals.h"

// Current mouth invasion state
MouthInvasionState currentMouthInvasionState = MOUTH_INVASION_ENTRY;

// State timing
unsigned long mouthInvasionStateStartTime = 0;
unsigned long mouthInvasionLastActionTime = 0;

// Speed multiplier for mouth invasion behavior (1.0 = normal, <1.0 = faster, >1.0 = slower)
// Adjust this to make all actions quicker or slower proportionally
const float MOUTH_INVASION_SPEED_MULTIPLIER = 0.5;  // 0.5 = 50% faster (actions happen 30% more frequently)

// Base timing constants for mouth invasion behavior (will be scaled by speed multiplier)
const unsigned long BASE_STATE_DURATION_SURPRISED = 2000;        // 2 seconds surprised
const unsigned long BASE_STATE_DURATION_LOOK_FORWARD = 1000;     // 1 second look forward
const unsigned long BASE_STATE_DURATION_SHUFFLING_MIN = 1500;    // 1.5 seconds minimum shuffling
const unsigned long BASE_STATE_DURATION_SHUFFLING_MAX = 2500;    // 2.5 seconds maximum shuffling
const unsigned long BASE_STATE_DURATION_INVITING = 2000;         // 2 seconds inviting
const unsigned long BASE_STATE_DURATION_QUICK_LOOK = 1000;       // 1 second quick look
const unsigned long BASE_ACTION_INTERVAL_TWITCH = 300;           // Twitch every 300ms
const unsigned long BASE_ACTION_INTERVAL_SHUFFLE = 400;          // Shuffle every 400ms
const unsigned long BASE_ACTION_INTERVAL_RANDOM = 1000;          // Random action every 1s

// Scaled timing constants (calculated from base values and speed multiplier)
const unsigned long STATE_DURATION_SURPRISED = (unsigned long)(BASE_STATE_DURATION_SURPRISED * MOUTH_INVASION_SPEED_MULTIPLIER);
const unsigned long STATE_DURATION_LOOK_FORWARD = (unsigned long)(BASE_STATE_DURATION_LOOK_FORWARD * MOUTH_INVASION_SPEED_MULTIPLIER);
const unsigned long STATE_DURATION_SHUFFLING_MIN = (unsigned long)(BASE_STATE_DURATION_SHUFFLING_MIN * MOUTH_INVASION_SPEED_MULTIPLIER);
const unsigned long STATE_DURATION_SHUFFLING_MAX = (unsigned long)(BASE_STATE_DURATION_SHUFFLING_MAX * MOUTH_INVASION_SPEED_MULTIPLIER);
const unsigned long STATE_DURATION_INVITING = (unsigned long)(BASE_STATE_DURATION_INVITING * MOUTH_INVASION_SPEED_MULTIPLIER);
const unsigned long STATE_DURATION_QUICK_LOOK = (unsigned long)(BASE_STATE_DURATION_QUICK_LOOK * MOUTH_INVASION_SPEED_MULTIPLIER);
const unsigned long ACTION_INTERVAL_TWITCH = (unsigned long)(BASE_ACTION_INTERVAL_TWITCH * MOUTH_INVASION_SPEED_MULTIPLIER);
const unsigned long ACTION_INTERVAL_SHUFFLE = (unsigned long)(BASE_ACTION_INTERVAL_SHUFFLE * MOUTH_INVASION_SPEED_MULTIPLIER);
const unsigned long ACTION_INTERVAL_RANDOM = (unsigned long)(BASE_ACTION_INTERVAL_RANDOM * MOUTH_INVASION_SPEED_MULTIPLIER);

// Sequence action index for tracking
uint8_t mouthInvasionSequenceIndex = 0;
uint8_t mouthInvasionShuffleDirection = 0;  // 0 = left, 1 = right
uint8_t mouthInvasionRandomActionCounter = 0;

/*
 * Mouth invasion behavior handler
 * Manages state machine and sequences
 */
void handleBehaviorMouthInvasion() {
  unsigned long currentTime = millis();
  
  // Handle current mouth invasion state
  switch (currentMouthInvasionState) {
    case MOUTH_INVASION_ENTRY:
      performEntryState(currentTime);
      break;
      
    case MOUTH_INVASION_SURPRISED:
      performSurprisedState(currentTime);
      break;
      
    case MOUTH_INVASION_LOOK_FORWARD:
      performLookForwardState(currentTime);
      break;
      
    case MOUTH_INVASION_SHUFFLING:
      performShufflingState(currentTime);
      break;
      
    case MOUTH_INVASION_INVITING:
      performInvitingState(currentTime);
      break;
      
    case MOUTH_INVASION_QUICK_LOOK:
      performQuickLookState(currentTime);
      break;
      
    case MOUTH_INVASION_RANDOM_LOOP:
      performRandomLoopState(currentTime);
      break;
  }
}

/*
 * Initialize mouth invasion behavior
 * Sets up initial state and positions
 */
void initializeMouthInvasionBehavior() {
  // Set initial state
  currentMouthInvasionState = MOUTH_INVASION_ENTRY;
  mouthInvasionStateStartTime = millis();
  mouthInvasionLastActionTime = 0;
  mouthInvasionSequenceIndex = 0;
  mouthInvasionShuffleDirection = 0;
  mouthInvasionRandomActionCounter = 0;
  
  // Set smooth movement speed for mouth invasion behavior
  setSmoothMovementSpeed(20);
  
  // Start with eyes open and looking forward
  OpenLookForward();
}

/*
 * Perform entry state - brief pause before surprised reaction
 */
void performEntryState(unsigned long currentTime) {
  // Quick transition to surprised state (scaled by speed multiplier)
  unsigned long entryDuration = (unsigned long)(200 * MOUTH_INVASION_SPEED_MULTIPLIER);
  if (currentTime - mouthInvasionStateStartTime >= entryDuration) {
    transitionToMouthInvasionState(MOUTH_INVASION_SURPRISED);
  }
}

/*
 * Perform surprised state - wide eyes with twitchy eyelids (2 seconds)
 */
void performSurprisedState(unsigned long currentTime) {
  // Initial surprised opening
  if (mouthInvasionLastActionTime == 0) {
    surprisedEyes(true);  // Open eyes wide
    mouthInvasionLastActionTime = currentTime;
  }
  
  // Twitchy eyelid movements
  if (currentTime - mouthInvasionLastActionTime >= ACTION_INTERVAL_TWITCH) {
    mouthInvasionLastActionTime = currentTime;
    eyelidTwitch(15, 150);  // Intense twitch
  }
  
  // Transition to look forward after surprised duration
  if (currentTime - mouthInvasionStateStartTime >= STATE_DURATION_SURPRISED) {
    transitionToMouthInvasionState(MOUTH_INVASION_LOOK_FORWARD);
  }
}

/*
 * Perform look forward state - look straight forward with normal eyes
 */
void performLookForwardState(unsigned long currentTime) {
  // Look straight forward
  if (mouthInvasionLastActionTime == 0) {
    moveEyeTo(0.0, 0.0);  // Look straight forward
    // Return eyelids to normal open position
    moveEyelids(1.0, 1.0);
    mouthInvasionLastActionTime = currentTime;
  }
  
  // Transition to shuffling after look forward duration
  if (currentTime - mouthInvasionStateStartTime >= STATE_DURATION_LOOK_FORWARD) {
    transitionToMouthInvasionState(MOUTH_INVASION_SHUFFLING);
  }
}

/*
 * Perform shuffling state - looking down with side-to-side movement
 */
void performShufflingState(unsigned long currentTime) {
  // Initial look down
  if (mouthInvasionLastActionTime == 0) {
    moveEyeTo(0.0, 0.8);  // Look down
    mouthInvasionLastActionTime = currentTime;
  }
  
  // Side-to-side shuffling while looking down
  if (currentTime - mouthInvasionLastActionTime >= ACTION_INTERVAL_SHUFFLE) {
    mouthInvasionLastActionTime = currentTime;
    
    // Alternate between left and right while maintaining down look
    if (mouthInvasionShuffleDirection == 0) {
      moveEyeTo(-0.3, 0.8);  // Look down-left
      mouthInvasionShuffleDirection = 1;
    } else {
      moveEyeTo(0.3, 0.8);   // Look down-right
      mouthInvasionShuffleDirection = 0;
    }
  }
  
  // Random duration for shuffling
  unsigned long shufflingDuration = random(STATE_DURATION_SHUFFLING_MIN, STATE_DURATION_SHUFFLING_MAX + 1);
  if (currentTime - mouthInvasionStateStartTime >= shufflingDuration) {
    transitionToMouthInvasionState(MOUTH_INVASION_INVITING);
  }
}

/*
 * Perform inviting state - look forward with inviting eyelid twitch
 */
void performInvitingState(unsigned long currentTime) {
  // Look forward
  if (mouthInvasionLastActionTime == 0) {
    moveEyeTo(0.0, 0.0);  // Look forward
    mouthInvasionLastActionTime = currentTime;
  }
  
  // Inviting eyelid twitch (softer than surprised) - scaled by speed multiplier
  unsigned long twitchInterval = (unsigned long)(500 * MOUTH_INVASION_SPEED_MULTIPLIER);
  if (currentTime - mouthInvasionLastActionTime >= twitchInterval) {
    mouthInvasionLastActionTime = currentTime;
    eyelidTwitch(8, 300);  // Gentle twitch
  }
  
  // Transition to random loop after inviting duration (skip quick look)
  if (currentTime - mouthInvasionStateStartTime >= STATE_DURATION_INVITING) {
    // Reset random action counter for fresh random loop
    mouthInvasionRandomActionCounter = 0;
    transitionToMouthInvasionState(MOUTH_INVASION_RANDOM_LOOP);
  }
}

/*
 * Perform quick look state - quick down/up/forward sequence
 */
void performQuickLookState(unsigned long currentTime) {
  // Quick sequence: down -> forward -> twitch (timings scaled by speed multiplier)
  unsigned long quickLookDownTime = (unsigned long)(300 * MOUTH_INVASION_SPEED_MULTIPLIER);
  unsigned long quickLookForwardTime = (unsigned long)(300 * MOUTH_INVASION_SPEED_MULTIPLIER);
  unsigned long quickLookTotalTime = (unsigned long)(600 * MOUTH_INVASION_SPEED_MULTIPLIER);
  unsigned long quickLookTwitchDelay = (unsigned long)(200 * MOUTH_INVASION_SPEED_MULTIPLIER);
  
  if (currentTime - mouthInvasionStateStartTime < quickLookDownTime && mouthInvasionLastActionTime == 0) {
    // Quick look down
    moveEyeTo(0.0, 0.6);
    mouthInvasionLastActionTime = currentTime;
  } else if (currentTime - mouthInvasionStateStartTime >= quickLookDownTime && currentTime - mouthInvasionLastActionTime >= quickLookForwardTime) {
    // Quick look forward
    moveEyeTo(0.0, 0.0);
    mouthInvasionLastActionTime = currentTime;
  } else if (currentTime - mouthInvasionStateStartTime >= quickLookTotalTime && currentTime - mouthInvasionLastActionTime >= quickLookTwitchDelay) {
    // Final twitch
    eyelidTwitch(10, 200);
    mouthInvasionLastActionTime = currentTime;
  }
  
  // Transition to random loop after quick look duration
  if (currentTime - mouthInvasionStateStartTime >= STATE_DURATION_QUICK_LOOK) {
    transitionToMouthInvasionState(MOUTH_INVASION_RANDOM_LOOP);
  }
}

/*
 * Perform random loop state - continuous random forward/down looking with occasional shuffling
 */
void performRandomLoopState(unsigned long currentTime) {
  // Random actions every 2 seconds
  if (currentTime - mouthInvasionLastActionTime >= ACTION_INTERVAL_RANDOM) {
    mouthInvasionLastActionTime = currentTime;
    
    // Check if we should transition back to inviting state
    if (mouthInvasionRandomActionCounter >= 5) {  // After 5 random actions, go back to inviting
      transitionToMouthInvasionState(MOUTH_INVASION_INVITING);
      return;
    }
    
    // Random action selection - basic looking behaviors only
    uint8_t action = random(0, 4);
    switch (action) {
      case 0:
        // Look forward
        moveEyeTo(0.0, 0.0);
        break;
      case 1:
        // Look down
        moveEyeTo(0.0, 0.7);
        break;
      case 2:
        // Look down-left
        moveEyeTo(-0.5, 0.6);
        break;
      case 3:
        // Look down-right
        moveEyeTo(0.5, 0.6);
        break;
    }
    
    // Occasional eyelid twitch for regular actions
    if (action < 4 && random(0, 3) == 0) {  // 1 in 3 chance for regular actions
      eyelidTwitch(5, 250);
    }
    
    mouthInvasionRandomActionCounter++;
  }
}


/*
 * Transition to a new mouth invasion state
 */
void transitionToMouthInvasionState(MouthInvasionState newState) {
  currentMouthInvasionState = newState;
  mouthInvasionStateStartTime = millis();
  mouthInvasionLastActionTime = 0;  // Reset action timing
}

/*
 * Get mouth invasion state name as string
 */
String getMouthInvasionStateName(MouthInvasionState state) {
  switch (state) {
    case MOUTH_INVASION_ENTRY: return "ENTRY";
    case MOUTH_INVASION_SURPRISED: return "SURPRISED";
    case MOUTH_INVASION_LOOK_FORWARD: return "LOOK_FORWARD";
    case MOUTH_INVASION_SHUFFLING: return "SHUFFLING";
    case MOUTH_INVASION_INVITING: return "INVITING";
    case MOUTH_INVASION_QUICK_LOOK: return "QUICK_LOOK";
    case MOUTH_INVASION_RANDOM_LOOP: return "RANDOM_LOOP";
    default: return "UNKNOWN";
  }
}
