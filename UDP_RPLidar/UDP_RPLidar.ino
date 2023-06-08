#include <RPLidar.h>
// #include <AsyncUDP.h>
// #include <WiFi.h>

#define RPLIDAR_MOTOR 5 // The PWM pin for controlling the speed of RPLIDAR's motor.
// #define RXPIN 16
// #define TXPIN 17

const char ssid[] = "XXXxxx_Modem";
const char pass[] = "XXXxxxXXX";

RPLidar lidar;
//AsyncUDP udp;

void setup() {
  Serial.begin(115200);
  // Serial2.begin(115200); // Setup UART2 with proper pins
  lidar.begin(Serial2);
  pinMode(RPLIDAR_MOTOR, OUTPUT);
/*
  WiFi.begin(ssid, pass);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Failed to connect to WiFi!");
    while (1) {
      delay(1000);
    }
  }

  if (udp.listen(12345)) {
    Serial.print("UDP Listening on IP: ");
    Serial.println(WiFi.localIP());

    udp.onPacket([](AsyncUDPPacket packet) {
      // Handle incoming UDP packets
    });
  }

  rplidar_response_device_info_t info;
  if (IS_OK(lidar.getDeviceInfo(info, 100))) {
    lidar.startScan();
    analogWrite(RPLIDAR_MOTOR, 255);
    delay(1000);
  }*/
}

void loop() {
  while (Serial2.available()) {
    Serial.print(char(Serial2.read()));
  }
  // if (IS_OK(lidar.waitPoint())) {
  //   float distance = lidar.getCurrentPoint().distance; // Distance value in mm unit
  //   float angle = lidar.getCurrentPoint().angle; // Angle value in degrees

  //   String data = String(angle) + "," + String(distance);
  //   // udp.broadcastTo(data.c_str(), 12345);

  // } else {
  //   analogWrite(RPLIDAR_MOTOR, 0); // Stop the RPLidar motor

  //   rplidar_response_device_info_t info;
  //   if (IS_OK(lidar.getDeviceInfo(info, 100))) {
  //     lidar.startScan();
  //     analogWrite(RPLIDAR_MOTOR, 255);
  //     delay(1000);
  //   }
  // }
}
