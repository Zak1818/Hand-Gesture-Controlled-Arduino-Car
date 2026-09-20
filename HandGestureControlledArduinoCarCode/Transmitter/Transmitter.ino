#include<SPI.h> //Libraries for NRF24L01
#include<nRF24L01.h>
#include<RF24.h>

int ENA = 3; // this pin will allow us to change the speed of the motor to our desired speed on the left set of wheels
int ENB = 9; // this pin will allow us to change the speed of the motor to our desired speed on the right set of wheels
int Lmotor1 = 4;//pin to direct current flow in motor in left side, allows change of direction
int Lmotor2 = 5;//pin to direct current flow in motor in left side, allows change of direction
int Rmotor1 = 6;//pin to direct current flow in motor in right side, allows change of direction
int Rmotor2 = 7;//pin to direct current flow in motor in right side, allows change of direction
int new1[4];// new list to store data
RF24 radio(8, 10);//CNS, CE



void setup() {
  Serial.begin(9600);
  recSetup(); //function to set up receiving data
  pinMode(ENA, OUTPUT);//all data is output from the nano into each screw terminal
  pinMode(ENB, OUTPUT);
  pinMode(Lmotor1, OUTPUT);
  pinMode(Lmotor2, OUTPUT);
  pinMode(Rmotor1, OUTPUT);
  pinMode(Rmotor2, OUTPUT);
}


void loop() {
  if (radio.available()) { //Receive data
    int value[4]; // list for data to be stored temporarily
    radio.read(&value, sizeof(value)); //read incoming data
    for (int i = 0; i < 4; i++) { //for loop to store data from value list into a new list to be used
      new1[i] = value[i];
    }
  }

  if (new1[0] == 0 && new1[1] == 0 && new1[2] == 0 && new1[3] == 0){ //if everything in the list is 0, car doesn't move.
    digitalWrite(Lmotor1, LOW);//Set both left pins to low to stop it from moving
    digitalWrite(Lmotor2, LOW);
    digitalWrite(Rmotor1, LOW);//Set both right pins to low to stop it from moving.
    digitalWrite(Rmotor2, LOW);
    analogWrite(ENA, 0);//Set ENA and ENB to 0 to have a speed of 0
    analogWrite(ENB, 0);
  }
  else if(new1[0]!=0) { //RIGHT TURN
    digitalWrite(Lmotor1, LOW);//left wheels spin backwards
    digitalWrite(Lmotor2, HIGH);
    digitalWrite(Rmotor1, HIGH);//right wheels spin forwards
    digitalWrite(Rmotor2, LOW);
    analogWrite(ENA, 200);//set speed
    analogWrite(ENB, 200);
  }else if(new1[1]!=0) { //LEFT TURN
    digitalWrite(Lmotor1, HIGH);//left wheels spin forward
    digitalWrite(Lmotor2, LOW);
    digitalWrite(Rmotor1, LOW);//right wheels spin backwards
    digitalWrite(Rmotor2, HIGH);
    analogWrite(ENA, 200);//set speed
    analogWrite(ENB, 200);
  }else if(new1[2]!=0){//FORWARDS
    digitalWrite(Lmotor1, HIGH);//left wheels spin forward
    digitalWrite(Lmotor2, LOW);
    digitalWrite(Rmotor1, HIGH);//right wheels spin forward
    digitalWrite(Rmotor2, LOW);
    analogWrite(ENA, 200);//set speed
    analogWrite(ENB, 200);
  }else if(new1[3]!=0){//BACKWARDS
    digitalWrite(Lmotor1, LOW);//left wheels spin backwards
    digitalWrite(Lmotor2, HIGH);
    digitalWrite(Rmotor1, LOW);//right wheels spin backwards
    digitalWrite(Rmotor2, HIGH);
    analogWrite(ENA, 200);//set speed
    analogWrite(ENB, 200);
  }
 
}

void recSetup(){ //create function to setup data
    radio.begin();//begin setup
    radio.openReadingPipe(1, 0xF0F0F0F0E1LL);//address for NRF24L01 to communicate with other NRF24L01
    radio.startListening();//function to listen for incoming data
}