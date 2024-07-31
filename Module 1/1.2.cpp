// Define pin numbers
const int motionSensorPin = 2;  // Digital pin connected to PIR motion sensor
const int ledPin1 = 10;         // Digital pin connected to LED 1
const int ledPin2 = 11;         // Digital pin connected to LED 2
const int ledPin3 = 13;         // Digital pin connected to LED 3

// Variable to store the motion state
volatile int motionState = LOW;

void setup() {
  // Initialize the digital pin as an input for the motion sensor
  pinMode(motionSensorPin, INPUT);
  
  // Initialize the digital pins as outputs for the LEDs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  
  // Start the Serial communication to print data to the Serial Monitor
  Serial.begin(9600);
  
  // Attach the interrupt to the motion sensor pin
  // Trigger the ISR on CHANGE (both HIGH and LOW transitions)
  attachInterrupt(digitalPinToInterrupt(motionSensorPin), motionISR, CHANGE);
}

void loop() {
  // Print the motion sensor state to the Serial Monitor
  Serial.print("Motion Sensor State: ");
  Serial.println(motionState);
  
  // Control the LEDs based on motion state
  if (motionState == HIGH) {
    // Motion detected, turn all LEDs ON
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
  } else {
    // No motion detected, turn all LEDs OFF
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
  }
}

// Interrupt Service Routine for motion sensor
void motionISR() {
  // Update the motion state variable
  motionState = digitalRead(motionSensorPin);
}