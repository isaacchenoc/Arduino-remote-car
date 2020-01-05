#include <NewPing.h>
#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11);


const int trigA = 7;
const int echoA = 8;
const int trigB = 12;
const int echoB = 13;
const int motorAPin1 = 3;
const int motorAPin2 = 5;
const int motorBPin1 = 4;
const int motorBPin2 = 6;
const int maxDistance = 50;
NewPing sonarA(trigA, echoA, maxDistance);
NewPing sonarB(trigB, echoB, maxDistance);
unsigned int distA;
unsigned int distB;
char c = 'D';

void setup() {
 BT.begin(9600);
 Serial.begin(9600);
  pinMode(motorAPin1, OUTPUT); 
  pinMode(motorAPin2, OUTPUT);  
  pinMode(motorBPin1, OUTPUT); 
  pinMode(motorBPin2, OUTPUT);   
  pinMode(trigA, OUTPUT);
  pinMode(echoA, INPUT);
  pinMode(trigB, OUTPUT);
  pinMode(echoB, INPUT);
}
void(* reset) (void) = 0;

void loop() {

  while (BT.available()){  
  delay(10); 
  c = BT.read(); 
  

Serial.println(c);

 if(c == '8')
  {
  Move();
  delay(100);
  break;
  }

  else if(c=='2')
  {
  Back();
  delay(100);
  break;
  }

  else if (c=='6')
  {
  Rturn();
  delay(100);
  break; 
  }

 else if (c=='4')
 {
  Lturn();
  delay(100);
  break;
 }

 else if (c=='0')
 {
  Stop();
  delay(100);
  break;
 }

 else if (c=='C')
 {
  reset();
  break;  
 }

  }


  
while (!BT.available()){
  if(c!='D'){break;}
  else if (c == 'D'){
distA = sonarA.ping_cm();
distB = sonarB.ping_cm();
Serial.println(distA);
Serial.println(distB);

if (distB>=8){
Rturn();
delay(400);
}

else if (distA>=5 && distB>=5 ) {
 Move();
 delay(500);
 }
 
else if (distA<2 && distB<2){
  Back();
delay(1000);
}

else if (distA>=8) {
Lturn();
delay(400);
}

else {
  Lturn();
  delay(100);
  Rturn();
  delay(100);
  }


}}}
 
void Move(){
    digitalWrite(motorAPin1, HIGH);
    digitalWrite(motorAPin2, LOW);
    digitalWrite(motorBPin1,HIGH);
    digitalWrite(motorBPin2,LOW);
 
}

void Lturn(){    
    digitalWrite (motorAPin1,HIGH);
    digitalWrite (motorAPin2,LOW);
    digitalWrite (motorBPin1,LOW);
    digitalWrite (motorBPin2,HIGH);
   
  }

void Rturn(){
    digitalWrite(motorAPin1, LOW);
    digitalWrite(motorAPin2, HIGH);
    digitalWrite(motorBPin1,HIGH);
    digitalWrite(motorBPin2,LOW);
 
}

void Back(){    
    digitalWrite (motorAPin1,LOW);
    digitalWrite (motorAPin2,HIGH);
    digitalWrite (motorBPin1,LOW);
    digitalWrite (motorBPin2,HIGH);
   
  }

void Stop(){    
    digitalWrite (motorAPin1,LOW);
    digitalWrite (motorAPin2,LOW);
    digitalWrite (motorBPin1,LOW);
    digitalWrite (motorBPin2,LOW);
}



