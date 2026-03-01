# Animatronic Eyes Controller v0.1 - AI Documentation

## ⚠️ CRITICAL AI INSTRUCTIONS - ARDUINO NANO PROJECT

**MANDATORY COMPLIANCE REQUIREMENTS:**

### Hardware Target
- **Platform**: Arduino Nano (ATmega328P microcontroller)
- **Memory Constraints**: 
  - Flash Memory: 32KB (program storage)
  - SRAM: 2KB (runtime variables)
  - EEPROM: 1KB (persistent storage)
- **Operating Voltage**: 5V
- **Clock Speed**: 16MHz

### Strict Coding Standards (MUST FOLLOW)

#### 1. Memory Management
- **CRITICAL**: Monitor SRAM usage - only 2KB available
- Use `PROGMEM` for large constant arrays to store in flash
- Minimize global variables - prefer local variables
- Use appropriate data types: `uint8_t` instead of `int` when possible
- Avoid dynamic memory allocation (`malloc`, `new`)
- Use `const` instead of `#define` for constants

#### 2. Naming Conventions (MANDATORY)
- **Variables/Functions**: `lowercase_with_underscores`
- **Constants**: `UPPERCASE_WITH_UNDERSCORES`
- **Classes/Structs**: `CamelCase`
- **Macros**: `ALL_CAPS`
- **Descriptive Names**: Use meaningful names (e.g., `left_upper_eyelid` not `servo1`)

#### 3. Code Structure (REQUIRED)
- **File Header**: Every file MUST start with comment block (purpose, author, date)
- **Library Includes**: At the top of each file
- **Constants**: Before global variables
- **Global Variables**: Before functions
- **Function Order**: `setup()` and `loop()` first, then other functions
- **Line Length**: Maximum 80 characters per line

#### 4. Function Design (MANDATORY)
- **Modularity**: Keep functions short and focused on single task
- **Parameters**: Use parameters instead of global variables
- **Return Values**: Always return appropriate values
- **Event Loop**: `loop()` must be non-blocking event loop
- **Initialization**: All one-time setup in `setup()` function

#### 5. Code Formatting (STRICT)
- **Indentation**: 2 spaces per level (consistent throughout)
- **Braces**: Opening `{` on same line, closing `}` on new line
- **Comments**: 
  - Single-line: `//`
  - Multi-line: `/* */`
  - Documentation: `/** */` for functions
- **Whitespace**: Use to separate logical sections

#### 6. Arduino-Specific Rules
- **No Static Variables**: Avoid `static` storage class
- **Global Scope**: Use global declarations for file-scope variables
- **Preprocessor**: Minimize `#define` usage
- **For-Loops**: Include all three terms even if optional
- **Non-Blocking**: Use `millis()` for timing, never `delay()` in main loop

#### 7. Error Handling (REQUIRED)
- **Servo Validation**: Check servo attachment before use
- **Range Checking**: Validate all servo positions before writing
- **Serial Debug**: Include debug output for troubleshooting
- **Graceful Degradation**: Handle servo failures without crashing

#### 8. Performance Requirements
- **Loop Frequency**: Main loop must complete in <100ms
- **Servo Updates**: Only update servos when position changes
- **Memory Efficiency**: Optimize for 2KB SRAM constraint
- **Power Management**: Consider power consumption for battery operation

### Code Review Checklist
Before any code changes, verify:
- [ ] Memory usage within 2KB SRAM limit
- [ ] All functions follow naming conventions
- [ ] No blocking delays in main loop
- [ ] Proper error handling for servo operations
- [ ] Consistent indentation and formatting
- [ ] Appropriate data types for memory efficiency
- [ ] Non-blocking timing implementation

### Documentation Maintenance Requirements

#### README Update Protocol (MANDATORY)
**Every code change MUST include corresponding documentation updates:**

1. **Immediate Updates Required:**
   - Function signatures in "Key Functions" section
   - New constants in "Technical Specifications"
   - Architecture changes in "Core Components"
   - New behaviors in "Behavior System"

2. **Version Control:**
   - Update version number in title (e.g., v0.1 → v0.2)
   - Add entry to Change Log section
   - Update "Future Enhancements" as items are completed

3. **Accuracy Verification:**
   - All code examples must match actual implementation
   - Pin mappings must reflect current hardware setup
   - Function parameters must match actual signatures
   - Memory usage estimates must be current

#### Change Log Maintenance (REQUIRED)
**Every code change must include a change log entry in CHANGELOG.md:**

**Format:** See CHANGELOG.md for complete format guidelines
**Location:** Separate CHANGELOG.md file in project root
**Categories:** Added, Changed, Deprecated, Removed, Fixed, Security
**Versioning:** Follow Semantic Versioning (Major.Minor.Patch)

#### Documentation Standards
- **Accuracy**: All technical details must match current codebase
- **Completeness**: Every public function must be documented
- **Clarity**: Use clear, technical language appropriate for AI consumption
- **Consistency**: Maintain consistent formatting and terminology
- **Timeliness**: Update documentation within same commit as code changes

#### AI Assistant Instructions
**CRITICAL: RESPONSIVE BUT FOCUSED APPROACH**

**WHEN USER REQUESTS CHANGES:**
1. **IMPLEMENT IMMEDIATELY**: When user asks for specific changes, implement them directly
2. **STAY IN SCOPE**: Only implement what the user has explicitly requested
3. **NO UNAUTHORIZED ADDITIONS**: Do not add features, improvements, or changes not requested
4. **ASK IF UNCLEAR**: If the request is ambiguous, ask for clarification before proceeding

**STRICT LIMITATIONS:**
- **NO SCOPE CREEP**: Do not add features not explicitly requested
- **NO "IMPROVEMENTS"**: Do not make changes you think are "better" unless asked
- **NO REFACTORING**: Do not reorganize code unless specifically requested
- **NO OPTIMIZATION**: Do not optimize code unless explicitly asked
- **NO STYLE CHANGES**: Do not change formatting unless requested
- **NO PROACTIVE CHANGES**: Do not make changes before being asked

**APPROACH:**
- **User asks → Implement immediately** (no approval needed for clear requests)
- **Stay focused** on exactly what was requested
- **Don't anticipate** what the user might want next
- **Ask questions** if the request is unclear rather than guessing

When making any code changes:
1. **Before coding**: Review current README-AI.md for context
2. **During coding**: Note any changes that affect documentation
3. **After coding**: Update README-AI.md with all changes
4. **Verification**: Ensure all examples and references are current
5. **Change Log**: Add appropriate entry to CHANGELOG.md with version and date

#### Development Workflow (CRITICAL)
**IMPORTANT**: This project uses Arduino IDE or Arduino CLI for compilation and upload. AI assistants must follow this workflow:

1. **Code Changes**: Make all code modifications in the current environment
2. **User Notification**: ALWAYS prompt the user to compile and upload using Arduino IDE or Arduino CLI
3. **No Direct Compilation**: AI cannot compile or upload code directly
4. **Testing**: User must test changes on hardware after upload
5. **Feedback Loop**: User reports results back to AI for further adjustments

**Required User Prompts:**
- "Please compile and upload the code in Arduino IDE (or using Arduino CLI)"
- "Test the changes on your hardware and report any issues"
- "Check the serial monitor at 9600 baud for debug output"

### Arduino CLI Support

This project supports Arduino CLI as an alternative to Arduino IDE for command-line development workflows.

**Arduino CLI Quick Commands:**
```bash
# List connected boards (shows FQBN and port)
arduino-cli board list

# Compile sketch (Arduino Nano with ATmega328P)
arduino-cli compile --fqbn arduino:avr:nano:cpu=atmega328old .

# Upload to board (replace <port> with actual port, e.g., COM3 on Windows)
arduino-cli upload -p <port> --fqbn arduino:avr:nano:cpu=atmega328old .

# Monitor serial output at 9600 baud
arduino-cli monitor -p <port> -c baudrate=9600
```

**Common FQBNs for Arduino Nano:**
- `arduino:avr:nano:cpu=atmega328old` - Original ATmega328P (bootloader v1.0)
- `arduino:avr:nano:cpu=atmega328` - Newer ATmega328P (bootloader v2.0)

**Note**: Use `arduino-cli board list` to identify the correct FQBN and port for your specific board.

**One-Command Workflow (PowerShell):**
```powershell
# Compile, upload, and start serial monitor in one command (PowerShell)
arduino-cli compile --upload -p COM3 --fqbn arduino:avr:nano:cpu=atmega328old .; arduino-cli monitor -p COM3 -c baudrate=9600
```

**Note**: Replace `COM3` with your actual port (use `arduino-cli board list` to find it). For conditional execution (only start monitor if upload succeeds), use:
```powershell
arduino-cli compile --upload -p COM3 --fqbn arduino:avr:nano:cpu=atmega328old .; if ($?) { arduino-cli monitor -p COM3 -c baudrate=9600 }
```

## Project Overview

This is an Arduino Nano-based animatronic eyes system that controls 6 servo motors to create realistic eye movements and expressions. The system uses a modular architecture with a behavior state machine for different eye personalities.

## Architecture

### Core Components

1. **Main Controller** (`pumpkin-eyes.ino`)
   - Entry point and initialization
   - Behavior system orchestration
   - Static variable initialization from defaults

2. **Global Definitions** (`Globals.h`)
   - Hardware pin mappings
   - Behavior enum definitions
   - Position constant structures
   - Function declarations

3. **Movement Engine** (`BaseMovements.ino`)
   - Low-level servo control functions
   - Normalized coordinate system (-1.0 to 1.0)
   - Basic eye and eyelid movements

4. **Behavior System** (`Behaviors.ino`)
   - State machine implementation
   - Behavior switching logic
   - Timing management

5. **Behavior Implementations**
   - `BehaviorSleepy.ino`: Sleepy behavior with droopy eyelids
   - `BehaviorTesting.ino`: Comprehensive test sequences
   - `BehaviorPumpkin.ino`: Pumpkin behavior with sequence-based states
   - `BehaviorMouthInvasion.ino`: Mouth invasion behavior triggered when someone reaches into mouth
   - `BehaviorSleeping.ino`: Sleeping behavior with tired blinking, half-closed eyes, slow blinks, and gradual closing
   - `BehaviorPostInvasion.ino`: Post invasion behavior - calm idle behavior after mouth invasion

## Technical Specifications

### Hardware Interface

#### Arduino Nano Breakout Board
This project uses an Arduino Nano mounted on a blue breakout board/shield that provides:
- **Digital Pins**: D0-D13 accessible via male/female pin headers (left side)
- **Analog Pins**: A0-A7 accessible via pin headers (right side)
- **Power Connections**: 5V and GND headers, plus DC power jack for external power
- **Communication Pins**: RX/TX (Serial) and SCL/SDA (I2C) headers
- **Reset Button**: Physical reset button on the board
- **Pin Access**: Both male and female headers for easy connections

**Note**: When troubleshooting sensor issues, if a pin appears faulty, try switching to an alternative pin (e.g., D3 instead of D2).

#### Servo Pin Mapping
```cpp
// Servo Pin Mapping
const int EYES_UP_DOWN_PIN = 13;       // Eye vertical movement
const int EYES_LEFT_RIGHT_PIN = 12;    // Eye horizontal movement
const int RIGHT_UPPER_EYELID_PIN = 9;  // Right upper eyelid
const int RIGHT_LOWER_EYELID_PIN = 8;  // Right lower eyelid
const int LEFT_UPPER_EYELID_PIN = 10;  // Left upper eyelid
const int LEFT_LOWER_EYELID_PIN = 11;  // Left lower eyelid
```

#### Sensor Pin Mapping
```cpp
const int MOVEMENT_SENSOR_PIN = 3;  // HC-SR501 PIR motion sensor (digital input)
```

### Coordinate System
- **Normalized Range**: -1.0 to 1.0 for both X and Y axes
- **X-axis**: -1.0 (left) to 1.0 (right), 0.0 (center)
- **Y-axis**: -1.0 (up) to 1.0 (down), 0.0 (center)
- **Servo Mapping**: Uses `map()` function to convert normalized values to servo angles

### Position Constants
```cpp
struct EyePos_Default {
  static const int EYES_LEFT_POS = 30;    // Maximum left position
  static const int EYES_CENTER_POS = 90;  // Center position
  static const int EYES_RIGHT_POS = 150;  // Maximum right position
  static const int EYES_UP_POS = 50;      // Maximum up position
  static const int EYES_DOWN_POS = 130;   // Maximum down position
  // ... eyelid positions
};
```

## Behavior System

### State Machine
```cpp
enum EyeBehavior {
  BEHAVIOR_IDLE,           // Default idle state
  BEHAVIOR_ATTENTIVE,      // More active looking
  BEHAVIOR_SLEEPY,         // Slow movements, droopy eyelids
  BEHAVIOR_SURPRISED,      // Wide eyes, quick movements
  BEHAVIOR_CURIOUS,        // Focused looking
  BEHAVIOR_PLAYFUL,        // Quick movements, winks
  BEHAVIOR_TESTING,        // Test mode
  BEHAVIOR_PUMPKIN,        // Pumpkin behavior with sequence-based states
  BEHAVIOR_MOUTH_INVASION, // Mouth invasion behavior - triggered when someone reaches into mouth
  BEHAVIOR_SLEEPING,       // Sleeping behavior - tired blinking, half-closed, slow blinks, gradual closing
  BEHAVIOR_POST_INVASION  // Post invasion behavior - calm idle behavior after mouth invasion
};
```

### Timing Constants
```cpp
const unsigned long BEHAVIOR_TICK_INTERVAL = 100;        // 100ms tick rate
const unsigned long BEHAVIOR_CHANGE_INTERVAL = 10000;    // 10s between changes
const unsigned long BLINK_INTERVAL = 3000;               // 3s blink interval
const unsigned long EYE_MOVE_INTERVAL = 2000;            // 2s eye movement
```

## Key Functions

### Movement Functions
- `moveEyeTo(float x, float y)`: Move eyes to specific coordinates
- `moveEyeHorizontal(float position)`: Horizontal movement only
- `moveEyeVertical(float position)`: Vertical movement only
- `blink(int holdDuration)`: Blinking animation
- `wink(bool isLeftEye)`: Individual eye winking
- `surprisedEyes(bool holdWide)`: Surprised expression with wide eyes
- `eyelidTwitch(int intensity, int duration)`: Quick eyelid twitching
- `smoothLookDown(float speed)`: Gradual downward eye movement
- `quickLookSequence()`: Rapid down/up/forward movement sequence

### Behavior Functions
- `setBehavior(EyeBehavior behavior)`: Switch to specific behavior
- `behaviorLoop()`: Main behavior tick function
- `initializeBehavior(EyeBehavior behavior)`: Initialize behavior state
- `changeToRandomBehavior()`: Random behavior switching
- `handleBehaviorMouthInvasion()`: Mouth invasion behavior handler
- `initializeMouthInvasionBehavior()`: Initialize mouth invasion behavior
- `handleBehaviorSleeping()`: Sleeping behavior handler
- `initializeSleepingBehavior()`: Initialize sleeping behavior
- `handleBehaviorPostInvasion()`: Post invasion behavior handler
- `initializePostInvasionBehavior()`: Initialize post invasion behavior

## Data Structures

### Position Management
```cpp
// Runtime position variables (can be modified)
struct Current_EyePos {
  static int EYES_LEFT_POS;
  static int EYES_CENTER_POS;
  static int EYES_RIGHT_POS;
  // ... other positions
};
```

### Servo Objects
```cpp
Servo leftUpperEyelid;    // Pin 10
Servo leftLowerEyelid;    // Pin 11
Servo rightUpperEyelid;   // Pin 8
Servo rightLowerEyelid;   // Pin 9
Servo eyesUpDown;         // Pin 13
Servo eyesLeftRight;      // Pin 12
```

## Implementation Details

### Behavior Loop
The main behavior loop runs every 100ms and:
1. Checks if enough time has passed for a behavior tick
2. Executes the current behavior's handler function
3. Checks if it's time to change behaviors (every 10 seconds)
4. Switches to a random behavior if needed

### Sleepy Behavior Implementation
The sleepy behavior modifies the default eyelid positions to create a droopy appearance:
```cpp
// Create droopy eyelids by adjusting position values
Current_EyePos::LEFT_EYELID_UPPER_OPEN = EyePos_Default::EYELID_UPPER_OPEN + leftDroop;
Current_EyePos::RIGHT_EYELID_UPPER_OPEN = EyePos_Default::EYELID_UPPER_OPEN + rightDroop;
```

### Testing Behavior
The testing behavior runs a comprehensive sequence every 5 seconds:
1. Horizontal eye movement test
2. Vertical eye movement test
3. Blinking test
4. Right eye wink test
5. Left eye wink test
6. Surprised expression test

## Error Handling

Currently minimal error handling is implemented. The system assumes:
- All servos are properly connected
- Power supply is adequate
- Pin assignments are correct

## Performance Considerations

- **Tick Rate**: 100ms behavior ticks provide smooth operation
- **Servo Updates**: Only updates servos when position changes
- **Memory Usage**: Static variables for position management
- **Timing**: Uses `millis()` for non-blocking timing

## Extension Points

### Adding New Behaviors
1. Add new enum value to `EyeBehavior`
2. Add case to `behaviorLoop()` switch statement
3. Implement handler function
4. Add initialization logic to `initializeBehavior()`
5. Create new behavior file following the pattern of `BehaviorPumpkin.ino`, `BehaviorMouthInvasion.ino`, or `BehaviorPostInvasion.ino` (for simple idle-like behaviors)

### Adding New Movements
1. Define function in `BaseMovements.ino`
2. Add declaration to `Globals.h`
3. Update test sequences if needed

### Movement Design Principles (CRITICAL)
**ALWAYS use proportional scaling for all movements:**

#### ✅ Correct Approach - Proportional Scaling:
```cpp
// Use multipliers for consistent, predictable movement
float multiplier = 0.85;  // 15% more open
int newPosition = (int)(basePosition * multiplier);

// For inverted movements (like lower eyelids):
int invertedPosition = (int)(basePosition * (2.0 - multiplier));
```

#### ❌ Incorrect Approach - Fixed Offsets:
```cpp
// DON'T use fixed additions/subtractions
int newPosition = basePosition + 10;  // This breaks with different base values
int newPosition = basePosition - 10;  // This causes asymmetric behavior
```

#### Why Proportional Scaling is Essential:
- **Consistent behavior** across different base positions
- **Predictable results** for both left and right eyes
- **Easy to tune** - change multiplier to adjust intensity
- **Scales properly** with different servo ranges
- **Prevents asymmetric movement** between left/right eyes

#### Examples in Codebase:
- Eye movements: `map(position * 100, -100, 100, minPos, maxPos)`
- Surprised eyes: `basePosition * 0.85` (15% more open)
- Eyelid twitch: `basePosition * (1.0 - intensity/100.0)`

### Hardware Modifications
- Pin assignments in `Globals.h`
- Position constants in `EyePos_Default` struct
- Servo attachment in `attachServos()`

## Debugging

The system provides extensive serial output:
- Servo attachment confirmations
- Movement commands with coordinates
- Behavior state changes
- Test sequence progress
- Timing information

## Documentation

For detailed documentation, debugging guides, and advanced topics, see the `docs/` folder:
- **Hardware Setup**: Detailed pin configurations and wiring diagrams
- **Sensor Configuration**: PIR sensor setup and calibration guides
- **Memory Optimization**: Strategies for managing Arduino Nano's 2KB SRAM limit
- **Behavior System**: In-depth explanation of the behavior state machine
- **Troubleshooting**: Extended troubleshooting guides and common issues

Additional documentation may be added to the `docs/` folder as needed for hardware-specific setup, sensor calibration, and advanced configuration.

## Future Enhancements

### Planned Features
- Error checking for servo attachment
- Servo range testing and calibration
- Power supply monitoring
- Serial command interface
- Sensor input integration
- Additional expressions and behaviors

### Code Quality Improvements
- Watchdog timer implementation
- Power-saving modes
- Configuration persistence
- Enhanced error handling
- Performance optimization

## Dependencies

- **Arduino Servo Library**: Standard Arduino library
- **Arduino IDE or Arduino CLI**: For compilation and upload
- **External Power Supply**: Recommended for multiple servos

## Resources

- [Arduino CLI Documentation](https://arduino.github.io/arduino-cli/)
- [Arduino Reference](https://www.arduino.cc/reference/en/)
- [Arduino Servo Library](https://www.arduino.cc/reference/en/libraries/servo/)

## Build Instructions

### Development Environment
- **Primary Tools**: Arduino IDE or Arduino CLI for compilation and upload
- **Development**: Code editing typically done in separate environment (VS Code, etc.)
- **Workflow**: Edit code → Arduino IDE/CLI → Compile → Upload → Test

### Build Process

**Using Arduino IDE:**
1. **Open Project**: Open `pumpkin-eyes.ino` in Arduino IDE
2. **File Structure**: Ensure all `.ino` files are in the same directory
3. **Compile**: Use Arduino IDE's "Verify" button to check for errors
4. **Upload**: Use Arduino IDE's "Upload" button to flash the Arduino Nano
5. **Hardware Setup**: Connect servos according to pin mapping
6. **Power Up**: Apply power and monitor serial output at 9600 baud

**Using Arduino CLI:**
1. **Verify Setup**: Run `arduino-cli board list` to identify your board's FQBN and port
2. **Navigate to sketch directory**: `cd pumpkin-eyes`
3. **Compile**: `arduino-cli compile --fqbn <fqbn> .`
4. **Upload**: `arduino-cli upload -p <port> --fqbn <fqbn> .`
5. **Monitor**: `arduino-cli monitor -p <port> -c baudrate=9600`

### AI Development Workflow
**CRITICAL**: AI assistants cannot compile or upload code directly. The workflow is:
1. AI makes code changes in development environment
2. AI prompts user to compile and upload using Arduino IDE or Arduino CLI
3. User tests on hardware and reports results
4. AI makes adjustments based on feedback

## Testing

The system includes built-in testing capabilities:
- Automatic test sequences in testing behavior
- Individual movement function tests
- Comprehensive movement validation
- Serial output for verification

## Maintenance

### Calibration
- Adjust position constants in `Globals.h`
- Test servo ranges and limits
- Verify mechanical setup
- Fine-tune timing intervals

### Troubleshooting
- Check serial output for error messages
- Verify servo connections and power
- Test individual servo responses
- Validate pin assignments
