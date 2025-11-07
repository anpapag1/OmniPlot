# OmniPlot

OmniPlot is an ESP-based controller sketch for a 3-wheel omnidirectional plotting robot. The main sketch is `OmniPlot.ino` and it uses the AccelStepper and MultiStepper libraries to drive three stepper motors.

This repository also contains PCB/board files under the `OmniPlot-PCB/` folder.

## Quick summary

- Libraries: AccelStepper
- Stepper1 (Back left) 
    - `step = 12`
    - `dir  = 14`
- Stepper2 (front) 
    - `step = 33`
    - `dir  = 32`
- Stepper3 (Back right) 
    - `step = 26`
    - `dir  = 25`

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

