#include <ESP8266WiFi.h>
#include "Firebase_ESP_Client.h"

#include "addons/RTDBHelper.h"

// wiFi credentials
const char *ssid = "TIGO-8E48"; // red name
const char *password = "4D9697504814";

// Firebase credentials
const char *FIREBASE_HOST = "https://es8266-f3250-default-rtdb.firebaseio.com/";
const char *FIREBASE_AUTH = "2UeH2dB5Hc7iI41IzubWSEBR0AhWh8kYQPmznIH7";

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool iterar = true;

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(250);
  }
  Serial.print("\nConectado al Wi-Fi");
  Serial.println();
  
  config.database_url = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.reconnectWiFi(true);

  Firebase.begin(&config, &auth);
}

void loop()
{

  while (iterar)
  {

   // write data
   Serial.printf("Set int... %s\n", 
                Firebase.RTDB.setInt(&fbdo, "/test/int", 512)
                ? "ok" : fbdo.errorReason().c_str());

   Firebase.RTDB.setInt(&fbdo, "lectura1", 512);
   Firebase.RTDB.setString(&fbdo, "string1", "On");
   Firebase.RTDB.setString(&fbdo,"project1/sensor", "DHT11");
   Firebase.RTDB.setInt(&fbdo,"project1/temperatura", 31);
   Firebase.RTDB.setBool(&fbdo, "project1/alarm", false);

    //read data
    Serial.printf("Get int... %s\n", 
                  Firebase.RTDB.getInt(&fbdo, "project1/temperatura") ?
                  String(fbdo.intData()).c_str() : fbdo.errorReason().c_str());

   // push de datos
   Firebase.RTDB.pushInt(&fbdo, "project1/temperatura", 29);
    
   iterar = false;
  }
}
