/*
LOW -  Occurs when pin in 0
HIGH - Occurs when pin is 1
Rising - 0 to 1
Falling -  1 to 0
Changing - 0 to 1 or 1 to 0
*/
int led = 33;
int led2 = 2;
int button = 32;
int state = 0; 

void IRAM_ATTR callback() //ISR
{
  state = !state;
  digitalWrite(led, state);
}
void setup() {
pinMode(led, OUTPUT);
pinMode(button, INPUT);
pinMode(led2, OUTPUT);
attachInterrupt(digitalPinToInterrupt(button), callback, RISING);
}

void loop() 
{

digitalWrite(led2, HIGH);
delay(2000);
digitalWrite(led2, LOW);
delay(2000);
}
