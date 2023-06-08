#include <DHTesp.h>
#define dhtPin 14

DHTesp dht;

void setup()
{
  pinMode(dhtPin, INPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
  dht.setup(dhtPin, DHTesp::DHT11);
  Serial.println("DHT initiated");
  digitalWrite(12, HIGH);
}

void loop()
{
  Serial.println();

  TempAndHumidity newValues = dht.getTempAndHumidity();
  Serial.println(" T:" + String(newValues.temperature) + " H:" + String(newValues.humidity));

  delay(5000);
}