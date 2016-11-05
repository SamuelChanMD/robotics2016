const int enableMotor1 = 6;
const int enableMotor2 = 7;

const int motor1Frwd = 2;
const int motor1Bkwd = 3;
const int motor2Frwd = 4;
const int motor2Bkwd = 5;

//Sensor variables
const int ultrasonicPin = 20;
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
  if(distance < 10){
    digitalWrite(motor1Frwd, LOW);
    digitalWrite(motor2Frwd, LOW);
    
  }else {
  digitalWrite(motor1Frwd, HIGH);
  digitalWrite(motor2Frwd, HIGH);
  delay(100);
  digitalWrite(motor1Frwd, LOW);
  digitalWrite(motor2Frwd, LOW);
  delay(10);
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
