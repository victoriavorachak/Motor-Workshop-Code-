#include <Servo.h>

Servo myservo1; // Position servo
Servo myservo2; // Continuous rotation servo

void setup() {
  Serial.begin(9600);

  // Attached pin 11 to the position servo and pin 9 to the rotation servo
  myservo1.attach(11);
  myservo2.attach(9);

  Serial.println("Enter 'P' followed by angle (0-180) for position servo");
  Serial.println("Enter 'R' followed by speed (-100 to 100) for rotation servo");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim(); 

    // Position Servo Input
    if (input.startsWith("P") || input.startsWith("p")) {
      int angle = input.substring(1).toInt();
      posServo(angle);
    }

    // Rotation Servo Input
    if (input.startsWith("R") || input.startsWith("r")) {
      int speed = input.substring(1).toInt();
      rotServo(speed);
    }
  }

// === Part 1(a): Position Servo ===
void posServo(int angle) {
  if (angle >= 0 && angle <= 180) {
    myservo1.write(angle);
    Serial.print("Moved to angle: ");
    Serial.println(angle);
  } else {
    Serial.println("Invalid angle. Please enter 0–180.");
  }
}

// === Part 1(b): Continuous Rotation Servo ===
void rotServo(int percentage) {
  percentage = constrain(percentage, -100, 100); // Clamp input

  // Map -100 to 100 → Servo write values: 0 (full reverse) to 180 (full forward)
  int servoSpeed = map(percentage, -100, 100, 0, 180);
  myservo2.write(servoSpeed);

  Serial.print("Rotation speed set to: ");
  Serial.print(percentage);
  Serial.println("%");
}
