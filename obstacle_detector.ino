/*
 * ============================================================
 *  Obstacle Detection Robot
 * ============================================================
 *  Author  : Muhammad Anas (24F-6125)
 *            Muhammad Usman (24F-6118)
 *  Course  : EL1005 - Digital Logic Design Lab
 *  Inst.   : FAST-NUCES, CFD Campus
 *  Date    : 2024
 * ------------------------------------------------------------
 *  Hardware:
 *    - Arduino Uno
 *    - Motor Driver Shield (L293D based)
 *    - HC-SR04 Ultrasonic Sensor
 *    - Servo Motor (for sensor scanning)
 *    - 4x TT Gear Motors
 *    - 2x 18650 Li-ion Battery
 * ============================================================
 */

#include <Servo.h>

// ── Pin Definitions ────────────────────────────────────────
// Ultrasonic Sensor
#define TRIG_PIN     A0
#define ECHO_PIN     A1

// Motor Driver Shield — Motor A (Left Motors)
#define MOTOR_A_EN    5   // PWM speed control
#define MOTOR_A_IN1   2
#define MOTOR_A_IN2   4

// Motor Driver Shield — Motor B (Right Motors)
#define MOTOR_B_EN    6   // PWM speed control
#define MOTOR_B_IN1   7
#define MOTOR_B_IN2   8

// Servo
#define SERVO_PIN     9

// ── Constants ──────────────────────────────────────────────
#define SAFE_DISTANCE    20    // cm — minimum safe distance
#define MOTOR_SPEED     180    // 0–255
#define TURN_SPEED      150
#define TURN_DELAY      400    // ms for turning

Servo scanServo;

// ── Setup ──────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);

  // Ultrasonic
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Motor pins
  pinMode(MOTOR_A_EN,  OUTPUT);
  pinMode(MOTOR_A_IN1, OUTPUT);
  pinMode(MOTOR_A_IN2, OUTPUT);
  pinMode(MOTOR_B_EN,  OUTPUT);
  pinMode(MOTOR_B_IN1, OUTPUT);
  pinMode(MOTOR_B_IN2, OUTPUT);

  // Servo — center position
  scanServo.attach(SERVO_PIN);
  scanServo.write(90);
  delay(500);

  stopMotors();
  Serial.println("Obstacle Detection Robot — Ready");
}

// ── Main Loop ──────────────────────────────────────────────
void loop() {
  long distFront = measureDistance(90);   // look straight

  Serial.print("Front distance: ");
  Serial.print(distFront);
  Serial.println(" cm");

  if (distFront > SAFE_DISTANCE) {
    moveForward();
  } else {
    stopMotors();
    delay(300);

    // Scan left and right to decide which way to turn
    long distLeft  = measureDistance(160);
    delay(300);
    long distRight = measureDistance(20);
    delay(300);

    // Return servo to center
    scanServo.write(90);
    delay(300);

    Serial.print("Left: "); Serial.print(distLeft);
    Serial.print(" cm  |  Right: "); Serial.print(distRight);
    Serial.println(" cm");

    if (distLeft > distRight) {
      turnLeft();
    } else if (distRight > distLeft) {
      turnRight();
    } else {
      // Both sides equally blocked — reverse and turn
      moveBackward();
      delay(400);
      turnRight();
    }
  }
}

// ── Distance Measurement ───────────────────────────────────
long measureDistance(int servoAngle) {
  scanServo.write(servoAngle);
  delay(400);   // let servo settle

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);  // 30ms timeout
  long distance = duration * 0.034 / 2;

  if (distance == 0 || distance > 400) distance = 400;  // clamp out-of-range
  return distance;
}

// ── Motor Control Functions ────────────────────────────────
void moveForward() {
  analogWrite(MOTOR_A_EN, MOTOR_SPEED);
  analogWrite(MOTOR_B_EN, MOTOR_SPEED);

  // Left motors forward
  digitalWrite(MOTOR_A_IN1, HIGH);
  digitalWrite(MOTOR_A_IN2, LOW);

  // Right motors forward
  digitalWrite(MOTOR_B_IN1, HIGH);
  digitalWrite(MOTOR_B_IN2, LOW);
}

void moveBackward() {
  analogWrite(MOTOR_A_EN, MOTOR_SPEED);
  analogWrite(MOTOR_B_EN, MOTOR_SPEED);

  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, HIGH);

  digitalWrite(MOTOR_B_IN1, LOW);
  digitalWrite(MOTOR_B_IN2, HIGH);

  delay(400);
}

void turnLeft() {
  analogWrite(MOTOR_A_EN, TURN_SPEED);
  analogWrite(MOTOR_B_EN, TURN_SPEED);

  // Left motors backward, right motors forward
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, HIGH);

  digitalWrite(MOTOR_B_IN1, HIGH);
  digitalWrite(MOTOR_B_IN2, LOW);

  delay(TURN_DELAY);
  stopMotors();
}

void turnRight() {
  analogWrite(MOTOR_A_EN, TURN_SPEED);
  analogWrite(MOTOR_B_EN, TURN_SPEED);

  // Left motors forward, right motors backward
  digitalWrite(MOTOR_A_IN1, HIGH);
  digitalWrite(MOTOR_A_IN2, LOW);

  digitalWrite(MOTOR_B_IN1, LOW);
  digitalWrite(MOTOR_B_IN2, HIGH);

  delay(TURN_DELAY);
  stopMotors();
}

void stopMotors() {
  analogWrite(MOTOR_A_EN, 0);
  analogWrite(MOTOR_B_EN, 0);

  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, LOW);
  digitalWrite(MOTOR_B_IN1, LOW);
  digitalWrite(MOTOR_B_IN2, LOW);
}
