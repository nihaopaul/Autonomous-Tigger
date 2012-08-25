/* 
  2012 / June / 30th
  Paul Adams
  XinCheJian RoboRacing
*/



#include <OneWire.h>
#include <AikoEvents.h>

using namespace Aiko;


int trig_fs = 7;
int trig_ls = 6;
int trig_rs = 5;


// ultrasonic sensor reply
int rx_fs = 4;
int rx_ls = 3;
int rx_rs = 2;

int drivep1 = 13; 
int drivep2 = 12; 
int speeda = 10;
int steerp1 = 11;
int steerp2 = 8;
int speedb = 9;


//test
int MAX = 30;
int MIN = 15;

//store variables
int FS,RS,LS = 0;

void setup() {
  
  //ping send
  pinMode(trig_fs, OUTPUT);
  pinMode(trig_ls, OUTPUT);
  pinMode(trig_rs, OUTPUT);
  
  //echo receive
  pinMode(rx_fs, INPUT);
  pinMode(rx_ls, INPUT);
  pinMode(rx_rs, INPUT);
  
  //motors
  pinMode(drivep1, OUTPUT);
  pinMode(drivep2, OUTPUT);
  pinMode(steerp1, OUTPUT);
  pinMode(steerp2, OUTPUT);
  
  //serial output
  Serial.begin(9600);
  analogWrite(speedb, 100);
  
  Events.addHandler(frontsensor, 20);  
  Events.addHandler(rightsensor, 20); 
  Events.addHandler(leftsensor, 20); 
  Events.addHandler(brains, 10); 

}



void brains() {
Serial.println(frd_or_rev());
  switch ( frd_or_rev() ) {
    case 1:    
      switch ( left_or_right() ) {
        case 0:
          center();
        break;
        case 2:
          left();
        break;
        case 1:
          right();
        break;
      }
      forward(40);
    break;
    case 2:
      switch ( left_or_right() ) {
        /* these are reversed when you reverse */
        case 0:
          center();
        break;
        case 1:
          right();
        break;
        case 2:
          left();
        break;
      }    
      reverse(50);
    break;
    case 0:
      switch ( left_or_right() ) {
        case 0:
          center();
        break;
        case 1:
          left();
        break;
        case 2:
          right();
        break;
      }
      forward(40);
    break;
  }
  
    //output the distacne
  Serial.print("Front: \t" );
  Serial.print(FS, DEC);
  Serial.print("\t Right: \t");
  Serial.print(RS,DEC);
  Serial.print("\t Left: \t");
  Serial.println(LS,DEC);
}

int left_or_right() {
  /*
    which way can we turn?
    1 = turn left
    2 = turn right
    0 = straight
  */
  if (LS == RS) {
    //go straight
    return 0; 
  } else if (LS < RS) {
    return 2; //left is smaller, turn right
  } else if (LS > RS ) {
    return 1; //left is bigger turn left
  }
  
}

int frd_or_rev() {
  /*
  can we go forward? 
  should we go in reverse?
    0 = turn
    1 = forward
    2 = reverse
    
  */
  if (FS < MIN) {
    return 2; //reverse, we are too close.
  } else if (FS < MAX) {
    return 0; //turn, we are in our comfort zone
  } else {
    return 1; //forward is fine.
  }
}

void loop() {
  Events.loop();
}



void forward(int myspeed) {
  /* speed @ 100% */
  digitalWrite(drivep1, HIGH);
  digitalWrite(drivep2, LOW);
  int speeds = map(myspeed, 0,100,0,255);
  analogWrite(speeda, speeds);
  Serial.println("forward");
}

void reverse(int myspeed) {
  digitalWrite(drivep1, LOW);
  digitalWrite(drivep2, HIGH);
  int speeds = map(myspeed, 0,100,0,255);
  analogWrite(speeda, speeds);
  Serial.println("reverse");
}
void pause() {
  digitalWrite(drivep1, LOW);
  digitalWrite(drivep2, LOW);
  Serial.println("pause");
}
void left() {
  digitalWrite(steerp1, HIGH);
  digitalWrite(steerp2, LOW);
  Serial.println("left");

}
void right() {
  digitalWrite(steerp1, LOW);
  digitalWrite(steerp2, HIGH);
  Serial.println("right");
}

void center() {
  digitalWrite(steerp1, LOW);
  digitalWrite(steerp2, LOW);
  Serial.println("center");
}

void frontsensor() {
 //get a distance
  digitalWrite(trig_fs, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_fs, HIGH);
  delay(5);
  digitalWrite(trig_fs, LOW);
  FS = microsecondsToCentimeters(pulseIn(rx_fs, HIGH));

  /*
  Smoothing to stop hasty decissions
  */
   const int numReadings = 2; //need it responsive
   static unsigned int readings[numReadings] = { 0 };
   static unsigned int index = 0;                  // the index of the current reading
   static unsigned int total = 0;                  // the running total
   static unsigned int average = 0;                // the average
  

   total= total - readings[index];
   readings[index] = FS;
   total= total + readings[index];
   index = index + 1;
  
   if (index >= numReadings) {
     index = 0;
   }
    average = total / numReadings;
    FS = average;
   
  /*
  end of smoothing
  */
  
}
void leftsensor() {
  //get a distance
  digitalWrite(trig_ls, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_ls, HIGH);
  delay(5);
  digitalWrite(trig_ls, LOW);

  LS = microsecondsToCentimeters(pulseIn(rx_ls, HIGH));
  
  /*
  Smoothing to stop hasty decissions
  */
   const int numReadings = 2; //need it responsive
   static unsigned int readings[numReadings] = { 0 };
   static unsigned int index = 0;                  // the index of the current reading
   static unsigned int total = 0;                  // the running total
   static unsigned int average = 0;                // the average
  

   total= total - readings[index];
   readings[index] = LS;
   total= total + readings[index];
   index = index + 1;
  
   if (index >= numReadings) {
     index = 0;
   }
    average = total / numReadings;
    LS = average;
   
  /*
  end of smoothing
  */
  
}
void rightsensor() {
  //get a distance
  digitalWrite(trig_rs, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_rs, HIGH);
  delay(5);
  digitalWrite(trig_rs, LOW);

  RS = microsecondsToCentimeters(pulseIn(rx_rs, HIGH));
  
  /*
  Smoothing to stop hasty decissions
  */
   const int numReadings = 2; //need it responsive
   static unsigned int readings[numReadings] = { 0 };
   static unsigned int index = 0;                  // the index of the current reading
   static unsigned int total = 0;                  // the running total
   static unsigned int average = 0;                // the average
  

   total= total - readings[index];
   readings[index] = RS;
   total= total + readings[index];
   index = index + 1;
  
   if (index >= numReadings) {
     index = 0;
   }
    average = total / numReadings;
    RS = average;
   
  /*
  end of smoothing
  */
}



long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
