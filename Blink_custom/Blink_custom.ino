/*
  Blink
  Turns an LED on for one second, then off for one second, repeatedly.
  http://www.arduino.cc/en/Tutorial/Blink
*/

#define BT_merah 2
#define BT_kuning 4
#define BT_hijau 5

#define BT_merah2 27
#define BT_kuning2 26
#define BT_hijau2 25

#define delayHijau 3000
#define delayHijau2 7000

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(BT_merah, OUTPUT);
  pinMode(BT_kuning, OUTPUT);
  pinMode(BT_hijau, OUTPUT);

  pinMode(BT_merah2, OUTPUT);
  pinMode(BT_kuning2, OUTPUT);
  pinMode(BT_hijau2, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  //delay(200);
  digitalWrite(BT_merah, HIGH);
  digitalWrite(BT_hijau2, HIGH);    
  delay(delayHijau);
  digitalWrite(BT_hijau2, LOW);
  digitalWrite(BT_kuning2, HIGH);
  delay(1000); 
  digitalWrite(BT_hijau2, LOW);
  digitalWrite(BT_kuning2, HIGH);    
  delay(1000); 
  digitalWrite(BT_merah, LOW);
  digitalWrite(BT_kuning2, LOW); 
  digitalWrite(BT_hijau, HIGH);
  digitalWrite(BT_merah2, HIGH);   
  delay(delayHijau);
  digitalWrite(BT_hijau, LOW);   
  digitalWrite(BT_kuning, HIGH);    
  delay(1000);
  digitalWrite(BT_kuning, LOW);    
  digitalWrite(BT_merah2, LOW);

  
    
}
