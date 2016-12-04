#include <TimeLib.h>
#include <ESP8266WiFi.h>

#include "DHT.h"

#define DHTPIN 13//temp&humid
#define DHTTYPE DHT22 

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "JaraWifi";
const char* password = "jaraz12345";

int fsrReading;

WiFiServer server(80);

void setup() {
  dht.begin();
  
  pinMode(2, OUTPUT);//door
  pinMode(4, OUTPUT);//light
  pinMode(5, OUTPUT);//fan
  pinMode(A0, INPUT);//window
  pinMode(12, OUTPUT);//window_Relay
  pinMode(16, OUTPUT);//Temp_Relay
  digitalWrite(2, 0);
  digitalWrite(12, 0);//@ the begining window is not active
  digitalWrite(16, 0);//From the begining temperature & humidity sensor is not running
  digitalWrite(14, 0);
 
  
  Serial.begin(115200);
  delay(10);  
  
  // Connect to WiFi network
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
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

}

void loop() {

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  String pos;
  int checkPos;
  int val;
  String s;
  if (req.indexOf("/living/door/0") != -1){
    digitalWrite(2, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nDoor locked!";}
    
  else if (req.indexOf("/living/door/1") != -1){
    digitalWrite(2, 1);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nDoor unlocked!";}
    
  else if (req.indexOf("/living/door/check/1") != -1){    
    if(digitalRead(2)==LOW){
      pos="Door is locked!";}
    else if(digitalRead(2)==HIGH){
      pos="Door is not locked!";}
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+pos;}
    
  else if (req.indexOf("/living/light/0") != -1){
    digitalWrite(4, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLiv_light is now low";}
    
  else if (req.indexOf("/living/light/1") != -1){
    digitalWrite(4, 1);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLiv_light is now high ";}
    
  else if (req.indexOf("/living/fan/0") != -1){
    digitalWrite(5, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLiv_fan is now low";}
    
  else if (req.indexOf("/living/fan/1") != -1){
    digitalWrite(5, 1);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLiv_fan is now high ";}
    
  else if (req.indexOf("/living/temp/check/1") != -1){
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float hic = dht.computeHeatIndex(t, h, false);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+String(t)+","+String(hic);}
    
  else if (req.indexOf("/living/humid/check/1") != -1){
    float h = dht.readHumidity();
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+String(h);}
    
  else if (req.indexOf("/living/window/0") != -1){
    digitalWrite(12, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nWindow Sensor Down";}
    
  else if (req.indexOf("/living/window/1") != -1){
    digitalWrite(12, 1);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nWindow Sensor Up";}

  else if (req.indexOf("/living/window/check/1") != -1){    
    if(analogRead(A0)>10){
      pos="Window is closed!";}
    else{
      pos="Window is not closed!";}
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+pos;}
  
  else if (req.indexOf("/living/temp/0") != -1){
    digitalWrite(16, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nTemp & Humid Sensor Down";}
    
  else if (req.indexOf("/living/temp/1") != -1){
    digitalWrite(16, 1);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nTemp & Humid Sensor Up";}
   
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }
  
  client.flush();

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed

}


