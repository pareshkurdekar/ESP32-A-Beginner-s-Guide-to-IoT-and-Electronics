
int led = 14;
int button = 13;
int curr_buttonState = 0;
int prev_buttonState = 0;
int toggle = LOW;
void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  pinMode(button,INPUT);
  digitalWrite(led,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
 
curr_buttonState = digitalRead(button);

if (curr_buttonState == 1 && prev_buttonState ==0)
{
  toggle = !toggle;
  prev_buttonState = 1;
}
else
{
  prev_buttonState = digitalRead(button);
}
digitalWrite(led,toggle);
} 
