void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.write(9);
  delay(200);
  Serial.write(0);
  delay(200);
}
