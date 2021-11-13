int led_pin = 33;

// setting PWM properties
int pwm_channel = 0;
int resolution = 8;
int frequency = 5000;

void setup() {
//  // put your setup code here, to run once:
// Configure the PWM properties to the PWM channel

ledcSetup(pwm_channel, frequency, resolution);
// Attach the PWM channel to the LED pin

ledcAttachPin(led_pin,pwm_channel);
}

void loop() {
  // put your main code here, to run repeatedly:

// Increasing the LED intensity
for(int dutycycle = 0; dutycycle <= 255; ++dutycycle)
{
ledcWrite(pwm_channel,dutycycle);   //analog output
delay(30);
}

//Decreasing the LED Intensity

for(int dutycycle = 255; dutycycle >= 0; --dutycycle)
{
  ledcWrite(pwm_channel, dutycycle);   // analog output
  delay(30);
}
}
