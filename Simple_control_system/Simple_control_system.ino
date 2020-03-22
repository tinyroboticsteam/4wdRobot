
#include <IRremote.h>
int receiverpin = 11;//Define the infrared receiving signal pin
int pinI1=A1;//Define I1 interface
int pinI2=A0;//Define I2 interface
int speedpin1=6;//The definition of EA (PWM speed control) interface
int pinI3=A3;//Define the I3 interface
int pinI4=A2;//Define the I4 interface
int speedpin2=5;//The definition of EB (PWM speed control) interface

 
#define ADVAN   0xFF629D   //The remote control >> key 7 forward
#define BAC     0xFFA857   //The remote control << key 8 back
#define STO     0xFF02FD   //The remote control > | key 6 stop
#define left    0xFF22DD  //The remote control - key 5 
#define right   0xFFC23D   //The remote control + key 4
IRrecv irrecv(receiverpin);//Initialize the
decode_results results;//Define the type of structure

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();// Begin to receive
   pinMode(pinI1,OUTPUT);//Define the interface for the output interface
   pinMode(pinI2,OUTPUT);
   pinMode(speedpin1,OUTPUT);
   pinMode(pinI3,OUTPUT);//Define the interface for the output interface
   pinMode(pinI4,OUTPUT);
   pinMode(speedpin2,OUTPUT);
   pinMode(receiverpin,INPUT);
   
   irrecv.enableIRIn();// Begin to receive
}

void loop() 
{
    if (irrecv.decode(&results))
    {
       Serial.println(results.value, HEX);
      switch(results.value)
      {
      case ADVAN://> > key forward
        goForward(1000);
        break;
      case BAC://< < key back
        goBackward(1000);
        break;
         case left://<< turn left key
        goLeft(1000);
        break;
         case right://>> key right
        goRight(1000);
        break;
      case STO://> | key to stop
        stopa();
        break;         
     default:
        delay(100);
        Serial.println(results.value);
      }
      irrecv.resume(); // To receive the next value
    }
    delay(100);
}

void goForward(int a)//go
{
analogWrite(speedpin1,a);//Input analog value set speed  
analogWrite(speedpin2,a);//Input analog value set speed
digitalWrite(pinI1,LOW);//I1 output low level 
digitalWrite(pinI2,HIGH);//I2 output high level
digitalWrite(pinI3,LOW);//I3 output low level 
digitalWrite(pinI4,HIGH);//I4 output high level
delay(100);//Delay time 100 milliseconds

}

void goBackward(int b)//back
{
analogWrite(speedpin1,b);  
analogWrite(speedpin2,b);
digitalWrite(pinI1,HIGH); 
digitalWrite(pinI2,LOW);
digitalWrite(pinI3,HIGH); 
digitalWrite(pinI4,LOW);
delay(100);
}
void goLeft(int c)//Left
{
analogWrite(speedpin1,c); 
analogWrite(speedpin2,c);
digitalWrite(pinI1,LOW); 
digitalWrite(pinI2,HIGH);
digitalWrite(pinI3,HIGH); 
digitalWrite(pinI4,LOW);
delay(100);
}
void goRight(int d)//Right
{
analogWrite(speedpin1,d);  
analogWrite(speedpin2,d);
digitalWrite(pinI1,HIGH);
digitalWrite(pinI2,LOW);
digitalWrite(pinI3,LOW); 
digitalWrite(pinI4,HIGH);
delay(100);
}

void stopa()//stop
{    
digitalWrite(pinI1,LOW);  
digitalWrite(pinI2,LOW); 
digitalWrite(pinI3,LOW);
digitalWrite(pinI4,LOW);    
delay(100);
}
