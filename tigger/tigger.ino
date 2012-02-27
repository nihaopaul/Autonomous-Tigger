/*
  this is my code.. nihaopaul @ gmail o com
  i will use it to win the race :D
  
  this is for 2 ultrasonic sensors mounted left and right front
*/



int trig_f = 12;
int trig_r = 7;
// ultrasonic sensors ping array..

// ultrasonic sensor reply
int rx_f = 13;
int rx_r = 8;


int drivep1 = 10; 
int drivep2 = 9; 
int steerp1 = 6;
int steerp2 = 5;
//test
int MAX = 50;
int MIN = 20;

int SIDEMIN = 40;
int SIDEMAX = 50;
//store variables
int F,R;



void setup() {
  
  
  //ping send
  pinMode(trig_f, OUTPUT);
  pinMode(trig_r, OUTPUT);
  
  //echo receive
  pinMode(rx_f, INPUT);
  pinMode(rx_r, INPUT);
  
  //motors
  pinMode(drivep1, OUTPUT);
  pinMode(drivep2, OUTPUT);
  pinMode(steerp1, OUTPUT);
  pinMode(steerp2, OUTPUT);
  
  //serial output
  Serial.begin(9600);
}

void loop() {
  
  ping();

  //output the distacne
 Serial.print("Front: \t" );
  Serial.print(F, DEC);
  Serial.print("\t Right: \t");
  Serial.println(R,DEC);
  brains();

  ///

}
int brains() {

 if (F > MAX) {
   //lots of space at the front, lets follow the line
   Serial.println(R);
   if (R > SIDEMAX) {
     left();
   } else if(R < SIDEMIN) {
     right();
   } else {
     center();
   }
   forward();
 } else {
   if (F < MIN) {
     
     if (R > SIDEMAX) {
       right();
     } else if(R < SIDEMIN) {
       left();
     } else {
       center();
     }
     reverse();
   } else {
     
     if (R > SIDEMAX) {
       left();
     } else if(R < SIDEMIN) {
       right();
     } else {
       center();
     }
     forward();
   }
   

 }
 
  
}


void forward() {
  analogWrite(drivep1, 100);
  analogWrite(drivep2, 0);
  Serial.println("forward");

}

void reverse() {
  analogWrite(drivep1, 0);
  analogWrite(drivep2, 155);
  Serial.println("reverse");
}
void pause() {
  analogWrite(drivep1, 0);
  analogWrite(drivep2, 0);
  Serial.println("pause");
}
void left() {
  analogWrite(steerp1, 125);
  analogWrite(steerp2, 0);
  Serial.println("left");

}
void right() {
    analogWrite(steerp1, 0);
  analogWrite(steerp2, 120);
  Serial.println("right");
}

void center() {
  analogWrite(steerp1, 0);
  analogWrite(steerp2, 0);
  Serial.println("center");
}

void ping() {
 //get a distance
  digitalWrite(trig_f, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_f, HIGH);
  delay(5);
  digitalWrite(trig_f, LOW);

   F = microsecondsToCentimeters(pulseIn(rx_f, HIGH));
 
  //get a distance
  digitalWrite(trig_r, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_r, HIGH);
  delay(5);
  digitalWrite(trig_r, LOW);

  R = microsecondsToCentimeters(pulseIn(rx_r, HIGH));
}




long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
