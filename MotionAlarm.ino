int pirPin = 2;      // PIR sensor output pin
int buzzer = 12;     // Buzzer pin
int motionState = LOW;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  motionState = digitalRead(pirPin);

  if (motionState == HIGH) {
    Serial.println("Motion Detected!");

    // Beep twice for 100ms
    for (int i = 0; i < 8; i++) {
      //digitalWrite(buzzer, HIGH); // buzzer on
      digitalWrite(13, HIGH);     // light on
      delay(100);                  // 100 ms
      //digitalWrite(buzzer, LOW);  // buzzer off
      digitalWrite(13, LOW);      // light off
      delay(150);                  // pause between beeps;  
    }
    delay(300); // 0.3 second pause before checking again
  }
}