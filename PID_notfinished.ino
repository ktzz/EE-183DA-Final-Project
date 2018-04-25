#include <QTRSensors.h>
#define encoder_L A0
#define encoder_R A7
#define RM_B 5   //right motor
#define RM_F 6
#define LM_F 9  //left motor
#define LM_B 10

#define Kp 0
#define Kd 0
#define Ki 0

#define setpoint 10 //reading when bot is directly on line

#define BASESPEED 35


QTRSensorsRC qtr((char[]) {15, 16, 17}, 3);
int left,middle,right;
int lastError = 0;
int totalError = 0;
int correction = 0;
int Left_Speed, Right_Speed;

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

if(middle == 8 && left == 8 && right == 28) //there is no line
{
	analogWrite(LM_F,Left_Speed);
	analogWrite(LM_B,0);
	analogWrite(RM_F,Right_Speed);
	analogWrite(RM_B,0);
}
else
{	
	if(left>right&&middle>left&&middle>right) // too right
		error = middle-Threshold;
		else if (right>left&&middle>left&&middle>right) // too left
		error = Threshold - middle
	//error>0 (too left), error<0 (too right)

	correction = Kp * error + Kd * (error - lastError) + Ki*totalError ;
	lastError = error;
	totalError+=error;

	Left_Speed=BASESPEED+correction;
	Right_Speed=BASESPEED-correction;

	analogWrite(LM_F,Left_Speed);
	analogWrite(LM_B,0);
	analogWrite(RM_F,Right_Speed);
	analogWrite(RM_B,0);
}

}