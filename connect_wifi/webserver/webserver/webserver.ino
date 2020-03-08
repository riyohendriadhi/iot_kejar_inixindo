
#include <WiFi.h>
#define PORT 8080
#define LED_BUILTIN 2

const char *SSID = "MOBILE-WIFI-LT1";
const char *PASSWORD = "Learning";

String header = "HTTP/1.1 200 OK\nContent-Type: text/html \n\n <html><body>";
String footer = "</body></html>";

WiFiServer server(8080);
WiFiClient client;

bool blinking = false;
bool ledOn = false;

String s;
String cmd;

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin( SSID, PASSWORD );

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("Web Server active: ");
  Serial.println(WiFi.localIP());
  server.begin();
}


void loop() {
  client = server.available(); //tunggu client

   if(client){
    while(client.connected()){
      if(client.available()){
        s = client.readString();
        
        cmd = getCommand(s);
        response(cmd);   
        if(cmd.equals("")){
          Serial.println("HOMEPAGE");
          
        }else if(cmd.equals("blink")){
            blinking  = true;
            ledOn = false;
        }else if(cmd.equals("on")){
            blinking  = false;
            ledOn = true;
        }else if(cmd.equals("off")){
            blinking  = false;
            ledOn = false;
        }else{
          client.stop();
        }
        
      }else{
        //Serial.println("No Client yet");  
      }

      if(blinking || ledOn){
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
      }

      if(blinking || !ledOn){
        digitalWrite(LED_BUILTIN, LOW);
        delay(1000);  
      }
    } 
   }
}

void response(String konten){
  client.println(header);
  String s1="<p><a href='blink'>LED Blinking</a></p>";
  String s2="<p><a href='on'>LED ON</a></p>";
  String s3="<p><a href='off'>LED OFF</a></p>";          
  Serial.print(konten);
  if(konten.equals("")){
    
  client.println(s1+s2+s3);
  }else{
    client.println(konten);
  }
  client.println(footer);  
}

String getCommand(String s){
  return (s.substring(5, s.indexOf(' ',5)));  
}
