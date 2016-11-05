const int enableMotor1 = 2;
const int enableMotor2 = 5;

const int motor1Frwd = 4;
const int motor1Bkwd = 3;
const int motor2Frwd = 7;
const int motor2Bkwd = 6;

//Sensor variables
const int usTrigPin = 8;
const int usEchoPin = 9;
long distance, duration;

char thing = 'f';

void setup() {
  // put your setup code here, to run once:
  pinMode(enableMotor1, INPUT);
  pinMode(enableMotor2, INPUT);
  pinMode(motor1Frwd, OUTPUT);
  pinMode(motor1Bkwd, OUTPUT);
  pinMode(motor2Frwd, OUTPUT);
  pinMode(motor2Bkwd, OUTPUT);

  pinMode(usTrigPin, OUTPUT);
  pinMode(usEchoPin, INPUT);

  digitalWrite(enableMotor1, HIGH);
  digitalWrite(enableMotor2, HIGH);
  // initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  /*switch(thing){
    case 'f':
      setMotors(1, 0, 1, 0);
      delay(2000);
      thing = 'l';
      break;
    case 'l':
      turn();
      thing = 'r';
      break;
    case 'r':
      turn();
      break;
  }*/
 distance = distanceUS();
 Serial.println(distance);
  if(distance < 25){
    digitalWrite(motor1Frwd, LOW);
    digitalWrite(motor2Frwd, LOW);
    digitalWrite(enableMotor1, LOW);
    digitalWrite(enableMotor2, LOW);
  }else if(distance < 50) { 
    digitalWrite(motor1Frwd, HIGH);
    digitalWrite(motor2Frwd, HIGH);
    delay(66);
    digitalWrite(motor1Frwd, LOW);
    digitalWrite(motor2Frwd, LOW);
    delay(33);
  }else {
    digitalWrite(motor1Frwd, HIGH);
    digitalWrite(motor2Frwd, HIGH);
    delay(100);
  }
}

//Read from ultrasonic and convert to cm
int distanceUS(){
  //Short LOW pulse to get clean HIGH Pulse
    digitalWrite(usTrigPin, LOW);
    delay(2);
    digitalWrite(usTrigPin, HIGH);
    delay(5);
    digitalWrite(usTrigPin, LOW);

    duration = pulseIn(usEchoPin, HIGH);

  //Random delay...not sure why
    delay(250);
    
  //Sound travels 29 milliseconds per centimeter. It travels forth and back, so divide by 2. 
    return duration / 29 / 2;
}

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
}
