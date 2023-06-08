#include <RPLidar.h>

// RPLidar definitions
RPLidar lidar;
#define RPLIDAR_MOTOR 3

void setup()
{
  lidar.begin(Serial);

  pinMode(RPLIDAR_MOTOR, OUTPUT);
  delay(3000); // Give time to turn on
}

void loop()
{
  // Read RPLidar
  if (IS_OK(lidar.waitPoint()))
  {
    float distance = lidar.getCurrentPoint().distance;
    float angle = lidar.getCurrentPoint().angle;
    bool startBit = lidar.getCurrentPoint().startBit; // whether this point is belong to a new scan
    if (distance < 150 && ((angle <= 45) || (angle >= 315)))
    {
      lidar.end();          // stop using Serial for lidar
      delay(2);
      Serial.begin(115200); // start using Serial for debugging
      Serial.print("Angle: ");
      Serial.println(angle);
      Serial.print("\tDistance: ");
      Serial.print(distance);
      Serial.end();        // stop using Serial for debugging
      delay(2);
      lidar.begin(Serial); // start using Serial for lidar again
    }
  }
  else
  {
    analogWrite(RPLIDAR_MOTOR, 0); // Stop the RPLidar motor
    // lidar isn't getting a point, let's debug
    // lidar.end();          // stop using Serial for lidar
    // Serial.begin(115200); // start using Serial for debugging

    // Serial.println("Lidar not getting a point");
    // // rest of your debugging code

    // Serial.end();        // stop using Serial for debugging
    // lidar.begin(Serial); // start using Serial for lidar again

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