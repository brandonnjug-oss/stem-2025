// Pin assignments
const int mq2Pin   = A0;    // MQ-2 analog output
const int ledPin   = 12;    // LED
const int buzzerPin = 13;   // Active buzzer

// Gas detection threshold (adjust after testing)
int threshold = 250;    // analog value, range 0–1023

unsigned long lastAlarmToggle = 0;    //tracks the last time the buzzer and LED were toggled

unsigned long lastReport = 0;   //tracks the last time a value of the gas reading was sent to the computer

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);  // for monitoring readings
}

void loop() {
  int gasValue = analogRead(mq2Pin);  // read gas level

  if (gasValue > threshold) {
    if (millis() - lastAlarmToggle >= 200) {              // causes toggle every 200ms
      digitalWrite(ledPin, !digitalRead(ledPin));         // LED toggle
      digitalWrite(buzzerPin, !digitalRead(buzzerPin));   // Buzzer toggle
      lastAlarmToggle = millis();                         // sets the lastAlarmToggle to the program run time
      gasValue = analogRead(mq2Pin);                      // read gas level
    }
  } else {
    digitalWrite(ledPin, LOW);    // LED OFF
    digitalWrite(buzzerPin, LOW);  // Buzzer OFF
  }

  if (millis() - lastReport >= 200) {   // causes the reading every 200ms
    Serial.print("Gas value:");          
    Serial.println(gasValue);            // these 2 lines send the gas value eto the computer
    lastReport = millis();               // sets the last report time to the program run time
  }
}
