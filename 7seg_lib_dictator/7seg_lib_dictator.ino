/**
 * @brief Controlling the 7 segment display directly. Sending characters via Serial communication.
 * @version 0.2
 * @date 2023-04-09
 */

#include "SevSeg.h"
SevSeg sevseg; // Instantiate a seven segment object

byte numDigits = 1;      // Number of displays
byte digitPins[] = {10}; // Power/GND pins
byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8};
bool resistorsOnSegments = true;    // 'false' means resistors are on digit pins
byte hardwareConfig = COMMON_ANODE; // See README.md for options
bool updateWithDelays = false;      // Default 'false' is Recommended
bool leadingZeros = false;          // Use 'true' if you'd like to keep the leading zeros
bool disableDecPoint = true;        // Use 'true' if your decimal point doesn't exist or isn't connected. Then, you only need to specify 7 segmentPins[]

void setup()
{
  Serial.begin(9600);
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
               updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(50);
  // char testchar[1] = "A";        // Character to display, MUST BE A CHAR ARRAY
  // sevseg.setChars(testchar);
}

void loop()
{
  if (Serial.available() > 0)
  {
    String incomingData = Serial.readStringUntil(' ');
    incomingData.trim();
    char incomingChar[numDigits] = {incomingData.charAt(0)};
    sevseg.setChars(incomingChar);     // Works with numbers too
  }

  sevseg.refreshDisplay(); // Must run repeatedly
}