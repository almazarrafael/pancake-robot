/* TODO: 
- adjust spinTime in order to get 90 degree turn
- check if trig and echo pins are correct
*/

#include <AFMotor.h>
AF_DCMotor R_motor(4);
AF_DCMotor L_motor(1);

// Parameters
int distanceThreshold = 10; // cm
int spinTime = 250;
int countMax = 5;

const int seconds = 1000; // mS -> S
int count = 0;

// Left sonar
int cm_distanceL = 0;
const int trigL = A0;
const int echoL = A1;

// Center sonar
int cm_distanceC = 0;
const int trigC = A2;
const int echoC = A3;

// Right sonar
int cm_distanceR = 0;
const int trigR = A4;
const int echoR = A5;



void setup() {
  Serial.begin(9600);

  // Motor setup
  L_motor.setSpeed(200);
  R_motor.setSpeed(200);
  L_motor.run(RELEASE);
  R_motor.run(RELEASE);

  // Sonar setup
  pinMode(trigC, OUTPUT);
  pinMode(echoC, INPUT);
  
  pinMode(trigL, OUTPUT);
  pinMode(echoL, INPUT);
  
  pinMode(trigR, OUTPUT);
  pinMode(echoR, INPUT);
}
void loop() {

  cm_distanceC = distance(trigC, echoC);
  cm_distanceL = distance(trigL, echoL);
  cm_distanceR = distance(trigR, echoR);

  Serial.print("C: "); Serial.println(cm_distanceC);
  Serial.print("L: "); Serial.println(cm_distanceL);
  Serial.print("R: "); Serial.println(cm_distanceR);
  Serial.println();
  
  if (cm_distanceC < distanceThreshold) {
    stopMotors();
    delay(500);
    backward(1*seconds);
    delay(500);
    if (cm_distanceL > cm_distanceR) {
      spinClockwise(spinTime);
    }
    else {
      spinClockwise(spinTime);
    }
  }
  else if (cm_distanceL < distanceThreshold) {
    stopMotors();
    delay(500);
    backward(500);
    delay(500);
    spinClockwise(spinTime);
  }
  else if (cm_distanceR < distanceThreshold) {
    stopMotors();
    delay(500);
    backward(1*seconds);
    delay(500);
    spinCounterClockwise(spinTime);
  }
  else {
    /*
    if (count < countMax) {
      forwardIndefinite();
    }
    else {
      count = 0;
      spinClockwise(random(1400));
    }
    */
    forwardIndefinite();
  }
  
  count++;
}

int distance(int trigPin, int echoPin) {
  long duration;
  int distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034/2;
  return distance;
}

void forwardIndefinite () {
  L_motor.run(FORWARD);
  R_motor.run(FORWARD);
}

void backwardIndefinite () {
  L_motor.run(BACKWARD);
  R_motor.run(BACKWARD);
}

void stopMotors () {
  L_motor.run(RELEASE);
  R_motor.run(RELEASE);
}

void forward (int time) {
  L_motor.run(FORWARD);
  R_motor.run(FORWARD);
  delay(time);
  L_motor.run(RELEASE);
  R_motor.run(RELEASE);
}

void backward (int time) {
  L_motor.run(BACKWARD);
  R_motor.run(BACKWARD);
  delay(time);
  L_motor.run(RELEASE);
  R_motor.run(RELEASE);
}

void spinClockwise (int time) {
  L_motor.run(FORWARD);
  R_motor.run(BACKWARD);
  delay(time);
  L_motor.run(RELEASE);
  R_motor.run(RELEASE);
}

void spinCounterClockwise (int time) {
  L_motor.run(BACKWARD);
  R_motor.run(FORWARD);
  delay(time);
  L_motor.run(RELEASE);
  R_motor.run(RELEASE);
}
