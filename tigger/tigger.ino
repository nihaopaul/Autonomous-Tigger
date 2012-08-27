/* 
 2012 / August / 25th
 Paul Adams
 XinCheJian RoboRacing
 */



#define BOUNDARY     50      // (cm) Avoid objects closer than 30cm.
#define INTERVAL     10      // (ms) Interval between distance readings.
#define MINLEFT    20
#define MAXLEFT    25



int m2[] = {  6, 5 };
int m1[] = { 
  10,9 };

int trig_fs = 8;
int echo_fs = 7;




int trig_ls = 13;
int echo_ls = 12;





int FS,LS = 0;

void setup() {

  //ping send
  pinMode(trig_fs, OUTPUT);
  pinMode(trig_ls, OUTPUT);
  
  //echo receive
  pinMode(echo_fs, INPUT);
  pinMode(echo_ls, INPUT);


  //motors
  pinMode(m1[0], OUTPUT);
  pinMode(m1[1], OUTPUT);
  pinMode(m2[0], OUTPUT);
  pinMode(m2[1], OUTPUT);

  //serial output
  Serial.begin(9600);
  pause();
  center();
}



/*
the story from http://letsmakerobots.com/node/696
 
 If something in front, turn left, go to main.
 If something closer than 30 cm to the right, turn left, go to main.
 if nothing in front and something closer than 70 cm to the right, drive ahead, go to main.
 If nothing to the right closer than 70 cm, turn right, go to main.
*/



void loop() {
  long frontfs, leftfs; 
  forward();                        // Robot moves forward continuously.
  do
  {
    delay(INTERVAL);                // Delay between readings.
    frontfs = frontsensor();      // Take a distance reading.
    leftfs = leftsensor();   
    Serial.print("front: "); 
    Serial.print(frontfs);
    Serial.print(" left: ");
    Serial.println(leftfs);
  }
  while(frontfs >= BOUNDARY && leftfs >= MINLEFT && leftfs <= MAXLEFT); //lets keep it close to the wall    

  if (frontfs < BOUNDARY && frontfs > 50) { //make sure we;re not against the wall//cheap i know
    right(350);
    center();
  } else if (frontfs <= 50) {

    right(50);
    left(0);
    reverse();
    delay(700);
    center();
    
  } else if (leftfs >=MAXLEFT) {
    left(300);
    center();
  } else if (leftfs <= MINLEFT) {
    right(500);
    center();
  } else {
  }


}



void forward() {
  /* speed @ 100% */
  digitalWrite(m1[0], HIGH);
  digitalWrite(m1[1], LOW);
}

void reverse() {
  digitalWrite(m1[0], LOW);
  digitalWrite(m1[1], HIGH);
}
void pause() {
  digitalWrite(m1[0], LOW);
  digitalWrite(m1[1], LOW);
}
void left(int wait) {
  digitalWrite(m2[0], HIGH);
  digitalWrite(m2[1], LOW);
  delay(wait);

}
void right(int wait) {
  digitalWrite(m2[0], LOW);
  digitalWrite(m2[1], HIGH);
  delay(wait);
}

void center() {
  digitalWrite(m2[0], LOW);
  digitalWrite(m2[1], LOW);

}


unsigned int frontsensor() {


  digitalWrite(trig_fs, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_fs, HIGH);
  delayMicroseconds(15);
  digitalWrite(trig_fs, LOW);
  delayMicroseconds(20);

  return microsecondsToCentimeters(pulseIn(echo_fs, HIGH));

}

unsigned int leftsensor() {
  //get a distance
  digitalWrite(trig_ls, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_ls, HIGH);
  delay(5);
  digitalWrite(trig_ls, LOW);
  return microsecondsToCentimeters(pulseIn(echo_ls, HIGH));
}


long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

