#include<DHT.h>

#define DHTPIN 21
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
 
  Serial.begin(9600);
  dht.begin();

  Serial.println("Check DHT Sensor");
}

float temperatureFrh = 0;
float temperature = 0;
float temperatureTmp = 0;
float humidityTmp = 0;
int counter = 0;
int counter2 = 0;

// the loop function runs over and over again forever
void loop() {
    delay(1000);            
    temperature = dht.readTemperature();
    temperatureFrh = (temperature*(9/5))+32;
    float humidity = dht.readHumidity();

    if(isnan(humidity) || isnan(temperature)){
      Serial.println("Failed to load/read from DHT sensor");  
      return;
    }
    //float hic = dht.computeHeatIndex(temperature, humidity, false);

    if(counter2%5 == 0){
        Serial.println("");
        Serial.print("Kelembapan     ");
        Serial.print("Temperature    ");
        Serial.print("Temperature    ");
        Serial.println("");

        Serial.print("     %    ");
        Serial.print("     Celcius    ");
        Serial.print("     Farenheit    ");
        Serial.println("");
       }

    if(temperatureTmp != temperature && humidityTmp != humidity){
      Serial.println("");
      Serial.print("     ");
      Serial.print(humidity);
      Serial.print("     ");
      Serial.print(temperature);
      Serial.print("     ");
      Serial.print(temperatureFrh);
      Serial.println("");
    }else{
      if(counter<20){
        Serial.print(".");
      }
     }
     
    if(counter == 20){counter=0;}
    temperatureTmp = temperature;
    humidityTmp = humidity;
    counter++;
    counter2++;
    delay(1000);
 }
