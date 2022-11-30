#include <Arduino.h>
#include <WiFi.h>

WiFiServer server(80);

const char* ssid     = "ESP32-Access-Point";
const char* password = "0937565253";
const char* saved_ssid = "";
const char* saved_password = "";
String wifi_state = "disconnected";
String header;
void initial_wifi() {
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(ssid, password);
    server.begin();
}

void connect_wifi() {
  WiFi.softAP(ssid, password);
  WiFi.mode(WIFI_AP_STA);
  IPAddress IP = WiFi.softAPIP();
  WiFi.begin(saved_ssid,saved_password);
  server.begin();
}

void setup() {
    initial_wifi();
}

void loop() {
    WiFiClient client = server.available();
    if (client) {
        if(wifi_state == "disconnected") {
        String currentLine = "";
        while (client.connected()) {
            if (client.available()) {
            char c = client.read();
            Serial.write(c);
            header += c;
            if (c == '\n') {
                if (currentLine.length() == 0) {
                client.println("HTTP/1.1 200 OK");
                client.println("Content-type:text/html");
                client.println("Connection: close");
                client.println();

                if (header.indexOf("GET /connect_wifi/conected") >= 0) {
                    Serial.println("wifi_connect on");
                    wifi_state = "conected";
                } else if (header.indexOf("GET /connect_wifi/disconected") >= 0) {
                    Serial.println("wifi_connect off");
                    wifi_state = "disconected";
                }

                client.println("\
                <!DOCTYPE html><html>\
                <head><meta name='viewport' content='width=device-width, initial-scale=1'>\
                <link rel='icon' href='data:,'>\
                <style>\
                    html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\
                    .button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;\
                    text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}\
                    .button2 {background-color: #555555;}\
                </style></head>\
                <body>\
                <form action='' method='GET'>\
                <p><input type='text' id='ssid' name='ssid' placeholder='ssid'></p>\
                <p><input type='password' id='password' name='password' placeholder='password'></p>\
                <p><a href='/connect_wifi/conecting'><button class='button'>Connect</button></a></p>\
                </form></body></html>");
                break;
                } else {
                currentLine = "";
                }
            } else if (c != '\r') {currentLine += c;}
            }
        }
        header = "";
        client.stop();
        }
    }
}