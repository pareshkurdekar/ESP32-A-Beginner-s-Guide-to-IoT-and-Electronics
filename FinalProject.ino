#include <WiFi.h>

#include "Adafruit_MQTT.h"

#include "Adafruit_MQTT_Client.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   23
#define OLED_CLK    18
#define OLED_DC     16
#define OLED_CS     5
#define OLED_RESET  17
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
  
#define WLAN_SSID       "*******"

#define WLAN_PASS       "********"

#define AIO_SERVER      "io.adafruit.com"

#define AIO_SERVERPORT  1883                  

#define AIO_USERNAME    "#######"

#define AIO_KEY         "######"

int relay=2;

WiFiClient client;     // Create an ESP32 WiFiClient class to connect to the MQTT server.

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);        // Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.

Adafruit_MQTT_Subscribe Relay_Control = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay_Toggle");

void MQTT_connect();
void oled();
void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  Serial.begin(115200);

  delay(10);

pinMode(relay,OUTPUT);
digitalWrite(relay, HIGH);
 // Connect to WiFi access point.

  Serial.println(); Serial.println();

  Serial.print("Connecting to ");
  oled("Connecting to " + String(WLAN_SSID));
  Serial.println(WLAN_SSID);
delay(1000);
 

  WiFi.begin(WLAN_SSID, WLAN_PASS);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.println();

 Serial.println("WiFi connected");
oled("WiFi connected");
delay(1000);
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  
  mqtt.subscribe(&Relay_Control);
   MQTT_connect();

  
}

uint32_t x=0;

void loop() {


Adafruit_MQTT_Subscribe *subscription;

  while ((subscription = mqtt.readSubscription(5000))) {

    if (subscription == &Relay_Control) {

      Serial.print(F("Got: "));

      Serial.println((char *)Relay_Control.lastread);

       if (!strcmp((char*) Relay_Control.lastread, "ON"))

      {

        digitalWrite(relay, LOW);
      oled("Relay State: ON");
      }

      else

      {

        digitalWrite(relay, HIGH);
      oled("Relay State: OFF");

      }

    }

  }

 

 

}

void oled(String text)
{
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(1);
display.setCursor(0,0);
display.println(text);
display.display();  
delay(1000);
}

void MQTT_connect() {

  int8_t ret;

  // Stop if already connected.

  if (mqtt.connected()) {

    return;

  }

 Serial.print("Connecting to MQTT... ");
oled("Connecting to MQTT... ");
delay(1000);
uint8_t retries = 3;

  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected

       Serial.println(mqtt.connectErrorString(ret));

       Serial.println("Retrying MQTT connection in 5 seconds...");

       mqtt.disconnect();

       delay(5000);  // wait 5 seconds

       retries--;

       if (retries == 0) {

         // basically die and wait for WDT to reset me

         while (1);

       }

  }

  Serial.println("MQTT Connected!");
oled("MQTT Connected!");
delay(1000);  
}
