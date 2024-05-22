#include <Servo.h>

const int trigPin = 10;
const int echoPin = 11;
const int buzzerPin = 9;
const int redPin = 6;    // Red LED pin
const int greenPin = 5;  // Green LED pin
const int bluePin = 3;   // Blue LED pin

long duration;
int distance;
Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
  myServo.attach(12);
}

void loop() {
  for (int i = 15; i <= 165; i++) {
    myServo.write(i);
    delay(30);
    distance = calculateDistance();

    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");

    if (distance < 30) {
      // If object is detected within 20 cm, sound the buzzer and turn LED to red
      digitalWrite(buzzerPin, HIGH);
      setColor(255, 0, 0);  // Red
    } else {
      // If no object is detected, turn off the buzzer and turn LED to green
      digitalWrite(buzzerPin, LOW);
      setColor(0, 255, 0);  // Green
    }
  }

  for (int i = 165; i > 15; i--) {
    myServo.write(i);
    delay(30);
    distance = calculateDistance();

    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");

    if (distance < 30) {
      // If object is detected within 20 cm, sound the buzzer and turn LED to red
      digitalWrite(buzzerPin, HIGH);
      setColor(255, 0, 0);  // Red
    } else {
      // If no object is detected, turn off the buzzer and turn LED to green
      digitalWrite(buzzerPin, LOW);
      setColor(0, 255, 0);  // Green
    }
  }
}

int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

