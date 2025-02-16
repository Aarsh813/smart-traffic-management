#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define redPin     2
#define yellowPin  4
#define greenPin   5
//=============================================CAMERA DEVICE ID==============================================
String id = "126DE3";
String type = "Camera";
//==================================================================================================================
String data;
//============================================WIFI CREDENTIALS OF HUB================================================
const char* ssid = "<MCU_WIFI_ID>";
const char* password = "<MCU_WIFI_PASS>";
String host = "http://<ip of the mcu server>/feed?";
//============================================defining the object====================================================
WiFiClient client;
HTTPClient http;
//============================================defining the IP Address of the sensor==================================
IPAddress ip (192,168,4,32);
IPAddress gateway (192,168,4,1);
IPAddress subnet (255, 255, 255, 0);

//============================================SETUP PART=============================================================
void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
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
  delay(5000);

}
//============================================SEND THE DATA TO SERVER================================================
void senddata(String str){
      data = "ID=";
      data += String(id);
      data += "&type=";
      data += String(type);
      data += "&data=";
      data += String(str);
      http.begin(client, host);
      http.addHeader("content-type","application/x-www-form-urlencoded");
      http.POST(data);
      http.writeToStream(&Serial);
      http.end();
      Serial.println("data stream: "+data);
}

void toggleLights(String lightColor) {
  // Turn off all lights initially
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
  
  // Toggle the specified light
  if (lightColor == "red") {
    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, HIGH);
    delay(1000);
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, HIGH);
  }
  else if (lightColor == "green") {
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, HIGH);
    delay(1000);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, HIGH);
  } 
  Serial.println("changed");
}

//============================================LOOP PART================================================
void loop () {
  if(Serial.available()){
      String dataInput = Serial.readStringUntil('\r\n');
      senddata(dataInput);
      toggleLights(dataInput);
      if(dataInput=="too much traffic" || dataInput=="Emergency Vehical" || dataInput=="Accident"){
        toggleLights("red");
      }
      if(dataInput=="less traffic"){
        toggleLights("green");
      }
    }
}

