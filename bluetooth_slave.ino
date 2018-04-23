#include <QTRSensors.h>
#define encoder_L A0
#define encoder_R A7
#define M1B 5
#define M1F 6
#define M2F 9
#define M2B 10
#define ledPin 13
#define MAXSPEED 30

QTRSensorsRC qtr((char[]) {15, 16, 17}, 3);
int left, middle, right;
int state = 0;
unsigned int sensors[3];

void setup() {
  Serial.begin(38400);
  pinMode(ledPin, OUTPUT);
  pinMode(encoder_L, INPUT);
  pinMode(encoder_R, INPUT);
  digitalWrite(ledPin, HIGH); //LED Testing
//  //Line detector calibration
//  for (int i = 0; i < 20; i++)
//  {
//    qtr.calibrate();
//    delay(20);
//  }
//  Serial.print("Calibration is Done!");
}

void loop() {
//  //IR sensors (line detector)
//  qtr.read(sensors);
//  left = sensors[0];
//  middle = sensors[1];
//  right = sensors[2];
//  Serial.print("\nleft: ");
//  Serial.print(left);
//  Serial.print("\tmiddle: ");
//  Serial.print(middle);
//  Serial.print("\tright: ");
//  Serial.print(right);
  //IR encoder (on wheels)
  Serial.print("\tEncoder_L: ");
  Serial.print(analogRead(encoder_L));
  Serial.print("\tEncoder_R: ");
  Serial.print(analogRead(encoder_R));
  delay(250);
  //Bluetooth Communication
  if (Serial.available() > 0) {
    Serial.print("\tDevice Connected: state=");
    state = Serial.read();
  }
  else Serial.print("\tNo Connection: state=");
  if (state == 9) {
    digitalWrite(ledPin, HIGH);
    Serial.println("9");
    state = 0;
  }
  else if (state == 0) {
    digitalWrite(ledPin, LOW);
    Serial.println("0");
  }
  delay(200);
  //Motion Replication (Down here)
  //Motion Mirroring (Down here)
  //Symetric Drawing (Down here)
}
