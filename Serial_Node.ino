

void setup() {

Serial.begin(9600); // Intitializing the Serial Interface with a baud rate

}


void loop() {  

if(Serial.available()>0)  // Checks if there is any data in the Serial Buffer
{
Serial.print(char(Serial.read()));  //  Reads the serial buffer that is in bytes, converts it to char, sends that back to Serial Monitor
}
}