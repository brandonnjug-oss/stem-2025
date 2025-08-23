/*
    A
   ---
F |   | B
  | G |
   ---
E |   | C
  |   |
   ---  . dec
    D

d1 - d4 is for digits 1 - 4
*/

//definition of pins for the screen
const int a = 2;
const int b = 6;
const int c = 9;
const int d = 8;
const int e = 7;
const int f = 3;
const int g = 10; 

const int d1 =1;
const int d2 =4;
const int d3 =5;
const int d4 =11;

//definition of other pins
const int mq2Pin   = A0;    //MQ-2 analog output
const int ledPin   = 12;    //LED
const int buzzerPin = 13;   //active buzzer

//setting the thresholds, analogue value range 0-1023
int warningThreshold = 250;   //the value at or above which the warning sequence is activated
int urgentThreshold = 450;    //the value at or above which the urgent sequence is activated

int gasValue = 0;   //the value that comes from the MQ-2 sensor, used to activate the buzzer and LED

//defining the values used for display updating
int displayGasValue = 0;                //the number shown on the display
unsigned long lastDisplayUpdate = 0;    //tracks the last time the display was updated

unsigned long lastAlarmToggle = 0;      //tracks the last time the buzzer and/or led was toggled

void setup()
{
  //defines the digital pins as output
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}
 
void loop()
{

  gasValue = analogRead(mq2Pin);    //sets the gasValue to the reading from the MQ-2 sensor

  if (gasValue > warningThreshold) {
    if (gasValue > urgentThreshold) {
      if (millis() - lastAlarmToggle >= 100) {              //causes the toggle to be every 100ms
        digitalWrite(ledPin, !digitalRead(ledPin));         //toggles the LED on/off
        digitalWrite(buzzerPin, HIGH);                      //turns the buzzer on
        lastAlarmToggle = millis();                         //sets the lastAlarmToggle to the current program run time
      }
    } else {
      if (millis() - lastAlarmToggle >= 500) {              //causes the toggle to be every 500ms
        digitalWrite(ledPin, !digitalRead(ledPin));         //toggles the LED on/off
        digitalWrite(buzzerPin, !digitalRead(buzzerPin));   //toggles the buzzer on/off
        lastAlarmToggle = millis();                         //sets the lastAlarmToggle to the current program run time
      }
    }
  } else {
    digitalWrite(ledPin, LOW);      //turns the LED off
    digitalWrite(buzzerPin, LOW);   //turns the buzzer off
  }

  if (millis() - lastDisplayUpdate >= 200) {    //causes screen refresh every 200ms
    lastDisplayUpdate = millis();               //sets the lastDisplayUpdate to the current program run time
    displayGasValue = analogRead(mq2Pin);       //sets the displayGasValue to the reading from the MQ-2 sensor
  }
  
  //selects which number each digit of the screen should show
  clearLEDs();
  pickDigit(1);                             //picks the first digit on the display
  pickNumber((displayGasValue/1000)%10);    //picks the forth digit of the number from the right
  delayMicroseconds(55);                    //waits 55 microseconds before showing the next digit
 
  clearLEDs();
  pickDigit(2);                             //picks the second digit on the display
  pickNumber((displayGasValue/100)%10);     //picks the third digit of the number from the right
  delayMicroseconds(55);                    //waits 55 microseconds before showing the next digit
 
  clearLEDs();
  pickDigit(3);                             //picks the second digit on the display
  pickNumber((displayGasValue/10)%10);      //picks the second digit of the number from the right
  delayMicroseconds(55);                    //waits 55 microseconds before showing the next digit
 
  clearLEDs();
  pickDigit(4);                             //picks the fourth digit on the display
  pickNumber((displayGasValue/1)%10);       //picks the first digit of the number from the right
  delayMicroseconds(55);                    //waits 55 microseconds before showing the next digit
}
 
void pickDigit(int x) //changes digit
{
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);
 
  switch(x)
  {
  case 1: 
    digitalWrite(d1, LOW); 
    break;
  case 2: 
    digitalWrite(d2, LOW); 
    break;
  case 3: 
    digitalWrite(d3, LOW);
    break;
  default: 
    digitalWrite(d4, LOW); 
    break;
  }
}
 
void pickNumber(int x) //changes value of number
{
  switch(x)
  {
  default: 
    zero(); 
    break;
  case 1: 
    one(); 
    break;
  case 2: 
    two(); 
    break;
  case 3: 
    three(); 
    break;
  case 4: 
    four(); 
    break;
  case 5: 
    five(); 
    break;
  case 6: 
    six(); 
    break;
  case 7: 
    seven(); 
    break;
  case 8: 
    eight(); 
    break;
  case 9: 
    nine(); 
    break;
  }
}

//determines how each digit looks
void clearLEDs()
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}
 
void zero()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}
 
void one()
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}
 
void two()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}
 
void three()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}
 
void four()
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
 
void five()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
 
void six()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
 
void seven()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}
 
void eight()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
 
void nine()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
