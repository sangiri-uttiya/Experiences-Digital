#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char *ssid = "OnePlus 6";
const char *password = "alphanumero1";
//const char *mqttServer = "ec2-15-206-215-190.ap-south-1.compute.amazonaws.com";
const char *mqttServer = "13.233.118.197";
const int mqttPort = 1883;

#define PUBLISH_TOPIC "esp32_pub"
#define SUBSCRIBE_TOPIC "esp32_sub"

WiFiClient net;
PubSubClient client(net);

int lightVal;

void messageHandler(char *topic, byte *payload, unsigned int length)
{
  Serial.print("incoming: ");
  Serial.println(topic);

  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char *message = doc["message"];
  Serial.println(message);
}

void connectEC2()
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqttServer, mqttPort);
  client.setCallback(messageHandler);

  Serial.println("Connecting to EC2 instance");

  while (!client.connect("ESP32Client"))
  {
    Serial.print(".");
    delay(100);
  }

  if (!client.connected())
  {
    Serial.println("EC2 Timeout!");
    return;
  }
  client.subscribe(SUBSCRIBE_TOPIC);
  Serial.println("EC2 Connected!");
}

void publishMessage()
{
  StaticJsonDocument<200> doc;
  doc["reading"] = 95;
  doc["message"] = "hello from esp32";
  doc["status"] = 1;
  doc["device_id"] = 4;
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client

  client.publish(PUBLISH_TOPIC, jsonBuffer);
}

void setup()
{
  Serial.begin(115200);
  connectEC2();
}

void loop()
{
  client.loop();
  if (Serial.available())
  {
    String data = Serial.readStringUntil('\n');
    Serial.println(data);
    publishMessage();
  }
}
