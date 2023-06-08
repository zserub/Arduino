/**
 * @brief Robot cleaner with Arduino UNO
 * @version 0.8.2
 * @updated 2023-05-16
 *
 */

// Motor control and RPLidar Libraries
#include <L298NX2.h>
#include <RPLidar.h>
// #include <elapsedMillis.h>

// elapsedMillis buzzTime;

// Motor control definitions
const int RightMotorIN1 = 8;
const int RightMotorIN2 = 7;
const int LeftMotorIN1 = 6;
const int LeftMotorIN2 = 5;
const int RightMotorPWM = 10;
const int LeftMotorPWM = 9;
//                               motor A                                    motor B
//             |------------------------------------------||----------------------------------------|
L298NX2 motors(RightMotorPWM, RightMotorIN1, RightMotorIN2, LeftMotorPWM, LeftMotorIN1, LeftMotorIN2);
// Motor base speed
#define MOTOR_BASE_SPEED 120
#define LEFT_M_OFFSET 15

// Buzzer
#define speakerPin 11

// RPLidar definitions
RPLidar lidar;
#define RPLIDAR_MOTOR 3

// Define the threshold distance (in mm) for detecting an object
#define OBJECT_DISTANCE_THRESHOLD 205 // Adjust this as needed

void setup()
{
  // Initialize RPLidar and motor control
  lidar.begin(Serial);

  pinMode(RPLIDAR_MOTOR, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  motors.setSpeedA(MOTOR_BASE_SPEED);
  motors.setSpeedB(MOTOR_BASE_SPEED + LEFT_M_OFFSET);
  delay(1000); // Give time to turn on
}

float minDistance = 100000;
float angleAtMinDist = 0;
void loop()
{
  // Read RPLidar
  if (IS_OK(lidar.waitPoint()))
  {
    analogWrite(speakerPin, 0); // Turn off the buzzer

    // Get RPLidar data
    float distance = lidar.getCurrentPoint().distance;
    float angle = lidar.getCurrentPoint().angle;

    if (lidar.getCurrentPoint().startBit) // a new scan, process the previous data...
    {
      if (minDistance < 110) // Check if point is too close
      {
        error();

        // Bip-bip
        for (int i = 0; i < 3; i++)
        {
          delay(150);
          analogWrite(speakerPin, 0);
          delay(150);
          analogWrite(speakerPin, 100);
        }
        delay(3000);
      }
      else if ((minDistance <= OBJECT_DISTANCE_THRESHOLD) && ((angleAtMinDist <= 74) || (angleAtMinDist >= 286))) // Check if object is close enough in front
      {
        motors.stop();
        sidecheck();
      }
      else
      {
        motors.forward();
      }
      minDistance = 100000; // Reset for new scan
      angleAtMinDist = 0;
    }
    else
    {
      if (distance > 0 && distance < minDistance) // Update closest point
      {
        minDistance = distance; // Update the minimum distance
        angleAtMinDist = angle;
      }
    }
  }
  else
  {
    error();

    // Try to detect RPLidar
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100)))
    {
      lidar.startScan();
      analogWrite(RPLIDAR_MOTOR, 255);
      delay(1000);
    }
  }
}

void turnLeft()
{
  // Set speeds for motors
  // motors.setSpeed(175);

  // Set direction for motors
  motors.forwardA();  // Right motor moves forward
  motors.backwardB(); // Left motor moves backward

  // Add a delay to achieve a 90 degree turn
  // This value will need to be adjusted based on the actual robot
  delay(800);

  // Stop motors after turn
  motors.stop();
  // motors.setSpeedA(MOTOR_BASE_SPEED);
  // motors.setSpeedB(MOTOR_BASE_SPEED + LEFT_M_OFFSET);
}

void turnRight()
{
  // Set speeds for motors
  // motors.setSpeed(180);

  // Set direction for motors
  motors.backwardA(); // Right motor moves backward
  motors.forwardB();  // Left motor moves forward

  // Add a delay to achieve a 90 degree turn
  // This value will need to be adjusted based on the actual robot
  delay(900);

  // Stop motors after turn
  motors.stop();
  // motors.setSpeedA(MOTOR_BASE_SPEED);
  // motors.setSpeedB(MOTOR_BASE_SPEED + LEFT_M_OFFSET);
}

void sidecheck()
{
  float closestRight = 100000;
  float closestLeft = 100000;
  bool isScanFinished = false;

  while (!isScanFinished) // check sides
  {
    analogWrite(speakerPin, 75);
    // Read RPLidar
    if (IS_OK(lidar.waitPoint()))
    {
      float distance = lidar.getCurrentPoint().distance;
      float angle = lidar.getCurrentPoint().angle;
      isScanFinished = lidar.getCurrentPoint().startBit;

      if (((angle > 70) && (angle <= 100)) && ((distance > 0) && (distance < closestRight))) // Right side check
      {
        closestRight = distance;
      }
      if (((angle > 260) && (angle <= 290)) && ((distance > 0) && (distance < closestLeft))) // Left side check
      {
        closestLeft = distance;
      }
    }
    else
    {
      error();
      // Try to detect RPLidar
      rplidar_response_device_info_t info;
      if (IS_OK(lidar.getDeviceInfo(info, 100)))
      {
        lidar.startScan();
        analogWrite(RPLIDAR_MOTOR, 255);
        delay(1000);
      }
      return;
    }
  }
  analogWrite(speakerPin, 0);

  if (closestRight > closestLeft) // Object on the right side is further
  {
    turnRight();
  }
  else if (closestRight < closestLeft) // Object on the left side is further
  {
    turnLeft();
  }
  else // closestLeft == closestRight
  {
    error();
  }
}

// void bipfunction()
// {
//   for (int i = 0; i < 2; i++)
//   {
//     analogWrite(speakerPin, 75);
//     delay(100);
//     analogWrite(speakerPin, 0);
//     delay(100);
//   }
// }

void error()
{
  analogWrite(RPLIDAR_MOTOR, 0);
  motors.stop();
  analogWrite(speakerPin, 100);
}