// #include <Arduino.h>
// #include <WiFi.h>

// const char* ssid     = "ESP32-Access-Point";
// const char* password = "0937565253";

// const char* saved_ssid = "";
// const char* saved_password = "";

// WiFiServer server(80);

// String header;

// String output26State = "disconnected";
// const int output26 = 2;

// String wifi_state = "disconnected";
// void initial_wifi() {
//   Serial.print("Setting AP (Access Point)…");
//   WiFi.softAP(ssid, password);
//   IPAddress IP = WiFi.softAPIP();
//   Serial.print("AP IP address: ");
//   Serial.println(IP);
//   server.begin();
// }
// void connect_wifi() {
//   Serial.print("Connecting wifi .....");
//   WiFi.softAP(ssid, password);
//   WiFi.mode(WIFI_AP_STA);
//   IPAddress IP = WiFi.softAPIP();
//   Serial.print("Connect IP address: ");
//   WiFi.begin(saved_ssid,saved_password); 
//   Serial.println(saved_ssid);
//   server.begin();
// }
// void setup() {
//   Serial.begin(115200);
//   pinMode(output26, OUTPUT);
//   digitalWrite(output26, LOW);
//   initial_wifi();
// }
// void loop(){
//   WiFiClient client = server.available();
//   if (client) {
//     if(wifi_state == "disconnected") {
//       Serial.println("New Client.");
//       String currentLine = "";
//       while (client.connected()) {
//         if (client.available()) {
//           char c = client.read();
//           Serial.write(c);
//           header += c;
//           if (c == '\n') {
//             if (currentLine.length() == 0) {
//               client.println("HTTP/1.1 200 OK");
//               client.println("Content-type:text/html");
//               client.println("Connection: close");
//               client.println();

//               if (header.indexOf("GET /connect_wifi/conected") >= 0) {
//                 Serial.println("wifi_connect on");
//                 wifi_state = "conected";
//               } else if (header.indexOf("GET /connect_wifi/disconected") >= 0) {
//                 Serial.println("wifi_connect off");
//                 wifi_state = "disconected";
//               }

//               client.println("\
//               <!DOCTYPE html><html>\
//               <head><meta name='viewport' content='width=device-width, initial-scale=1'>\
//               <link rel='icon' href='data:,'>\
//               <style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\
//               .button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;\
//               text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}\
//               .button2 {background-color: #555555;}</style></head>\
//               <body><h1>ESP32 Web Server</h1>\
//               <form action='' method='GET'>\
//               <p>wifi:" + wifi_state + "</p>\
//               <p><input type='text' id='ssid' name='ssid' placeholder='ssid'></p>\
//               <p><input type='password' id='password' name='password' placeholder='password'></p>\
//               " + ((wifi_state=="disconected") ? "<p><a href='/connect_wifi/conecting'><button class='button'>Connected</button></a></p>" : "<p><a href='/connect_wifi/disconected'><button class='button button2'>Disconnected</button></a></p>") + "</form></body></html>");
//               break;
//             } else {
//               currentLine = "";
//             }
//           } else if (c != '\r') {currentLine += c;}
//         }
//       }
//       header = "";
//       client.stop();
//       Serial.println("Client disconnected.");
//       Serial.println("");
//     }
//     else if(wifi_state == "connecting") {
//       client.println("HTTP/1.1 200 OK");
//       client.println("Content-type:text/html");
//       client.println("\
//               <!DOCTYPE html><html>\
//               <head><meta name='viewport' content='width=device-width, initial-scale=1'>\
//               <link rel='icon' href='data:,'>\
//               <style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\
//               .button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;\
//               text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}\
//               .button2 {background-color: #555555;}</style></head>\
//               <body><h1>connecting....</h1></body>\
//       ");
//       connect_wifi();
//       if(WiFi.status()==WL_CONNECTED) {
//         Serial.println("WiFi connected");
//         delay(200);
//       }
//       else {

//       }
//     }
//     else if(wifi_state == "connected") {

//     }
//     // else if(wifi_state == "connected") {
//     //   Serial.println("New Client.");
//     //   String currentLine = "";
//     //   while (client.connected()) {
//     //     if (client.available()) {
//     //       char c = client.read();
//     //       Serial.write(c);
//     //       header += c;
//     //       if (c == '\n') {
//     //         if (currentLine.length() == 0) {
//     //           client.println("HTTP/1.1 200 OK");
//     //           client.println("Content-type:text/html");
//     //           client.println("Connection: close");
//     //           client.println();
//     //           if (header.indexOf("GET /26/on") >= 0) {
//     //             Serial.println("GPIO 26 on");
//     //             output26State = "on";
//     //             digitalWrite(output26, HIGH);
//     //           } else if (header.indexOf("GET /26/off") >= 0) {
//     //             Serial.println("GPIO 26 off");
//     //             output26State = "off";
//     //             digitalWrite(output26, LOW);
//     //           }
//     //           client.println("<!DOCTYPE html><html>");
//     //           client.println("<head><meta name='viewport' content='width=device-width, initial-scale=1'>");
//     //           client.println("<link rel='icon' href='data:,'>");
//     //           client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
//     //           client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
//     //           client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
//     //           client.println(".button2 {background-color: #555555;}</style></head>");
//     //           client.println("<body><h1>ESP32 Web Server</h1>");

//     //           /*----------------------------------------------------------------------------------------------------------*/
//     //           client.println("<p>GPIO 26 - State " + output26State + "</p>");
//     //           if (output26State=="off") {
//     //             client.println("<p><a href='/26/on'><button class='button'>ON</button></a></p>");
//     //           } else {
//     //             client.println("<p><a href='/26/off'><button class='button button2'>OFF</button></a></p>");
//     //           }
//     //           /*----------------------------------------------------------------------------------------------------------*/
//     //           client.println("</body></html>");
//     //           client.println();
//     //           break;
//     //         } else {
//     //           currentLine = "";
//     //         }
//     //       } else if (c != '\r') {currentLine += c;}
//     //     }
//     //   }
//     //   header = "";
//     //   client.stop();
//     //   Serial.println("Client disconnected.");
//     //   Serial.println("");
//     // }
//     // else {
//     //   client.println("<!DOCTYPE html><html>");
//     //   client.println("<head><meta name='viewport' content='width=device-width, initial-scale=1'>");
//     //   client.println("<link rel='icon' href='data:,'>");
//     //   client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
//     //   client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
//     //   client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
//     //   client.println(".button2 {background-color: #555555;}</style></head><body>");
//     //   client.println("<h1>ESP32 Web Server</h1>");
//     //   client.println("<h2>Error Request</h2>");
//     //   client.println("</body></html>");
//     // }

//   }
// }