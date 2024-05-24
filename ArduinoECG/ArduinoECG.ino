#include <WiFi.h>
#include <ArduinoMqttClient.h>


const char* ssid = "Wifi Name";
const char* passwd = "passwd";

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "192.168.4.226";
int        port     = 1883;
const char topic[]  = "arduino/simple";

const long interval = 1000;
unsigned long previousMillis = 0;

int count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid, passwd);
   while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  
  
  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

}

void loop() {
  // put your main code here, to run repeatedly:
  mqttClient.poll();
  if((digitalRead(14) == 1)||(digitalRead(12) == 1)){
  Serial.println('!');
  }
  else{
  // send the value of analog input 0:
  float valueSensor = analogRead(A0);
  mqttClient.beginMessage(topic);
  mqttClient.print(valueSensor);
  mqttClient.endMessage();
  Serial.print("Variable_1:");
  Serial.print(valueSensor);
  Serial.print(",");
  Serial.print("Variable_2:");
  Serial.println(0);
  }
  delay(25);
}
