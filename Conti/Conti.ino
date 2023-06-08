#define LeftButton 2
#define RightButton 3
#define LeftLed 4
#define RightLed 5
#define BreakLed 6
#define Trigger 8
#define Echo 9
#define PedalPWM A5
#define Frequency 500
#define StandFrequency 1000
#define FALSE 0
#define TRUE 1
#define TIMEOUT 2000
#define LIMIT 21600
#define DISTANCE_DIVIDER 58
#define CYCLE_TIME 60 // ultrahang mérési idő
#define TRIGGER_PULSE_WIDTH 11
#define RANGE_LIMIT (100 * 58)
#define NUMBER_OF_PERIODIC_TASKS 2

//Gombok és Ledek
int LeftButtonState = 0;
int RightButtonState = 0;
byte First_EdgeCaughtLeft;
byte First_EdgeCaughtRight;
unsigned long TimeStampLeft;
unsigned long TimeStampRight;
byte Previous_StateLeft;
byte Actual_StateLeft;
byte Previous_StateRight;
byte Actual_StateRight;
boolean Starter_Exiter_Right = FALSE;
boolean Starter_Exiter_Left = FALSE;

// Feladat kezelő
bool Index_enabled = false;
byte IndexPin = 1;
byte blinkingState;
bool isDoublePush = false;

// Ultrahang szenzor
byte Actual_Level = LOW;
byte Previous_Level = LOW;
unsigned long TimeStamp;
byte Measurement_Running = FALSE;
byte Sensor_Triggered = FALSE;

void InterruptRED()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200)
  {
    Serial.println("Interrupted by Red button");
    if (Index_enabled == true && IndexPin == LeftLed || isDoublePush == true)
    {
      Index_enabled = false;
    }
    else
    {
      Index_enabled = true;
    }
    IndexPin = LeftLed;
    last_interrupt_time = interrupt_time;
    delay(50);
    if (digitalRead(RightButton) == HIGH)
    {
      isDoublePush = !isDoublePush;
    }
  }
}
void InterruptBLUE()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200)
  {
    Serial.println("Interrupted by Blue button");
    if (Index_enabled == true && IndexPin == RightLed || isDoublePush == true)
    {
      Index_enabled = false;
    }
    else
    {
      Index_enabled = true;
    }
    IndexPin = RightLed;
    last_interrupt_time = interrupt_time;
    delay(50);
    if (digitalRead(LeftButton) == HIGH)
    {
      isDoublePush = !isDoublePush;
    }
  }
}

void setup()
{
  pinMode(LeftLed, OUTPUT);
  pinMode(RightLed, OUTPUT);
  pinMode(BreakLed, OUTPUT);
  pinMode(LeftButton, INPUT);
  pinMode(RightButton, INPUT);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);     // ultrahang
  pinMode(PedalPWM, INPUT); // Signal    // also érték 90 - felső érték 887
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(LeftButton), InterruptRED, FALLING);
  attachInterrupt(digitalPinToInterrupt(RightButton), InterruptBLUE, FALLING);

  digitalWrite(LeftLed, HIGH);
  digitalWrite(RightLed, HIGH);
}

void loop()
{
  Emergency();
  Index_blinking(Index_enabled, IndexPin);
  Brake_Blinking(blinkingState);
  PedalAngelNum();

  //Read Pedal_angle() with   timedAction.check();
  // Read UltraS_distance() with   timedAction.check();
}

unsigned int PedalAngelInterface()
{

  unsigned int ADC_value;
  unsigned long int cumulative = 0;
  unsigned int num;

  for (num = 0; num < 50; num++)
  { //155 volt
    ADC_value = analogRead(PedalPWM);
    cumulative += ADC_value;
  }

  ADC_value = cumulative / 50; // also érték 0 - felső érték 5 korrrekció után
  return ADC_value;
}

void PedalAngelNum()
{
  int ADC_value_AVG = 900;
  unsigned int ADC_value = PedalAngelInterface();
  unsigned int UltraSound_Distance = UltraSoundInterface();

  if (ADC_value > ADC_value_AVG * 0.7 || (UltraSound_Distance > 0 && UltraSound_Distance < 41))
  {
    blinkingState = 3; //4Hz blinking
  }
  if ((ADC_value > ADC_value_AVG * 0.5 && ADC_value < ADC_value_AVG * 0.7) || (UltraSound_Distance > 40 && UltraSound_Distance < 81))
  {
    blinkingState = 2; //2Hz blinking
  }
  if ((ADC_value > ADC_value_AVG * 0.2 && ADC_value < ADC_value_AVG * 0.5) || (UltraSound_Distance > 80 && UltraSound_Distance < 121))
  {
    blinkingState = 1; //Light up
  }
  if (ADC_value <= ADC_value_AVG * 0.2 || UltraSound_Distance > 121)
  {
    blinkingState = 0; //Light down
  }
}

unsigned int UltraSoundInterface()
{
  unsigned long Echo_Time = 0, Pulse_Width = 0;
  byte Measurement_Error;

  digitalWrite(Echo, LOW);
  digitalWrite(Trigger, LOW);
  delay(CYCLE_TIME);

  TriggerUltraSound();
  Measure_Echo(&Echo_Time, &Pulse_Width, &Measurement_Error);
  // pulseIn(pin, value, timeout);
  unsigned int Distance = Pulse_Width / DISTANCE_DIVIDER;
  // Serial.println(Distance , DEC);
  return Distance;
}

void TriggerUltraSound(void)
{
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(TRIGGER_PULSE_WIDTH);
  digitalWrite(Trigger, LOW);
}

void Measure_Echo(unsigned long *P_Echo_Time, unsigned long *P_Value, byte *P_Error)
{
  unsigned long Length_Of_Echo_Pulse = 0;
  unsigned long Time_Stamp;
  byte Previous_Echo_State = FALSE;
  byte Actual_Echo_State = FALSE;

  *P_Error = TRUE;

  Time_Stamp = micros();

  while (micros() - Time_Stamp <= RANGE_LIMIT)
  {
    Actual_Echo_State = digitalRead(Echo);

    if ((Previous_Echo_State == LOW) && (Actual_Echo_State == HIGH))
    {
      *P_Echo_Time = micros() - Time_Stamp;
      Time_Stamp = micros();
    }
    else if ((Previous_Echo_State == HIGH) && (Actual_Echo_State == LOW))
    {
      Length_Of_Echo_Pulse = micros() - Time_Stamp;
      *P_Value = Length_Of_Echo_Pulse;
      *P_Error = FALSE;
      break;
    }

    Previous_Echo_State = Actual_Echo_State;
  }
}

void Index_blinking(bool isEnable, byte in_IndexPin)
{
  if (isEnable == true)
  {
    digitalWrite(in_IndexPin, LOW);
    delay(Frequency);
    digitalWrite(in_IndexPin, HIGH);
    delay(Frequency);
  }
}

void Brake_Blinking(byte in_blinkingState)
{
  switch (in_blinkingState)
  {
  case 0:
    digitalWrite(BreakLed, HIGH);
    break;

  case 1:
    digitalWrite(BreakLed, LOW);
    break;

  case 2:
    digitalWrite(BreakLed, LOW);
    delay(Frequency);
    digitalWrite(BreakLed, HIGH);
    delay(Frequency);
    break;

  case 3:
    digitalWrite(BreakLed, LOW);
    delay(Frequency/2);
    digitalWrite(BreakLed, HIGH);
    delay(Frequency/2);
    break;

  default:
    Serial.println("Error: wrong blinkingState value");
    break;
  }
}

void Emergency()
{
  if (isDoublePush == true)
  {
    digitalWrite(LeftLed, LOW);
    digitalWrite(RightLed, LOW);
    delay(Frequency);
    digitalWrite(LeftLed, HIGH);
    digitalWrite(RightLed, HIGH);
    delay(Frequency);
  }
}
