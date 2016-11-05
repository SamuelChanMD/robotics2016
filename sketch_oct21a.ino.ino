#include <PID_v1.h>

//Need to work with light/switch. If after certain has elapsed, automatically turn off? 

int autoStop = 0;   //Temporary

//Motor 1 and 2 outputs for both forward and backward
const int motor1Frwd = 7;
const int motor1Bkwd = 8;
const int motor2Frwd = 9;
const int motor2Bkwd = 10;

//Sensor pins
const int infraredPin = 19;
const int ultrasonicPin = 20; //was 7 in example...
//int inputUltrasonic = 20;
//int outputUltrasonic = 21;

//Variables for ultrasonic sound
long distance, duration;

//Variables for speed
double desiredSpeed, currentSpeed, pedalAngle;

//Controlling turning
char turnDirection; 

void setup() {  
  pinMode(motor1Frwd, OUTPUT);
  pinMode(motor1Bkwd, OUTPUT);
  pinMode(motor2Frwd, OUTPUT);
  pinMode(motor2Bkwd, OUTPUT);
  
  // initialize serial communication:
  Serial.begin(9600);
  setMotors(0, 0, 0, 0);
}

void loop() {
  if(autoStop == 5){
    setMotors(0,0,0,0);
    break;
  }else { autoStop = autoStop + 1;}
  switch(turnDirection){
    case 'l': 
      turn();
      distance = distanceUS();
      if(distance > 10){ turnDirection = ' ';}
      else { turnDirection = 'r';}
      break;
    case 'r':
      turn();
      distance = distanceUS();
      if(distance > 10){ turnDirection = ' ';}
      else { turnDirection = 'b';}
      break;
    case 'b':
      reverse();
      turnDirection = 'l';
      break;
   default:
      distance = distanceUS();
      moveForward();   
  }
  
}

//Move forward
void moveForward(){
  setMotors(1, 0, 1, 0);
  
  if(distance > 100){
    analogWrite(motor1Frwd, 150);
    analogWrite(motor2Frwd, 150);
    Serial.println("Gear 3");
    delay(200); 
  } else if(distance > 50){
    analogWrite(motor1Frwd, 100);
    analogWrite(motor2Frwd, 100);
    Serial.println("Gear 2");
    delay(50);
  } else if(distance > 25){
    analogWrite(motor1Frwd, 50);
    analogWrite(motor2Frwd, 50);
    Serial.println("Gear 1");
    delay(20);
  } else if(distance > 0){
    analogWrite(motor1Frwd, 0);
    analogWrite(motor2Frwd, 0);
    Serial.println("Stop");
    delay(2000);
    turnDirection = 'l';
  }
}

//Read from ultrasonic and convert to cm
int distanceUS(){
  //Short LOW pulse to get clean HIGH Pulse
    pinMode(ultrasonicPin, OUTPUT);
    digitalWrite(ultrasonicPin, LOW);
    delay(2);
    digitalWrite(ultrasonicPin, HIGH);
    delay(5);
    digitalWrite(ultrasonicPin, LOW);

    pinMode(ultrasonicPin, INPUT);
    duration = pulseIn(ultrasonicPin, HIGH);

  //Used for testing for now
    Serial.println("Ultrasonic duration: ");
    Serial.println(duration);

  //Sound travels 29 milliseconds per centimeter. It travels forth and back, so divide by 2. 
    return duration / 29 / 2;
}

//Turn
//NOTE: MIGHT NEED TO SET SPEEDS?
void turn(){
  if(turnDirection == 'l'){
    setMotors(0, 0, 1, 0);
    delay(500);
  }else if(turnDirection == 'r'){
    setMotors(0, 0, 0, 1);
    delay(500);
    setMotors(1, 0, 0, 0);
    delay(500);
  }
}

//NOTE: MIGHT NEED TO SET SPEEDS?
void reverse(){
  setMotors(0, 1, 0, 0);
  delay(500);
  setMotors(0, 1, 0, 1);
  delay(1000);
}

void setMotors(int frwd1, int bkwd1, int frwd2, int bkwd2){
  if(frwd1 == 1){
    digitalWrite(motor1Frwd, HIGH);
    digitalWrite(motor1Bkwd, LOW);
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
