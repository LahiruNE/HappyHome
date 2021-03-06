#include <TimeLib.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "JaraWifi";
const char* password = "jaraz12345";

const char* host = "www.txtlocal.com";

const int sensorMin = 0;     // rainSensor minimum
const int sensorMax = 1024;  // rainSensor maximum

WiFiServer server(80);

static const char ntpServerName[] = "lk.pool.ntp.org";
const float timeZone = 5.50; 

WiFiUDP Udp;
unsigned int localPort = 8888;  // local port to listen for UDP packets

boolean lockLow = true;//rain vars
boolean lockHigh = true;//rain vars
String store_var="stTime1|endTime1&";

time_t getNtpTime();
String digitalClockDisplay();
String printDigits(int digits);
void sendNTPpacket(IPAddress &address);

void setup() {  
  pinMode(4, OUTPUT);//light
  pinMode(2, INPUT);//waterLevel
  pinMode(5, OUTPUT);//WaterLevel Relay
  pinMode(14, OUTPUT);//tankvalve
  pinMode(12,OUTPUT);//rainRelay
  digitalWrite(4, 0);
  digitalWrite(14, 1);
  
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

  Udp.begin(localPort);
  setSyncProvider(getNtpTime);
  setSyncInterval(300);
}

time_t prevDisplay = 0;

void loop() {
  //waterLevel 
  if (digitalRead(2)==HIGH){
    digitalWrite(14,0);
    }
  else{
    digitalWrite(14,1);
    }
  //rain sensor
  int sensorReading = analogRead(0);//rainSensor
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);//map rainSensor readings

    // rainSensor range value:
  switch (range) {
    case 0:    // Sensor getting wet      
      if(lockHigh){
        Serial.println("Flood");
        lockHigh=false;

        
        
        store_var+="HeavyRain|";
        store_var+= digitalClockDisplay();
        store_var+= "|";

        WiFiClient client;
        const int httpPort = 80;
        if (!client.connect(host, httpPort)) {
          Serial.println("connection failed");
          return;
        }

        String url = "/sendsmspost.php?uname=lahiruepa@gmail.com&pword=Lahiru@ucsc_1994&message=It's%20raining%20heavily!-HomeAssistent&selectednums=+94716482041&info=1&test=0";

        client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                  "Host: " + host + "\r\n" + 
                  "Connection: close\r\n\r\n");
        unsigned long timeout = millis();
         while (client.available() == 0) {
          if (millis() - timeout > 5000) {
            client.stop();
            return;
          }
        }
         
      Serial.print(store_var);
         delay(50);
        }
      break;
    case 1:    // Sensor getting wet      
      if(lockLow){
        Serial.println("Rain Warning");
        lockLow=false;        
        
        store_var+="LightRain";
        store_var+= digitalClockDisplay();
        store_var+= "|";

        WiFiClient client;
        const int httpPort = 80;
        if (!client.connect(host, httpPort)) {
          Serial.println("connection failed");
          return;
        }

        String url = "/sendsmspost.php?uname=lahiruepa@gmail.com&pword=Lahiru@ucsc_1994&message=Light%20rain%20detected!-HomeAssistent&selectednums=+94716482041&info=1&test=0";

        client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                  "Host: " + host + "\r\n" + 
                  "Connection: close\r\n\r\n");
        unsigned long timeout = millis();
         while (client.available() == 0) {
          if (millis() - timeout > 5000) {
            client.stop();
            return;
          }
        }
         
      Serial.print(store_var);
         delay(50);
        }
      break;
    case 2:    // Sensor dry - To shut this up delete the " Serial.println("Not Raining"); " below.
      Serial.println("Not Raining");
      lockLow=true;
      lockHigh=true;
      break;
    }

  delay(500);    
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
  String s;
  if (req.indexOf("/garden/tankvalve/0") != -1){
    digitalWrite(14, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\ntankValve closed!";}
    
  else if (req.indexOf("/garden/tankvalve/1") != -1){
    digitalWrite(14, 1);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\ntankValve open!";}
    
  else if (req.indexOf("/garden/tankvalve/check/1") != -1){    
    if(digitalRead(14)==LOW){
      pos="tankValve is closed!";}
    else if(digitalRead(14)==HIGH){
      pos="tankValve is open!";}
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+pos;}
    
  else if (req.indexOf("/garden/light/0") != -1){
    digitalWrite(4, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLiv_light is now low";}
    
  else if (req.indexOf("/garden/light/1") != -1){
    digitalWrite(4, 1);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLiv_light is now high ";}
         
  else if (req.indexOf("/garden/waterlevel/0") != -1){
    digitalWrite(5, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nWaterlevel Sensor Down";}
    
  else if (req.indexOf("/garden/waterlevel/1") != -1){
    digitalWrite(5, 1);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nWaterlevel Sensor Up";}
    
  else if (req.indexOf("/garden/waterlevel/check/1") != -1){
    if(digitalRead(2)==LOW){
      pos="Tank is not full";}
    else if(digitalRead(2)==HIGH){
      pos="Tank is full";}
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+pos;}
    
  else if (req.indexOf("/garden/rain/0") != -1){
    digitalWrite(12, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nRain Sensor Down";}

  else if (req.indexOf("/garden/rain/1") != -1){
    digitalWrite(12, 1);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nRain Sensor Sensor Up";}
    
  else if (req.indexOf("/garden/notification") != -1){
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+store_var;}
    
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

String digitalClockDisplay()
{
  // digital clock display of the time
  String s= String(hour());
  s+=printDigits(minute());
  s+=printDigits(second());
  s+=" ";
  s+=String(day());
  s+=".";
  s+=String(month());
  s+=".";
  s+=String(year());

  return s;
}

String printDigits(int digits)
{
  // utility for digital clock display: prints preceding colon and leading 0
  String dts=":";
  if (digits < 10)
    dts=dts+'0';
  dts=dts+String(digits);
  return dts;
}

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

time_t getNtpTime()
{
  IPAddress ntpServerIP; // NTP server's ip address

  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  // get a random server from the pool
  WiFi.hostByName(ntpServerName, ntpServerIP);
  Serial.print(ntpServerName);
  Serial.print(": ");
  Serial.println(ntpServerIP);
  sendNTPpacket(ntpServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Receive NTP Response");
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
