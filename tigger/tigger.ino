
int driveA= 8;
int driveB =7;
int speedpin = 6;
int left = A0;
int right = A1;


#include <DistanceGP2Y0A21YK.h>
DistanceGP2Y0A21YK Left;
DistanceGP2Y0A21YK Right;
int distance;


#include <Servo.h> 
Servo myservo;

int pos = 180;

void setup() {
  pinMode(driveA, OUTPUT);
  pinMode(driveB, OUTPUT);
  analogWrite(speedpin, LOW);
  Left.begin(left);
  Right.begin(right);
  myservo.attach(3);
  Serial.begin(9600);

}


void loop() {

    if (Left.getDistanceCentimeter() < 12 || Right.getDistanceCentimeter() < 12) {
      reverse(85);
    } else {
      forward(60);
    }
    dir();

}

//-255 - 255
void dir() {
  int pos, servopos =0;
  if ( Left.getDistanceCentimeter() > Right.getDistanceCentimeter() ) {
    pos = -255;

  } else if(Left.getDistanceCentimeter() < Right.getDistanceCentimeter()) {
    pos = 255;
  } else {
    pos = 0;
  }
  if (Left.getDistanceCentimeter() < 12 || Right.getDistanceCentimeter() < 12) {
   servopos = map(pos, 255,-255, 70,102);
  } else {
    servopos = map(pos, -255,255, 70,102);
  }
  myservo.write(servopos);
  //Serial.println(servopos);
}

void forward(int speed) {
  digitalWrite(driveA, HIGH);
  digitalWrite(driveB, LOW);
  analogWrite(speedpin, speed);
}

void reverse(int speed) {
  digitalWrite(driveA, LOW);
  digitalWrite(driveB, HIGH);
  analogWrite(speedpin, speed);
}

void stop() {
  digitalWrite(driveA, LOW);
  digitalWrite(driveB, LOW);
  analogWrite(speedpin, 0);
}

