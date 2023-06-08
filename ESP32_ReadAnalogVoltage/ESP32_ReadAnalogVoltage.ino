// https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
void setup() {
  pinMode(34, INPUT);
  // pinMode(32, OUTPUT);
  // digitalWrite(32, HIGH);
  Serial.begin(9600);
  analogReadResolution(9);
}

void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(34);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = 3.24-(sensorValue * (3.24 / 511.0));
  // print out the value you read:
  Serial.println(voltage);
  delay(1000);
}
