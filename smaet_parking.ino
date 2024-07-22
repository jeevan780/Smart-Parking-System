#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;

#define sensorpin 7
//#define LED2 13
#define trigPin 8
#define echoPin 9
#define distance_threshold 10
#define RS 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

int val;
int i = 0;
int amount;

unsigned long startTime = 0;
unsigned long elapsedTime = 0;
bool counting = false;

void setup() {
  myservo.attach(10);
  pinMode(sensorpin, INPUT);
  lcd.begin(16, 2);
  lcd.print("amount:");
  lcd.setCursor(0, 1);
  lcd.print("Time: 0 sec");
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  //pinMode(LED2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(sensorpin);

  if (val == 0) {
    i = 100;
    myservo.write(i);
    delay(1800);
  } else {
    i = 0;
  }
  myservo.write(i);

  int duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0344) / 2;

  //lcd.setCursor(10, 0);
  //lcd.print(distance);
  //lcd.print(" cm  ");

  if (distance <= distance_threshold) {
    if (!counting) {
      counting = true;
      startTime = millis();
    }
    elapsedTime = (millis() - startTime) / 1000;
    amount = elapsedTime * 0.008333;
    lcd.setCursor(10, 0);
    lcd.print(amount);
    lcd.print("rupees");
    //digitalWrite(LED2, HIGH);
  } else {
    if (counting) {
      counting = false;
      Serial.print("Total time: ");
      Serial.print(elapsedTime);
      Serial.println(" seconds");
      elapsedTime = 0; 
    }
    Serial.println("LED off");
    Serial.print(distance);
    Serial.println(" cm");
    //digitalWrite(LED2, LOW);
  }

  lcd.setCursor(6, 1);
  lcd.print(elapsedTime);
  lcd.print(" sec  ");
  delay(50);
}
