//for RFID
#define SS_PIN 15  //D2
#define RST_PIN 9 //D1

#include <SPI.h>
#include <MFRC522.h>
#include <FirebaseESP8266.h>
#include <FirebaseESP8266HTTPClient.h>
//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

//wifi firebase connection
#define FIREBASE_HOST "nodemcu-3aeeb.firebaseio.com"
#define FIREBASE_AUTH "yhMrp1GbgyvN745VJ9xojEWWrof3UTNf2mRkReC6"
#define WIFI_SSID "SLT-FH7"
#define WIFI_PASSWORD "prasad3232"

//Define FirebaseESP8266 data object
FirebaseData firebaseData;

Servo servo;
LiquidCrystal_I2C lcd(0x27, 20, 4);
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;
String content= "";
String path = "/Car_Parking";//firebase path

void setup() 
{
  Serial.begin(115200);   // Initiate a serial communication

  ////////RFID///////////////////////////////////////
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  //////////////////////////////////////

  servo.attach(2);
  servo.write(0);

  lcd.begin(20,4);
  lcd.init();

  // Turn on the backlight.
  lcd.backlight();
  lcd_d(0,7,"Welcome");
  delay(3000);
  lcd.clear();
  lcd_d(1,1,"Use Your RFID Card");
  
  //////wifi//////
  

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  
  /*
  This option allows get and delete functions (PUT and DELETE HTTP requests) works for device connected behind the
  Firewall that allows only GET and POST requests.
  
  Firebase.enableClassicRequest(firebaseData, true);
  */
  
}
void loop() 
{
  //wifiData("46546",769374789);
   //wifiData("12324",769374789);
  
 rfid();
 if(statuss==1){
  statuss=0;
  Serial.println(content.substring(1));
 }
} 
