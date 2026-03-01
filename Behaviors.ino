/*
 * Behaviors.ino
 * 
 * Behavior management system for animatronic eyes
 * This file handles different eye behaviors and state management
 * 
 * MEMORY OPTIMIZATION NOTES:
 * =========================
 * To save SRAM on Arduino Nano (2KB limit), most behaviors are commented out.
 * Currently only IDLE and MOUTH_INVASION behaviors are enabled.
 * 
 * TO ENABLE A BEHAVIOR:
 * 1. Uncomment the case in behaviorLoop() switch statement
 * 2. Uncomment the case in getBehaviorName() switch statement  
 * 3. Uncomment the case in initializeBehavior() switch statement
 * 4. Add the corresponding .ino file to your project (e.g., BehaviorPumpkin.ino)
 * 5. Add the behavior handler function declaration to Globals.h
 * 
 * AVAILABLE BEHAVIORS:
 * - BEHAVIOR_TESTING: Requires BehaviorTesting.ino  
 * - BEHAVIOR_PUMPKIN: Requires BehaviorPumpkin.ino
 * - BEHAVIOR_ATTENTIVE, BEHAVIOR_SURPRISED, BEHAVIOR_CURIOUS, BEHAVIOR_PLAYFUL: 
 *   These are placeholder behaviors that need implementation
 */

#include "Globals.h"

// Current behavior state
EyeBehavior currentBehavior = BEHAVIOR_IDLE;

// Timing variables for behavior management
unsigned long lastBehaviorTick = 0;
unsigned long lastBehaviorChange = 0;

/*
 * Main behavior tick function - called each loop iteration
 * This function manages the current behavior and handles state transitions
 */
void behaviorLoop() {
  unsigned long currentTime = millis();
  
  // Only process behavior ticks at the specified interval
  if (currentTime - lastBehaviorTick >= BEHAVIOR_TICK_INTERVAL) {
    lastBehaviorTick = currentTime;
    
    // Handle current behavior
    switch (currentBehavior) {
      case BEHAVIOR_IDLE:
        handleBehaviorIdle();
        break;
        
      // MEMORY OPTIMIZATION: Commented out unused behaviors to save SRAM
      // To enable a behavior, uncomment the case and add the handler function
      
      // case BEHAVIOR_ATTENTIVE:
      //   handleBehaviorAttentive();
      //   break;
        
        
      // case BEHAVIOR_SURPRISED:
      //   handleBehaviorSurprised();
      //   break;
        
      // case BEHAVIOR_CURIOUS:
      //   handleBehaviorCurious();
      //   break;
        
      // case BEHAVIOR_PLAYFUL:
      //   handleBehaviorPlayful();
      //   break;
        
      // case BEHAVIOR_TESTING:
      //   handleBehaviorTesting();
      //   break;
        
      // case BEHAVIOR_PUMPKIN:
      //   handleBehaviorPumpkin();
      //   break;
        
      case BEHAVIOR_MOUTH_INVASION:
        handleBehaviorMouthInvasion();
        break;
        
      case BEHAVIOR_SLEEPING:
        handleBehaviorSleeping();
        break;
        
      default:
        // Fallback to idle behavior
        currentBehavior = BEHAVIOR_IDLE;
        break;
    }
    
    // Automatic behavior switching disabled - behavior stays as set at startup
    // Uncomment the lines below to re-enable automatic behavior changes:
    // if (currentBehavior != BEHAVIOR_TESTING && 
    //     currentTime - lastBehaviorChange >= BEHAVIOR_CHANGE_INTERVAL) {
    //   changeToRandomBehavior();
    // }
  }
}

/*
 * Set the current behavior
 * @param behavior: The behavior to switch to
 */
  void setBehavior(EyeBehavior behavior) {
    Serial.print("Changing behavior to: ");
    Serial.println(getBehaviorName(behavior));
    
    currentBehavior = behavior;
  lastBehaviorChange = millis();
  
  // Initialize the new behavior
  initializeBehavior(behavior);
}

/*
 * Get the name of a behavior as a string
 * @param behavior: The behavior enum value
 * @return: String representation of the behavior
 */
String getBehaviorName(EyeBehavior behavior) {
  switch (behavior) {
    case BEHAVIOR_IDLE: return "IDLE";
    case BEHAVIOR_MOUTH_INVASION: return "MOUTH_INVASION";
    case BEHAVIOR_SLEEPING: return "SLEEPING";
    // MEMORY OPTIMIZATION: Commented out unused behaviors
    // case BEHAVIOR_ATTENTIVE: return "ATTENTIVE";
    // case BEHAVIOR_SURPRISED: return "SURPRISED";
    // case BEHAVIOR_CURIOUS: return "CURIOUS";
    // case BEHAVIOR_PLAYFUL: return "PLAYFUL";
    // case BEHAVIOR_TESTING: return "TESTING";
    // case BEHAVIOR_PUMPKIN: return "PUMPKIN";
    default: return "UNKNOWN";
  }
}

/*
 * Initialize a behavior when it's first set
 * @param behavior: The behavior to initialize
 */
void initializeBehavior(EyeBehavior behavior) {
  switch (behavior) {
    case BEHAVIOR_IDLE:
      // Return to neutral position
      OpenLookForward();
      break;
      
    case BEHAVIOR_MOUTH_INVASION:
      // Initialize mouth invasion behavior
      initializeMouthInvasionBehavior();
      break;
      
    case BEHAVIOR_SLEEPING:
      // Initialize sleeping behavior
      initializeSleepingBehavior();
      break;
      
    // MEMORY OPTIMIZATION: Commented out unused behaviors
    // To enable a behavior, uncomment the case and add the initialization
    // You'll also need to include the corresponding .ino file in your project
    
    // case BEHAVIOR_ATTENTIVE:
    //   // Open eyes wide and look forward
    //   OpenLookForward();
    //   break;
      
      
    // case BEHAVIOR_SURPRISED:
    //   // Open eyes very wide
    //   OpenLookForward();
    //   break;
      
    // case BEHAVIOR_CURIOUS:
    //   // Look forward with focused expression
    //   OpenLookForward();
    //   break;
      
    // case BEHAVIOR_PLAYFUL:
    //   // Start with a wink
    //   OpenLookForward();
    //   break;
      
    // case BEHAVIOR_TESTING:
    //   // Initialize testing behavior
    //   initializeTestingBehavior();
    //   break;
      
    // case BEHAVIOR_PUMPKIN:
    //   // Initialize pumpkin behavior
    //   initializePumpkinBehavior();
    //   break;
  }
}

/*
 * Change to a random behavior (excluding current one)
 */
void changeToRandomBehavior() {
  EyeBehavior newBehavior;
  do {
    // MEMORY OPTIMIZATION: Only randomize between available behaviors
    // Currently only IDLE (0), MOUTH_INVASION (8), and SLEEPING (9) are enabled
    EyeBehavior availableBehaviors[] = {BEHAVIOR_IDLE, BEHAVIOR_MOUTH_INVASION, BEHAVIOR_SLEEPING};
    uint8_t randomIndex = random(0, 3); // 0-2
    newBehavior = availableBehaviors[randomIndex];
  } while (newBehavior == currentBehavior);
  
  setBehavior(newBehavior);
}

/*
 * Behavior handler functions
 * These will be implemented with specific behaviors for each state
 */

void handleBehaviorIdle() {
  // Occasional blinks and small random movements
  // TODO: Implement idle behavior logic
}

void handleBehaviorAttentive() {
  // More active looking around
  // TODO: Implement attentive behavior logic
}

void handleBehaviorSurprised() {
  // Wide eyes, quick movements
  // TODO: Implement surprised behavior logic
}

void handleBehaviorCurious() {
  // Focused looking, head tilting simulation
  // TODO: Implement curious behavior logic
}

void handleBehaviorPlayful() {
  // Quick movements, winks, expressive behavior
  // TODO: Implement playful behavior logic
}