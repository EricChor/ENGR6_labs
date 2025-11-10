
// const int X_pin = A0;   // analog pin connected to X output
// const int Y_pin = A1;   // analog pin connected to Y output

// const int enA = 11;
// const int enB = 6;

// //left motor
// const int in1 = 10;
// const int in2 = 9;  

const int enA = 9;
const int in1 = 6;
const int in2 = 7;


const int in3 = 8;
const int in4 = 12;
const int enB = 10;

const int X_pin = 14;
const int Y_pin = 15;


const int Y_center = 600;
const int X_center = 600;

int left_motor_speed = 0;
bool left_motor_direction = true; //fwd is true
bool left_motor_prev_direction = true;

//right motor;
// const int in3 = 5;
// const int in4 = 3;

int right_motor_speed = 0;
bool right_motor_direction = true;
bool right_motor_prev_direction = true;


const int deadband = 3;


int X_axis_value = 0;
int Y_axis_value = 0;



void set_left_forward(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in1, HIGH);
}

void set_left_reverse(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in2, HIGH);
}

void set_right_forward(){
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in3, HIGH);
}

void set_right_reverse(){
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in4, HIGH);
}

void check_motor_directions(){
  if(left_motor_speed >= 0){
    left_motor_direction = true;
  } else {
    left_motor_direction = false;
  }

  if(right_motor_speed >= 0){
    right_motor_direction = true;
  } else {
    right_motor_direction = false;
  }

  if((right_motor_direction) && (!right_motor_prev_direction)){
    set_right_forward();
  }
  if((!right_motor_direction) && (right_motor_prev_direction)){
    set_right_reverse();
  }
  if((left_motor_direction) && (!left_motor_prev_direction)){
    set_left_forward();
  }
  if((!left_motor_direction) && (left_motor_prev_direction)){
    set_left_reverse();
  }
}


void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(X_pin, INPUT);
  pinMode(Y_pin, INPUT);

  set_left_forward();
  set_right_forward();

  Serial.begin(115200);
}


void loop() {
  
  X_axis_value = analogRead(X_pin);
  Y_axis_value = analogRead(Y_pin);

  // Serial.print(X_axis_value);
  // Serial.print(" ");
  // Serial.println(Y_axis_value);

  
  if(X_axis_value > X_center){
    X_axis_value = map(X_axis_value, X_center,1023,0,100);
  } else {
    X_axis_value = map(X_axis_value, 0 ,X_center, -100, 0  );
  }

  if(Y_axis_value > Y_center){
    Y_axis_value = map(Y_axis_value, Y_center,1023,0,100);
  } else {
    Y_axis_value = map(Y_axis_value, 0 ,Y_center, -100, 0  );
  }


  // X_axis_value = map(X_axis_value,0,1023,-100,100);
  X_axis_value = constrain(X_axis_value,-100,100);

  // Y_axis_value = map(Y_axis_value,1023,0,-100,100);
  Y_axis_value = constrain(Y_axis_value,-100,100);

  left_motor_speed = Y_axis_value + X_axis_value;
  right_motor_speed = Y_axis_value - X_axis_value;

  left_motor_speed = constrain(left_motor_speed,-100,100);
  right_motor_speed = constrain(right_motor_speed,-100,100);


  Serial.print("X : ");
  Serial.print(X_axis_value);
  Serial.print(" Y : ");
  Serial.println(Y_axis_value);
  // Serial.print("left : ");
  // Serial.print(left_motor_speed);
  // Serial.print(" right : ");
  // Serial.println(right_motor_speed);
  // check_motor_directions();


  if((abs(X_axis_value) > deadband) || (abs(Y_axis_value) > deadband)){
    analogWrite(enA,abs(left_motor_speed*(255.0/100)));
    analogWrite(enB,abs(right_motor_speed*255.0/100));
  } else {
    analogWrite(enA,0);
    analogWrite(enB,0);
  }

  left_motor_prev_direction = left_motor_direction;
  right_motor_prev_direction = right_motor_direction;

  delay(10);

}
