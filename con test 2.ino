#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define CE_PIN  7
#define CSN_PIN 8
#include<LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 6, 7, 8);// VEE,E,DB4,DB5,DB6,DB7
const int SW_pin = 3; // digital pin connected to switch output
const int X_pin = A0; // analog pin connected to X output
const int Y_pin = A1; // analog pin connected to Y output
const int SW2_pin = 4; // digital pin connected to switch output
const int X2_pin = A2; // analog pin connected to X output
const int Y2_pin = A3;
const int b1 = 5;//BUTTON CONTROLS

#include <Wire.h>
const byte slaveAddress[5] = {'R','x','A','A','A'};
RF24 radio(CE_PIN, CSN_PIN);
int nam[2];
int jam[3];

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    lcd.begin(16, 2);
  radio.begin();
  radio.openWritingPipe(slaveAddress);
  radio.setPALevel(RF24_PA_MAX);
 // radio.setDataRate(RF24_250KBPS);   
    radio.stopListening(); 
    pinMode(SW_pin,INPUT);
    pinMode(X_pin,INPUT);
    pinMode(Y_pin,INPUT);
      pinMode(SW_pin2,INPUT);
    pinMode(X_pin2,INPUT);
    pinMode(Y_pin2,INPUT);
    pinMode(b1,INPUT);
    

}

void loop() {
  
  // put your main code here, to run repeatedly:
   lcd.setCursor(0,0);   
   lcd.setCursor(0,0);   
     lcd.print(" ");// can print required data 
     lcd.setCursor(2,1);
  
  nam[0]=analogRead(A0);// x axis reading from joystick 1
    nam[1]=analogRead(A1);// y axis reading from joystick 1
      jam[0]=analogRead(A2);// x axis reading from joystick 2
    jam[1]=analogRead(A3);// y axis reading from joystick 2
    jam[2]=digitalRead(5);// button status 
   radio.write(&nam,sizeof(nam));
  radio.write(&jam,sizeof(jam));
  

}
