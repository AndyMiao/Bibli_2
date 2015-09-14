// connect motor controller pins to Arduino digital pins
// motor one
int enA = 9;
int in1 = 8;
int in2 = 7;
// motor two
int enB = 3;
int in3 = 6;
int in4 = 5;
//ir sensor
#define ir A1
char cmd = 's';


void setup()
{
  Serial.begin(9600);
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  // initialize digital pin 13 as an output.
  pinMode(ir, INPUT);
  pinMode(13, OUTPUT);
}

void blink(){
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(100);              // wait for a second
 }

double get_ir(uint16_t value){
  if(value<16) value=16; 
  return 2076.0/(value-11.0); 
  }

void forward() //move forward
{
  //motor left
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 220);
  //motor right
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 220);
}

void left() //turn left
{
  //motor left
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 130);
  //motor right
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 130);
}

void right() //turn right
{
  //motor left
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 130);
  //motor right
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 130);
}

void back() //reverse
{
  //motor left
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 140);
  //motor right
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 140);
}

void stopmove() //stop move
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void dance()
{
left();
delay(3000);
right();
delay(3000);
forward();
delay(1000);
back();
delay(1000);
stopmove();
}

void auto_drive()
{
  uint16_t value = analogRead(ir);
  double ds = get_ir(value);
  Serial.println(value);
  if(ds>=15){
    forward();
  }
  else{
    left();
    delay(450);
    stopmove();
    Serial.println("obstacle1");
    }
  value = analogRead(ir);  
  ds = get_ir(value);
  Serial.println(value);
  if(ds>=15){
    forward();
  }
  else{
    right();
    delay(900);
    stopmove();
    Serial.println("obstacle2");
    }

  value = analogRead(ir);  
  ds = get_ir(value);
  Serial.println(value);
  if(ds>=15){
    forward();
  }
  else{
    right();
    delay(450);
    Serial.println("obstacle3");
    forward();
    }  
}


void loop()
{
  while (Serial.available() > 0)
  {
  cmd = Serial.read();
  Serial.print(cmd);
  delay(2);
  }
  if (cmd == 'f')
  {
    forward();
  }
  else if(cmd == 'l')
  {
    left();
  }
  else if(cmd == 'r')
  {
    right();
    
  }
  else if(cmd == 'b')
  {
    back();
    
  }
  else if(cmd == 'd')
  {       
      dance();  
  }
  else if (cmd=='v')
  {
    auto_drive();
  }
  else if(cmd == 's')
  {
    stopmove();   
  } 
 
}

