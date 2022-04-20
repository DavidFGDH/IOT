#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;
String estado = "";
int rele1 = D1;

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

void setup(){
  Serial.begin(115200);
  pinMode(rele1,OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = FIREBASE_AUTH;



  config.database_url = FIREBASE_HOST;

  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  config.token_status_callback = tokenStatusCallback; 
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}



void loop(){
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 2000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    count++;
    estado=Firebase.RTDB.getString(&fbdo, F("/casa1/foco1")) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();
    Serial.println(estado);
  
    if(estado== "prende" || estado=="on" || estado == "encendido"){
    digitalWrite(rele1,LOW);
    Serial.println("LOW");
    }
    if(estado== "apaga" || estado=="off" || estado == "apagado"){
    digitalWrite(rele1,HIGH);
    Serial.println("HIGH");
    }
  }
}
