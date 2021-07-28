#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#include <Wire.h>
//#include <ACROBOTIC_SSD1306.h>
#include <WiFiManager.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

char auth[] = "qCnEUqfMiR7ZNH8sflfltkNN4Wzf_h5p";  //Blynk Authentication Token
char ssid[] = "kun";           //WIFI Name
char pass[] = "rican0987"; 

Servo servo;
 int horn=0;
 
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
      if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
 //  WiFiManager wm;
//   wm.autoConnect("SISTEM MOBIL");
Blynk.begin(auth, ssid, pass);
servo.attach(2);
pinMode(horn,OUTPUT);
//Wire.begin();  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(30, 0);

  display.println("INISIALISASI");
  
  display.setCursor(50, 10);
  display.println("SISTEM");
  display.display();
  
delay(4000);
display.clearDisplay();


}
 
void servo_via_button1() {
  int pos;
//sudut 0 - 180 derajat
  for (pos = 0; pos <= 180; pos += 1) {
    servo.write(pos);              
    delay(5);        
  }
}
 
void servo_via_button2() {
  int pos1;
//sudut 180 - 0 derajat
  for (pos1 = 180; pos1 >= 0; pos1 -= 1) {
    servo.write(pos1);            
    delay(5);              
  }
}
 
BLYNK_WRITE(V3) {
//servo.write(param.asInt());
  int pinValue = param.asInt();
  if (pinValue == 1) {    
    servo_via_button1(); 
    display.setTextSize(1);
  display.setCursor(20, 10);
  display.println("TANGKI TERBUKA");
  display.display();
  
  tone(horn,494);             
    Blynk.run(); 
    int pinValue = 0;  
    Blynk.syncVirtual(V3);

  delay(3000);
  noTone(horn);
  display.clearDisplay();  
  }
}
 
BLYNK_WRITE(V4) {
  int pinValue1 = param.asInt();
  if (pinValue1 == 1) {    
    servo_via_button2();   
display.setTextSize(1);
    display.setCursor(20, 10);
  display.println("TANGKI TERTUTUP");
  display.display();
      tone(horn,494);        
    Blynk.run(); 
    int pinValue1 = 0;  
    Blynk.syncVirtual(V4);

  delay(3000);
  noTone(horn);
display.clearDisplay();  
  }
}
 
BLYNK_WRITE(V5)
{
  servo.write(param.asInt());
}
 
void loop()
{
Blynk.run();
display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("__STATUS__");
  
  display.setCursor(0, 20);
   display.println("__TANGKI__");
   
  display.display();
  display.clearDisplay();
}
