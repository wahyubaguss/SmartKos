#define BLYNK_TEMPLATE_ID "TMPLxxx32Xe_"
#define BLYNK_DEVICE_NAME "Mobile Dashboard"
#define BLYNK_AUTH_TOKEN "rdPFHby7lwASBL25n_ZElKWmdxj66mJa"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "HotSpot@UNESA";
char password[] ="";

#include <DHT.h>
#include <DHT_U.h>
#include <HCSR04.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h> // include library
#include <BlynkSimpleEsp32.h>
int LDR = 15;
int sensorValue;
const int relay = 19;
const int sensorMin = 0;
const int sensorMax = 4096;
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 0
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define BLYNK_PRINT Serial
#define DHTPIN 5
#define RedLed 23
#define trigPin 2
#define echoPin 4
#define buzzer 13
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
long duration;
float jarak;
HCSR04 hc(trigPin,echoPin);
#define SCREEN_ADDRESS 0x3C 

void SmartDoor(){
jarak = hc.dist();
  if(jarak < 7){ 
  digitalWrite(buzzer,HIGH);
  display.clearDisplay();
  display.setTextSize(2); 
  display.setCursor(0,25);
  display.print("Ada Maling!!!");
}
  else if(jarak > 7){ 
  digitalWrite(buzzer,LOW); 
  display.setTextSize(1); 
  display.setCursor(0,35);
  display.print("Aman");
}
  Blynk.virtualWrite(V8,jarak);
  display.setTextSize(1); 
  display.setCursor(0,0); 
  display.print ("Jarak(cm) "); 
  display.setTextSize(2); 
  display.setCursor(0,10); 
  display.print(jarak); 
  delay(500); 
  display.display(); 
  display.clearDisplay();
}

void SmartEnvirontment(){
float h = dht.readHumidity(); // pengukuran kelembaban
  float t = dht.readTemperature(); // pengukuran tempperature
    if ( t > 27 ){
    digitalWrite(relay,HIGH);
  } 
    else {
    digitalWrite(relay,LOW);
  }
    Blynk.virtualWrite(V3,t);
    Blynk.virtualWrite(V4,h);
}

//void SmartLamp(){
  int sensorValue = analogRead(LDR);
  int range = map(sensorValue, sensorMin, sensorMax, 0, 100);
  Blynk.virtualWrite(V0, range);
  if( range > 50 ){
  digitalWrite(RedLed,HIGH);
  } 
  else {
  digitalWrite(RedLed,LOW);
  }
}

void setup() {
  pinMode(buzzer,OUTPUT);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
  Serial.println(F("SSD1306 allocation failed"));
  for(;;); 
}
  display.setTextSize(2); 
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();
  Blynk.begin(auth,ssid,password); 
  dht.begin();
}

void loop() {
  
// Smart Door 
SmartDoor();
//Smart Environment
SmartEnvirontment();
//Smart Lamp 
SmartLamp();
//kontrol Smart door
  int Kontrol_Smartdoor = analogRead(buzzer);
  Blynk.virtualWrite(V6, Kontrol_Smartdoor);

//kontrol Smart Lamp
  int Kontrol_SmartLamp = analogRead(RedLed);
  Blynk.virtualWrite(V7,Kontrol_SmartLamp);

//kontrol Smart Environtment
  int Kontrol_SmartEnvirontment = analogRead(relay);
  Blynk.virtualWrite(V5, Kontrol_SmartEnvirontment);
}
