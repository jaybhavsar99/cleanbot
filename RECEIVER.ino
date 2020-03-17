# include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define CE_PIN  7
#define CSN_PIN 8
#include <Servo.h>

const byte slaveAddress[5] = {'R','x','A','A','A'};
RF24 radio(CE_PIN, CSN_PIN);
int joyStick[5];
int x,y,z,pot1,pot2;

Servo myservo1,myservo2;
int pos = 90;
//int pos1= -90;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0,slaveAddress);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening(); 
  myservo1.attach(9); 
  myservo2.attach(6); 
}

void loop() {
  // put your main code here, to run repeatedly:
  if(radio.available()){
    radio.read(&joyStick,sizeof(joyStick));
    x=joyStick[0];
    y=joyStick[1];
    z=joyStick[2];
    pot1=joyStick[3];
    pot2=joyStick[4];
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
    int servo1=map(pot1,0,180,90,180);
     int servo2=map(pot1,0,180,90,0);
     for (pos = 90; pos <= servo1; pos += 1) { 
    // in steps of 1 degree
    myservo1.write(pos); 
   // myservo2.write(pos);             
    delay(15);                      
  }
  
   for (pos = 90; pos >= servo2; pos -= 1) { 
    // in steps of 1 degree
    myservo2.write(pos);              
    delay(15);                      
  }
  
  for (pos = servo1; pos >= 90; pos -= 1) { 
    myservo1.write(pos);
   // myservo2.write(pos);              
    delay(15);                       
  }
  
  for (pos = servo2; pos <= 90; pos += 1) { 
    myservo2.write(pos);              
    delay(15);                       
  }
  
  }
}
