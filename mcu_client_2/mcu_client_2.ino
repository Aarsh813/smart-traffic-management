#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

//=============================================CAMERA DEVICE ID==============================================
String id = "45E9YE";
String type = "Speed Gun";
//==================================================================================================================
String data;
//============================================WIFI CREDENTIALS OF HUB================================================
const char* ssid = "server1";
const char* password = "qwertyuiop";
String host = "http://192.168.4.1/feed?";
//============================================defining the object====================================================
WiFiClient client;
HTTPClient http;
//============================================defining the IP Address of the sensor==================================
IPAddress ip (192,168,4,32);
IPAddress gateway (192,168,4,1);
IPAddress subnet (255, 255, 255, 0);

//============================================SETUP PART=============================================================
void setup() {
  Serial.begin(9600);
  ESP.eraseConfig();
  WiFi.persistent(false);
  Serial.println("SET ESP IN STA MODE");
  WiFi.mode(WIFI_STA);
  Serial.println("- connecting to wifi");
  WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, password);
  Serial.println(".");
  Serial.println("- wifi connected");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
//============================================SEND THE DATA TO SERVER================================================
void senddata(String str){

      data = "ID=";
      data += String(id);
      data += "&type=";
      data += String(type);
      data += "&data=";
      data += String(str);
      data +=" km/h";
      http.begin(client, host);
      http.addHeader("content-type","application/x-www-form-urlencoded");
      http.POST(data);
      http.writeToStream(&Serial);
      http.end();
      Serial.println("data stream: "+data);
}


//============================================LOOP PART================================================
void loop () {
  senddata(String(random(40,100)));
  delay(5000);
}

