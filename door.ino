#include "WiFi.h"
int password[4] = {1,0,0,1};    //BT18ECE099-->9-->1001

int b0;
int check = 0;
int comp =0;
int newpassword[4] = {0,0,0,0};   //variable for new password

const char* ssid = "Shruti-ESP";    //name to be displayed
const char* Wifi_Password = "Shubh@123";

WiFiServer server(80);            //creates server

String html_print = "<!DOCTYPE html>\
<html> \
<body> \
<form> \
<h1>Welcome Home Shruti </h1> \
</form> \
</body> \
</html>";

String html_print2 ="<!DOCTYPE html>\
<html> \
<body> \
<form> \
<h1>Wrong Password!! Bye</h1> \
</form> \
</body> \
</html>";

int compare();
int detect();

void setup()
{
  Serial.begin(115200); //begin serial communication with baudrate 115200
  pinMode(2, OUTPUT); //builtin led as output
  pinMode (4, INPUT);   //gpio pin 4(touchsensor) as input
  digitalWrite(2, LOW); //led off initially
  WiFi.softAP(ssid, Wifi_Password);  //esp32 acts as soft access point to establish a WiFi.
  IPAddress IP = WiFi.softAPIP();//get IP address
  Serial.print("AP IP Address: ");
  Serial.println(IP);   //print ip address 
  server.begin();   //begin webserver
}

void loop() 
{
  if(touchRead(4) < 40)     //check if touch interrupted
  {check =1;}
  else 
  {check =0;}
  if(check)       //if touched
  { 
    for(int i=0;i<3;i++)  //blink 3 times
    {
      digitalWrite(2, HIGH);   // turn LED on 
      delay(500);                      
      digitalWrite(2, LOW);    // turn LED off 
      delay(500);           
    }
    Serial.println("Enter password");
    for(int i =0; i<4 ;i++)
    {
      newpassword[i] = detect();    //detect touch
      //Serial.println(" Wait processing ");
      delay(2000);
     }
    comp = compare(); //compare passwords
    if (comp == 1)			//if password matches
    {WiFiClient client = server.available(); //if incoming request is available
   //Serial.println(client);
   if(client)
  {
    String request = client.readStringUntil('\r');    // reading the request
    client.print(html_print);
    request="";
  } 
     Serial.println("Welcome Home Shruti");
     delay(10000);
    }
    else				//if password doesn't matches
    {WiFiClient client = server.available(); //if incoming request is available
   //Serial.println(client);
   if(client)
  {
    String request = client.readStringUntil('\r');    // reading the request
    client.print(html_print2);
    request="";
  }

    Serial.println("Wrong password!! Bye");
    delay(10000);         //delay 1sec
    } 
 }
}

int compare()   //function to compare passwords
{
  for(int i =0 ; i < 4 ; i++)
  {
    if(password[i] == newpassword[i])
    continue;
    else
    return 0;   // if nos. isnt same return 0
    }
    return 1;   //if all numberes correct return 1
}

int detect()    //function to detect touch
{       
  Serial.println("Press touchsensor for 1sec for 1");
  unsigned long Start_Time = millis();    //store current time stamp
   while(millis() - Start_Time < 1001)   //loop for 1sec
  { if (touchRead(4) < 40)
   b0=1;         //if touched 1
   else
   b0=0;         //if not touched 0
  } 
   Serial.println(b0);
   return b0;
}
