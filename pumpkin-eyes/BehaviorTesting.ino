/*
 * BehaviorTesting.ino
 * 
 * Testing behavior implementation for animatronic eyes
 * This file contains the testing behavior handler and related functions
 */

#include "Globals.h"

/*
 * Initialize testing behavior
 * Sets up the initial testing behavior
 */
void initializeTestingBehavior() {
  Serial.println("=== TESTING BEHAVIOR INITIALIZED ===");
  Serial.println("Testing behavior will run servo tests every 5 seconds");
  Serial.println("Watch for test sequence messages...");
  // Set up test sequence parameters
  // Initialize test timing variables
  // Prepare for test sequence execution
}

/*
 * Testing behavior handler
 * Runs through all available eye and eyelid movements
 */
void handleBehaviorTesting() {
  // Test mode - runs through all movements
  // This behavior runs the complete test sequence
  
  static bool testCompleted = false;
  static unsigned long lastTestTime = 0;
  const unsigned long TEST_INTERVAL = 5000; // 5 seconds between test runs
  
  unsigned long currentTime = millis();
  
  // Only run test sequence at specified intervals
  if (currentTime - lastTestTime >= TEST_INTERVAL) {
    lastTestTime = currentTime;
    testCompleted = false;
    
    Serial.println("=== Running Test Sequence ===");
    TestAllMovements();
    testCompleted = true;
    
    Serial.println("=== Test Sequence Complete ===");
  }
  
  // If test is completed, we could switch to another behavior
  // For now, just keep running tests
  if (testCompleted) {
    // Could add logic here to switch to a different behavior after testing
    // setBehavior(BEHAVIOR_IDLE);
  }
}

/*
 * Test all movement functions in sequence
 * This function demonstrates all available eye and eyelid movements
 */
void TestAllMovements() {
  Serial.println("=== Starting All Movements Test ===");
  
  // Test eye movements
  Serial.println("1. Testing horizontal eye movement...");
  moveEyeTo(-1.0, 0.0);  // Left
  delay(1000);
  moveEyeTo(1.0, 0.0);   // Right
  delay(1000);
  moveEyeTo(0.0, 0.0);   // Center
  delay(1000);
  
  Serial.println("2. Testing vertical eye movement...");
  moveEyeTo(0.0, -1.0);  // Up
  delay(1000);
  moveEyeTo(0.0, 1.0);   // Down
  delay(1000);
  moveEyeTo(0.0, 0.0);   // Center
  delay(1000);
  
  // Test blinking
  Serial.println("3. Testing blink...");
  blink();
  delay(2000);
  
  // Test individual eye winks
  Serial.println("4. Testing right eye wink...");
  winkRightEye();
  delay(2000);
  
  Serial.println("5. Testing left eye wink...");
  winkLeftEye();
  delay(2000);
  
  Serial.println("=== All Movements Test Complete ===");
} 