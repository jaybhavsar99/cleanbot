# include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#define CE_PIN  7
#define CSN_PIN 8
#define enA 2
#define enB 3

float boardValues[2];
int n=5;

int voltageSensor = A0;

float voltageOutput = 0.0;
float voltageInput = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int voltageValue = 0;

// sonar variables
int trigger_pin = 9;
int echo_pin = 10;
int buzzer_pin = 1; 
int time;
int distance; 


RF24 radio(CE_PIN, CSN_PIN);
int joyStick[7];
int x,y,z,pot1,pot2;
int pwmOutput;

// for servo
int servo1;
int servo2;

const byte addresses[][5]= {"'R','x','A','A','A'","'x','R','A','A','A'"};

int int1 = 23;
int int2 = 24;
int int3 = 25;
int int4= 26;

// switch buttton state
int switchMode=0;
int flipMotion=0;

// for upper motor
int intM1 = 30;
int intM2 = 31;

// servo initialize
Servo myservo1,myservo2;
int pos = 90;

void forwardMotion(){
    digitalWrite(int1,HIGH);
    digitalWrite(int2,LOW);
    digitalWrite(int3,HIGH);
    digitalWrite(int4,LOW);
  }

void backwardMotion(){
    digitalWrite(int1,LOW);
    digitalWrite(int2,HIGH);
    digitalWrite(int3,LOW);
    digitalWrite(int4,HIGH);
  }

  void rightMotion(){
    digitalWrite(int1,HIGH);
    digitalWrite(int2,LOW);
    digitalWrite(int3,LOW);
    digitalWrite(int4,HIGH);
  }
  void leftMotion(){
    digitalWrite(int1,LOW);
    digitalWrite(int2,HIGH);
    digitalWrite(int3,HIGH);
    digitalWrite(int4,LOW);
  }

  void stopMotion(){
    digitalWrite(int1,LOW);
    digitalWrite(int2,LOW);
    digitalWrite(int3,LOW);
    digitalWrite(int4,LOW);
  }

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,addresses[0]);
  radio.openWritingPipe(addresses[1]);
  radio.setPALevel(RF24_PA_MAX);

  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);
  pinMode(int1,OUTPUT);
  pinMode(int2,OUTPUT);
  pinMode(int3,OUTPUT);
  pinMode(int4,OUTPUT);

  myservo1.attach(9); 
  myservo2.attach(6);

  pinMode(intM1,OUTPUT);
  pinMode(intM2,OUTPUT);
  pinMode (voltageSensor, INPUT);

  pinMode (trigger_pin, OUTPUT); 
  pinMode (echo_pin, INPUT);
  pinMode (buzzer_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  // voltage calculating
  voltageValue = analogRead(voltageSensor);
  voltageOutput = (voltageValue * 5.0)/1024.0 ;
  voltageInput = voltageOutput/(R2/(R1+R2));
  boardValues[0] = n;
  boardValues[1] = voltageInput;

  
  digitalWrite (trigger_pin, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigger_pin, LOW);
  time = pulseIn (echo_pin, HIGH);
  distance = (time * 0.034) / 2;
  Serial.println (distance);        

  delay(15);
  radio.startListening();
  if(radio.available()){
    radio.read(&joyStick,sizeof(joyStick));
    pot1=joyStick[3];
    pot2=joyStick[4];

    servo1=map(pot1,0,180,90,180);
    servo2=map(pot1,0,180,90,0);
    
    x=joyStick[0];
    y=joyStick[1];
    z=joyStick[2];
    switchMode=joyStick[5];
    flipMotion=joyStick[6];

    pwmOutput = map(pot2,0,1023,0,255);

    analogWrite(enA,pwmOutput);
    analogWrite(enB,pwmOutput);
    
    Serial.print("x:");
    Serial.println(x);
    Serial.print("y:");
    Serial.println(y);
    Serial.print("z:");
    Serial.println(z);
    Serial.print("pot1:");
    Serial.println(pot1);
    Serial.print("pot2:");
    Serial.println(pot2);
    Serial.print("flipMotion:");
    Serial.println(flipMotion);

     // up motor control and servo motion
  if(flipMotion > 10){
    digitalWrite(intM1,HIGH);
    digitalWrite(intM2,LOW);
  } else{
     digitalWrite(intM1,LOW);
    digitalWrite(intM2,LOW); 
   
  }


// down motor control
  if(x < -100){
    forwardMotion();
    delay(300);
  }else if(x > 100){
     backwardMotion();
     delay(300);
  }else if(y < -100){
    rightMotion();
    delay(300);
  }else if(y > 100){
    leftMotion();
    delay(300);
  }else{
    stopMotion();
    delay(3);
  }

  // servo motion
    for (pos = 90; pos <= servo1; pos += 1) { 
        myservo1.write(pos);              
        delay(15);                      
      }
      
      for (pos = 90; pos >= servo2; pos -= 1) { 
        myservo2.write(pos);              
        delay(15);                      
      }
      
     for (pos = servo1; pos >= 90; pos -= 1) { 
        myservo1.write(pos);           
        delay(15);                       
      }
      
     for (pos = servo2; pos <= 90; pos += 1) { 
        myservo2.write(pos);              
        delay(15);                       
      }
      //delay(100);
 
}
  delay(15);
  radio.stopListening();
  radio.write(&boardValues,sizeof(boardValues));
  Serial.println(boardValues[0]);
  Serial.println(boardValues[1]);
}
