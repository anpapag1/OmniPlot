# OmniPlot

OmniPlot is an ESP-based controller sketch for a 3-wheel omnidirectional plotting robot. The main sketch is `OmniPlot.ino` and it uses the AccelStepper and MultiStepper libraries to drive three stepper motors.

This repository also contains PCB/board files under the `OmniPlot-PCB/` folder.

## Quick summary

- Libraries to download: 
  - AccelStepper.h  `for steppers`
  - ESP32Servo.h  `for pen servo`
  - Adafruit_SSD1306.h `for display`

- Pinout:
  - Stepper1 (Back left) (`step = 35`, `dir  = 34`, `en  = 26`)
  - Stepper2 (front) (`step = 14`, `dir  = 12`, `en  = 27`)
  - Stepper3 (Back right) (`step = 25`, `dir  = 33`, `en  = 32`)
  - Pen_Servo (`servo_Pin = 23`)
  - Encoder (`A = 19`, `B = 18`, `btn = 5`)
  - Oled 
    - `SCREEN_WIDTH 128`
    - `SCREEN_HEIGHT 32`
    - `OLED_RESET -1 `
    - `SCREEN_ADDRESS 0x3C`


## Functions and behavior

This section documents the important functions in `OmniPlot.ino` and what each does.

- `GnR(int speed, int steps1, int steps2, int steps3)`
  - Sets `setMaxSpeed(speed)` for each stepper (units: steps per second for AccelStepper).
  - Writes the requested target positions into a `long gotoposition[3]` array.
  - Calls `steppersControl.moveTo(gotoposition);` followed by `steppersControl.runSpeedToPosition();` — this blocks until all steppers reach their target positions.
  - Waits 1 second, then commands all motors to return to position zero and waits again.


- `omniTest()`
  - A simple test routine that calls `GnR(...)` with several sets of speeds and step targets to demonstrate movement patterns. The calls look like:
    - `GnR(1000, 1000, -1000, 0);`
    - `GnR(2000, 0, 1000, -1000);`
    - and so on.
  - These sequences are examples — change or expand them to drive your robot.


- `spin(int steps)`
  - Example helper that sets all motors to a target (int steps) and back to zero. Also uses `runSpeedToPosition()` so it blocks until complete.

## Rotary Encoder with Interrupts

To read a rotary encoder efficiently using hardware interrupts on ESP32, use the following code pattern:

```cpp
// Encoder pin definitions
const int encoderPinA = 19;  // CLK
const int encoderPinB = 18;  // DT
const int encoderBtn = 5;    // SW (button)

volatile long encoderPosition = 0;
volatile bool buttonPressed = false;

// Interrupt service routine for encoder
void IRAM_ATTR encoderISR() {
  int stateB = digitalRead(encoderPinB);
  if (stateB == HIGH) {
    encoderPosition++;  // Clockwise
  } else {
    encoderPosition--;  // Counter-clockwise
  }
}

// Interrupt service routine for button
void IRAM_ATTR buttonISR() {
  buttonPressed = true;
}

void setup() {
  // Configure encoder pins
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(encoderBtn, INPUT_PULLUP);
  
  // Attach interrupts (trigger on FALLING edge)
  attachInterrupt(digitalPinToInterrupt(encoderPinA), encoderISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(encoderBtn), buttonISR, FALLING);
}

void loop() {
  // Read encoder position (interrupt updates it automatically)
  static long lastPosition = 0;
  if (encoderPosition != lastPosition) {
    Serial.print("Encoder: ");
    Serial.println(encoderPosition);
    lastPosition = encoderPosition;
  }
  
  // Check button press
  if (buttonPressed) {
    Serial.println("Button pressed!");
    buttonPressed = false;  // Reset flag
    delay(200);  // Simple debounce
  }
}
```

**Key points:**
- Use `IRAM_ATTR` for interrupt functions to place them in RAM for faster execution
- Use `volatile` for variables shared between interrupts and main code
- GPIO 19 and 18 support interrupts and are safe for encoder use
- The encoder position updates automatically in the background via interrupts

