#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define CE_PIN  7
#define CSN_PIN 8
#include <Servo.h>
#define enA 2
#define enB 3
#define servoMin 125
#define servoMax 575

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

RF24 radio(CE_PIN, CSN_PIN);
const byte addresses[][5]= {"'R','x','A','A','A'","'x','R','A','A','A'"};

int joyStick[7];
int x,y,z,pot1,pot2,switchMode,flipMotion,servo1,servo2,flip=0;
int pwmOutput;

float boardValues[2];
int n=5;

int master=13;

int voltageSensor = A0;
float voltageOutput = 0.0;
float voltageInput = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int voltageValue = 0;

// DOWN MOTORS
int int1 = 23;
int int2 = 24;
int int3 = 25;
int int4= 26;

// for upper motor
int intM1 = 30;
int intM2 = 31;

// servo initialize
Servo myservo1,myservo2;
int pos = 90;

// sonar variables
int trigger_pin = 9;
int echo_pin = 10;
int buzzer_pin = 1; 
int time;
int distance;

// servo angle
int angle=0;

void forwardMotion(){
    digitalWrite(int1,HIGH);
    digitalWrite(int2,LOW);
    digitalWrite(int3,HIGH);
    digitalWrite(int4,LOW);
  }

void backwardMotion(){
  Serial.println("backward");
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
  pwm.begin();
    pwm.setPWMFreq(60); 
  radio.openReadingPipe(1,addresses[0]);
  radio.openWritingPipe(addresses[1]);
  radio.setPALevel(RF24_PA_MAX);

  myservo1.attach(4); 
  myservo2.attach(6);

  pinMode (voltageSensor, INPUT);

  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);
  pinMode(int1,OUTPUT);
  pinMode(int2,OUTPUT);
  pinMode(int3,OUTPUT);
  pinMode(int4,OUTPUT);

  pinMode(intM1,OUTPUT);
  pinMode(intM2,OUTPUT);

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
    
    x=joyStick[0];
    y=joyStick[1];
    z=joyStick[2];
    switchMode=joyStick[5];
    flipMotion=joyStick[6];

    if(flipMotion > 5){
      flip=1;
    }else{
      flip=0; 
    }

    pwmOutput = map(pot2,0,1023,0,255);
    angle=map(pot1,0,180,servoMin,servoMax);

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
  if(flip==1){
    digitalWrite(intM1,HIGH);
    digitalWrite(intM2,LOW);

    // servo motion
    /*
    pwm.setPWM(0,0,angle);
    delay(500);
    pwm.setPWM(1,0,angle);
    delay(500);
    pwm.setPWM(0,0,90); // need to change
    delay(500);
    pwm.setPWM(1,0,90); // need to change
    delay(500);
    */
    for (pos = 90; pos <= servo1; pos += 1) { 
        myservo1.write(pos);              
        delay(5);                      
      }
      
      for (pos = 90; pos >= servo2; pos -= 1) { 
        myservo2.write(pos);              
        delay(5);                      
      }
      
     for (pos = servo1; pos >= 90; pos -= 1) { 
        myservo1.write(pos);           
        delay(5);                       
      }
      
     for (pos = servo2; pos <= 90; pos += 1) { 
        myservo2.write(pos);              
        delay(5);                       
      }
      
      delay(100);
   
  } else{
     digitalWrite(intM1,LOW);
    digitalWrite(intM2,LOW); 
  }

    // down motor control
  if(x < -100){
    //forwardMotion();
    rightMotion();
    delay(100);
  }else if(x > 100){
    // backwardMotion();
    leftMotion();
     delay(100);
  }else if(y < -100){
    //rightMotion(); // forward
    forwardMotion();
    delay(100);
  }else if(y > 100){
    //leftMotion();
    backwardMotion();
    delay(100);
  }else{
    stopMotion();
    delay(100);
  }
/*
    pwm.setPWM(0,0,125);
    delay(500);
    pwm.setPWM(0,0,575);
    delay(500);
 */     
}
   delay(15);
  radio.stopListening();
  radio.write(&boardValues,sizeof(boardValues));
  Serial.println(boardValues[0]);
  Serial.println(boardValues[1]);

}
