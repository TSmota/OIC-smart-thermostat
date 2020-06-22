#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Mitsubishi.h>
#include<stdio.h> 
#include <iostream>
#include <string>

// Change the credentials below, so your ESP8266 connects to your router
const char* ssid = "maceninha";
const char* password = "18108486";

// Change the variable to your server IP address, so it connects to your MQTT broker
const char* mqtt_server = "192.168.1.105";

// Initializes the espClient. You should change the espClient name if you have multiple ESPs running in your home automation system
WiFiClient espClient;
PubSubClient client(espClient);

// Temperature sensor
const int tempPin = A0;

// AC control variables
const uint16_t kIrLed = 14;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRMitsubishiAC ac(kIrLed); //GPIO to control AC
IRsend irsend(kIrLed); //GPIO to control TV
int acTemp = 26;
int desiredTemp = 26;
boolean autoMode = false;

// Timers auxiliar variables
long now = millis();
long lastUpdate = 0;
long acUpdate = 0;

// Don't change the function below. This functions connects your ESP8266 to your router
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}

// This functions is executed when some device publishes a message to a topic that your ESP8266 is subscribed to
// Change the function below to add logic to your program, so when a device publishes a message to a topic that 
// your ESP8266 is subscribed you can actually do something
void callback(String topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp = "";
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }

  Serial.println();

  //turn on led 16 (demo)
  if(topic=="demo/led16"){
      Serial.println("Changing nodemcu led 16 to: ");
      if(messageTemp == "true"){
        Serial.print("on");
        digitalWrite(16, LOW);
      }
      else if(messageTemp == "false"){
        Serial.print("off");
        digitalWrite(16, HIGH);
      }
  }

  //turn on led 2 (demo)
  if(topic=="demo/led2"){
      Serial.println("Changing nodemcu led 2 to: ");
      if(messageTemp == "true"){
        Serial.print("on");
        digitalWrite(2, LOW);
      }
      else if(messageTemp == "false"){
        Serial.print("off");
        digitalWrite(2, HIGH);
      }
  }

  //turn on/off sony tv (demo)
  if(topic=="demo/tv"){
      Serial.println("Turning on/off the tv");
      irsend.sendSony(0xa90, 12, 2);  // 12 bits & 2 repeats
  }

  //switch ac control to automatic mode
  if(topic=="ac/auto"){
      Serial.println("Switching AC to ");
      if(messageTemp == "true"){
        Serial.print("automatic control");
        autoMode = true;
        desiredTemp = acTemp;
      }
      else if(messageTemp == "false"){
        Serial.print("manual control");
        autoMode = false;
        ac.on();
        ac.setTemp(desiredTemp);
        ac.send();
      }
  }

  
  //manually define the ac temperature
  if(topic=="ac/temp"){
    
    acTemp = messageTemp.toInt();
    if(!autoMode){
      Serial.println("Temperature updated to: ");
      Serial.print(acTemp);
      ac.on();
      ac.setTemp(acTemp);
      ac.send();
    }else{
      Serial.println("Desired temperature updated to: ");
      Serial.print(acTemp);
      desiredTemp = acTemp;
    }
  }
  
  Serial.println();
}

// This functions reconnects your ESP8266 to your MQTT broker
// Change the function below if you want to subscribe to more topics with your ESP8266 
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");  
      // Subscribe or resubscribe to a topic
      client.subscribe("demo/led16");
      client.subscribe("demo/led2");
      client.subscribe("demo/tv");
      client.subscribe("ac/auto");
      client.subscribe("ac/temp");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// The setup function sets your ESP GPIOs to Outputs, starts the serial communication at a baud rate of 115200
// Sets your mqtt broker and sets the callback function
// The callback function is what receives messages and actually controls the LEDs
void setup() {
  pinMode(16, OUTPUT);
  pinMode(2, OUTPUT);

  //inicia o serviço de ligar a tv
  irsend.begin();

  //turn off builtin leds
  digitalWrite(16, HIGH);
  digitalWrite(2, HIGH);

  //connects to wifi and mqtt server
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  //AC default values
  ac.on();
  ac.setFan(1);
  ac.setMode(kMitsubishiAcCool);
  ac.setTemp(acTemp);
  ac.setVane(kMitsubishiAcVaneAuto);
}

// For this project, you don't need to change anything in the loop function. Basically it ensures that you ESP is connected to your broker
void loop() {
  float celsius;
  
  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP8266Client");

  now = millis();
  // Publishes new temperature every 10 seconds
  if (now - lastUpdate > 5000) {
    lastUpdate = now;
    
    //read temperature
    int analogValue = analogRead(tempPin);
    float millivolts = (analogValue/1024.0) * 3300; //3300 is the voltage provided by NodeMCU
    celsius = millivolts/10;
    
    char celsiusChar[8]; // Buffer big enough for 7-character float
    dtostrf(celsius, 6, 2, celsiusChar); 

    // Publishes Temperature values
    client.publish("info/temp", celsiusChar);
  
    String acStatus = "<table><tr><td>Estado</td><td>";
    if(ac.getPower()){
      acStatus += "Ligado";
      acStatus += "</td></tr><tr><td>Temperatura</td><td>";
      acStatus += ac.getTemp();
      acStatus += "</td></tr></table>";
    }else{
      acStatus += "Desligado</td></tr></table>";
    }
    
    //publish ac current details
    client.publish("info/ac", acStatus.c_str());
  }

  if(now - acUpdate > 300000){

    acUpdate = now;
    int ambientTemp = (int) celsius;
    
    if (desiredTemp != ambientTemp && autoMode){
      
      if(desiredTemp < ambientTemp && acTemp < 31){
        ac.on();
        acTemp += 1;
        ac.setTemp(acTemp);
        ac.send();
        
      } else if (desiredTemp < ambientTemp && acTemp == 31){
        ac.off();
        ac.send();
        
      } else if (desiredTemp > ambientTemp && acTemp > 16){
        ac.on();
        acTemp -= 1;
        ac.setTemp(acTemp);
        ac.send();
        
      } else if (desiredTemp > ambientTemp && acTemp == 16){
        ac.off();
        ac.send();
      }
      
    }
    
  }
  
} 
