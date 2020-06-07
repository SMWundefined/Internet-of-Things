#include<Arduino.h>
#include <WiFi.h>
WiFiServer server(80);
const char* ssid     = "iPhone";      // SSID of local network
const char* password = "Applicious"; 

int inputPin = 5; //AddPin
int CAMERA = 25; //AddPin
int pirState = LOW;             
int val = 0; 
//PIRHEADER

int moisturePin = 33; //AddPin
int thresholdValue = 500;
//MOISTUREHEADER

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME680 bme; 
//BMEHEADER

#define M5STACKFIRE_MICROPHONE_PIN 34
int micValue;
//M5STACK

void setup() { 
  pinMode(CAMERA, OUTPUT);     
  pinMode(inputPin, INPUT); 
  bme.begin(); 
   Serial.begin(9600);
  Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();
}

void loop() {
WiFiClient client = server.available();
motionSensor();
moistureSensor();
temperature();
microphone();
}

void ifttt() //Wifi connection and send all the data to IFTTT
{
  const char host[ ]        = "maker.ifttt.com";          // maker channel of IFTTT
  const char trigger[ ]     = "pirState";                   //name of the trigger you would like to send to IFTTT
  const char APIKey[ ]      = "bjlSsJkh4BIJXO6wgJgXcS";      //Your maker key for Webhooks on IFTTT
  Serial.print("Connect to: ");
  Serial.println(host);
  // WiFiClient to make HTTP connection
  WiFiClient client;
  if (!client.connect(host, 80)) {
    Serial.println("connection failed");
    return;
    }

// Build URL
  String url = String("/trigger/") + trigger + String("/with/key/") + APIKey;
  Serial.print("Requesting URL: ");
  Serial.println(url);

// Send request to IFTTT
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n"); 
  //FYI rn rn is just two new lines to comply with http format
   delay(20);
}

void ifttt_temp() //Wifi connection and send all the data to IFTTT
{
  const char host[ ]        = "maker.ifttt.com";          // maker channel of IFTTT
  const char trigger[ ]     = "temperature";                   //name of the trigger you would like to send to IFTTT
  const char APIKey[ ]      = "bjlSsJkh4BIJXO6wgJgXcS";      //Your maker key for Webhooks on IFTTT
  Serial.print("Connect to: ");
  Serial.println(host);
  // WiFiClient to make HTTP connection
  WiFiClient client;
  if (!client.connect(host, 80)) {
    Serial.println("connection failed");
    return;
    }

// Build URL
  String url = String("/trigger/") + trigger + String("/with/key/") + APIKey;
  Serial.print("Requesting URL: ");
  Serial.println(url);

// Send request to IFTTT
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n"); 
  //FYI rn rn is just two new lines to comply with http format
   delay(20);
}

void ifttt_temp2() //Wifi connection and send all the data to IFTTT
{
  const char host[ ]        = "maker.ifttt.com";          // maker channel of IFTTT
  const char trigger[ ]     = "temperature2";                   //name of the trigger you would like to send to IFTTT
  const char APIKey[ ]      = "bjlSsJkh4BIJXO6wgJgXcS";      //Your maker key for Webhooks on IFTTT
  Serial.print("Connect to: ");
  Serial.println(host);
  // WiFiClient to make HTTP connection
  WiFiClient client;
  if (!client.connect(host, 80)) {
    Serial.println("connection failed");
    return;
    }

// Build URL
  String url = String("/trigger/") + trigger + String("/with/key/") + APIKey;
  Serial.print("Requesting URL: ");
  Serial.println(url);

// Send request to IFTTT
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n"); 
  //FYI rn rn is just two new lines to comply with http format
   delay(20);
}

void ifttt_moisture() //Wifi connection and send all the data to IFTTT
{
  const char host[ ]        = "maker.ifttt.com";          // maker channel of IFTTT
  const char trigger[ ]     = "moisture";                   //name of the trigger you would like to send to IFTTT
  const char APIKey[ ]      = "bjlSsJkh4BIJXO6wgJgXcS";      //Your maker key for Webhooks on IFTTT
  Serial.print("Connect to: ");
  Serial.println(host);
  // WiFiClient to make HTTP connection
  WiFiClient client;
  if (!client.connect(host, 80)) {
    Serial.println("connection failed");
    return;
    }

// Build URL
  String url = String("/trigger/") + trigger + String("/with/key/") + APIKey;
  Serial.print("Requesting URL: ");
  Serial.println(url);

// Send request to IFTTT
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n"); 
  //FYI rn rn is just two new lines to comply with http format
   delay(20);
}

void ifttt_mic() //Wifi connection and send all the data to IFTTT
{
  const char host[ ]        = "maker.ifttt.com";          // maker channel of IFTTT
  const char trigger[ ]     = "mic";                   //name of the trigger you would like to send to IFTTT
  const char APIKey[ ]      = "bjlSsJkh4BIJXO6wgJgXcS";      //Your maker key for Webhooks on IFTTT
  Serial.print("Connect to: ");
  Serial.println(host);
  // WiFiClient to make HTTP connection
  WiFiClient client;
  if (!client.connect(host, 80)) {
    Serial.println("connection failed");
    return;
    }

// Build URL
  String url = String("/trigger/") + trigger + String("/with/key/") + APIKey;
  Serial.print("Requesting URL: ");
  Serial.println(url);

// Send request to IFTTT
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n"); 
  //FYI rn rn is just two new lines to comply with http format
   delay(20);
}

void motionSensor()
{
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(CAMERA, HIGH);  // turn LED ON
    if (pirState == LOW) {
      Serial.println("Baby Moved");
      pirState = HIGH;
      ifttt();
    }
  } else {
    digitalWrite(CAMERA, LOW);
    if (pirState == HIGH){
      Serial.println("Motion ended!");
      pirState = LOW;
    }
  }
}

void moistureSensor()
{
  int sensorValue = analogRead(moisturePin);
  Serial.print(sensorValue);
  if(sensorValue < thresholdValue){
    Serial.println("\nThe Diaper is Wet, Needs Changing");
    ifttt_moisture();
  }
  delay(20000);
}

void temperature()
{
    bme.performReading();
  Serial.print(bme.temperature);
  if (bme.temperature < 20)
  {
    Serial.println("\nThe Baby temperature is LOW");
    ifttt_temp();
  }
  else if(bme.temperature > 24)
  {
    Serial.println("\nThe Baby tempreature is HIGH");
    ifttt_temp2();
  }
  delay(20000);
}
void microphone()
{
  micValue = analogRead(M5STACKFIRE_MICROPHONE_PIN);
  Serial.println(micValue);
  delay(1);  
  ifttt_mic();
     
}
