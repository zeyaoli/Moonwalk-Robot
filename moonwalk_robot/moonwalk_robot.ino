#include <Servo.h>


// create servo object to control a servo
// twelve servo objects can be created on most boards
Servo rightthigh;
Servo rightfoot;
Servo leftfoot;
Servo leftthigh;
// create variables for the value
float sinVal;
int toneVal;
int pos1 = 10;
int pos2 = 10;
const int pingPin = 7;

// establish variables for duration of the ping,
// and the distance result in inches and centimeters:
long duration, cm;
// store 10 variables to the arrary
int cmAvg[10];
int avg;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  rightthigh.attach(9);
  rightfoot.attach(12);
  leftfoot.attach(10);
  leftthigh.attach(11);
  pinMode(8, OUTPUT);
}

void loop() {
  // The PING is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  // inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  for (int i = 0; i < 10; i++) {
    cmAvg[i] = cm;
  };

  for (int i = 0; i < 10; i++) {
    avg += cmAvg[i];
  };
  avg = avg / 10;

  if (avg > 75) {
    // if condition: when the statement is true, do something
    //if dis greatter than 50, do something
    staying();
  } else if (avg > 35 && avg <= 75) {
    walking();
  } else {
    alarming();
  }

  // Serial.print(inches);
  // Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm     ");
  Serial.print(avg);
  Serial.print("avg");
  Serial.println();
  delay(10);

}

void staying() {
  rightfoot.write(pos1); //15
  rightthigh.write(24);
  leftfoot.write(pos2); //15
  leftthigh.write(24);
  noTone(8);
}

void walking() {
  noTone(8);
  //move right
  rightfoot.write(0);
  leftfoot.write(2 * pos2);
  delay(200);
  rightthigh.write(0);
  leftthigh.write(0);
  delay(200);
  rightfoot.write(pos1);
  leftfoot.write(pos2);
  delay(200);

  rightfoot.write(2 * pos1);
  leftfoot.write(0);
  delay(200);
  rightthigh.write(24);
  leftthigh.write(24);
  delay(200);
  rightfoot.write(pos1);
  leftfoot.write(pos2);
  delay(200);

  // move left
  rightfoot.write(0);
  leftfoot.write(2 * pos2);
  delay(200);
  rightthigh.write(2 * 24);
  leftthigh.write(2 * 24);
  delay(200);

  rightfoot.write(2 * pos1);
  leftfoot.write(0);
  delay(200);
  rightthigh.write(24);
  leftthigh.write(24);
  delay(200);
}

void alarming() {
  for (int x = 0; x < 180; x++) {
    sinVal = (sin(x * (3.1412 / 180)));
    toneVal = 800 + (int(sinVal * 2000));
    tone(8, toneVal);
    delay(2);
  }
}


long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
