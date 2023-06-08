// define the pins for the encoder
#define encoderPinA 3

// define the variables
volatile int count = 0;
unsigned long previousMillis = 0;

void setup() {
  // set the encoder pin as an input
  pinMode(encoderPinA, INPUT);

  // set up an interrupt for the encoder
  attachInterrupt(digitalPinToInterrupt(encoderPinA), countPulse, RISING);

  // start the serial communication
  Serial.begin(9600);
}

void loop() {
  // get the current time
  unsigned long currentMillis = millis();

  // if a second has passed, print the count and reset it
  if (currentMillis - previousMillis >= 1000) {
    Serial.print("Count: ");
    Serial.println(count);
    //count = 0;
    previousMillis = currentMillis;
  }
}

void countPulse() {
  // increment the count when the encoder pulses
  count++;
}
