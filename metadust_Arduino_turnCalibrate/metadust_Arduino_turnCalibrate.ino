#include <L298NX2.h>
#include <EasyButton.h>

EasyButton left_button(12);
EasyButton right_button(11);

// Motor control definitions
const int RightMotorIN1 = 10;
const int RightMotorIN2 = 9;
const int LeftMotorIN1 = 8;
const int LeftMotorIN2 = 7;
const int RightMotorPWM = 6;
const int LeftMotorPWM = 5;
L298NX2 motors(RightMotorPWM, RightMotorIN1, RightMotorIN2, LeftMotorPWM, LeftMotorIN1, LeftMotorIN2);
const int range = 256;

void setup()
{
  // pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, OUTPUT);
  left_button.begin();
  left_button.onPressed(turnLeft); // onPressed function will be called when the onPressed event of the button gets triggered.
  right_button.begin();
  right_button.onPressed(turnRight);
}

void loop()
{
  right_button.read();
  left_button.read();
}

void turnLeft() {
  digitalWrite(2, HIGH);
  motors.setSpeed(175);

  // Set direction for motors
  motors.forwardA();  // Left motor moves forward
  motors.backwardB(); // Right motor moves backward

  // Add a delay to achieve a 90 degree turn
  delay(850);

  // Stop motors after turn
  motors.stop();
  digitalWrite(2, LOW);
}

void turnRight()
{
  digitalWrite(2, HIGH);
  motors.setSpeed(180);

  // Set direction for motors
  motors.backwardA(); // Left motor moves backward
  motors.forwardB();  // Right motor moves forward

  // Add a delay to achieve a 90 degree turn
  delay(850);

  // Stop motors after turn
  motors.stop();
  digitalWrite(2, LOW);
}
