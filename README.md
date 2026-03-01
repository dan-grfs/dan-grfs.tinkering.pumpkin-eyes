# Animatronic Eyes Controller v0.1

An Arduino-based animatronic eyes system inspired by Will Cogley's design. This project controls 6 servo motors to create realistic eye movements and expressions.

## 🎯 Features

- **6 Servo Control**: Independent control of eye movement and individual eyelids
- **Multiple Behaviors**: 7 different eye personalities (Idle, Attentive, Sleepy, Surprised, Curious, Playful, Testing)
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
| Eyes Up/Down Movement | Pin 4 |
| Eyes Left/Right Movement | Pin 5 |
| Right Upper Eyelid | Pin 8 |
| Right Lower Eyelid | Pin 9 |
| Left Upper Eyelid | Pin 10 |
| Left Lower Eyelid | Pin 11 |

## 🚀 Quick Start

### Development Workflow
- **Code Editing**: Typically done in VS Code or similar editor
- **Compilation**: Use Arduino IDE for building and uploading
- **Testing**: Hardware testing after each upload

### Setup Steps
1. **Open Project**: Open `eyes-v0.1.ino` in Arduino IDE
2. **Compile & Upload**: Use Arduino IDE to compile and upload to your Arduino Nano
3. **Connect Servos**: Wire the servos according to the pin mapping above
4. **Power Up**: Connect external power supply if using multiple servos
5. **Watch the Magic**: The eyes will start with sleepy behavior and automatically cycle through different personalities
6. **Debug**: Open Serial Monitor at 9600 baud to see debug output

## 🎭 Eye Behaviors

- **IDLE**: Occasional blinks and small movements
- **ATTENTIVE**: More active looking around
- **SLEEPY**: Slow movements, frequent blinking, droopy eyelids
- **SURPRISED**: Wide eyes, quick movements, alert behavior
- **CURIOUS**: Focused looking, head tilting simulation
- **PLAYFUL**: Quick movements, winks, expressive behavior
- **TESTING**: Runs through all movements in sequence

## 📁 Project Structure

```
eyes-v0.1/
├── eyes-v0.1.ino          # Main Arduino sketch
├── Globals.h              # Header file with all declarations
├── BaseMovements.ino      # Core movement functions
├── Behaviors.ino          # Behavior management system
├── BehaviorSleepy.ino     # Sleepy behavior implementation
├── BehaviorTesting.ino    # Testing behavior implementation
└── README.md              # This file
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

---

*Happy building! 👁️*
