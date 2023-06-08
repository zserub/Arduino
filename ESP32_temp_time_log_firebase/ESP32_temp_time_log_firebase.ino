#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "time.h"
#include <DHTesp.h>

// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "XXXxxx_Modem"
#define WIFI_PASSWORD "XXXxxxXXX"

// Insert Firebase project API Key
#define API_KEY "XXXxxxXXX"

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "XXX@gmail.com"
#define USER_PASSWORD "xxxxxxxxxxx"

// Insert RTDB URLefine the RTDB URL
#define DATABASE_URL "https://esplogtest-default-rtdb.europe-west1.firebasedatabase.app"

// Sensor pin
#define dhtPin 14

// Define Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Variable to save USER UID
String uid;

// Database main path (to be updated in setup with the user UID)
String databasePath;
// Database child nodes
String tempPath = "/temperature";
String humPath = "/humidity";
// String presPath = "/pressure";
String timePath = "/timestamp";

// Parent Node (to be updated in every loop)
String parentPath;

String timestamp;
FirebaseJson json;

const char *ntpServer = "pool.ntp.org";

DHTesp dht;
float temperature;
float humidity;
// float pressure;

// Timer variables (send new readings every three minutes)
unsigned long sendDataPrevMillis = 0; 
unsigned long timerDelay = 600000;

// Initialize WiFi
void initWiFi()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}

// Function that gets current epoch time
String callLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    // Serial.println("Failed to obtain time");
    return "Null";
  }
  // Serial.println(&timeinfo, "%B %d %H:%M:%S");    //%A: Dayname, %B: Month, %d: day, %Y: year, %H:%M:%S time
  char buffer[30];
  strftime(buffer, sizeof(buffer), "%B %d %H:%M:%S", &timeinfo);
  return String(buffer);
}

void setup()
{
  pinMode(dhtPin, INPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);

  dht.setup(dhtPin, DHTesp::DHT11);
  Serial.println("DHT initiated");
  digitalWrite(12, HIGH);

  initWiFi();
  configTime(0, 0, ntpServer);

  // Assign the api key (required)
  config.api_key = API_KEY;

  // Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  // Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  // Assign the maximum retry of token generation
  config.max_token_generation_retry = 5;

  // Initialize the library with the Firebase authen and config
  Firebase.begin(&config, &auth);

  // Getting the user UID might take a few seconds
  Serial.println("Getting User UID");
  while ((auth.token.uid) == "")
  {
    Serial.print('.');
    delay(1000);
  }
  // Print user UID
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.println(uid);

  // Update database path
  databasePath = "/UsersData/" + uid + "/readings";
}

void loop()
{

  // Send new readings to database
  if (Firebase.ready() && (millis() - sendDataPrevMillis > timerDelay || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();

    // Get current timestamp
    timestamp = callLocalTime();
    // Serial.print("time: ");
    // Serial.println(timestamp);

    parentPath = databasePath + "/" + timestamp;

    TempAndHumidity newValues = dht.getTempAndHumidity();

    json.set(tempPath.c_str(), String(newValues.temperature));
    json.set(humPath.c_str(), String(newValues.humidity));
    // json.set(timePath, timestamp);
    Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
  }
}
