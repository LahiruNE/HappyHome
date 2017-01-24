#include <TimeLib.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "DHT.h"

#define DHTPIN 13//temp&humid
#define DHTTYPE DHT22 

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "JaraWifi"; //your ssid
const char* password = "jaraz12345"; //password of your wifi network
String phoneNumber="+94716482041"; //phone number to which notification messages are sent

const char* host = "www.txtlocal.com";

WiFiServer server(80);

static const char ntpServerName[] = "lk.pool.ntp.org";
const float timeZone = 5.50; 

WiFiUDP Udp;
unsigned int localPort = 8888;  // local port to listen for UDP packets

boolean buzzer=false;

int calibrationTime = 30;  //pir vars
long unsigned int lowIn;
long unsigned int pause = 5000; 
boolean lockLow = true;
boolean takeLowTime;
boolean curr=false; 
boolean pir=false;//pir vars

boolean smokeFirst=true;//smoke vars
boolean smokeEnd=false;//smoke vars

String store_var="desc|stTime|endTime&";
String store_var1="desc|stTime1|endTime1&";

time_t getNtpTime();
String digitalClockDisplay();
String printDigits(int digits);
void sendNTPpacket(IPAddress &address);

void setup() {
  dht.begin();
  
  pinMode(2, OUTPUT);//smoke_Relay
  pinMode(4, OUTPUT);//light
  pinMode(5, OUTPUT);//fan
  pinMode(14, INPUT);//PIR
  pinMode(12, OUTPUT);//PIR_Relay
  pinMode(16, OUTPUT);//Temp_Relay
  digitalWrite(2, 0);
  digitalWrite(12, 0);//@ the begining PIR is not active
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

  Udp.begin(localPort);
  setSyncProvider(getNtpTime);
  setSyncInterval(300);
}

time_t prevDisplay = 0;

void loop() {
   //PIR reading...
 if(digitalRead(14) == HIGH){
  if(curr==true && pir==true){
    buzzer=true;
    }  
    if(lockLow==true && curr==true && pir==true){
         lockLow = false;            
         Serial.println(buzzer);
         
         if (timeStatus() != timeNotSet) {
            if (now() != prevDisplay) { //update the display only if time has changed
                prevDisplay = now();
                store_var+="Movement detected|";
                store_var+= digitalClockDisplay();
                store_var+= "|";

                WiFiClient client;
                const int httpPort = 80;
                if (!client.connect(host, httpPort)) {
                  Serial.println("connection failed");
                  return;
                }

                String url = "/sendsmspost.php?uname=hirunikegalle@gmail.com&pword=Dell1994&message=Unidentified%20movement%20detected%20in%20the%20living%20room.-HomeAssistent&selectednums="+phoneNumber+"&info=1&test=0";

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
            }
          }      
         
         delay(50);
         }         
         takeLowTime = true;      
 } 

 if(digitalRead(14) == LOW){ 
    if(pir==true){
      curr=true;}
    if(takeLowTime){
        lowIn = millis();          //save the time of the transition from high to LOW
        takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }
       //if the sensor is low for more than the given pause, 
       //we assume that no more motion is going to happen
       if(!lockLow && millis() - lowIn > pause){
           lockLow = true; 
           
           if (timeStatus() != timeNotSet) {
            if (now() != prevDisplay) { 
                prevDisplay = now();
                store_var+= digitalClockDisplay();
                store_var+= "&";
            }
          }
           Serial.println(store_var);              
           delay(50);
           }
       }

     //smokeSensor reading
  if(1<0){//analogRead(A0)>100
    buzzer=true;//buzzer on
    if(smokeFirst){
      smokeFirst=false;

      if (timeStatus() != timeNotSet) {
            if (now() != prevDisplay) { //update the display only if time has changed
                prevDisplay = now();
                store_var1+="Smoke detected|";
                store_var1+= digitalClockDisplay();
                store_var1+= "|";

                WiFiClient client;
                const int httpPort = 80;
                if (!client.connect(host, httpPort)) {
                  Serial.println("connection failed");
                  return;
                }

               String url = "/sendsmspost.php?uname=hirunikegalle@gmail.com&pword=Dell1994&message=Smoke%20detected%20in%20the%20living%20room.-HomeAssistent&selectednums="+phoneNumber+"&info=1&test=0";

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
            }
          }      
         
         delay(50);
      }
      smokeEnd=true;    
    }
  else{
    
    smokeFirst=true;
    if(smokeEnd){
      if (timeStatus() != timeNotSet) {
            if (now() != prevDisplay) { 
                prevDisplay = now();
                store_var1+= digitalClockDisplay();
                store_var1+= "&";
            }
          }
           Serial.println(store_var1);              
           delay(50);
      }
    }
       
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
  if (req.indexOf("/smoke/0") != -1){
    digitalWrite(2, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nSmoke Sensor Down";}
    
  else if (req.indexOf("/smoke/1") != -1){
    digitalWrite(2, 1);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nSmoke Sensor Up";}

  else if (req.indexOf("/smoke/check/1") != -1){    
    if(digitalRead(12)==LOW){
      pos="Smoke sensor down!";}
    else if(digitalRead(12)==HIGH){
      pos="Smoke sensor up!";}
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+pos;} 
    
  else if (req.indexOf("/light/0") != -1){
    digitalWrite(4, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLiv_light is now low";}
    
  else if (req.indexOf("/light/1") != -1){
    digitalWrite(4, 1);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLiv_light is now high ";}

  else if (req.indexOf("/light/check/1") != -1){    
    if(digitalRead(4)==LOW){
      pos="light off!";}
    else if(digitalRead(4)==HIGH){
      pos="light on!";}
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+pos;}
    
  else if (req.indexOf("/fan/0") != -1){
    digitalWrite(5, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLiv_fan is now low";}
    
  else if (req.indexOf("/fan/1") != -1){
    digitalWrite(5, 1);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLiv_fan is now high ";}

  else if (req.indexOf("/fan/check/1") != -1){    
    if(digitalRead(5)==LOW){
      pos="fan off!";}
    else if(digitalRead(5)==HIGH){
      pos="fan on!";}
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+pos;}
    
  else if (req.indexOf("/temp/check/1") != -1){
    digitalWrite(16, 1);
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float hic = dht.computeHeatIndex(t, h, false);
    delay(1000);
    digitalWrite(16, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nReal Temp:"+String(t)+",Feel:"+String(hic);}
    
  else if (req.indexOf("/humid/check/1") != -1){
    digitalWrite(16, 1);
    float h = dht.readHumidity();
    delay(1000);
    digitalWrite(16, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+String(h);}
    
  else if (req.indexOf("/pir/0") != -1){
    digitalWrite(12, 0);
    pir=false;
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPIR Sensor Down";}
    
  else if (req.indexOf("/pir/1") != -1){
    digitalWrite(12, 1);
    pir=true;
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPIR Sensor Up";}

  else if (req.indexOf("/pir/check/1") != -1){    
    if(digitalRead(12)==LOW){
      pos="pir is down!";}
    else if(digitalRead(12)==HIGH){
      pos="pir is up!";}
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+pos;}
    
  else if (req.indexOf("/temp/0") != -1){
    digitalWrite(16, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nTemp & Humid Sensor Down";}
    
  else if (req.indexOf("/temp/1") != -1){
    digitalWrite(16, 1);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nTemp & Humid Sensor Up";}

  else if (req.indexOf("/temprelay/check/1") != -1){    
    if(digitalRead(12)==LOW){
      pos="temprelay is down!";}
    else if(digitalRead(12)==HIGH){
      pos="temprelay is up!";}
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+pos;}

  else if (req.indexOf("/buzzer/check/1") != -1){
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+String(buzzer);

    if(buzzer==true){
      buzzer=false;
      }
    }
    
  else if (req.indexOf("/notification") != -1){
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+store_var+"-"+store_var1;}
    
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
