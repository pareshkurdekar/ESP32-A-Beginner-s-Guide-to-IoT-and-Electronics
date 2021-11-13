
int led = 14;
int button = 13;
int buttonState = 0;
void setup() {
  // put your setup code here, to run once:
pinMode(led,OUTPUT);
pinMode(button,INPUT);
digitalWrite(led,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

buttonState = digitalRead(button);

if (buttonState == 1)        // Condition: Pressed
{
  digitalWrite(led,HIGH);    

}
else                         //Condition: Not Pressed
{
  digitalWrite(led,LOW);
}
}
