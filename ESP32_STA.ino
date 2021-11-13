#include <WiFi.h>
#include <WebServer.h>

/*Put your SSID & Password*/
const char* ssid = "Vasanth";  // Enter SSID here
const char* password = "9443914610";  //Enter Password here


WebServer server(80);  // port at which the server communicates  wit the clients

uint8_t LED1pin = 2;
bool LED1status = LOW;   // state of led 1

uint8_t LED2pin = 32;
bool LED2status = LOW;   // state of led 2

void setup() {
  Serial.begin(115200);
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);
  
  Serial.println("Connecting to ");
  Serial.println(ssid);
  
    
  WiFi.begin(ssid, password);    //  Connect to your local wi-fi network

  //check if Wi-Fi is connected to the Network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
  
  // Handler functions
  
  server.on("/", handle_OnConnect);       // handle_OnConnect is called when the IP address is entered and the Webserver has started
  server.on("/led1on", handle_led1on);    // the ledbutton is assigned to handle_led1on. Called when the button 1 is pressed to 'ON' Condition
  server.on("/led1off", handle_led1off);  // the ledbutton is assigned to handle_led1off. Called when the button 1 is pressed to 'OFF' Condition
  
  server.on("/led2on", handle_led2on);    // the ledbutton is assigned to handle_led2on. Called when the button 2 is pressed to 'ON' Condition
  server.on("/led2off", handle_led2off);  // the ledbutton is assigned to handle_led2off. Called when the button 2 is pressed to 'OFF' Condition
 
  server.onNotFound(handle_NotFound);     // when wrong url is entered
  
  server.begin();   // Starting the server
  
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();    // for the server to listen to multiple connections at the same time
  
  if(LED1status)
  {
    digitalWrite(LED1pin, HIGH);
  }
  else
  {
    digitalWrite(LED1pin, LOW);
  }
  
  if(LED2status)
  {
    digitalWrite(LED2pin, HIGH);
  }
  else
  {
    digitalWrite(LED2pin, LOW);
  }
}


// Web Server handler function. These functions are generally called to display the webserver and to take necessary actions when a button is pressed
// and to update the webserver based on the action took by the user.

//Handle_on connect is called initially when the Web server starts 

void handle_OnConnect() {
  LED1status = LOW;
  LED2status = LOW;
  Serial.println("LED 1 Status: OFF | LED 2 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status)); 
}

// When Button 1 is pressed to 'ON', handle_led1on funtion is called. It updates the webserver with the current states of the LED
void handle_led1on() {
  LED1status = HIGH;
  Serial.println("LED 1 Status: ON");
  server.send(200, "text/html", SendHTML(true,LED2status)); 
}


// When Button 1 is pressed to 'OFF', handle_led1off funtion is called. It updates the webserver with the current states of the LED
void handle_led1off() {
  LED1status = LOW;  // 
  Serial.println("LED 1 Status: OFF");
  server.send(200, "text/html", SendHTML(false,LED2status)); 
}

// When Button 2 is pressed to 'ON', handle_led2on funtion is called. It updates the webserver with the current states of the LED
void handle_led2on() {
  LED2status = HIGH;
  Serial.println("LED 2 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status,true)); 
}

// When Button 2 is pressed to 'OFF', handle_led2off funtion is called. It updates the webserver with the current states of the LED
void handle_led2off() {
  LED2status = LOW;
  Serial.println("LED 2 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,false)); 
}

//When the user enters the wrong url, 'Not Found' is displayed
void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}



//HTMl code for displaying the server which is used to update the server based on the inputs

String SendHTML(uint8_t led1stat,uint8_t led2stat){
  
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";   // Title of the Webserver
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #554444;margin: 50px auto 30px;} h3 {color: #111144;margin-bottom: 50px;}\n";    // Colour & Size of Heading
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 5px;}\n";
 // Size of button, Padding,design
 
  ptr += ".button-on {background-color: #228B22;}\n";               // Color of Button in ON State
  ptr += ".button-on:active {background-color: #228B22;}\n";        // Color of Button (when it is being pressed) in ON State
  ptr += ".button-off {background-color: #FF0000;}\n";              // Color of Button in OFF State
  ptr += ".button-off:active {background-color: #FF0000;}\n";       // Color of Button (when it is being pressed) in OFF State
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";  // Size of Text in Button
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  
  ptr += "<h1>ESP32 Course - Webserver</h1>\n";          // Heading shown on the Webserver
  ptr += "<h3>ESP32 used in Station(STA) Mode</h3>\n";  // any thing that starts with <hx> is heading where x tells the number which decides the size of the text

  
  if (led1stat) 
  { 
    ptr += "<p>LED1 Status: ON</p><a class=\"button button-on\" href=\"/led1off\">ON</a>\n"; 
  }  // when the button is pressed led1state is updated and the button shows a different design
  else 
  {
    ptr += "<p>LED1 Status: OFF</p><a class=\"button button-off\" href=\"/led1on\">OFF</a>\n";
  }  // when the button is not pressed led1state is updated and the button shows a different design
  // same as above
  if (led2stat) 
  {
    ptr += "<p>LED2 Status: ON</p><a class=\"button button-on\" href=\"/led2off\">ON</a>\n";
  } 
  else {
    ptr += "<p>LED2 Status: OFF</p><a class=\"button button-off\" href=\"/led2on\">OFF</a>\n";
  }

  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}