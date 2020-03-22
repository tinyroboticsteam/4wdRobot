
#include <IRremote.h>
int receiverpin = 11;//Define the infrared receiving signal pin
int pinI1=A1;//Define I1 interface
int pinI2=A0;//Define I2 interface
int speedpin1=6;//The definition of EA (PWM speed control) interface
int pinI3=A3;//Define the I3 interface
int pinI4=A2;//Define the I4 interface
int speedpin2=5;//The definition of EB (PWM speed control) interface

int speedLeft = 0;
int speedRight = 0;
int stepp = 40;
 
#define ADVAN   0xFF629D   //The remote control >> key 7 forward
#define BAC     0xFFA857   //The remote control << key 8 back
#define STO     0xFF02FD   //The remote control > | key 6 stop
#define left    0xFF22DD  //The remote control - key 5 
#define right   0xFFC23D   //The remote control + key 4
#define ONE     0xFFA25D
#define THREE   0xFFE21D
#define SEVEN   0xFFE01F
#define NINE    0xFF906F

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
        goForward(100);
        break;
      case ONE://> > key forward
        goOne(stepp);
        break;
      case THREE://> > key forward
        goThree(stepp);
        break;
      case SEVEN://> > key forward
        goSeven(stepp);
        break;
      case NINE://> > key forward
        goNine(stepp);
        break;
      case BAC://< < key back
        goBackward(100);
        break;
         case left://<< turn left key
        goLeft(100);
        break;
         case right://>> key right
        goRight(100);
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

void goForward(int d)//go
{
  speedLeft = d;
  speedRight = d;
analogWrite(speedpin1,d);//Input analog value set speed  
analogWrite(speedpin2,d);//Input analog value set speed
digitalWrite(pinI1,LOW);//I1 output low level 
digitalWrite(pinI2,HIGH);//I2 output high level
digitalWrite(pinI3,LOW);//I3 output low level 
digitalWrite(pinI4,HIGH);//I4 output high level
delay(100);//Delay time 100 milliseconds

}

void goBackward(int d)//back
{
  speedLeft = d;
  speedRight = d;
analogWrite(speedpin1,d);  
analogWrite(speedpin2,d);
digitalWrite(pinI1,HIGH); 
digitalWrite(pinI2,LOW);
digitalWrite(pinI3,HIGH); 
digitalWrite(pinI4,LOW);
delay(100);
}
void goLeft(int d)//Left
{
  speedLeft = d;
  speedRight = d;
analogWrite(speedpin1,d); 
analogWrite(speedpin2,d);
digitalWrite(pinI1,LOW); 
digitalWrite(pinI2,HIGH);
digitalWrite(pinI3,HIGH); 
digitalWrite(pinI4,LOW);
delay(100);
}
void goRight(int d)//Right
{
  speedLeft = d;
  speedRight = d;
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
  speedLeft = 0;
  speedRight = 0;
digitalWrite(pinI1,LOW);  
digitalWrite(pinI2,LOW); 
digitalWrite(pinI3,LOW);
digitalWrite(pinI4,LOW);    
delay(100);
}

void goOne(int d)//Right
{
  speedLeft +=d;
  if(speedLeft>255) speedLeft=255;
  analogWrite(speedpin2,speedLeft);  
  delay(100);
}

void goThree(int d)//Right
{
  
speedRight +=d;
  if(speedRight>255) speedRight=255;

  analogWrite(speedpin1,speedRight);  
delay(100);
}

void goSeven(int d)//Right
{
speedLeft -=d;
if(speedLeft<0) speedLeft=0;
  analogWrite(speedpin2,speedLeft);  
delay(100);
}

void goNine(int d)//Right
{
speedRight -=d;
if(speedRight<0) speedRight=0;

  analogWrite(speedpin1,speedRight);  
delay(100);
}
