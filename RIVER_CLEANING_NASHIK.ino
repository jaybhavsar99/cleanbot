/*
 RC PulseIn Serial Read out
 By: Nick Poole
 SparkFun Electronics
 Date: 5
 License: CC-BY SA 3.0 - Creative commons share-alike 3.0
 use this code however you'd like, just keep this license and
 attribute. Let me know if you make hugely, awesome, great changes.
 */
 
int ch4; // Here's where we'll keep our channel values
int ch5;
int ch6;
#include <Servo.h>
//Servo servo1;
//Servo servo2;

void setup() {
  Serial.begin(9600);
 // servo1.attach(5);
 // servo2.attach(6);
  pinMode(2, INPUT); // Set our input pins as such
  pinMode(3, INPUT);
  pinMode(4, INPUT);
    pinMode(A0, INPUT);
    pinMode(8,  OUTPUT); // Set our input pins as such
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
   pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
   
  
  

  Serial.begin(9600); // Pour a bowl of Serial

}

void loop() {

  ch4 = pulseIn(2, HIGH, 25000); // Read the pulse width of 
  ch5 = pulseIn(3, HIGH, 25000); // each channel
  ch6 = pulseIn(4, HIGH, 25000);
  //ch1=pulseIn(7, HIGH, 25000);

  Serial.println(ch4);
    if(ch4>1700)
    {

      digitalWrite(8,HIGH);
      
      digitalWrite(9,LOW);


      digitalWrite(10,HIGH);


      digitalWrite(11,HIGH);
      Serial.print("forward");
    
     
   

      
      
      }
       else if(ch4<1300)                                                                                              
      {
        
      digitalWrite(8,LOW);
      
      digitalWrite(9,HIGH);


      digitalWrite(10,LOW);


      digitalWrite(11,HIGH);
       Serial.print("reverse");
        
        
        }
        else
        {
                digitalWrite(8,LOW);
      
      digitalWrite(9,LOW);


      digitalWrite(10,LOW);


      digitalWrite(11,LOW);
          }
        if(ch5>1700)                                                                                              
      {
        
      digitalWrite(8,HIGH);
      
      digitalWrite(9,LOW);


      digitalWrite(10,LOW);


      digitalWrite(11,HIGH);
         Serial.print("left");
        
        
        }
        
       else if(ch5<1300)                                                                                              
      {
        
      digitalWrite(8,LOW);
      
      digitalWrite(9,HIGH);


      digitalWrite(10,HIGH);


      digitalWrite(11,LOW);
         Serial.print("right");
        
        
        }
        else
        {
                          digitalWrite(8,LOW);
      
      digitalWrite(9,LOW);


      digitalWrite(10,LOW);


      digitalWrite(11,LOW);
          }
        if(ch6>1700)                                                                                              
      {
        
        digitalWrite(12,HIGH);//SW
      }
      else if(ch6<1300)                                                                                              
      {
        
        digitalWrite(12,LOW);//SW
      }
     
      
}      
        
        
              
