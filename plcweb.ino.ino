// plc에서 html 작성 참조 : https://youtu.be/Ule_wKCxJZc
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

String sChipId="";
char cChipId[40]="";
ESP8266WebServer server(80);
String ss;

void handleRoot();
void handleOnOff();
void handleOnOffAll();
void handleScan();
void handleWifi();
void handleNotFound();
void cal();

//int LED = LED_BUILTIN;// 사용하지 마세요 serial1 통신과 충돌합니다.
int ledOn[]={0, 0, 0, 0, 0};
boolean flag = false;

void setup() {

  // put your setup code here, to run once:
  Serial.begin(19200);
  Serial1.begin(19200);


  sChipId = "LJW-"+String(ESP.getChipId(),HEX);
  sChipId.toCharArray(cChipId,sChipId.length()+1);
  Serial.println(sChipId);

  //WiFiManager
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  WiFiManager wm;
  // wm.resetSettings(); //reset settings - for testing

  if (!wm.autoConnect(cChipId)) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.restart();
    delay(1000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("connected... :)");

  server.on("/", handleRoot);
  server.on("/on", handleOnOff);
  server.on("/onAll",handleOnOffAll);
  server.on("/scan", handleScan);
  server.on("/wifi", handleWifi);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  flag = true;
}

void loop() {
  server.handleClient();

}
