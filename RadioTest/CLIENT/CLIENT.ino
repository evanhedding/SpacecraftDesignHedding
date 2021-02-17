#include <xCS11_SDU.h>

#include <xRL0x.h>
#include <SC18IS602.h>

#include <xCore.h>

#define Serial SerialUSB
#define RL03_FREQ 915.0

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);

  // Set the RGB Pin directions
  //pinMode(LED_RED, OUTPUT);
  //pinMode(LED_GREEN, OUTPUT);
  //pinMode(LED_BUILTIN, OUTPUT);

  // Start the I2C Comunication
  #ifdef ESP8266
  Wire.pins(2,14);
  Wire.setClockStretchLimit(15000);
  #endif
  Wire.begin();
  
  if (!RL0X.begin()) {
    Serial.println("Check the connector to CR01");
    
  } else {
    // RL0X Initialized correctly
    RL0X.setModemConfig(RL0X.Bw125Cr48Sf4096);
    RL0X.setFrequency(RL03_FREQ);
    RL0X.setTxPower(23, false);
  }
}

void loop() {
  Serial.println("Sending to RL0X Server");

  uint8_t data[] = "Hello World!";
  delay(100);
  RL0X.send(data, sizeof(data));

  uint8_t buf[195];
  uint8_t len = sizeof(buf);

  if (RL0X.waitAvailableTimeout(3000)) {
    if (RL0X.recv(buf, &len)) {
      Serial.print("got reply: ");
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(RL0X.lastRssi(), DEC);
    } else {
      Serial.println("recv failed");
    }
  } else {
    Serial.println("No reply, is the RL01 server running ?");
  }
}
