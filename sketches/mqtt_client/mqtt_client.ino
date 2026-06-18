#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "PiWiFi";
const char* password = "1234509876";
const char* mqttServer = "10.42.0.1";
const int LEDPin = 2;

WiFiClient esp;
PubSubClient client(esp);

void setupWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int tries = 0;
  while (WiFi.status() != WL_CONNECTED && tries < 20) {  // ~10s timeout
    delay(500);
    Serial.print(".");
    tries++;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nWiFi FAILED. Scanning for visible networks...");
    int n = WiFi.scanNetworks();
    for (int i = 0; i < n; i++) Serial.println(WiFi.SSID(i));  // is your hotspot even listed?
    return;
  }

  Serial.print("\nConnected. IP: ");
  Serial.println(WiFi.localIP());      // confirms you're on 172.20.10.x
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");

  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  if(message == "4"){
    digitalWrite(LEDPin, HIGH);
  } else {
    digitalWrite(LEDPin, LOW);
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("healthStation")) {
      Serial.println("connected");
      // Subscribe to the topic you care about
      client.subscribe("health");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  setupWiFi();
  client.setServer(mqttServer, 1883);
  client.setCallback(callback);
  pinMode(LEDPin, OUTPUT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}