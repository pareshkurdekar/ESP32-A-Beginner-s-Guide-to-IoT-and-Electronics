int pot_pin = 33;
int value = 0;
void setup() {
  // put your setup code here, to run once:
analogReadResolution(10);
pinMode(pot_pin, INPUT);
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
value = analogRead(pot_pin);
Serial.println(value);
delay(50);

}
