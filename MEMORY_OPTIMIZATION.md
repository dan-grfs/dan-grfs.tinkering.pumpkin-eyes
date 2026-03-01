# Memory Optimization Guide

## Arduino Nano Memory Constraints
- **Flash Memory**: 32KB (program storage)
- **SRAM**: 2KB (runtime variables) - **CRITICAL LIMIT**
- **EEPROM**: 1KB (persistent storage)

## Current Memory Optimization Status

### ✅ Enabled Behaviors (Minimal Memory Usage)
- `BEHAVIOR_IDLE`: Basic idle behavior
- `BEHAVIOR_MOUTH_INVASION`: Mouth invasion behavior with 6 states

### 🚫 Disabled Behaviors (Commented Out to Save Memory)
- `BEHAVIOR_SLEEPY`: Requires BehaviorSleepy.ino
- `BEHAVIOR_TESTING`: Requires BehaviorTesting.ino
- `BEHAVIOR_PUMPKIN`: Requires BehaviorPumpkin.ino
- `BEHAVIOR_ATTENTIVE`: Placeholder (needs implementation)
- `BEHAVIOR_SURPRISED`: Placeholder (needs implementation)
- `BEHAVIOR_CURIOUS`: Placeholder (needs implementation)
- `BEHAVIOR_PLAYFUL`: Placeholder (needs implementation)

## How to Enable a Behavior

### Step 1: Uncomment in Behaviors.ino
1. **behaviorLoop()** switch statement - uncomment the case
2. **getBehaviorName()** switch statement - uncomment the case
3. **initializeBehavior()** switch statement - uncomment the case

### Step 2: Add Behavior File
- Copy the corresponding `.ino` file to your project directory
- Example: Copy `BehaviorPumpkin.ino` to enable pumpkin behavior

### Step 3: Update Globals.h
- Uncomment the function declarations for the behavior
- Example: Uncomment `void handleBehaviorPumpkin();`

### Step 4: Test Memory Usage
- Compile and check for memory warnings
- Monitor SRAM usage in Arduino IDE
- If you get "Low memory" warnings, disable other behaviors

## Memory Usage Tips

### ✅ Good Practices
- Use `uint8_t` instead of `int` for small numbers
- Use `const` for constants
- Minimize global variables
- Use local variables when possible

### ❌ Avoid
- Large arrays in SRAM
- String concatenation
- Dynamic memory allocation
- Unnecessary global variables

## Current Startup Behavior
The system starts with `BEHAVIOR_MOUTH_INVASION` by default.

To change this, edit `eyes-v0.1.ino` line 146:
```cpp
setBehavior(BEHAVIOR_IDLE); // or BEHAVIOR_MOUTH_INVASION
```

## Troubleshooting Memory Issues

### If you get "Low memory" warnings:
1. Disable more behaviors by commenting them out
2. Remove unused movement functions
3. Reduce string usage in Serial.print statements
4. Use PROGMEM for large constant arrays

### If compilation fails:
1. Check that all enabled behaviors have their files included
2. Verify function declarations in Globals.h
3. Ensure no duplicate variable names between behavior files
