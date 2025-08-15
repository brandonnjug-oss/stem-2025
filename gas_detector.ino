// Pin assignments
const int mq2Pin   = A0;   // MQ-2 analog output
const int ledPin   = 12;   // LED
const int buzzerPin = 13;  // Active buzzer

// Gas detection threshold (adjust after testing)
int threshold = 250;  // analog value, range 0–1023
unsigned long levelStart = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  int gasValue = analogRead(mq2Pin);  // Read gas level

  if (gasValue > threshold) {
    if (millis() - levelStart >= 200) { //causes screen refresh every 200ms
      digitalWrite(ledPin, !digitalRead(ledPin));   // LED FLASH
      digitalWrite(buzzerPin, !digitalRead(buzzerPin)); // Buzzer FLASH
      levelStart = millis();
      gasValue = analogRead(mq2Pin);
    }
  } else {
    digitalWrite(ledPin, LOW);    // LED OFF
    digitalWrite(buzzerPin, LOW);  // Buzzer OFF
  }
}