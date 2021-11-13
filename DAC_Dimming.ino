// DAC -> GPIO25 & GPIO26
int led_dac_pin = 25;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
// Increase the intensity
for(int brightness = 0; brightness <=255; ++brightness)
{
  dacWrite(led_dac_pin, brightness);  //analog output
  delay(30);
}
// Decrease the intensity
for(int brightness = 255; brightness >= 0; --brightness)
{
  dacWrite(led_dac_pin, brightness);  //analog output
delay(30);
}
}
