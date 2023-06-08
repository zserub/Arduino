/**
 * @brief Basic encoder usage with libraries. 
 * @version 0.3
 * @date 2023-04-09
 * 
 * Print the encoder value to the serial monitor.
 */

#include <Encoder.h>  // https://github.com/PaulStoffregen/Encoder
#include <EasyButton.h> // for the button of the encoder https://github.com/evert-arias/EasyButton

EasyButton encoderButton(12);

// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder encoder(10, 11);
int newPosition = 0;
int oldPosition = 0;
unsigned long lastDebounceTime = 0;

void setup()
{
  Serial.begin(9600);
  encoderButton.begin();
  encoderButton.onPressed(onPressed); // onPressed function will be called when the onPressed event of the button gets triggered.
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH); // Power for encoder
}

void loop()
{
  encoderButton.read();
  newPosition = encoder.read();
  if ((millis() - lastDebounceTime) > 200)  // only update after 200ms
  {
    if (newPosition != oldPosition)
    {
      /*int absPosition = abs(newPosition) / 2;
      if (absPosition > 9)
      {
        absPosition = 0;
      }*/
      Serial.println(newPosition);
      // Serial.print("\t");
      // Serial.println(absPosition);
      oldPosition = newPosition;
    }
    lastDebounceTime = millis();
  }
}

// reset the encoder
void onPressed()
{
  encoder.write(0);
  oldPosition = 0;
  Serial.println("Encoder reset to 0");
}