#include <SoftwareSerial.h>
SoftwareSerial esp(2,3);
 
#define DEBUG true 
#define IP "184.106.153.149"// thingspeak.com ip
String Api_key = "GET /update?key=BW6IV70ZUHN77DQY"; //change it with your api key eg: "GET /update?key=Your_Api_Key"

int error;
const int sensor_pin = A0;
float turbidity,voltage;  
float output;  

void setup()
{ 
  Serial.begin(9600);
  esp.begin(9600);
  pinMode(sensor_pin,INPUT);
  
  send_command("AT+RST\r\n", 2000, DEBUG); //reset module
  send_command("AT+CWMODE=1\r\n", 1000, DEBUG); //set station mode
  send_command("AT+CWJAP=\"Your_wifi_name\",\"Your_wifi_password\"\r\n", 2000, DEBUG);   //connect wifi network
  while(!esp.find("OK")) { //wait for connection
  Serial.println("Connected to Wi-Fi");}  //Shows wifi is connected
}

void loop()
{
  output=analogRead(sensor_pin);
  turbidity =(output*500)/1023;
  start: //label 
  error=0;
  updatedata();
  if (error==1){
    goto start; //go to label "start"
  }
  delay(1000);
}

void updatedata(){
  String command = "AT+CIPSTART=\"TCP\",\"";
  command += IP;
  command += "\",80";
  Serial.println(command);
  esp.println(command);
  delay(2000);
  if(esp.find("Error")){
    return;
  }
  command = Api_key ;
  command += "&field1=";   
  command += turbidity;
  command += "\r\n";
  Serial.print("AT+CIPSEND=");
  esp.print("AT+CIPSEND=");
  Serial.println(command.length());
  esp.println(command.length());
  if(esp.find(">")){
    Serial.print(command);
    esp.print(command);
  }
  else{
    
   Serial.println("AT+CIPCLOSE");
   esp.println("AT+CIPCLOSE");
    //Resend...
    error=1;
  }
  }

String send_command(String command, const int timeout, boolean debug)
{
  String response = "";
  esp.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp.available())
    {
      char c = esp.read();
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}
