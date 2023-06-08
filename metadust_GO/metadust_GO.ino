/**
 * @brief Controlling Metadust with Blynk joystick
 * @version 0.6
 * @date 2023-04-13
 */

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "XXXxxxXXX"
#define BLYNK_TEMPLATE_NAME "joystick"
#define BLYNK_AUTH_TOKEN "XXXxxxXXX"

/* Comment this out to disable prints and save space */
// #define BLYNK_PRINT Serial

#include <math.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <L298NX2.h>

// Your WiFi credentials.
const char ssid[] = "XXXxxx_Modem";
const char pass[] = "XXXxxxXXX";

// Define the pins for the motor driver
// Set the motor pins
const int RightMotorIN1 = 19;
const int RightMotorIN2 = 18;
const int LeftMotorIN1 = 5;
const int LeftMotorIN2 = 17;
const int RightMotorPWM = 16;
const int LeftMotorPWM = 4;
L298NX2 motors(RightMotorPWM, RightMotorIN1, RightMotorIN2, LeftMotorPWM, LeftMotorIN1, LeftMotorIN2);

// joystick range
const int range = 256;

// Set the initial joystick values
int xValue = range / 2;
int yValue = range / 2;

// BLYNK_CONNECTED()
// {
//   Serial.println("Connected to Blynk!");
// }

void setup()
{
  // Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Set motor pins as output
  pinMode(RightMotorIN1, OUTPUT);
  pinMode(RightMotorIN2, OUTPUT);
  pinMode(LeftMotorIN1, OUTPUT);
  pinMode(LeftMotorIN2, OUTPUT);
  pinMode(RightMotorPWM, OUTPUT);
  pinMode(LeftMotorPWM, OUTPUT);

  // Set initial motor state
  motorControl(xValue, yValue);

  digitalWrite(RightMotorIN1, LOW);
  digitalWrite(RightMotorIN2, LOW);
  digitalWrite(LeftMotorIN1, LOW);
  digitalWrite(LeftMotorIN2, LOW);
}

void loop()
{
  Blynk.run();
}

BLYNK_WRITE(V0)
{
  xValue = param.asInt();
  motorControl(xValue, yValue);
}

BLYNK_WRITE(V13)
{
  yValue = param.asInt();
  motorControl(xValue, yValue);
}

void motorControl(int x, int y)
{
  // Map X and Y joystick values to the range -range/2 to range/2-1
  int mappedX = x - (range / 2);
  int mappedY = y - (range / 2);

  // Calculate motor speeds
  int LeftM_Speed = 2 * (mappedY - mappedX);
  int RightM_Speed = 2 * (mappedY + mappedX);

  // Calculate the angle and magnitude of the joystick position
  // float angle = atan2(mappedY, mappedX);
  // float magnitude = sqrt(sq(mappedX) + sq(mappedY));

  // Map magnitude to the range 0 to range-1
  // magnitude = map(magnitude, 0, sqrt(sq(range / 2) + sq(range / 2)), 0, range - 1);

  // Calculate the motor speeds based on the angle and magnitude
  // LeftM_Speed = magnitude * (cos(angle + M_PI_4));
  // RightM_Speed = magnitude * (sin(angle + M_PI_4));

  // Constrain motor speeds to valid range (-range to range-1)
  LeftM_Speed = constrain(LeftM_Speed, -range + 1, range - 1);
  RightM_Speed = constrain(RightM_Speed, -range + 1, range - 1);

  // Set motor speeds using the L298NX2 library
  motors.setSpeedA(abs(LeftM_Speed));
  motors.setSpeedB(abs(RightM_Speed));

  // Set motor directions using the L298NX2 library
  if (LeftM_Speed > 0)
  {
    motors.forwardA();
  }
  else if (LeftM_Speed < 0)
  {
    motors.backwardA();
  }
  else
  {
    motors.stopA();
  }

  if (RightM_Speed > 0)
  {
    motors.forwardB();
  }
  else if (RightM_Speed < 0)
  {
    motors.backwardB();
  }
  else
  {
    motors.stopB();
  }
}



