#include <QTRSensors.h>
#define encoder_L A0
#define encoder_R A7
#define M1B 5
#define M1F 6
#define M2F 9
#define M2B 10
QTRSensorsRC qtr((char[]) {15, 16, 17}, 3);
int left,middle,right;
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
 //IR encoder
 Serial.print("\tEncoder_L: ");
 Serial.print(analogRead(encoder_L));
 Serial.print("\tEncoder_R: ");
 Serial.print(analogRead(encoder_R));
 delay(250);
 // testing motor forward
 analogWrite(M1B,0);
 analogWrite(M1F,50);
 analogWrite(M2B,0);
 analogWrite(M2F,50);
}
