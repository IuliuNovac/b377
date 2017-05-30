#include <SoftwareSerial.h>                          //Include library
SoftwareSerial esp8266Module(11, 10);                // RX, TX
#define DEBUG 1                                      // 0 - Debugging off // 1 - Debugging on 
#define Qt 1                                         // 0 - Qt off // 1 - Qt on [ Debug should be off ]
#define IP "184.106.153.149"                         // IP address of thingspeak.com

String network = "b377";                             //define network               (replace if requred)
String password = "robotics";                        //define pass                  (replace if requred)
String GET = "GET /update?key=UNCAAVG8SIV9IF6R";     // UNCAAVG8SIV9IF6R is api key (replace if requred)
const int trigPin = 5;                               // Define trigPin To send Data to sensor 1
const int echoPin = 4;                               // Define echoPin To recive Data for future conversion to sensor 1
long duration, cm, cmm;

void setup() 
{
  Serial.begin(9600);                                // Setting hardware serial baud rate to 9600
  esp8266Module.begin(9600);                         // Setting softserial(esp) baud rate to 9600
  pinMode(trigPin, OUTPUT);                          // Use trigpin of ultrasonic sensor to send pulse
  pinMode(echoPin, INPUT);                           // Use echoPin of ultrasonic sensor to read pulse so it can mesure lenth [duration / 29 / 2]
  delay(500);                                
  if(DEBUG) { Serial.println("Setup Finished"); }
}

void loop() 
{
  setupEsp8266();         //run void setupEsp8266()   // Check if ESP8266 Resonds OK and if is ok // run void connectToWiFi()                        
  Sensor1();              //run void Sensor1();       // Gets Data from Ultrasonic Sensor
  int centimeters = cm;                               // Define data recived from Sensor1() and define it as [centimeters]
  SendData(String (centimeters));     //Sends both sensor value to SendData()
  delay(500);
}

void SendData(String centimeters )      //Run code that recieve sensors value and sends it to thingspeak
{  
  if(DEBUG) {  Serial.println("Send Data Initiated"); }
  String cmd = "AT+CIPSTART=\"TCP\",\"";            
  cmd += IP;
  cmd += "\",80";
  esp8266Module.println(cmd);
  if(DEBUG)
  {
    Serial.print("Sent to Esp8266= ");
    Serial.println(cmd);
  }
  delay(500);
  if(esp8266Module.find("Error"))
  {
    if(DEBUG) {  Serial.println("ERROR while SENDING"); }  
    return;
  }
  cmd = GET + "&field1=" + centimeters +"\r\n";
  esp8266Module.print("AT+CIPSEND=");
  esp8266Module.println(cmd.length());
  if(DEBUG)
  {
    Serial.print("Sent to Esp8266= ");
    Serial.print(cmd.length());
    Serial.println("Byte");
  }
  delay(1000);
  if(esp8266Module.find(">"))
  {
    esp8266Module.print(cmd);
    if(DEBUG)
    {
      Serial.print("Sent to Esp8266= ");
      Serial.println(cmd);
      Serial.println("Data is sent");
    }
  }
  else
  {
    esp8266Module.println("AT+CIPCLOSE");
    if(DEBUG) { Serial.println("Connection closed");  }  
  }
}

int Sensor1()
{
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cmm = duration / 29 / 2 ;
  if (cmm < 200)
  {cm = 100 - cmm /2 ;}
  if(Qt) { Serial.println(cm);}
  if(DEBUG) { Serial.println(cmm);}
  
  return cm;
  
}

void setupEsp8266()                                   
{
  if(DEBUG){  Serial.println("Reseting esp8266"); }
  esp8266Module.flush();                  //Clean Buffer
  esp8266Module.println(F("AT+RST"));     //Check if esp is set up
  if(DEBUG){  Serial.println("SENT AT+RST "); }
  delay(5000);
  if (esp8266Module.find("OK")) 
  { 
    if(DEBUG){  Serial.println("Found OK"); }
    esp8266Module.flush();                //Clean Buffer
    delay(1000);
    esp8266Module.flush();                //Clean Buffer
    connectToWiFi();                      //run connectToWiFi file
  }
  else 
  { 
    if(DEBUG){  Serial.println("OK not found"); }
    setupEsp8266();
  }
}
bool connectToWiFi()
{ 
  if(DEBUG){  Serial.println("connectToWiFi"); }
  String cmd = F("AT+CWJAP=\"");
  cmd += network;
  cmd += F("\",\"");
  cmd += password;
  cmd += F("\"");
  esp8266Module.println(cmd);
  if(DEBUG) {  Serial.println(cmd);  }
  delay(1000);
  if (esp8266Module.find("OK"))
  { 
    if(DEBUG) {  Serial.println("Connected to Access Point");  }
    
  } 
  else  
  {
    if(DEBUG) {  Serial.println("Could not connect to Access Point"); }
    connectToWiFi();
  }
}


