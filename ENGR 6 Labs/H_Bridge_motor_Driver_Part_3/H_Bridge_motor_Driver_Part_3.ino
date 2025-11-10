//Pin definitions
const int enA = 9;

const int enB = 10;
const int in1 = 11;
const int in2 = 12;

const int in3 = 7;
const int in4 = 6;
const int POT = A0;

int motor_speed = 0;
//variable to check if motor is spinning forward or reverse
bool motor_state = true; //fwd = true
//variable to store previous motor state, used to check if motor state changes
bool prev_motor_state = true; 

//if the motor goes forward set in1 and in3 to high
void set_motor_forward(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(20);

  digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
}

//if the motor is going reverse set in2 and in4 to high
void set_motor_reverse(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(20);

  digitalWrite(in2, HIGH);
  digitalWrite(in4, HIGH);
}


void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(POT, INPUT);

  // ensure motors stopped
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(20);

  //start in the forward state
  digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  Serial.begin(9600);
}
void loop() {
  //read potentiometer input
  motor_speed = analogRead(POT);
  //translate from 0 - 1023 to -512 - 511
  motor_speed = motor_speed-512;

  //if motor_speed is positive spin forward, if it is negative spin in reverse
  if(motor_speed > 0){
    motor_state = true;
  } else {
    motor_state = false;
  }

  //absolute value is used because only positive voltages can be output from the GPIO pins
  
  //if motor_state changes, then reverse the polarity of the current
  if(motor_state != prev_motor_state){
    if(motor_speed > 0){
      set_motor_forward();
      Serial.println("Forward ----------------------------------------------------------------------------------------------");
    } else {
      set_motor_reverse();
      Serial.println("--------------------------------------------------------------------------------Reverse");
    }
  }

  //rescale the potentiometer inputs (0 - ~512) to analogWrite outputs (0-255)
  motor_speed = fabs(motor_speed);
  
  motor_speed = motor_speed*255.0/512;

  Serial.print(motor_state);
  Serial.print("   ");
  Serial.println(motor_speed);
  analogWrite(enA,motor_speed);
  analogWrite(enB,motor_speed);

  //set previous motor state to current motor state
  prev_motor_state = motor_state;


}
