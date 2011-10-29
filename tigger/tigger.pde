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
int MIN_DISTANCE = 50;
int EMERGENCY_DISTANCE = 30;

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
  
  delay(brains());
  ///

}
int brains() {
 
  if (F <= EMERGENCY_DISTANCE || R <= EMERGENCY_DISTANCE) {
    //too close
    if (F < EMERGENCY_DISTANCE && R < EMERGENCY_DISTANCE) {
      //right();
      reverse();
      delay(1300);
      left();
      forward();
      return 500;
    }
    if (F > EMERGENCY_DISTANCE && R > EMERGENCY_DISTANCE) {
      //wont run
      return 10000;
    }
    if (F < EMERGENCY_DISTANCE && R > EMERGENCY_DISTANCE) {
      //cannot, must reverse and turn left
      reverse();
      delay(100);
      right();
      reverse();
      delay(1300);
            left();
      forward();
      return 500;
    }
    if (F > EMERGENCY_DISTANCE && R < EMERGENCY_DISTANCE) {
      left();
      forward();
      return 300;
    }
  } else {
    if (F <= MIN_DISTANCE || R <= MIN_DISTANCE) {
      //time to turn if front is close
      if(F > MIN_DISTANCE && R < MIN_DISTANCE) {
        //go forward
        center();
        forward(); 
        return 100;
      }
      if (F < MIN_DISTANCE && R < MIN_DISTANCE) {
        /* turn left */
        left();
        forward();
        return 100;
      }
      if (F > MIN_DISTANCE && R > MIN_DISTANCE) {
        //wont run

        return 1000;
      }
      if (F < MIN_DISTANCE && R > MIN_DISTANCE) {
        right();
        forward();
        return 200;
      }
    } else {
      //go straight
      center();
      forward();
      return 200;
    }
  }
  
}


void forward() {
  analogWrite(drivep1, 180);
  analogWrite(drivep2, 0);
  //digitalWrite(drivep1,HIGH);
  //digitalWrite(drivep2,LOW);
}

void reverse() {
  analogWrite(drivep1, 0);
  analogWrite(drivep2, 255);
  //digitalWrite(drivep1,LOW);
  //digitalWrite(drivep2,HIGH);
}
void pause() {
  analogWrite(drivep1, 0);
  analogWrite(drivep2, 0);
 //digitalWrite(drivep1,LOW);
 //digitalWrite(drivep2,LOW);
}
void left() {
  analogWrite(steerp1, 255);
  analogWrite(steerp2, 0);
 // digitalWrite(steerp1,HIGH);
  //digitalWrite(steerp2,LOW);

}
void right() {
    analogWrite(steerp1, 0);
  analogWrite(steerp2, 255);
  //digitalWrite(steerp1,LOW);
  //digitalWrite(steerp2,HIGH);

}

void center() {
  analogWrite(steerp1, 0);
  analogWrite(steerp2, 0);
 // digitalWrite(steerp1,LOW);
  //digitalWrite(steerp2,LOW);
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
