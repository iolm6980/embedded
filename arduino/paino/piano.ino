#include "ESP8266WiFi.h"
#define buzzerPin D1

const char* ssid = "U+Net8C88";
const char* password = "C03HB7@071";

WiFiServer server(80);
WiFiClient client;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
  Serial.println("Server started");
}
 
void loop() {
  client = server.available();
  if(!client) return;
  
  client.setTimeout(5000);
  
  String request = client.readStringUntil('\r');
  
  while(client.available()) {
    client.read();
  }

    if(request.indexOf("/c") != -1) {
      Serial.println("도");
      tone(buzzerPin, 261, 250);
    }
    else if(request.indexOf("/CH") != -1) {
      Serial.println("도#");
      tone(buzzerPin, 277, 250);
    }
    else if(request.indexOf("/d") != -1) {
      Serial.println("레");
      tone(buzzerPin, 294, 250);
    }
    else if(request.indexOf("/DH") != -1) {
      Serial.println("레#");
      tone(buzzerPin, 311, 250);
    }
     else if(request.indexOf("/e") != -1) {
      Serial.println("미");
      tone(buzzerPin, 329, 250);
    }
     else if(request.indexOf("/F") != -1) {
      Serial.println("파");
      tone(buzzerPin, 349, 250);
    }
    else if(request.indexOf("/fH") != -1) {
      Serial.println("파#");
      tone(buzzerPin, 369, 250);
    }
     else if(request.indexOf("/g") != -1) {
      Serial.println("솔");
      tone(buzzerPin, 391, 250);
    }
    else if(request.indexOf("/GH") != -1) {
      Serial.println("솔#");
      tone(buzzerPin, 415, 250);
    }
     else if(request.indexOf("/a") != -1) {
      Serial.println("라");
      tone(buzzerPin, 440, 250);
    }
    else if(request.indexOf("/AH") != -1) {
      Serial.println("라#");
      tone(buzzerPin, 466, 250);
    }
     else if(request.indexOf("/b") != -1) {
      Serial.println("시");
      tone(buzzerPin, 493, 250);
    }
     else if(request.indexOf("/C") != -1) {
      Serial.println("도");
      tone(buzzerPin, 523, 250);
    }
  
 

  
  client.print("HTTP/1.1 200 OK");
  client.print("Content-Type: text/html\r\n\r\n");
  client.print("<!DOCTYPE HTML>");
  client.print("<style>");
  client.print("#Key{background-color: white; width:50px; height: 250px;}");
  client.print("#cHKey{position: absolute;  left: 44px; top: 73px;background-color: black; width:30px; height: 130px;}");
  client.print("#DHKey{position: absolute;  left: 94px; top: 73px;background-color: black; width:30px; height: 130px;}");
  client.print("#FHKey{position: absolute;  left: 194px; top: 73px;background-color: black; width:30px; height: 130px;}");
  client.print("#GHKey{position: absolute;  left: 244px; top: 73px;background-color: black; width:30px; height: 130px;}");
  client.print("#AHKey{position: absolute;  left: 294px; top: 73px;background-color: black; width:30px; height: 130px;}");
 // client.print("background-color: white; width:100px; height: 100px;}");
   
  client.print("</style>");
  client.print("<html>");
  client.print("<head>"); 
  client.print("<meta&nbsp;charset=\"UTF-8\">");
  client.print("<title>Piano</title>");
  client.print("<script>");
  client.print("function onDisplay(){ $('#recordA').show(); }");
  client.print("function offDisplay(){ $('#recordA').hide(); }");
  client.print("</script>");
  client.print("</head>");
  client.print("<body>");
  client.print("<h2 id = 'hello1'>Piano</h2>");

  client.print("<a>      </a>");
  client.print("<button onclick ='location.href=&quot;/c&quot;' id = 'Key'></button>");
  client.print("<button onclick ='location.href=&quot;/CH&quot;'' id = 'cHKey'></button>");
  client.print("<button onclick ='location.href=&quot;/d&quot;' id = 'Key'></button>");
  client.print("<button onclick ='location.href=&quot;/DH&quot;'' id = 'DHKey'></button>");
  client.print("<button onclick ='location.href=&quot;/e&quot;' id = 'Key'></button>");
  client.print("<button onclick ='location.href=&quot;/F&quot;' id = 'Key'></button>");
  client.print("<button onclick ='location.href=&quot;/fH&quot;'' id = 'FHKey'></button>");
  client.print("<button onclick ='location.href=&quot;/g&quot;' id = 'Key'></button>");
  client.print("<button onclick ='location.href=&quot;/GH&quot;'' id = 'GHKey'></button>");
  client.print("<button onclick ='location.href=&quot;/a&quot;' id = 'Key'></button>");
  client.print("<button onclick ='location.href=&quot;/AH&quot;'' id = 'AHKey'></button>");
  client.print("<button onclick ='location.href=&quot;/b&quot;' id = 'Key'></button>");
  client.print("<button onclick ='location.href=&quot;/C&quot;' id = 'Key'></button>");
  client.print("</body>");
  client.print("</html>");

}
