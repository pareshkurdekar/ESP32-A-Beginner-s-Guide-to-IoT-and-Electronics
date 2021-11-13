#define RXD2 16
#define TXD2 17
/*
UART Pins
UART	  RX IO	  TX IO	

UART0	  GPIO3	  GPIO1	
UART1	  GPIO9	  GPIO10	
UART2	  GPIO16	GPIO17

  UART0 is used to communicate with the ESP32 for programming and during reset/boot.
  UART1 is unused and can be used for your projects. Some boards use this port for SPI Flash access
  UART2 is unused and can be used for your projects.
 
*/
void setup() {
  Serial.begin(9600);

  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  // Format for setting a serial port is:  Serial2.begin(baud_rate, protocol, RX pin, TX pin);
  // 8N1 -> 1 start bit, 8 data bits, 1 stop bit


}

void loop() { // Choose Serial1  or Serial2 
  
Serial.println("Sending Data to NodeMCU");   // Debugging Purpose
Serial2.println("Hello, this is ESP32");     // Data to be sent
delay(1000);
}