hw_timer_t* timer = NULL;  // Configure timer

/*

Clk Freq = 80MHz  
Timer Counter (64 bit)
Increments the counter 80 000 000  times per second
Pre Scaler divides the input frequency and the timer uses the new freq
Pre Scalar (16 bit) - 80
New Freq = 80 000 000 / 80 ==> 1 000 000 (1MHz)
Now, Increments the counter 1 000 000  times per second
Inverse of this provides us, 1 increment every 1 microsecond (F = 1/T)

*/
int led = 33;
int led2 = 2;
int state = 0;

void IRAM_ATTR callback() {  // ISR
  // ISR
  state = !state;

  digitalWrite(led, state);  // Toggles LED
  Serial.println("Interrupt");
}
void setup() {

  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);

  timer = timerBegin(0, 80, true);               // Start the Timer
  timerAttachInterrupt(timer, &callback, true);  // ATtach the interrupt to the ISR
  timerAlarmWrite(timer, 1000000, true);         //
  timerAlarmEnable(timer);                       // Enable the timer
  Serial.begin(9600);
}

void loop() {

digitalWrite(led2, HIGH);
delay(2000);
digitalWrite(led2, LOW);
delay(2000);
}

