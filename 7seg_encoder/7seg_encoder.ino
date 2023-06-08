/**
 * @brief Controlling 7segmenet with encoder
 * @version 0.3
 * @date 2023-04-09
 *
 * The encoder controles the 7segmenet display, counting from 0 to 9 both direction, as it can only display one digit.
 */

#include <Encoder.h>
#include <EasyButton.h>
#include "SevSeg.h"

SevSeg sevseg; // Instantiate a seven segment object
EasyButton encoderButton(12);

// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder encoder(10, 11);
int newPosition = 0;
int oldPosition = 0;
unsigned long lastDebounceTime = 0;

// Initialize 7 segment display for 5161BS
byte numDigits = 1;     // Number of displays
byte digitPins[] = {9}; // Power/GND pins
byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8};
bool resistorsOnSegments = true;    // 'false' means resistors are on digit pins
byte hardwareConfig = COMMON_ANODE; // See README.md for options
bool updateWithDelays = false;      // Default 'false' is Recommended
bool leadingZeros = false;          // Use 'true' if you'd like to keep the leading zeros
bool disableDecPoint = true;        // Use 'true' if your decimal point doesn't exist or isn't connected. Then, you only need to specify 7 segmentPins[]

void setup()
{
  // Serial.begin(9600);
  encoderButton.begin();
  encoderButton.onPressed(onPressed); // onPressed function will be called when the onPressed event of the button gets triggered.
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
               updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(1);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH); // Power for encoder
}

void loop()
{
  encoderButton.read();
  newPosition = encoder.read();
  if (newPosition != oldPosition)
  {
    int absPosition = abs(newPosition) / 2;
    if (absPosition > 9)
    {
      absPosition = 0;
    }
    // Serial.print(newPosition);
    // Serial.print("\t");
    // Serial.println(absPosition);
    sevseg.setNumber(absPosition);
    oldPosition = newPosition;
  }
  sevseg.refreshDisplay(); // Must run repeatedly
}

// reset the encoder
void onPressed()
{
  encoder.write(0);
  oldPosition = 0;
  sevseg.setNumber(0);
  // Serial.println("Encoder reset to 0");
}