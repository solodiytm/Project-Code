#include <Servo.h>

#define IR_PIN D1
#define SERVO_PIN D4

Servo myServo;

void setup() {
  pinMode(IR_PIN, INPUT);
  myServo.attach(SERVO_PIN);
  myServo.write(0);  // Tap initially OFF
}

void loop() {
  int irState = digitalRead(IR_PIN);

  if (irState == LOW) { // Object detected
    myServo.write(180); // Rotate to open tap
    delay(100); 
  } else {
    myServo.write(0); // Rotate back to close tap
    delay(100);
  }
}