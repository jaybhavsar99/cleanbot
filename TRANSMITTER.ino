#include <LiquidCrystal.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN  9
#define CSN_PIN 10

#include <Wire.h>

const byte slaveAddress[][5] = {"'R','x','A','A','A'","'x','R','A','A','A'"};
RF24 radio(CE_PIN, CSN_PIN);
int joyStick[7];
float receivedReading[2];

// lcd display
LiquidCrystal lcd(8, 6, 5, 4, 3, 2);



// switchButton 
int switchButton = A5;
int buttonState = 0;

int flipButton = A2;
int flipButtonState= 0;

// for joystick
int VRx = A0;
int VRy = A1;
int SW = 7;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

// for pot
int pot1=A4;
int pot2=A3; 

int potReading1=0;
int potReading2=0;

int mapPot1=0;
int mapPot2=0;

// receiver
int test=0;

// voltage reading
float voltageReading = 0.0;


void setup() {
  // put your setup code here, to run once:
  
  lcd.begin(16, 2);
  lcd.print("hello");

  Serial.begin(9600);
  radio.begin();
  
  radio.openWritingPipe(slaveAddress[0]);
  radio.openReadingPipe(1, slaveAddress[1]);
  radio.setPALevel(RF24_PA_MAX);
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 
  pinMode(switchButton, INPUT);
  pinMode(flipButton, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  radio.stopListening(); 
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  potReading1 = analogRead(pot1);
  potReading2 = analogRead(pot2);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  mapPot1 = map(potReading1, 0, 1023, -38, 180);
  //mapPot2 = map(potReading2, 0, 1023, -38, 180);
  
  // switch button
  buttonState = analogRead(switchButton);
  Serial.print("switch: ");
  Serial.println(buttonState);
  flipButtonState = analogRead(flipButton);
  Serial.print("flip: ");
  Serial.println(flipButtonState);
  
  joyStick[0]=mapX;
  joyStick[1]=mapY;
  joyStick[2]=SW_state;
  joyStick[3]=mapPot1;
  joyStick[4]=potReading2;
  joyStick[5]=buttonState;
  joyStick[6]=flipButtonState;

  Serial.print("X: ");
  Serial.print(joyStick[0]);
  Serial.print(" | Y: ");
  Serial.print(joyStick[1]);
  Serial.print(" | Button: ");
  Serial.println(joyStick[2]);
 
  Serial.print("pot1-> ");
  Serial.println(mapPot1);
  Serial.print("pot2-> ");
  Serial.println(potReading2);

  lcd.setCursor(0, 0);
  lcd.print("speed");
  lcd.setCursor(5, 0);
  lcd.print("-");
  lcd.setCursor(6, 0);
  lcd.print(potReading2);
  lcd.setCursor(0, 1);
  lcd.print("voltage");
  lcd.setCursor(7, 1);
  lcd.print("-");
 
  radio.write(&joyStick,sizeof(joyStick));
  delay(5);
  radio.startListening();
  if(radio.available()){
    radio.read(&receivedReading,sizeof(receivedReading));
    test = receivedReading[0];
    voltageReading = receivedReading[1];
    Serial.println(test);
    Serial.println(voltageReading);
  }
  lcd.setCursor(8, 1);
  lcd.print(voltageReading);
  //delay(1000);
}
