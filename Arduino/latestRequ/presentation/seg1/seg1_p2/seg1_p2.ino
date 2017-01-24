#include <TimeLib.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

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
boolean autoLight=false;
boolean autoLightStatus=true;

float calibrationFactor = 4.5;//flow sensor vars
volatile byte pulseCount;  
float flowRate;
float floatR;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;
unsigned long oldTime;
boolean flowFirst=true;
boolean flowEnd=false;//flow sensor vars

//sound Sensor vars
int vibDetectedVal = HIGH; //where record our Sound Measurement
boolean bAlarm = false;
unsigned long lastVibDetectTime; // Record the time that measured a sound
int vibAlarmTime = 500; // Number of milli seconds to keep the sound alarm high
//sound sensor vars


String store_var="desc|stTime1|endTime1&";
String store_var1="desc|stTime1|endTime1&";

time_t getNtpTime();
String digitalClockDisplay();
String printDigits(int digits);
void sendNTPpacket(IPAddress &address);

void setup() {  
  pinMode(2, INPUT);//water leak
  pinMode(4, OUTPUT);//door
  pinMode(12, OUTPUT);//vib_Relay
  pinMode(13,INPUT);//vibration sensor
  pinMode(5, INPUT);//autolight
  pinMode(16, OUTPUT);//buzzer
  pinMode(14, OUTPUT);//waterleak_Relay
  digitalWrite(2, 1);
  digitalWrite(12,0);//@ the begining vib sensor is not active 
  digitalWrite(14,0);//@ the begining water leakage sensor is not active
  digitalWrite(16, 0);//From the begining buzzer is not active
  digitalWrite(2, 1);

  pulseCount        = 0;//flow sensor 
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;//flow sensor
  
  attachInterrupt(2, pulseCounter, FALLING);//flow sensor 
  
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
  vibSensing();

  if(digitalRead(5)==HIGH){
    autoLight=true;   
  }else{
    autoLight=false;
    }
  
  //flow sensing
  floatR=flow(); 
  
  if (floatR!=0){
    buzzer=true;//buzzer on
    Serial.print(".......");
    if (flowFirst){
      flowFirst=false;
      flowEnd=true;

      if (timeStatus() != timeNotSet) {
            if (now() != prevDisplay) { //update the display only if time has changed
                prevDisplay = now();
                store_var1+="Water leakage detected|";
                store_var1+= digitalClockDisplay();
                store_var1+= "|";

                WiFiClient client;
                const int httpPort = 80;
                if (!client.connect(host, httpPort)) {
                  Serial.println("connection failed");
                  return;
                }

                String url = "/sendsmspost.php?uname=lahiruepa@zoho.com&pword=Idontknow94&message=Water%20leakage%20of%20"+String(floatR)+"L/min%20detected%20in%20kitchen.-HomeAssistent&selectednums="+phoneNumber+"&info=1&test=0";

                client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                          f"Host: " + host + "\r\n" + 
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
    } 
   }else{
    buzzer=false;//buzzer off
    if (flowEnd){
      flowEnd=false;
      flowFirst=true;

      if (timeStatus() != timeNotSet) {
            if (now() != prevDisplay) { 
                prevDisplay = now();
                store_var1+= digitalClockDisplay();
                store_var1+= "&";
            }
          }
      Serial.println(store_var);   

      delay(50);
      }
    }
   //end of water leakage reading    

       
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
  if (req.indexOf("/door/0") != -1){
    digitalWrite(4, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nDoor locked!";}
    
  else if (req.indexOf("/door/1") != -1){
    digitalWrite(4, 1);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nDoor unlocked!";}
    
  else if (req.indexOf("/door/check/1") != -1){    
    if(digitalRead(4)==LOW){
      pos="Door is locked!";}
    else if(digitalRead(4)==HIGH){
      pos="Door is not locked!";}
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+pos;}    
  
  else if (req.indexOf("/vibration/0") != -1){
    digitalWrite(5, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nKitchen_fan is now low";}
    
  else if (req.indexOf("/vibration/1") != -1){
    digitalWrite(5, 1);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nKitchen_fan is now high ";}

  else if (req.indexOf("/vibration/check/1") != -1){    
    if(digitalRead(5)==LOW){
      pos="Vibration sensor down!";}
    else if(digitalRead(5)==HIGH){
      pos="Vibration sensor up!";}
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+pos;}    

  else if (req.indexOf("/leak/0") != -1){
    digitalWrite(14, 0);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLeakage Sensor Down";}
    
  else if (req.indexOf("/leak/1") != -1){
    digitalWrite(14, 1);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLeakage Sensor Up";}

  else if (req.indexOf("/leak/check/1") != -1){    
    if(digitalRead(14)==LOW){
      pos="Water leakage sensor down!";}
    else if(digitalRead(14)==HIGH){
      pos="Water leakage sensor up!";}
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+pos;}

  else if (req.indexOf("/buzzer") != -1){
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+String(buzzer);}
  
  else if (req.indexOf("/notification") != -1){
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"+store_var1+"&"+store_var;}

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

void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}

//water leakage reading
int flow(){
    detachInterrupt(2);
   
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;    
    oldTime = millis();
    flowMilliLitres = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;
      

    // Reset the pulse counter so we can start incrementing again
    pulseCount = 0;
    
    // Enable the interrupt again now that we've finished sending output
    attachInterrupt(2, pulseCounter, FALLING);
    delay(1000);
    return flowRate;
  }

//vibration sensor reading
void vibSensing(){
  vibDetectedVal = digitalRead (13) ; // read the vibration alarm time
  
  if (vibDetectedVal == LOW) // If hear a sound
  {  
    buzzer=true; //buzzer on
    lastVibDetectTime = millis(); // record the time of the sound alarm
    if (!bAlarm){
      Serial.println("LOUD, LOUD");
      bAlarm = true;

      if (timeStatus() != timeNotSet) {
            if (now() != prevDisplay) { //update the display only if time has changed
                prevDisplay = now();
                store_var+="Vibration Detected|";
                store_var+= digitalClockDisplay();
                store_var+= "|";

                WiFiClient client;
                const int httpPort = 80;
                if (!client.connect(host, httpPort)) {
                  Serial.println("connection failed");
                  return;
                }

                String url = "/sendsmspost.php?uname=lahiruepa@zoho.com&pword=Idontknow94&message=Vibration%20detected%20in%20the%20living%20room.-HomeAssistent&selectednums="+phoneNumber+"&info=1&test=0";

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
    }
  }
  else
  {
    buzzer=false;//buzzer off
    if( (millis()-lastVibDetectTime) > vibAlarmTime  &&  bAlarm){
      Serial.println("quiet");
      bAlarm = false;

      if (timeStatus() != timeNotSet) {
            if (now() != prevDisplay) { 
                prevDisplay = now();
                store_var+= digitalClockDisplay();
                store_var+= "&";
            }
          }
    }
  }
  }
 //vibration sensor reading ends

