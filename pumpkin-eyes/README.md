# Animatronic Eyes Controller v0.1

An Arduino-based animatronic eyes system inspired by Will Cogley's design. This project controls 6 servo motors to create realistic eye movements and expressions.

## 🎯 Features

- **6 Servo Control**: Independent control of eye movement and individual eyelids
- **Multiple Behaviors**: Multiple eye personalities including Idle, Testing, Mouth Invasion, Sleeping, and Post Invasion
- **Realistic Movements**: Natural blinking, winking, and eye tracking
- **Modular Design**: Clean separation of movement functions and behaviors
- **Built-in Testing**: Comprehensive test sequences to verify all movements

## 🔧 Hardware Requirements

- Arduino board (compatible with Servo library)
- 6 servo motors
- External power supply (recommended for multiple servos)
- Jumper wires

## 📌 Pin Connections

| Servo Function | Arduino Pin |
|----------------|-------------|
| Eyes Left/Right Movement | Pin 12 |
| Eyes Up/Down Movement | Pin 13 |
| Right Lower Eyelid | Pin 8 |
| Right Upper Eyelid | Pin 9 |
| Left Upper Eyelid | Pin 10 |
| Left Lower Eyelid | Pin 11 |

## 🚀 Quick Start

### Development Workflow
- **Code Editing**: Typically done in VS Code or similar editor
- **Compilation**: Use Arduino IDE or Arduino CLI for building and uploading
- **Testing**: Hardware testing after each upload

### Setup Steps
1. **Open Project**: Open `pumpkin-eyes.ino` in Arduino IDE (or use Arduino CLI)
2. **Compile & Upload**: Use Arduino IDE to compile and upload to your Arduino Nano, or use Arduino CLI commands
3. **Connect Servos**: Wire the servos according to the pin mapping above
4. **Power Up**: Connect external power supply if using multiple servos
5. **Watch the Magic**: The eyes will start with the default behavior (currently IDLE) and can be configured to cycle through different personalities
6. **Debug**: Open Serial Monitor at 9600 baud to see debug output

### Arduino CLI (Alternative to Arduino IDE)

Arduino CLI provides command-line development capabilities. This is useful for automated builds, CI/CD, or if you prefer command-line workflows.

**Quick Commands:**
```bash
# List connected boards
arduino-cli board list

# Navigate to sketch directory first
cd pumpkin-eyes

# Compile a sketch (replace <fqbn> with your board's FQBN, e.g., arduino:avr:nano)
arduino-cli compile --fqbn arduino:avr:nano .

# Upload to board (replace <port> with your board's port, e.g., COM3 or /dev/ttyUSB0)
arduino-cli upload -p <port> --fqbn arduino:avr:nano .

# Monitor serial output
arduino-cli monitor -p <port> -c baudrate=9600
```

**Finding Your Board's FQBN:**
- Run `arduino-cli board list` to see connected boards and their FQBNs
- For Arduino Nano: typically `arduino:avr:nano` with `cpu=atmega328old` or `cpu=atmega328`

## 🎭 Eye Behaviors

- **IDLE**: Occasional blinks and small movements
- **TESTING**: Runs through all movements in sequence
- **MOUTH_INVASION**: Triggered when someone reaches into mouth - surprised, shuffling, and inviting expressions
- **SLEEPING**: Tired blinking, half-closed eyes, slow blinks, and gradual closing
- **POST_INVASION**: Calm idle behavior after mouth invasion

**Note**: Some behaviors (Attentive, Surprised, Curious, Playful, Pumpkin) are defined but currently disabled to save memory on Arduino Nano.

## 📁 Project Structure

```
pumpkin-eyes/
├── pumpkin-eyes.ino              # Main Arduino sketch
├── Globals.h                     # Header file with all declarations
├── BaseMovements.ino             # Core movement functions
├── Behaviors.ino                 # Behavior management system
├── BehaviorTesting.ino           # Testing behavior implementation
├── BehaviorMouthInvasion.ino     # Mouth invasion behavior
├── BehaviorSleeping.ino          # Sleeping behavior
├── BehaviorPostInvasion.ino      # Post invasion behavior
├── Sensor_IR.ino                 # IR sensor handling
├── CHANGELOG.md                  # Change log
└── README.md                     # This file
```

## 🎮 Movement System

The system uses a normalized coordinate system:
- **X-axis**: -1.0 (full left) to 1.0 (full right), 0.0 is center
- **Y-axis**: -1.0 (full up) to 1.0 (full down), 0.0 is center

### Available Movements

- **Eye Movement**: `moveEyeTo(x, y)` - Move eyes to specific coordinates
- **Blinking**: `blink(duration)` - Standard blink animation
- **Winking**: `wink(isLeftEye)` - Individual eye winking
- **Surprised**: `surprisedEyes()` - Wide-eyed expression
- **Reset**: `OpenLookForward()` - Return to neutral position

## 🔧 Calibration

The system includes default position values that may need adjustment for your specific mechanical setup:

- **Eye Positions**: Left (30°), Center (90°), Right (150°)
- **Vertical Range**: Up (50°), Center (90°), Down (130°)
- **Eyelid Positions**: Open (90°), Closed (120°), Surprised (60°)

### Development Process
1. **Edit Code**: Make changes in your preferred editor
2. **Compile**: Use Arduino IDE to compile and upload
3. **Test**: Observe behavior on hardware
4. **Adjust**: Modify values in `Globals.h` as needed
5. **Repeat**: Iterate until behavior is satisfactory

## 🐛 Troubleshooting

### Common Issues

1. **Servos Not Moving**: Check power supply and pin connections
2. **Jittery Movement**: Ensure adequate power supply capacity
3. **Wrong Positions**: Calibrate position values in `Globals.h`
4. **Serial Monitor**: Open at 9600 baud to see debug output

### Debug Output

The system provides detailed serial output for troubleshooting:
- Servo attachment confirmations
- Movement commands and positions
- Behavior state changes
- Test sequence progress

## 📚 Documentation

For detailed documentation, debugging guides, and advanced topics, see the `docs/` folder:
- **Hardware Setup**: Detailed pin configurations and wiring diagrams
- **Sensor Configuration**: PIR sensor setup and calibration
- **Memory Optimization**: Strategies for managing Arduino Nano's 2KB SRAM limit
- **Behavior System**: In-depth explanation of the behavior state machine
- **Troubleshooting**: Extended troubleshooting guides and common issues

## 📋 TODO List

### High Priority
- [ ] Verify pin assignments with specific Arduino board
- [ ] Test servo response on each pin
- [ ] Calibrate center positions for mechanical setup
- [ ] Test and adjust position values
- [ ] Calibrate movement ranges

### Medium Priority
- [ ] Add error checking for servo attachment
- [ ] Implement servo range testing
- [ ] Add power supply voltage monitoring
- [ ] Adjust timing intervals based on testing
- [ ] Add randomness to timing for natural movement

### Low Priority
- [ ] Add watchdog timer to prevent servo jitter
- [ ] Implement power-saving mode
- [ ] Add serial command interface
- [ ] Consider sensor input for reactive behavior
- [ ] Add different expressions (anger, sadness, etc.)

## 🤝 Contributing

Feel free to contribute improvements, bug fixes, or new behaviors! The modular design makes it easy to add new features.

## 📄 License

This project is open source. Please credit Will Cogley for the original design inspiration.

## 🙏 Acknowledgments

- **Will Cogley**: Original animatronic eye design inspiration
- **Arduino Community**: For the Servo library and support

## 📚 Resources

- [Arduino CLI Documentation](https://arduino.github.io/arduino-cli/)
- [Arduino Reference](https://www.arduino.cc/reference/en/)
- [Arduino Servo Library](https://www.arduino.cc/reference/en/libraries/servo/)

---

*Happy building! 👁️*
