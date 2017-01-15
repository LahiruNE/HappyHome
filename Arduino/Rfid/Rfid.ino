#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
 
#define SS_PIN 2
#define RST_PIN 15
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

String response;//response variable

const char* ssid = "JaraWifi";
const char* password = "jaraz12345";

WiFiServer server(80);


 
void setup() 
{
  Serial.begin(115200);   // Initiate a serial communication

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
  
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop() 
{
    // Check if a client has connected
  WiFiClient client = server.available();
  if (client) {
      // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  String s;
  
  if (req.indexOf("/reading") != -1){
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+response;}
    
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
  
 
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Response : ");
  content.toUpperCase();

  response+=content.substring(1);
  response+="|";
  Serial.println(response);
  Serial.println();
  delay(3000);  
} 
