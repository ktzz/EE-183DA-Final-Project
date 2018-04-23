#define ledPin 13
int state=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,HIGH);
  Serial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    state=Serial.read();
  }


  if(state==9){
    digitalWrite(ledPin,HIGH);
    Serial.println("9");
    state=0;
  }
  else if(state==0){
    digitalWrite(ledPin,LOW);
    Serial.println("0");
    state=0;
  }
  delay(200);
}
