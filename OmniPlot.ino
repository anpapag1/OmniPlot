#include <AccelStepper.h>
#include <MultiStepper.h>

// Pin definitions for Motor 1 (Front)
const int step1 = 12;
const int dir1 = 14;

// Pin definitions for Motor 2 (Back-Left)
const int step2 = 33;
const int dir2 = 32;

// Pin definitions for Motor 3 (Back-Right)
const int step3 = 26;
const int dir3 = 25;

// Define the stepper motor and the pins that is connected to
AccelStepper stepper1(1,step3, dir3); // (Typeof driver: with 2 pins, STEP, DIR)
AccelStepper stepper2(1,step2, dir2);
AccelStepper stepper3(1,step1, dir1);

MultiStepper steppersControl;  // Create instance of MultiStepper

long gotoposition[3]; // An array to store the target positions for each stepper motor

void setup() {

  stepper1.setMaxSpeed(2000); // Set maximum speed value for the stepper
  stepper2.setMaxSpeed(2000);
  stepper3.setMaxSpeed(2000);

  // Adding the 3 steppers to the steppersControl instance for multi stepper control
  steppersControl.addStepper(stepper1);
  steppersControl.addStepper(stepper2);
  steppersControl.addStepper(stepper3);
}

void loop() {
  // spin();
  omniTest();

}

void omniTest() {
  // Example movements to test omni-directional movement
  GnR(1000, 1000, -1000, 0); // speed, steps for motor1, motor2, motor3
  GnR(2000, 0, 1000, -1000);
  GnR(800, -1000, 0, 1000);
  GnR(1000, 1500, 1500, 1500);
  GnR(700, -500, -500, -500);
}

// Go to specified positions and return to zero 
void GnR(int speed, int steps1, int steps2, int steps3) {
  stepper1.setMaxSpeed(speed); // Set maximum speed value for the stepper
  stepper2.setMaxSpeed(speed);
  stepper3.setMaxSpeed(speed);

  // Store the target positions in the "gotopostion" array
  gotoposition[0] = steps1;  
  gotoposition[1] = steps2;
  gotoposition[2] = steps3;

  steppersControl.moveTo(gotoposition); // Calculates the required speed for all motors
  steppersControl.runSpeedToPosition(); // Blocks until all steppers are in position

  delay(1000);

  gotoposition[0] = 0;
  gotoposition[1] = 0;
  gotoposition[2] = 0;

  steppersControl.moveTo(gotoposition);
  steppersControl.runSpeedToPosition();

  delay(1000);

}

void spin() {
  // Store the target positions in the "gotopostion" array
  gotoposition[0] = 3200;  // 800 steps - full rotation with quater-step resolution
  gotoposition[1] = 3200;
  gotoposition[2] = 3200;

  steppersControl.moveTo(gotoposition); // Calculates the required speed for all motors
  steppersControl.runSpeedToPosition(); // Blocks until all steppers are in position

  delay(1000);

  gotoposition[0] = 0;
  gotoposition[1] = 0;
  gotoposition[2] = 0;

  steppersControl.moveTo(gotoposition);
  steppersControl.runSpeedToPosition();

  delay(1000);

}

