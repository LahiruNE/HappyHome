#include <ESP8266WiFi.h>

const char* ssid = "JaraWifi";
const char* password = "jaraz12345";

WiFiServer server(80);

void setup() {
 
  pinMode(2, OUTPUT);//light1
  pinMode(4, OUTPUT);//light2
  pinMode(5, OUTPUT);//fan
  pinMode(14, OUTPUT);//light3
  digitalWrite(2, 0);
  digitalWrite(4, 0);
  digitalWrite(5, 0);
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
  String s;
  if (req.indexOf("/living/light1/0") != -1){
    digitalWrite(2, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLiv_light1 is now low";}
    
  else if (req.indexOf("/living/light1/1") != -1){
    digitalWrite(2, 1);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLiv_light1 is now high ";}

  else if (req.indexOf("/living/light2/0") != -1){
    digitalWrite(4, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLiv_light2 is now low";}
    
  else if (req.indexOf("/living/light2/1") != -1){
    digitalWrite(4, 1);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLiv_light2 is now high ";}

  else if (req.indexOf("/living/light3/0") != -1){
    digitalWrite(4, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLiv_light3 is now low";}
    
  else if (req.indexOf("/living/light3/1") != -1){
    digitalWrite(4, 1);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLiv_light3 is now high ";}
    
  else if (req.indexOf("/living/fan/0") != -1){
    digitalWrite(5, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLiv_fan is now low";}
    
  else if (req.indexOf("/living/fan/1") != -1){
    digitalWrite(5, 1);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLiv_fan is now high ";}  
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


