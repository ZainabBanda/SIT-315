// Define pin numbers
const int motionSensorPin = 2; // Digital pin connected to PIR motion sensor
const int ldrPin = 3;          // Digital pin connected to photoresistor (LDR)
const int potPin = A0;         // Analog pin connected to potentiometer
const int ledPin1 = 10;        // Digital pin connected to LED 1
const int ledPin2 = 11;        // Digital pin connected to LED 2
const int ledPin3 = 13;        // Digital pin connected to LED 3

// Threshold for potentiometer to be considered "activated"
const int potThreshold = 512; // Adjust this value as needed (0-1023 range)

// Variables to store states
volatile int motionState = LOW;
volatile int ldrState = LOW; // Assuming LOW means not activated
int potValue = 0;  // Potentiometer value

// Timer variables
volatile bool timerFlag = false;
unsigned long previousMillis = 0; // Store last time LED was updated
const long interval = 500; // Interval for the timer interrupt (in milliseconds)

void setup() {
  // Initialize pins
  pinMode(motionSensorPin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  // Start Serial communication
  Serial.begin(9600);

  // Attach the interrupt for motion sensor
  attachInterrupt(digitalPinToInterrupt(motionSensorPin), motionISR, CHANGE);

  // Set up Pin Change Interrupt for LDR pin
  PCICR |= (1 << PCIE2); // Enable Pin Change Interrupts for PCINT[23:16]
  PCMSK2 |= (1 << PCINT19); // Enable Pin Change Interrupt for pin 3 (PCINT19)
}

void loop() {
  // Read the potentiometer value
  potValue = analogRead(potPin);

  // Print states to Serial Monitor
  Serial.print("Motion Sensor State: ");
  Serial.println(motionState);
  Serial.print("Photoresistor State: ");
  Serial.println(ldrState);
  Serial.print("Potentiometer Value: ");
  Serial.println(potValue);

  // Check if any sensor is activated
  if (motionState == HIGH || ldrState == HIGH || potValue > potThreshold) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
  } else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
  }

  // Timer interrupt logic
  if (millis() - previousMillis >= interval) {
    previousMillis = millis();
    timerFlag = true; // Set timer flag to true
  }

  // Check if timer flag is set
  if (timerFlag) {
    timerFlag = false; // Reset the flag
    // Do something in response to the timer interrupt
    digitalWrite(ledPin1, !digitalRead(ledPin1)); // Toggle LED1
    Serial.println("Timer interrupt occurred: LED1 state toggled"); // Print to Serial Monitor
  }

  delay(100); // Short delay for stability
}

// Interrupt Service Routine for motion sensor
void motionISR() {
  // Update the motion state variable
  motionState = digitalRead(motionSensorPin);
}

// Pin Change Interrupt Service Routine for LDR
ISR(PCINT2_vect) {
  ldrState = digitalRead(ldrPin); // Update LDR state
}