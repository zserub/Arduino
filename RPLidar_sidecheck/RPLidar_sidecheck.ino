#include <RPLidar.h>

// RPLidar definitions
RPLidar lidar;
#define RPLIDAR_MOTOR 3

// Define the threshold distance (in mm) for detecting an object
#define OBJECT_DISTANCE_THRESHOLD 300 // Adjust this as needed

#define frontLED 8
#define rightLED 9
#define leftLED 10
#define backLED 11

void setup()
{
  // Initialize RPLidar and motor control
  lidar.begin(Serial);

  pinMode(RPLIDAR_MOTOR, OUTPUT);
  pinMode(frontLED, OUTPUT);
  pinMode(rightLED, OUTPUT);
  pinMode(leftLED, OUTPUT);
  pinMode(backLED, OUTPUT);
}

float minDistance = 100000;
float angleAtMinDist = 0;
void loop()
{

  // Read RPLidar
  if (IS_OK(lidar.waitPoint()))
  {
    float distance = lidar.getCurrentPoint().distance;
    float angle = lidar.getCurrentPoint().angle;

    if (lidar.getCurrentPoint().startBit) // a new scan, process the previous data
    {
      displayside(angleAtMinDist, minDistance);
      minDistance = 100000;
      angleAtMinDist = 0;
    }
    else
    {
      if (distance > 0 && distance < minDistance) // Update closest point
      {
        minDistance = distance;
        angleAtMinDist = angle;
      }
    }
  }
  else
  {
    analogWrite(RPLIDAR_MOTOR, 0); // Stop the RPLidar motor

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

// Turn on LED based on the side of the closest point
void displayside(float angle, float distance)
{
  // Turn off all the LEDs first
  digitalWrite(frontLED, LOW);
  digitalWrite(rightLED, LOW);
  digitalWrite(leftLED, LOW);
  digitalWrite(backLED, LOW);
  if (distance <= OBJECT_DISTANCE_THRESHOLD)
  {
    if ((angle <= 45) || (angle > 315)) // front
    {
      digitalWrite(frontLED, HIGH);
    }
    else if ((angle > 45) && (angle <= 135)) // right
    {
      digitalWrite(rightLED, HIGH);
    }
    else if ((angle > 225) && (angle <= 315)) // left
    {
      digitalWrite(leftLED, HIGH);
    }
    else if ((angle > 135) && (angle <= 225)) // back
    {
      digitalWrite(backLED, HIGH);
    }
  }
}