// Define pin numbers
const int motionSensorPin = 2; // Digital pin connected to PIR motion sensor
const int ledPin1 = 10; // Digital pin connected to LED 1
const int ledPin2 = 11; // Digital pin connected to LED 2
const int ledPin3 = 13; // Digital pin connected to LED 3
const int ldrPin = 3; // Digital pin connected to photoresistor (LDR)

// Threshold for photoresistor to be considered "activated"
const int ldrThreshold = 100; // Adjust this value as needed

// Variables to store states
volatile int motionState = LOW;
int ldrState = LOW; // Assuming LOW means not activated

void setup() {
  // Initialize the digital pin as an input for the motion sensor
  pinMode(motionSensorPin, INPUT);
  pinMode(ldrPin, INPUT); // Initialize digital pin for LDR

  // Initialize the digital pins as outputs for the LEDs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  // Start the Serial communication to print data to the Serial Monitor
  Serial.begin(9600);

  // Attach the interrupt to the motion sensor pin
  // Trigger the ISR on CHANGE (both HIGH and LOW transitions)
  attachInterrupt(digitalPinToInterrupt(motionSensorPin), motionISR, CHANGE);

  // Attach the interrupt to the LDR pin
  // Note: LDR reading might not need an interrupt if it's just HIGH/LOW
  attachInterrupt(digitalPinToInterrupt(ldrPin), ldrISR, CHANGE);
}

void loop() {
  // Read the photoresistor value directly
  ldrState = digitalRead(ldrPin);

  // Print the motion sensor state and photoresistor state to the Serial Monitor
  Serial.print("Motion Sensor State: ");
  Serial.println(motionState);
  Serial.print("Photoresistor State: ");
  Serial.println(ldrState);

  // Check if either the motion sensor detected motion or the photoresistor is activated
  if (motionState == HIGH || ldrState == HIGH) {
    // Motion detected or photoresistor activated, adjust LED brightness
    int brightness = (ldrState == HIGH) ? 255 : 255; // Set brightness to 255 if any state is HIGH
    analogWrite(ledPin1, brightness);
    analogWrite(ledPin2, brightness);
    analogWrite(ledPin3, brightness);
  } else {
    // No motion detected and photoresistor not activated, turn all LEDs OFF
    analogWrite(ledPin1, 0);
    analogWrite(ledPin2, 0);
    analogWrite(ledPin3, 0);
  }

  delay(100); // Short delay for stability
}

// Interrupt Service Routine for motion sensor
void motionISR() {
  // Update the motion state variable
  motionState = digitalRead(motionSensorPin);
}

// Interrupt Service Routine for photoresistor threshold
void ldrISR() {
  // Update the LDR state variable
  ldrState = digitalRead(ldrPin);
}