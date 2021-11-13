#include "BluetoothSerial.h"

// Check if Bluetooth configurations are enabled in the SDK
// If not, then you have to recompile the SDK 
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial BTSerial;

int led = 32;
byte data;

void setup() {
  Serial.begin(115200);

  //Default Name: ESP32
// If you want to give your own name for the ESP32
// BTSerial.begin("myDevice")  --> Example
  BTSerial.begin();
  Serial.println("Bluetooth has Started!!");
  pinMode(led, OUTPUT);
}

void loop() {


// RX from Phone to ESP32
  if(BTSerial.available())  //Checks if the Bluetooth Buffer is empty
  {
    data = BTSerial.read();
    Serial.write(data);  // Reads the Bluetooth Buffer & sends data to the Serial Monitor
  
  }

  if (data == '1')
  {
    digitalWrite(led, HIGH);  // Check if data is '1', then light up the LED
  }

  if (data == '0')
  {
    digitalWrite(led, LOW);   // Check if data is '0', then switch of the Led
  }
delay(30);

}