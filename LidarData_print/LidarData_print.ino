#include <RPLidar.h>

RPLidar lidar;

#define RPLIDAR_MOTOR 5
#define RXPIN 16
#define TXPIN 17

void setup() {
  Serial.begin(115200); // Initiate the serial communication with computer for the printout
  lidar.begin(Serial2);
  pinMode(RPLIDAR_MOTOR, OUTPUT);
}

void loop() {
  if (IS_OK(lidar.waitPoint())) {
    float distance = lidar.getCurrentPoint().distance;
    float angle    = lidar.getCurrentPoint().angle;
    
    // Here we print the distance and angle data
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print("\tDistance: ");
    Serial.println(distance);
    // Serial.println(" degree");
    
  } else {
    analogWrite(RPLIDAR_MOTOR, 0); 

    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100))) {
       lidar.startScan();
       analogWrite(RPLIDAR_MOTOR, 255);
       delay(1000);
    }
  }
}
