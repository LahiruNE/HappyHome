#include <TimeLib.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "JaraWifi"; //your ssid
const char* password = "jaraz12345"; //password of your wifi network
String phoneNumber="+94716482041"; //phone number to which notification messages are sent

const char* host = "www.txtlocal.com";

const int sensorMin = 0;     // rainSensor minimum
const int sensorMax = 1024;  // rainSensor maximum

WiFiServer server(80);

static const char ntpServerName[] = "lk.pool.ntp.org";
const float timeZone = 5.50; 

WiFiUDP Udp;
unsigned int localPort = 8888;  // local port to listen for UDP packets

boolean buzzer=false;
boolean autoLight=false;
boolean autoLightStatus=true;

boolean lockLow = true;//rain vars
boolean lockHigh = true;//rain vars

String store_var="desc|stTime1|endTime1&";

time_t getNtpTime();
String digitalClockDisplay();
String printDigits(int digits);
void sendNTPpacket(IPAddress &address);

void setup() {  
  pinMode(5,INPUT);//autolight
  pinMode(16, OUTPUT);//buzzer
  pinMode(14, OUTPUT);//rain_Relay
  digitalWrite(2, 1);
  digitalWrite(12, 0);//@ the begining phtocell is not active
  digitalWrite(14,0);//@ the begining rain sensor is not active
  digitalWrite(16, 0);//From the begining buzzer is not active
  digitalWrite(2, 1);
  
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
  if(digitalRead(5)==HIGH){
    autoLight=true;   
  }else{
    autoLight=false;
    }
       
  // Check if a client has connected
  WiFiClient client = server.available();
  //if (!client) {
    //return;
  //}
  
  // Wait until the client sends some data
 //Serial.println("new client");
  //while(!client.available()){
  //  delay(1);
  //}
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  String pos;
  int checkPos;
  int val;
  String s;

  if (req.indexOf("/rain/0") != -1){
    digitalWrite(14, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLeakage Sensor Down";}
    
  else if (req.indexOf("/rain/1") != -1){
    digitalWrite(14, 1);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLeakage Sensor Up";}

  else if (req.indexOf("/rain/check/1") != -1){    
    if(digitalRead(14)==LOW){
      pos="Rain sensor down!";}
    else if(digitalRead(14)==HIGH){
      pos="Rain sensor up!";}
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+pos;} 

  else if (req.indexOf("/buzzer/check/1") != -1){
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+String(buzzer);}

  else if (req.indexOf("/buzzer/1") != -1){
    digitalWrite(16,1);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nBuzzer on";}

  else if (req.indexOf("/buzzer/0") != -1){
    digitalWrite(16,0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nBuzzer off";}
  
  else if (req.indexOf("/notification") != -1){
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+store_var;}

 else if (req.indexOf("/photocell/data") != -1){
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+String(autoLightStatus)+","+String(autoLight);}

 else if (req.indexOf("/photocell/0") != -1){
    autoLightStatus=false;
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPhotocell sensor deactivated";}

    
  else if (req.indexOf("/photocell/1") != -1){
    autoLightStatus=true;
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPhotocell sensor activated!";}
   
  else {
    Serial.println("invalid request");
    client.stop();
    //return;
  }
  
  client.flush();

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
  
//rain sensor
  int sensorReading = analogRead(0);//rainSensor
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);//map rainSensor readings

    // rainSensor range value:
  switch (range) {
    case 0:    // Sensor getting wet  
      buzzer=true;    
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

        String url = "/sendsmspost.php?uname=happyhome.ucsc@gmail.com&pword=Happyhome.ucsc1994&message=It's%20raining%20heavily!.-HomeAssistent&selectednums="+phoneNumber+"&info=1&test=0";

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
      buzzer=true;      
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

        String url = "/sendsmspost.php?uname=happyhome.ucsc@gmail.com&pword=Happyhome.ucsc1994&message=Light%20rain%detected!.-HomeAssistent&selectednums="+phoneNumber+"&info=1&test=0";

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
      buzzer=false;
      Serial.println("Not Raining");
      lockLow=true;
      lockHigh=true;
      break;
    }   

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



