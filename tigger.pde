/*
  this is my code.. nihaopaul @ gmail o com
  i will use it to win the race :D
  
  this is for 2 ultrasonic sensors mounted left and right front
*/



int trig_l = 7;
int trig_r = 12;
// ultrasonic sensors ping array..

// ultrasonic sensor reply
int rx_l = 8;
int rx_r = 13;


int drivep1 = 10; 
int drivep2 = 9; 
int steerp1 = 6;
int steerp2 = 5;
//test
int MIN_DISTANCE = 30;
int EMERGENCY_DISTANCE = 10;

//store variables
int l,r;



void setup() {
  
  
  //ping send
  pinMode(trig_l, OUTPUT);
  pinMode(trig_r, OUTPUT);
  
  //echo receive
  pinMode(rx_l, INPUT);
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
  Serial.print("LEFT: \t" );
  Serial.print(l, DEC);
  Serial.print("\t Right: \t");
  Serial.println(r,DEC);
  
  delay(brains());
  ///

}
int brains() {
  if (l < EMERGENCY_DISTANCE || r < EMERGENCY_DISTANCE) {
    //we need to reverse a little, turning the opposite way..
    if (l > r) {
      right(); // it's backwards on purpose!
      reverse();
    } else if ( r > l ) {
      left(); //also backwards on purpose!
      reverse();
    } else {
      //go back a little
      center();
      reverse();
    }
   return (int)300;
  } else {
    if (l < MIN_DISTANCE || r < MIN_DISTANCE) {
      //we need to turn, so lets turn.. but which way
      if (l > r) {
        //turn left
        left();
        forward();
      } else if (r > l) {
        //turn right
        right();
        forward();
      } else {
        //go straight
        center();
        forward();
      }
    } else {
      //go forward, cautiously
      center();
      forward();
    }
    return (int)300;
  }
  
}


void forward() {
  digitalWrite(drivep1,HIGH);
  digitalWrite(drivep2,LOW);
}

void reverse() {
  digitalWrite(drivep1,LOW);
  digitalWrite(drivep2,HIGH);
}
void pause() {
 digitalWrite(drivep1,LOW);
 digitalWrite(drivep2,LOW);
}
void left() {
  digitalWrite(steerp1,HIGH);
  digitalWrite(steerp2,LOW);

}
void right() {
  digitalWrite(steerp1,LOW);
  digitalWrite(steerp2,HIGH);

}

void center() {
  digitalWrite(steerp1,LOW);
  digitalWrite(steerp2,LOW);
}

void ping() {
 //get a distance
  digitalWrite(trig_l, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_l, HIGH);
  delay(5);
  digitalWrite(trig_l, LOW);

   l = microsecondsToCentimeters(pulseIn(rx_l, HIGH));
 
  //get a distance
  digitalWrite(trig_r, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_r, HIGH);
  delay(5);
  digitalWrite(trig_r, LOW);

  r = microsecondsToCentimeters(pulseIn(rx_r, HIGH));
}




long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
