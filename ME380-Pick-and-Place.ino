void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.write("Led pin set to HIGH");
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.write("Led pin set to LOW");
  delay(1000);
}
