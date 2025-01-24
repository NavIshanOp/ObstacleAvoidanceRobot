#include <Servo.h>

// Pin definitions
#define TRIG_PIN 9
#define ECHO_PIN 10
#define ENA 2
#define IN1 3
#define IN2 4
#define IN3 5
#define IN4 6
#define ENB 7
#define SERVO_PIN 8

// Variables
Servo servo;
int distanceLeft = 0;
int distanceRight = 0;
int distanceFront = 0;

void setup() {
  Serial.begin(9600);
  
  // Set up motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  // Set up sonar sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Attach servo
  servo.attach(SERVO_PIN);
  servo.write(90); // Start with servo at the center
  
  Serial.println("Obstacle Avoidance Robot Initialized");
}

void loop() {
  // Check front distance
  distanceFront = getDistance();
  Serial.print("Front Distance: ");
  Serial.println(distanceFront);
  
  if (distanceFront < 20) {
    Serial.println("Obstacle detected! Stopping motors.");
    stopMotors();
    
    // Check left and right distances
    distanceLeft = checkSideDistance(150); // Look left
    distanceRight = checkSideDistance(30); // Look right
    
    if (distanceLeft > distanceRight) {
      Serial.println("Turning left...");
      turnLeft();
    } else {
      Serial.println("Turning right...");
      turnRight();
    }
  } else {
    Serial.println("Path is clear. Moving forward.");
    moveForward();
  }
  delay(100); // Short delay to avoid overwhelming the servo
}

// Function to measure distance using HC-SR04
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2; // Convert to cm
  return distance;
}

// Function to check side distance
int checkSideDistance(int angle) {
  servo.write(angle);
  delay(500); // Wait for servo to reach the position
  int distance = getDistance();
  Serial.print("Distance at angle ");
  Serial.print(angle);
  Serial.print(": ");
  Serial.println(distance);
  servo.write(90); // Reset servo to center
  return distance;
}

// Function to move forward
void moveForward() {
  analogWrite(ENA, 150); // Adjust speed if necessary
  analogWrite(ENB, 150);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Function to turn left
void turnLeft() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(500); // Adjust timing for a proper turn
  stopMotors();
}

// Function to turn right
void turnRight() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(500); // Adjust timing for a proper turn
  stopMotors();
}

// Function to stop motors
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  delay(500); // Pause for stability
}
