int trig = 12; //assign variables to pins
int echo = 11;
int buzz = 5;
int led = 13;

int del = 0;//del used to increase time between beeps/buzzes

void setup() {
  pinMode(trig,OUTPUT); //output signal to trig, which allows it so send echoes for the echo pin to listen to.
  pinMode(echo,INPUT); //distance is received from trig pin
  pinMode(buzz, OUTPUT); //output to buzzer
  pinMode(led, OUTPUT); //output to LED
  Serial.begin(9600);
}

void loop() {
  digitalWrite (trig,LOW);
  delayMicroseconds(2); //clears trig pin

  digitalWrite (trig,HIGH); //send out an echo for 10microseconds, that the echo sensor can listen to and detect distance
  delayMicroseconds (10);
  digitalWrite (trig,LOW);
  long t =pulseIn(echo,HIGH); //reads travel time
  int distance = t/29/2; //conversion factor to centimeters

  if (distance < 10){ //if distance is less than 10 cm, the set delay is basically 0
    delay(1);
  }
  else if (distance < 25){// if distance less than 25cm, the delay is set depending on the distance. longer distance, longer delay
    del = distance/0.1;
    delay(del);
  }
  else if (distance > 24 && distance < 50){//same idea as the previous statement, except in this range delay is slightly longer
    del = distance * 9;
    delay(del);
  }

  if (distance < 50) { //if the distance is below 50
    digitalWrite(led, HIGH); //Led turns on
    int calc = 50 - distance;
    float note = calc * 65; //the closer an object is, the higher pitch is calculated
    tone(buzz, note, 100);//plays pitch for 100microseconds. when an wall is close, the delay is less therefore there is less time between every buzz, therefore the 100milliseconds can be ignored at closer distances
  }
  digitalWrite(led, LOW); //LED turns off
}