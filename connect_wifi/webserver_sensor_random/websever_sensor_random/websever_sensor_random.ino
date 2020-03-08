
#include <WiFi.h>
#define PORT 8080
#define LED_BUILTIN 2

const char *SSID = "MOBILE-WIFI-LT1";
const char *PASSWORD = "Learning";

String header = "HTTP/1.1 200 OK\nContent-Type: text/html \n\n <html><body>";
String footer = "</body></html>";

WiFiServer server(8080);
WiFiClient client;

long randomNumber;

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

  randomSeed(42);
}


void loop() {
  client = server.available(); //tunggu client
  //Serial.print("waiting fro Client");

   if(client){
    //Serial.print("Got new Client");
    while(client.connected()){
      if(client.available()){
        
        s = client.readString();
        cmd = getCommand(s);
        //response(cmd);   
        
        if(cmd.equals("")){
          refresh(0);        
        }else if(cmd.equals("refresh?")){
          refresh(random(0,10000));       
        }else{
          refresh(0);       
          client.stop();
        }

        Serial.println(cmd);
        delay(100);
        
      }else{
        //Serial.println("No Client yet");  
        client.stop();
      }

      delay(1000);
    } 
   }
}

void refresh(int nilai){
  client.println(header);
  client.println("<html><heand><title>Sensor</title>");
  client.println("<meta name='viewport' content=width=device-width, intial-scale=1.0'>");
  client.println("</head>");
  client.println("</body><h1>Data Sensor</h1>");
  client.printf("<p>Nilai Data dari Sensor adalah : %d </p>", nilai);
  client.println("<p><form action='/refresh'><input type='submit' value='Refresh'></form></p>");
  client.println(footer);
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
