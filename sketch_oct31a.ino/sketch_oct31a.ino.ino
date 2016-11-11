#include <SharpIR.h>

const int motor1Frwd = 4;
const int motor1Bkwd = 3;
const int motor2Frwd = 7;
const int motor2Bkwd = 6;

//Sensor variables
const int usTrigPin = 8;
const int usEchoPin = 9;
long distanceUS, duration;

#define ifPin A0
SharpIR sharp(ifPin, 25, 93, 20150);
long distanceIR;

boolean obstacle = false;
boolean initialBoost = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1Frwd, OUTPUT);
  pinMode(motor1Bkwd, OUTPUT);
  pinMode(motor2Frwd, OUTPUT);
  pinMode(motor2Bkwd, OUTPUT);

  pinMode(usTrigPin, OUTPUT);
  pinMode(usEchoPin, INPUT);
  pinMode(ifPin, INPUT);
  
  // initialize serial communication:
  Serial.begin(9600);
}

void loop() {
 if(obstacle){ //Turn if obstacle found
  //Serial.println("Obstacle found. I will turn.");
  delay(400);
  setMotors(1, 0, 0, 1);
  delay(900);
  setMotors(0, 0, 0, 0);
  initialBoost = true;
  obstacle = false;
 }
 if(initialBoost){
  //Serial.println("Initial boost: Activated");
  setMotors(1, 0, 1, 0);
  delay(10 00);
  initialBoost = false; 
 }
 distanceUS = distancecalcUS();
 distanceIR = sharp.distance();
 //Serial.println(distanceUS);
 Serial.println(distanceIR);
  moveForward();
}

//Read from ultrasonic and convert to cm
int distancecalcUS(){
  //Short LOW pulse to get clean HIGH Pulse
    digitalWrite(usTrigPin, LOW);
    delay(2);
    digitalWrite(usTrigPin, HIGH);
    delay(5);
    digitalWrite(usTrigPin, LOW);

    duration = pulseIn(usEchoPin, HIGH);

  //Random delay...not sure why
    delay(20);
    
  //Sound travels 29 milliseconds per centimeter. It travels forth and back, so divide by 2. 
    return duration / 29 / 2;
}
/*
void turn(){
  if(thing == 'l'){
    setMotors(0, 0, 1, 0);
    delay(1000);
  }else if(thing == 'r'){
    setMotors(0, 0, 0, 1);
    delay(1000);
    setMotors(1, 0, 0, 0);
    delay(1000);
  }
*/
void moveForward(){
  if(distanceUS < 10 || distanceIR> 60){
    Serial.println("Move 10");
    setMotors(0, 1, 0, 1);
    delay(900);
    setMotors(0, 0, 0, 0);
    obstacle = true;
   }else if(distanceUS < 25){
    Serial.println("Move 25");
    setMotors(0, 1, 0, 1);
    delay(400);
    setMotors(0, 0, 0, 0);
    obstacle = true;
  }else if(distanceUS < 50) { 
    Serial.println("Move 50");
    setMotors(1, 0, 1, 0);
    delay(66);
    setMotors(0, 0, 0, 0);
    delay(33);
    setMotors(0, 0, 1, 0);
    delay(10);
    setMotors(0, 0, 0, 0);
  }else{
    //Serial.println("Move Max");
    setMotors(1, 0, 1, 0);
    delay(100);
    setMotors(0, 0, 1, 0);
    delay(10);
    setMotors(1, 0, 1, 0);
  } 
}

void setMotors(int frwd1, int bkwd1, int frwd2, int bkwd2){
  if(frwd1 == 1){
    digitalWrite(motor1Bkwd, LOW);
    digitalWrite(motor1Frwd, HIGH);
  }else{
    digitalWrite(motor1Frwd, LOW);
    if(bkwd1 == 1){
      digitalWrite(motor1Bkwd, HIGH);
    }else{
      digitalWrite(motor1Bkwd, LOW);
    }
  }

  if(frwd2 == 1){
    digitalWrite(motor2Frwd, HIGH);
    digitalWrite(motor2Bkwd, LOW);
  }else{
    digitalWrite(motor2Frwd, LOW);
    if(bkwd2 == 1){
      digitalWrite(motor2Bkwd, HIGH);
    }else{
      digitalWrite(motor2Bkwd, LOW);
    }
  }
}
