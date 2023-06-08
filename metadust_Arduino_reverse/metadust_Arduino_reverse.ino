/**
 * @brief Robot cleaner with Arduino UNO, reversing test
 * @version 0.3.12
 * @updated 2023-05-17
 *
 */

#include <L298NX2.h>
#include <RPLidar.h>
#include <elapsedMillis.h>

elapsedMillis reversingTime;

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
#define MOTOR_BASE_SPEED 125
#define LEFT_M_OFFSET 23
bool isReverseActive = false;

// Buzzer
#define speakerPin 11

// RPLidar definitions
RPLidar lidar;
#define RPLIDAR_MOTOR 3

// Define the threshold distance (in mm) for detecting an object
#define OBJECT_DISTANCE_THRESHOLD 250 // Adjust this as needed

void bipfunction()
{
  // reverse order
  if (reversingTime >= 100 * 3)
  {
    analogWrite(speakerPin, 0);
  }
  else if (reversingTime >= 100 * 2)
  {
    analogWrite(speakerPin, 50);
  }
  else if (reversingTime >= 100)
  {
    analogWrite(speakerPin, 0);
  }
  else // first
  {
    analogWrite(speakerPin, 50);
  }
}

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
  readLidar();

  if (isReverseActive)
  {
    bipfunction();
    reversing();
  }
}

void error()
{
  analogWrite(RPLIDAR_MOTOR, 0);
  motors.stop();
  analogWrite(speakerPin, 100);
}

void readLidar()
{
  if (IS_OK(lidar.waitPoint()))
  {
    analogWrite(speakerPin, 0); // Turn off the buzzer

    // Get RPLidar data
    float distance = lidar.getCurrentPoint().distance;
    float angle = lidar.getCurrentPoint().angle;

    if (lidar.getCurrentPoint().startBit) // a new scan, process the previous data...
    {
      if (minDistance < 125) // Check if point is too close
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
      else if (!isReverseActive && ((minDistance <= OBJECT_DISTANCE_THRESHOLD) && ((angleAtMinDist <= 74) || (angleAtMinDist >= 286)))) // Check if object is close enough in front
      {
        isReverseActive = true;
        reversingTime = 0;
      }
      else if (!isReverseActive)
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

void reversing()
{
  if (reversingTime >= 3000) // 0.5 sec delay after stop
  {
    isReverseActive = false;
  }
  else if (reversingTime >= 2500) // Stop reversing after 2 sec
  {
    motors.stop();
    motors.setSpeedB(MOTOR_BASE_SPEED + LEFT_M_OFFSET);
  }
  else if (reversingTime >= 500) // Start reversing after 0.5 sec delay
  {
    motors.setSpeedB(MOTOR_BASE_SPEED + LEFT_M_OFFSET / 2);
    motors.backward();
  }
  else // Stop first time
  {
    motors.stop();
  }
}