#include <AccelStepper.h>
#include <MultiStepper.h>

// Pin definitions for Motor 1 (Back-Left)
const int step1 = 16;
const int dir1 = 17;
const int en1 = 26;

// Pin definitions for Motor 2 (Front)
const int step2 = 14;
const int dir2 = 12;
const int en2 = 27;

// Pin definitions for Motor 3 (Back-Right)
const int step3 = 25;
const int dir3 = 33;
const int en3 = 32;

// Define the stepper motor and the pins that is connected to
AccelStepper stepper1(1, step1, dir1); // (Typeof driver: with 2 pins, STEP, DIR)
AccelStepper stepper2(1, step2, dir2);
AccelStepper stepper3(1, step3, dir3);

MultiStepper steppersControl;  // Create instance of MultiStepper

long gotoposition[3]; // An array to store the target positions for each stepper motor

void setup() {
  // Set enable pins as outputs and enable the drivers (LOW = enabled)
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(en3, OUTPUT);
  digitalWrite(en1, LOW);
  digitalWrite(en2, LOW);
  digitalWrite(en3, LOW);

  // Adding the 3 steppers to the steppersControl instance for multi stepper control
  steppersControl.addStepper(stepper1);
  steppersControl.addStepper(stepper2);
  steppersControl.addStepper(stepper3);
}

void loop() {
  // spin(1000); // Example spin movement
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

void spin(int steps) {
  stepper1.setMaxSpeed(1000); // Set maximum speed value for the stepper
  stepper2.setMaxSpeed(1000);
  stepper3.setMaxSpeed(1000);

  // Store the target positions in the "gotopostion" array
  gotoposition[0] = steps;  // 800 steps - full rotation with quater-step resolution
  gotoposition[1] = steps;
  gotoposition[2] = steps;

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

