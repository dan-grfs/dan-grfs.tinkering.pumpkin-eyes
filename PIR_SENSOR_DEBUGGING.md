# HC-SR501 PIR Sensor Debugging Guide
https://www.handsontec.com/dataspecs/SR501%20Motion%20Sensor.pdf

## How the HC-SR501 Sensor Works

### Basic Operation
- **Type**: Passive Infrared (PIR) motion sensor
- **Output**: Digital HIGH/LOW signal
- **Detection**: Detects changes in infrared radiation from moving warm objects (humans, animals)
- **Range**: Up to ~7 meters (adjustable via sensitivity potentiometer)

### Key Components on the Sensor Module

1. **Sensitivity Potentiometer** (usually labeled "Sx" or "Sensitivity")
   - Controls detection range
   - Turn clockwise = more sensitive (longer range)
   - Turn counter-clockwise = less sensitive (shorter range)

2. **Delay Time Potentiometer** (usually labeled "Tx" or "Time")
   - Controls how long output stays HIGH after detection
   - Range: 0.3 seconds to ~5 minutes
   - Turn clockwise = longer delay
   - Turn counter-clockwise = shorter delay

3. **Trigger Mode Jumper** (usually 3-pin header with jumper)
   - **H Position (Repeatable Trigger)**: Output stays HIGH as long as motion continues
   - **L Position (Non-repeatable Trigger)**: Output goes HIGH on detection, then LOW after delay time regardless of continued motion

### Important Characteristics

1. **Warm-up Period**: 30-60 seconds after power-on
   - Sensor needs time to calibrate to environment
   - During warm-up, readings may be unstable
   - This is NORMAL behavior

2. **Lockout Period**: ~2 seconds after output goes LOW
   - Sensor won't detect new motion during this time
   - Prevents false triggers from residual signals

3. **Power Requirements**: 5V DC (can work with 3.3V-20V, but 5V is standard)

## Debugging Plan

### Step 1: Verify Enhanced Debugging Code
The code has been updated with comprehensive diagnostics:
- Tracks state changes in real-time
- Shows statistics every 5 seconds
- Monitors warm-up period
- Provides diagnostic warnings

**Action**: Upload the updated code and monitor serial output at 9600 baud.

### Step 2: Check Physical Wiring

Verify connections:
```
HC-SR501 Module    →    Arduino Nano
VCC                →    5V
GND                →    GND
OUT                →    Digital Pin 2 (D2)
```

**Common Issues**:
- Loose connections
- Wrong pin (should be D2)
- Power supply issues (use stable 5V)
- Ground not connected properly

### Step 3: Wait for Warm-up Period

**Critical**: The sensor needs 30-60 seconds to stabilize after power-on.

**What to do**:
1. Power on the Arduino
2. Wait at least 60 seconds
3. Watch serial monitor for "Sensor warm-up complete" message
4. Only start testing AFTER warm-up is complete

**During warm-up**: Unstable readings are NORMAL - ignore them.

### Step 4: Check Sensor Module Settings

#### A. Sensitivity Adjustment
**Problem**: If stuck HIGH, sensitivity may be too high.

**Solution**:
1. Turn sensitivity potentiometer **counter-clockwise** (reduce sensitivity)
2. Test after each adjustment
3. Find balance: sensitive enough to detect motion, but not too sensitive

#### B. Delay Time Adjustment
**Problem**: If stuck HIGH, delay time may be set too long.

**Solution**:
1. Turn delay time potentiometer **counter-clockwise** (reduce delay)
2. Recommended: Start with minimum delay (~0.3 seconds)
3. Increase if needed for your application

#### C. Trigger Mode Jumper
**Problem**: In "H" (repeatable) mode, output stays HIGH with continuous motion.

**Solution**:
1. Check jumper position on sensor module
2. Try switching to "L" (non-repeatable) mode
3. In "L" mode, output will go LOW after delay time even if motion continues

### Step 5: Environmental Factors

**Check for**:
- **Heat sources**: Heaters, radiators, direct sunlight
- **Air movement**: Fans, air conditioning vents
- **Reflective surfaces**: Mirrors, windows
- **Background IR**: Other electronics emitting heat

**Solution**:
- Move sensor away from heat sources
- Point sensor away from windows/sunlight
- Test in different locations
- Cover sensor temporarily to see if readings change

### Step 6: Test with Serial Monitor

The enhanced code provides detailed diagnostics:

**What to look for**:
1. **State changes**: Should see "[STATE CHANGE]" messages when sensor actually changes
2. **Statistics**: Every 5 seconds, check HIGH/LOW percentages
3. **Warnings**: Code will warn if sensor is stuck HIGH (>95% HIGH readings)

**Expected behavior after warm-up**:
- Mostly LOW when no motion
- HIGH when motion detected
- Returns to LOW after delay time (if in "L" mode)

### Step 7: Test Sensor Output Directly

If still having issues, test sensor independently:

**Simple LED Test**:
1. Connect LED + resistor (220Ω) between sensor OUT and GND
2. LED should light when motion detected
3. If LED stays on constantly, sensor hardware issue or settings problem

**Multimeter Test**:
1. Measure voltage between OUT and GND
2. Should read ~0V (LOW) when no motion
3. Should read ~3.3V-5V (HIGH) when motion detected

### Step 8: Check for Floating Pin Issue

**Problem**: If Arduino pin is floating (not properly connected), it can read random values.

**Symptoms**:
- Random HIGH/LOW readings
- Unstable readings
- Readings don't match actual sensor state

**Solution**:
- Verify wiring is secure
- Check that OUT pin is actually connected to D2
- Try a different digital pin to test
- The HC-SR501 should have proper output driver, so floating shouldn't be an issue if wired correctly

### Step 9: Power Supply Check

**Problem**: Unstable power can cause erratic behavior.

**Check**:
- Arduino powered via USB or external supply?
- If USB, try external 5V supply
- Measure voltage at sensor VCC pin (should be ~5V)
- Check for voltage fluctuations

### Step 10: Sensor Hardware Test

**If all else fails**, the sensor module itself may be faulty:

**Test**:
1. Try a different HC-SR501 module (if available)
2. Test with minimal code (just read pin and print)
3. Check sensor module for physical damage
4. Verify sensor module is genuine HC-SR501 (some clones have issues)

## Using digitalRead() - Is This Correct?

**YES, `digitalRead()` is the correct method** for reading the HC-SR501 sensor.

### Why digitalRead() is correct:
- HC-SR501 outputs a **digital signal** (HIGH/LOW)
- The OUT pin is a digital output from the sensor module
- Arduino digital pins are designed to read digital signals
- No analog-to-digital conversion needed

### Pin Mode Configuration:
```cpp
pinMode(MOVEMENT_SENSOR_PIN, INPUT);  // Correct for digital sensor
```

**NOT** `INPUT_PULLUP` because:
- INPUT_PULLUP enables internal pull-up resistor
- This would invert the logic (LOW = active)
- HC-SR501 has its own output driver, doesn't need pull-up

### Alternative (if needed):
If you suspect floating pin issues, you could try:
```cpp
pinMode(MOVEMENT_SENSOR_PIN, INPUT_PULLDOWN);  // If your Arduino supports it
```
But this is usually NOT necessary for HC-SR501.

## Expected Serial Output

### During Warm-up (first 60 seconds):
```
=== PIR Sensor Initialization ===
Movement sensor initialized on pin D2
WARNING: Sensor requires 30-60 second warm-up period
Initial sensor reading: HIGH
===================================
PIR Sensor: HIGH | Movement: NONE | Uptime: 5s [WARMING UP - 55s remaining]
[STATE CHANGE] HIGH -> LOW (held for 5234 ms)
PIR Sensor: LOW | Movement: NONE | Uptime: 10s [WARMING UP - 50s remaining]
```

### After Warm-up (normal operation):
```
=== Sensor warm-up complete (60 seconds) ===
PIR Sensor: LOW | Movement: NONE | Uptime: 65s
--- Sensor Statistics (last 5 seconds) ---
HIGH readings: 0 (0.0%)
LOW readings: 5000 (100.0%)
Current state duration: 5000 ms
INFO: Sensor mostly LOW - normal if no motion
------------------------------------------
[STATE CHANGE] LOW -> HIGH (held for 5234 ms)
Movement detected! Sensor reading: HIGH
PIR Sensor: HIGH | Movement: DETECTED | Uptime: 70s
```

### If Stuck HIGH:
```
--- Sensor Statistics (last 5 seconds) ---
HIGH readings: 5000 (100.0%)
LOW readings: 0 (0.0%)
WARNING: Sensor stuck HIGH - check:
  1. Sensitivity too high?
  2. Delay time too long?
  3. Trigger mode jumper position?
  4. Heat sources in view?
  5. Wiring issue (pin floating)?
------------------------------------------
```

## Quick Troubleshooting Checklist

- [ ] Wait 60 seconds after power-on (warm-up period)
- [ ] Check wiring: VCC→5V, GND→GND, OUT→D2
- [ ] Reduce sensitivity (turn potentiometer counter-clockwise)
- [ ] Reduce delay time (turn potentiometer counter-clockwise)
- [ ] Check trigger mode jumper (try "L" position)
- [ ] Remove heat sources from sensor view
- [ ] Test in different location
- [ ] Verify power supply is stable 5V
- [ ] Check serial monitor for diagnostic messages
- [ ] Test sensor with LED or multimeter directly

## Next Steps

1. Upload the enhanced debugging code
2. Open serial monitor at 9600 baud
3. Wait 60 seconds for warm-up
4. Observe the diagnostic output
5. Follow the troubleshooting steps based on what you see
6. Adjust sensor potentiometers as needed
7. Report back with serial monitor output for further assistance

