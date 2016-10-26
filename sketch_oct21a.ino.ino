const int enableMotor1 = 5;
const int enableMotor2 = 6;

const int motor1Frwd = 7;
const int motor1Bkwd = 8;
const int motor2Frwd = 9;
const int motor2Bkwd = 10;

const int infraredPin = 19;
const int ultrasonicPin = 20; //was 7 in example...
//int inputUltrasonic = 20;
//int outputUltrasonic = 21;

int switchInput = 11;
int lightOutput = 12;

//Variables for ultrasonic sound
long distance, duration;

//Read example on lightswitch
//Read example on sensors. First find ultrasonic, then infrared.

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  long duration, cm;
  //get input from ultrasonic
  distance = distanceUS();

  if(distance > 100){
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
    Serial.write("Ultrasonic duration");
    Serial.write(duration);

  //Sound travels 29 milliseconds per centimeter. It travels forth and back, so divide by 2. 
    return duration / 29 / 2;
}

