#include <WiFi.h>
#define PORT 8080
#define LED_BUILTIN 2
#include<DHT.h>
#define DHTPIN 22
#define LDRPIN 32
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int tg1 = 18, ech1 = 19;
int jarak, LDRValue ;
long randomNumber;
String s;
String cmd;
float temperature = 0;
float humidity = 0;

const char *SSID = "MOBILE-WIFI-LT1";
const char *PASSWORD = "Learning";

String header = "HTTP/1.1 200 OK\nContent-Type: text/html \n\n <html><body>";
String footer = "</body></html>";

WiFiServer server(8080);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  dht.begin();

  
  
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
          refresh(0,0,0,0);        
        }else if(cmd.equals("refresh?")){
          delay(300);
          jarak = cek_sensor(tg1, ech1);
          temperature = dht.readTemperature();
          humidity = dht.readHumidity(); 
          LDRValue = analogRead(LDRPIN); // read the value from the LDR
         Serial.println(" LDR : ");
         Serial.print(LDRValue);
          refresh(jarak, temperature, humidity, LDRValue);
                 
        }else{
          refresh(0,0,0,0);       
          client.stop();
        }

        //Serial.println(cmd);
        delay(100);
        
      }else{
        //Serial.println("No Client yet");  
        client.stop();
      }

      delay(1000);
    } 
   }
}

void refresh(int jarak, float temperature, float humidity, int ldrValue){
  client.println(header);
  client.println("<html><heand><title>Sensor</title>");
  client.println("<meta name='viewport' content=width=device-width, intial-scale=1.0'>");
  client.println("</head>");
  client.println("</body><h1>Data Sensor</h1>");
  client.printf("<p>Nilai Data dari Sensor jarak adalah : %d </p>", jarak);
  client.printf("<p>Nilai Data dari Sensor Suhu adalah : %f </p>", temperature);
  client.printf("<p>Nilai Data dari Sensor Humidity adalah : %f </p>", humidity);
  client.printf("<p>Nilai Data dari Sensor LDR adalah : %d </p>", ldrValue);
  client.println("<p><form action='/refresh'><input type='submit' value='Refresh'></form></p>");
  client.println(footer);
} 

String getCommand(String s){
  return (s.substring(5, s.indexOf(' ',5)));  
}

int cek_sensor(int  out, int in){
    long duration, distance;
    digitalWrite(out, LOW);
    delayMicroseconds(2);
    digitalWrite(out,HIGH);
    delayMicroseconds(10);
    digitalWrite(out, LOW);

    duration = pulseIn(in, HIGH);
    distance = (duration/2)/29;
    
    //Serial.println(" Jarak : ");
    //Serial.print(distance);
    return distance;
  }
