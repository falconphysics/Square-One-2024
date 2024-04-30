// #include <XBOXRECV.h>
#include<Servo.h>
// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
// USB Usb;
// XBOXRECV Xbox(&Usb);

/* Define the rotational speed of the motor. MUST be between 0 and 255. */
int Motorpin = 6; // must use pins 5 and 6 to avoid pin conflict with usb shield 
int Turnpin = 12; 
int Stick = 0;
int Speed=1;
int Turn=1;
int ActualSpeed = 90; // servo write of stop
int ActualTurn = 87; // degree of straight
bool NoTurn = true;
int i;

//seting up the pins for the front distance sensors
const int frontTrigPin = 2;
const int frontEchoPin = 3;

//seting up the pins for the left distance sensors
const int leftTrigPin = 4;
const int leftEchoPin = 5;

//seting up the pins for the right distance sensors
const int rightTrigPin = 6;
const int rightEchoPin = 7;

//seting up the pins for the front distance sensors
const int backTrigPin = 8;
const int backEchoPin = 9;

Servo Move;
Servo Turning;
void setup() {
  Move.attach(Motorpin);
  Turning.attach(Turnpin);
  TCCR1B = TCCR1B & 0b11111000 | 0x02;
  Serial.begin(9600);
  // if (Usb.Init() == -1) {
  //   Serial.print(F("\r\nOSC did not start"));
  // }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
  pinMode (Motorpin, OUTPUT);
  pinMode (Turnpin, OUTPUT);
  
  // Front Distant Sensors
  pinMode(frontTrigPin, OUTPUT);
  pinMode(frontEchoPin, INPUT);

  // Left Distance Sensors
  pinMode(leftTrigPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);

  // Right Distance Sensors
  pinMode(rightTrigPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);

  // Back Distance Sensors
  pinMode(backTrigPin, OUTPUT);
  pinMode(backEchoPin, INPUT);
  Serial.begin(9600);

}

void loop() {
  NoTurn = 1;
  // Usb.Task(); 
  // Speed = map((Xbox.getButtonPress(L2, 0)-Xbox.getButtonPress(R2,0)), -255, 255, 0, 180);
  // Stick = Xbox.getAnalogHat(LeftHatX, 0);
  Speed = 20;
  if(i%20==0){
    if(Stick<-7500){
    Turn = map(Stick,-7501, -32767, 86, 78);
    NoTurn = 0;
  }
  if(Stick>7500){
    Turn = map(Stick,7501, 32767, 86, 100);
    NoTurn = 0;
  }
  if(NoTurn>0){
    Turn = 87;
  }
  if (Speed > 85){
    //Speed = map(Xbox.getButtonPress(R2, 0), 0, 255, 90, 180);
  }
  if(ActualSpeed>Speed){
    ActualSpeed = ActualSpeed - 3;
  }
  else if(ActualSpeed<Speed){
    ActualSpeed = ActualSpeed +3;
  }
  if((ActualSpeed<92&&ActualSpeed>88)){
    ActualSpeed = 90;
  }
  Serial.print("Turn = ");
  Serial.print(Turn);
  Serial.print("Speed = ");
  if(ActualSpeed> 110){
    ActualSpeed = 105;
  }
  else if(ActualSpeed< 75){
    ActualSpeed = 75;
  }
  Serial.println(ActualSpeed);
  Move.write(ActualSpeed);
  Turning.write(Turn);
  }

  Serial.println("Distance: " + String(getDistanceFront()));
  i++;
}

float getDistanceFront() {
  digitalWrite(frontTrigPin, LOW);
  
  delayMicroseconds(2);

  digitalWrite(frontTrigPin, HIGH); 

	delayMicroseconds(10);  
	
  digitalWrite(frontTrigPin, LOW);  

  return pulseIn(frontEchoPin, HIGH);
}

float getDistanceLeft() {
  digitalWrite(leftTrigPin, LOW);
  
  delayMicroseconds(2);

  digitalWrite(leftTrigPin, HIGH); 

	delayMicroseconds(10);  
	
  digitalWrite(leftTrigPin, LOW);  

  return pulseIn(leftEchoPin, HIGH);
}

float getDistanceRight() {
  digitalWrite(rightTrigPin, LOW);
  
  delayMicroseconds(2);

  digitalWrite(rightTrigPin, HIGH); 

	delayMicroseconds(10);  
	
  digitalWrite(rightTrigPin, LOW);  

  return pulseIn(rightEchoPin, HIGH);
}

float getDistanceBack() {
  digitalWrite(backTrigPin, LOW);
  
  delayMicroseconds(2);

  digitalWrite(backTrigPin, HIGH); 

	delayMicroseconds(10);  
	
  digitalWrite(backTrigPin, LOW);  

  return pulseIn(backEchoPin, HIGH);
}