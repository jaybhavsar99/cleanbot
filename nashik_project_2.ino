int ch4; // Here's where we'll keep our channel values
int ch5;
int ch6;

void setup() {
  Serial.begin(9600);

  pinMode(3, INPUT); // Set our input pins as such
  pinMode(4, INPUT);
  pinMode(5, INPUT);
    pinMode(8,  OUTPUT); // Set our input pins as such
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
   pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
     Serial.begin(9600); // Pour a bowl of Serial
}
void loop() 

{
   ch4 = pulseIn(5, HIGH, 25000); // Read the pulse width of 
  ch5 = pulseIn(6, HIGH, 25000); // each channel
  ch6 = pulseIn(7, HIGH, 25000);

  Serial.print("Channel 6:"); // Print the value of //max 2007 to 997 min
  Serial.println(ch4);        // each channel

  if(ch4>1700)
    {

      digitalWrite(8,LOW);
      
      digitalWrite(9,HIGH);


      digitalWrite(10,LOW);


      digitalWrite(11,HIGH);
      Serial.print("forward");
      
    
     
   

      
      
      }
       else if(ch4<1300)                                                                                              
      {
        
      digitalWrite(8,HIGH);
      
      digitalWrite(9,LOW);


      digitalWrite(10,HIGH);


      digitalWrite(11,LOW);
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
        {      digitalWrite(8,HIGH);
      
      digitalWrite(9,LOW);


      digitalWrite(10,LOW);


      digitalWrite(11,HIGH);
      Serial.print("LEFT");
      
          }
      else if(ch5<1300)
      {digitalWrite(8,);
      
      digitalWrite(9,HIGH);


      digitalWrite(10,HIGH);


      digitalWrite(11,LOW);
        }
         if(ch6>1700)                                                                                              
      {
        
        digitalWrite(12,HIGH);//SW
      }
     else                                                                                            
      {
        
        digitalWrite(12,LOW);//SW
      }
          
}
