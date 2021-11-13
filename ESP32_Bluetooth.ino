#include "BluetoothSerial.h"

// Check if Bluetooth configurations are enabled in the SDK
// If not, then you have to recompile the SDK 
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial BTSerial;

void setup() {
  Serial.begin(115200);

  //Default Name: ESP32
// If you want to give your own name for the ESP32
// BTSerial.begin("myDevice")  --> Example
  BTSerial.begin();
  Serial.println("Bluetooth has Started!!");
}

void loop() {

// TX from ESP32 to Phone
  if(Serial.available())   // Checks if the Serial Buffer is empty
  {
    BTSerial.write(Serial.read());   // Reads the Serial Buffer & sends the data to the Phone
  }

// RX from Phone to ESP32
  if(BTSerial.available())  //Checks if the Bluetooth Buffer is empty
  {

    Serial.write(BTSerial.read());  // Reads the Bluetooth Buffer & sends data to the Serial Monitor
  
  }

delay(30);

}