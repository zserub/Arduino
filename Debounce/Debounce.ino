/*
  Debounce

  Each time the input pin goes from LOW to HIGH (e.g. because of a push-button
  press), the output pin is toggled from LOW to HIGH or HIGH to LOW. There's a
  minimum delay between toggles to debounce the circuit (i.e. to ignore noise).
*/

// constants won't change. They're used here to set pin numbers:
#define  buttonPin  2   // the number of the pushbutton pin

// Variables will change:
volatile byte ledState = HIGH;       // the current state of the output pin

void setup()
{
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);

    // set initial LED state
    digitalWrite(LED_BUILTIN, ledState);
    attachInterrupt(digitalPinToInterrupt(2), interruption, FALLING);   //Because the button pullup, FALLING makes the interruption instant
}

void loop()
{
    digitalWrite(LED_BUILTIN, ledState);
}

void interruption()
{
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    // If interrupts come faster than 200ms, assume it's a bounce and ignore
    if (interrupt_time - last_interrupt_time > 200)
    {
        Serial.println("Interrupted");
        ledState = !ledState;
        last_interrupt_time = interrupt_time;
    }
}
