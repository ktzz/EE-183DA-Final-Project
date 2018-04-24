#include <QTRSensors.h>
#define encoder_L A0
#define encoder_R A7
#define RM_B 5   //right motor
#define RM_F 6
#define LM_F 9  //left motor
#define LM_B 10

#define Kp 0
#define Kd 0

#define setpoint 10 //reading when bot is directly on line

#define MAXSPEED 35


QTRSensorsRC qtr((char[]) {15, 16, 17}, 3);
int left,middle,right;
int lastError = 0;


void setup() {
  Serial.begin(9600);
  pinMode(encoder_L,INPUT);
  pinMode(encoder_R,INPUT);
  for (int i = 0; i < 20; i++)  
  {
    qtr.calibrate();
    delay(20);
  }
  
  Serial.print("Calibration is Done!");
}


void loop() {
 unsigned int sensors[3];

 //Read sensor values
 qtr.read(sensors);
 left=sensors[0];
 middle=sensors[1];
 right=sensors[2];
 Serial.print("\nleft: ");
 Serial.print(left);
 Serial.print("\tmiddle: ");
 Serial.print(middle);
 Serial.print("\tright: ");
 Serial.print(right);

 
// //IR encoders
// Serial.print("\tEncoder_L: ");
// Serial.print(analogRead(encoder_L));
// Serial.print("\tEncoder_R: ");
// Serial.print(analogRead(encoder_R));
// delay(250);


// PID control

int error = position - setpoint;

int motorSpeed = Kp * error + Kd * (error - lastError);
lastError = error;

//Basic Line following

if (middle == 8 && left == 8 && right == 28)  // Brake if not on line
{
     analogWrite(M1B,0);
     analogWrite(M1F,0);
     analogWrite(M2B,0);
     analogWrite(M2F,0);
}

else
{
   if (middle > left && middle && right)  //move forward
     {
       analogWrite(M1B,0);
       analogWrite(M1F,MAXSPEED);
       analogWrite(M2B,0);
       analogWrite(M2F, MAXSPEED);
       Serial.print("Forward");
       delay(250);
     }
     
   if (left > right && left > middle )  // turn right
     {
       analogWrite(M1B,0);
       analogWrite(M1F,0);
       analogWrite(M2B,0);
       analogWrite(M2F,MAXSPEED-5);
       Serial.print("Right");
       delay(250);
     }
    
   if (right > left && right > middle) // turn left
     {
       analogWrite(M1B,0);
       analogWrite(M1F,MAXSPEED-5);
       analogWrite(M2B,0);
       analogWrite(M2F,0);
       Serial.print("Left");
       delay(250);
     }
}

}
