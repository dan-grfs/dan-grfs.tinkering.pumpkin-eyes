# Change Log

All notable changes to the Animatronic Eyes Controller project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- BehaviorSleeping.ino - New sleeping behavior with tired blinking, half-closed eyes, slow blinks, and gradual closing
- Sleeping behavior with 5 states: TIRED_BLINK, HALF_CLOSED, SLOW_BLINKS, CLOSING, CLOSED
- Non-blocking slow blink implementation using timing variables
- BEHAVIOR_SLEEPING enum value and SleepingState enum
- State machine following mouth invasion behavior pattern
- BehaviorMouthInvasion.ino - New mouth invasion behavior triggered when someone reaches into mouth
- Mouth invasion behavior with 6 states: ENTRY, SURPRISED, SHUFFLING, INVITING, QUICK_LOOK, RANDOM_LOOP
- Specialized movement functions: surprisedEyes(), eyelidTwitch(), smoothLookDown(), quickLookSequence()
- BEHAVIOR_MOUTH_INVASION enum value and MouthInvasionState enum
- Comprehensive state machine following pumpkin behavior pattern
- BehaviorPumpkin.ino - New sequence-based pumpkin behavior with state machine
- Pumpkin behavior with 5 states: IDLE, SCANNING, CURIOUS, PLAYFUL, RETURN
- Smooth state transitions with timing-based state management
- Per-behavior rest position management system
- resetToDefaultPositions() function for behavior cleanup

### Changed
- Added BEHAVIOR_SLEEPING to behavior enum in Globals.h
- Added sleeping behavior to behavior system and switch statements
- Modified initializeBehavior() to include sleeping behavior initialization
- Updated README-AI.md with sleeping behavior documentation
- Set sleeping behavior as default startup behavior in eyes-v0.1.ino
- Added BEHAVIOR_MOUTH_INVASION to behavior enum in Globals.h
- Updated behavior system to support mouth invasion behavior
- Modified initializeBehavior() to include mouth invasion behavior initialization
- Updated README-AI.md with new behavior and movement function documentation
- Replaced testing behavior with pumpkin behavior as default startup behavior
- Added BEHAVIOR_PUMPKIN to behavior enum in Globals.h
- Updated behavior system to support behavior-specific state machines
- Modified initializeBehavior() to include pumpkin behavior initialization

### Removed
- Behavior sleepiness feature removed in favor of pumpkin behavior demonstration

## [v0.1] - 2024-12-19

### Added
- Initial project structure with 6-servo animatronic eyes system
- Behavior state machine with 7 different eye personalities
- Modular architecture with separate files for movements and behaviors
- Normalized coordinate system (-1.0 to 1.0) for eye positioning
- Comprehensive test sequences for all movements
- Sleepy behavior implementation with droopy eyelids
- Base movement functions for eye and eyelid control
- Complete documentation (README.md and README-AI.md)
- Arduino Nano coding standards and best practices

### Technical Updates
- Arduino Nano (ATmega328P) target platform
- 2KB SRAM memory constraint awareness
- Non-blocking timing implementation using millis()
- Servo pin mapping: Pins 4,5,8,9,10,11
- Behavior tick rate: 100ms intervals
- Automatic behavior switching every 10 seconds

### Documentation
- Complete README-AI.md with technical specifications
- Human-readable README.md for users
- Comprehensive function documentation
- Hardware setup and pin mapping details
- Coding standards and best practices
- Documentation maintenance requirements

---

## Change Log Format

### Categories
- **Added**: New features, functions, or behaviors
- **Changed**: Modifications to existing functionality
- **Deprecated**: Features that will be removed in future versions
- **Removed**: Features that have been removed
- **Fixed**: Bug fixes and corrections
- **Security**: Security improvements

### Version Numbering
- **Major** (X.0.0): Breaking changes or major feature additions
- **Minor** (0.X.0): New features that don't break existing functionality
- **Patch** (0.0.X): Bug fixes and minor improvements

### Entry Format
```
### [Version] - YYYY-MM-DD
#### Added
- New feature description

#### Changed
- Change description

#### Fixed
- Bug fix description
```

### Maintenance Guidelines
- Update change log with every code change
- Use clear, descriptive language
- Group related changes together
- Include technical details for significant changes
- Maintain chronological order (newest first)
