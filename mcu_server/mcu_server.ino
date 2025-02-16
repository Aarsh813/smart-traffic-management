#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include <FirebaseESP32.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

//======================================FIREBASE CREDENTIALS===========================================          
 
#define DATABASE_URL "nodemcu-3fec1-default-rtdb.firebaseio.com"      
#define API_KEY "fm2Gh4EF7h2fEhR6HiLQ2EwBZWeRo7mYSnlwoKyq"            
#define WIFI_SSID "OnePlus 5g"                                  
#define WIFI_PASSWORD "123456789"   
#define AP_SSID "server1"
#define AP_PASSWORD "qwertyuiop"
//======================================Defining Firebase objects==================================
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
int max_connection = 8;
//====================================================================================================
String URL;
int httpCode;
String payload;
String ID;
String state;
String server_location = "testLocation1";
//=============================================define the objects======================================
WebServer server(80);
HTTPClient http;
//===============================================dafine the IP Address of the hotspot==================
IPAddress ip (192,168,4,1);
IPAddress gateway (192,168,4,1);
IPAddress subnet (255, 255, 255, 0);
//=========================================SETUP PART==================================================
void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_MODE_APSTA);
 
  WiFi.softAP(AP_SSID, AP_PASSWORD);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.print("ESP32 IP as soft AP: ");
  Serial.println(WiFi.softAPIP());
 
  Serial.print("ESP32 IP on the WiFi network: ");
  Serial.println(WiFi.localIP());

  server.on("/",handleroot);
  server.on("/feed",feed);
  server.begin();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  config.signer.test_mode = true;
  config.token_status_callback = tokenStatusCallback;
  Firebase.reconnectWiFi(true);
  fbdo.setBSSLBufferSize(4096, 1024);
  Firebase.begin(&config, &auth);
  Firebase.setDoubleDigits(5);
                    
}
//=====================================handle root page================================================
void handleroot(){
  server.send(200,"text/plain","hello");
}
//===================================handle sensor's page===========================================
void feed(){
  String ID = server.arg("ID");
  String type = server.arg("type");
  String data = server.arg("data");
  server.send(200,"text/plain","Response");
  Serial.println(type + "(" + ID + ") at " + server_location + " sends data: " + data);
  String firebasePath = "/"+server_location+"/"+type+"/"+ID;
  if (Firebase.ready()) {
    Serial.printf("Set string... %s\n", Firebase.setString(fbdo, firebasePath, data) ? "ok" : fbdo.errorReason().c_str());

    Serial.printf("Get string... %s\n", Firebase.getString(fbdo, firebasePath) ? fbdo.to<const char *>() : fbdo.errorReason().c_str());
  }
  delay(1500);
}

//==============================================LOOP===================================================
void loop (){
      server.handleClient();  
}
