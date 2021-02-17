#include <xSL01.h>
#include <si1133_config.h>

#include <SI01_CONFIG.h>
#include <xSI01.h>

#include <xSW01.h>

#include <xCore.h>
#include <xVersion.h>

#include <xSN01.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

WiFiClient client;
xSN01 SN01;
xSW01 SW01;
xSI01 SI01;
xSL01 SL01;

const int DELAY_TIME = 10000;
#define RED 12
#define GREEN 13
#define BLUE 5

const char* ssid = "httr";               // your network SSID (name)
const char* pass = "Soxydog1"; 

void setup() {
  Serial.begin(115200);

  // Set the I2C Pins for CW01
  #ifdef ESP8266
    Wire.pins(2, 14);
  #endif
  
  Wire.begin();
  
  //SW01
  SW01.begin();
  SL01.begin();
  SN01.begin();
  SI01.begin();
  

  delay(DELAY_TIME); //Gives time for sensors to normalize
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  WIFI_connect();
}

void loop() {
  checkSW01();
  checkSL01();
  checkSN01();
  checkSI01();
  Serial.println();
  delay(1000);
}

void checkSI01() {
  SI01.poll();
  //Gyro
  Serial.print("SI01 - Gyro: ");
  Serial.print(SI01.getGX(), 2);
  Serial.print(", ");
  Serial.print(SI01.getGY(), 2);
  Serial.print(", ");
  Serial.print(SI01.getGZ(), 2);

  //Acceleration
  Serial.print(".  Acc: ");
  Serial.print(SI01.getAX(), 2);
  Serial.print(", ");
  Serial.print(SI01.getAY(), 2);
  Serial.print(", ");
  Serial.print(SI01.getAZ(), 2);

  //Attitude
  Serial.print(".  Roll: ");
  Serial.print(SI01.getRoll(), 2);
  Serial.print(".  Pitch :");
  Serial.print(SI01.getPitch(), 2);
  Serial.print(".  GForce :");
  Serial.println(SI01.getGForce(), 2);
}

void checkSL01() {
  //SL01
  float lux;
  float uv;
  uv = 0;
  lux = 0;
  SL01.poll();
  lux = SL01.getLUX();
  uv = SL01.getUVA();
  Serial.print("SL01 - Ambient Light Level: ");
  Serial.print(lux);
  Serial.print(".  ");
  Serial.print("UVA Intersity: ");
  Serial.print(uv);
  Serial.println(" uW/m^2");
}

void checkSN01() {
  String time;
  long latitude = 0;
  long longitude = 0;
  String date;
  SN01.poll();

  date = SN01.getDate();
    
  time = SN01.getTime();
  latitude = SN01.getLatitude();
  longitude = SN01.getLongitude();
    
  Serial.print("SN01 - GPS Time: ");
  Serial.print(time);
  Serial.print(".  GPS Date: ");
  Serial.print(date);
  Serial.print(".  GPS Latitude: ");
  Serial.print(latitude);
  Serial.print(".  GPS longitude: ");
  Serial.println(longitude);
}

void checkSW01() {
  //SW01
  float pressure;
  pressure = 0;
  float alt;
  alt = 0;
  float tempF;
  tempF = 0;
  SW01.poll();
  tempF = SW01.getTempF();
  pressure = SW01.getPressure();
  alt = SW01.getAltitude(pressure);
  Serial.print("SW01 - Output Temp: ");
  Serial.print(tempF);
  Serial.print("deg F.  ");
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.print(" Pa.  ");
  Serial.print("Altitude: ");
  Serial.print(alt);
  Serial.println(" m.");
}

//Connects to WIFI and lights up some LEDs
void WIFI_connect() {
  if (WiFi.status() != WL_CONNECTED) {
    digitalWrite(GREEN, LOW);
    
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
      Serial.println("Connected to WIFI!");
    }
  }
}
