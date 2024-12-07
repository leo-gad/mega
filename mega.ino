#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define WIFI_SSID "EdNet"
#define WIFI_PASSWORD "Huawei@123"

#define FIREBASE_HOST "mega-af56e-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "PODOy0nOtNYkLuziYHWZO3j6HNfaj2xMY45Yk7o9"

FirebaseData firebaseData;
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;

#define LED_PIN LED_BUILTIN

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConnected to Wi-Fi");

  firebaseConfig.host = FIREBASE_HOST;
  firebaseConfig.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.begin(&firebaseConfig, &firebaseAuth);
  Firebase.reconnectWiFi(true);

  Serial.println("Connected to Firebase");
}

void loop() {
  if (Firebase.getString(firebaseData, "/voice/led")) {
    String ledStatus = firebaseData.stringData();
    Serial.print("LED Status: ");
    Serial.println(ledStatus);

    if (ledStatus == "on") {
      digitalWrite(LED_PIN, LOW);
    } else if (ledStatus == "off") {
      digitalWrite(LED_PIN, HIGH);
    }
  } else {
    Serial.print("Error getting data: ");
    Serial.println(firebaseData.errorReason());
  }

  delay(1000);
}
