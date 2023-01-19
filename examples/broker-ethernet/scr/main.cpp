#include <Arduino.h>

#include <SPI.h>
#include <Ethernet.h>

#define TINY_MQTT_DEBUG 1
// #define TINY_MQTT_ASYNC

#include <TinyConsole.h>
#include "TinyMqtt.h"

#define PORT 1883
MqttBroker broker(PORT);


//RESET_P 26 rst pin from W5500 is connected to ESP to GPIO26
#define RESET_P	26

//change your network settings
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0xa1 };
IPAddress ip(192, 168, 8, 240);
IPAddress dns(8, 8, 8, 8);
IPAddress gw(192, 168, 8, 1);
IPAddress subnet(255, 255, 255, 0);



void setup() {
  Serial.begin(115200);
  Serial << endl << endl << "simple W5500 mqtt broker" << endl;

  Ethernet.init(5); // pin for CS => on some boards might be written SS
  Serial.print("Resetting Ethernet Board...  ");
  pinMode(RESET_P, OUTPUT);
  digitalWrite(RESET_P, HIGH);
  delay(250);
  digitalWrite(RESET_P, LOW);
  delay(50);
  digitalWrite(RESET_P, HIGH);
  delay(350);
  Serial.println("Eth reset done.");
  delay(1000);
  Ethernet.begin(mac, ip, dns, gw, subnet);
  delay(5000);
  if (Ethernet.hardwareStatus() == EthernetNoHardware) { Serial.println("XXXXXXXXXXXXXXXXX NO ETHERNET MODUL XXXXXXXXXXXXXXXXX"); }
  if (Ethernet.linkStatus() == LinkOFF) { Serial.println("XXXXXXXXXXXXXXXXX Ethernet cable disconnected XXXXXXXXXXXXXXXXX"); }
  Serial << endl;


  // Serial << TinyConsole::green << "Connected to: " << ssid << " IP address: " << WiFi.localIP() << endl;

  broker.begin();
  Serial << "Broker ready!" ;//<< WiFi.localIP() << " on port " << PORT << endl;
}

void loop() {
  broker.loop();
}

