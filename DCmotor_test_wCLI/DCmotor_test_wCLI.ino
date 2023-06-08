// Include the SerialCommand library
#include <SerialCommand.h>

// Create a SerialCommand object
SerialCommand cmd;

// Define the pins used to control the motor
const int motorPin1 = 9;
const int motorPin2 = 10;

// Setup function - runs once on startup
void setup()
{
  // Start serial communication at a baud rate of 9600
  Serial.begin(9600);

  // Set the motor pins to output mode
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  // Add the "speed" command and its handler function to the SerialCommand object
  cmd.addCommand("speed", setSpeed);

  // Set the default handler function for unrecognized commands
  cmd.setDefaultHandler(unrecognized);

  // Send a message to the serial port to indicate that the code is ready
  Serial.println("Ready");
}

// Loop function - runs continuously after setup
void loop()
{
  // Read the serial port for incoming commands
  cmd.readSerial();
}

// Handler function for the "speed" command
void setSpeed()
{
  // Initialize the speed variable to 0
  int speed = 0;

  // Get the next argument passed with the command
  char *arg = cmd.next();

  // If an argument is present, convert it to an integer and set the motor speed
  if (arg != NULL)
  {
    speed = atoi(arg); // Convert the argument to an integer
    analogWrite(motorPin1, speed); // Set the motor speed
    Serial.print("Speed set to: ");
    Serial.println(speed); // Send a message to the serial port
  }
  else
  {
    // If no argument is present, send an error message to the serial port
    Serial.println("error: No argument");
  }
}

// Default handler function for unrecognized commands
void unrecognized(const char *command)
{
  // Send an error message to the serial port indicating that the command is unknown
  Serial.print("error: Unknown command: ");
  Serial.println(command);
}
