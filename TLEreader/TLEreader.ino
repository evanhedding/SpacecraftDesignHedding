#include <xCore.h>
#include <xVersion.h>

#include <SSD1306init.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>
#include <xOD01.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "httr";               // your network SSID (name)
const char* pass = "Soxydog1";             // your network password
char servername[]= "celestrak.com";           // Celestrak Server

WiFiClient client;
xOD01 OD01;

#define RED 12
#define GREEN 13
#define BLUE 5

void setup() {
  Serial.begin(115200);
  #ifdef ESP8266
  Wire.pins(2, 14);
  #endif
  Wire.begin();
  OD01.begin();
  OD01.println("Attempting to connect to WiFi");
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  OD01.println("Attempting to connect to WiFi");
  WIFI_connect();
  OD01.println("Connected to wifi");
  OD01.println("\nStarting connection with server...");
  makeRequest();
}

void makeRequest(){
  // if you get a connection, report back via serial:
  OD01.clear();
  if (client.connect(servername, 80)) {
    OD01.println("connected to server");
    Serial.println();
    Serial.print("TLE for: ");
    // Make HTTP request:
    client.println("GET /NORAD/elements/stations.txt HTTP/1.0");     // rest of url for your chosen txt file, i.e extension following celestrak.com , Replace everything EXCEPT: GET HTTP/1.0
    client.println();                                                         
 }
    
   // if there are incoming bytes available
   // from the server, read them and print them:
 char c;
 int lineCounter=0; 
 while (!client.available()){
  // while loop runs while waiting for server availability
 }

// Skip HTTP headers
 char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders))
  {
    OD01.println(F("Invalid response"));
    return;
  }

 while (client.available()) {
    c = client.read();
    Serial.print(c);
    
    if (c == '\n'){
      lineCounter = lineCounter+1;
    }

    if (lineCounter==3){
      client.stop();
      break;
    }
  }

  // if the server becomes disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    OD01.println("disconnecting from server");
    client.stop();
  }
}



//Connects to WIFI and lights up some LEDs
void WIFI_connect() {
  if (WiFi.status() != WL_CONNECTED) {
    digitalWrite(GREEN, LOW);
    // Connect to WiFi access point.
    Serial.println(); Serial.println();
    OD01.print("Connecting to :");
    OD01.print("[");
    OD01.print(ssid);
    OD01.print("]");

    // Start ESP8266 STA mode
    WiFi.begin(ssid, pass);

    // check connection status
    while (WiFi.status() != WL_CONNECTED) {
      digitalWrite(RED, HIGH);
      delay(100);
      digitalWrite(RED, LOW);
      delay(100);
      Serial.print(".");
    }
    if (WiFi.status() == WL_CONNECTED) {
      digitalWrite(GREEN, HIGH);
      OD01.println("[CONNECTED]");
    }
  }
}

void loop() {
  //makeRequest();
}
