
#include <ESP8266WiFi.h>
#include "PubSubClient.h"
#include <SimpleDHT.h>


const char* ssid = "TP-LINK_HyFi_11D67D";                  
const char* password = "123456";          
const char* mqtt_server = "bemfa.com";      
const int mqtt_server_port = 9501;         
#define ID_MQTT  "4d9ec352e0376f2110a0c601a2857225"  
const char*  topic = "led002";                     
const char * dhttopic = "temp004";                
int pinDHT11 = D4;                        
int B_led = D5;                         
long timeval = 3 * 1000;                

String ledstatus = "off";
long lastMsg = 0;
SimpleDHT11 dht11(pinDHT11);
WiFiClient espClient;
PubSubClient client(espClient);


void turnOnLed();
void turnOffLed();



void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String Mqtt_Buff = "";
  for (int i = 0; i < length; i++) {
    Mqtt_Buff += (char)payload[i];
  }
  Serial.print(Mqtt_Buff);
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if (Mqtt_Buff == "on") {
    turnOnLed();

  } else if (Mqtt_Buff == "off") {
    turnOffLed();
  }
  Mqtt_Buff = "";
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(ID_MQTT)) {
      Serial.println("connected");
      client.subscribe(topic);
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
  pinMode(B_led, OUTPUT);

  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_server_port);
  client.setCallback(callback);
  digitalWrite(B_led, HIGH);
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();


  long now = millis();
  if (now - lastMsg > timeval) {
    lastMsg = now;


    // read without samples.
    byte temperature = 0;
    byte humidity = 0;
    int err = SimpleDHTErrSuccess;
    if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
      Serial.print("Read DHT11 failed, err="); Serial.println(err); delay(1000);
      return;
    }


    String  msg = "#" + (String)temperature + "#" + (String)humidity + "#" + ledstatus; 
    client.publish(dhttopic, msg.c_str());
  }



}


void turnOnLed() {
  ledstatus = "on";
  Serial.println("turn on light");
  digitalWrite(B_led, LOW);
}

void turnOffLed() {
  ledstatus = "off";
  Serial.println("turn off light");
  digitalWrite(B_led, HIGH);
}
