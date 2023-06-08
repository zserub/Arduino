// modified version of https://lastminuteengineers.com/esp32-ntp-server-date-time-tutorial/

#include <WiFi.h>
#include "time.h"

// Insert your network credentials
#define WIFI_SSID "XXXxxx_Modem"
#define WIFI_PASSWORD "XXXxxxXXX"

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

String callLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    // Serial.println("Failed to obtain time");
    return "Failed to obtain time";
  }
  // Serial.println(&timeinfo, "%B %d %H:%M:%S");    //%A: Dayname, %B: Month, %d: day, %Y: year, %H:%M:%S time
  char buffer[30];
  strftime(buffer, sizeof(buffer), "%B %d %H:%M:%S", &timeinfo);
  return String(buffer);
}

void setup()
{
  Serial.begin(9600);

  // connect to WiFi
  Serial.printf("Connecting to %s ", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");

  // init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println(callLocalTime());    //must use here for init purpose

  // disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop()
{
  delay(1000);
  Serial.println(callLocalTime());
}