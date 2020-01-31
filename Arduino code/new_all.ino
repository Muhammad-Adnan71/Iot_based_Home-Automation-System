#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Wire.h>       //I2C library
#include <RtcDS3231.h>
#include "hw_timer.h"   


RtcDS3231<TwoWire> rtcObject(Wire);

// Set these to run example.
#define FIREBASE_HOST "homeautu1.firebaseio.com"
#define FIREBASE_AUTH "6JwsAI16G4ESzRGlMQPdMtWImVol9FB7FU0WAolG"
#define WIFI_SSID "CA.US.PK"
#define WIFI_PASSWORD "03343219439"
       

const byte zcPin = 12;
const byte pwmPin = 13;  

byte fade = 1;
byte state = 1;
byte tarBrightness = 255;
byte curBrightness = 0;
byte zcState = 0; // 0 = ready; 1 = processing;

void ICACHE_RAM_ATTR zcDetectISR ();
void ICACHE_RAM_ATTR dimTimerISR ();

//int y;
//int m;
//int d;
//int hr;
//int mi;
//int sec;

void setup() {
  Serial.begin(115200);   
  pinMode(zcPin, INPUT_PULLUP);
  pinMode(pwmPin, OUTPUT);
  pinMode(D5,OUTPUT);
  pinMode(D0,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("LIGHT_1", 0);
  Firebase.set("LIGHT_2", 0);
  Firebase.set("LIGHT_3", 0);
  Firebase.set("LIGHT_4", 0);
  Firebase.set("CONTROL", 0);
  Firebase.set("HOUR", 0);
  Firebase.set("MINUTE", 0);
  Firebase.set("DAY", 0);
  Firebase.set("MONTH", 0);
  Firebase.set("YEAR", 0);
  Firebase.set("HOUREND", 0);
  Firebase.set("MINUTEEND", 0);
  Firebase.set("DAYEND", 0);
  Firebase.set("MONTHEND", 0);
  Firebase.set("YEAREND", 0);
  attachInterrupt(zcPin, zcDetectISR, RISING);    // Attach an Interupt to Pin 2 (interupt 0) for Zero Cross Detection
  hw_timer_init(NMI_SOURCE, 0);
  hw_timer_set_func(dimTimerISR);
  
  //y = Firebase.getInt("SYEAR");
  //m = Firebase.getInt("SMONTH");
  //d = Firebase.getInt("SDAY");
  //hr = Firebase.getInt("SHOUR");
  //mi = Firebase.getInt("SMINUTE");
  //sec = Firebase.getInt("SSECOND");
  rtcObject.Begin(); 
  //RtcDateTime currentTime = RtcDateTime(2019,11,14,11,21,00); //define date and time object
  //rtcObject.SetDateTime(currentTime); //configure the RTC with object

  // connect to wifi.

 
//  //declare a string as an array of chars
 


}

int n1 = 0;
int n2 = 0;
int n3 = 0;
int n4 = 0;
int n5 = 0;
int val = 0;




void loop() {



int n6;
int n7;
int n9;
int n10;
int n11;
int n12;
int n13;
int n15;
int n16;
int n17;




  
 /* // put your main code here, to run repeatedly:
    if (Serial.available()){
        int val = Serial.parseInt();
        if (val>0){
          tarBrightness =val;
          Serial.println(tarBrightness);
        }
        
    }*/
 n1= Firebase.getInt("LIGHT_1");
 n2= Firebase.getInt("LIGHT_2");
 n3= Firebase.getInt("LIGHT_3");
 n5= Firebase.getInt("CONTROL");
 n6= Firebase.getInt("HOUR");
 n7= Firebase.getInt("MINUTE");
 n9= Firebase.getInt("DAY");
 n10= Firebase.getInt("MONTH");
 n11= Firebase.getInt("YEAR");
 n12= Firebase.getInt("HOUREND");
 n13= Firebase.getInt("MINUTEEND");
 n15= Firebase.getInt("DAYEND");
 n16= Firebase.getInt("MONTHEND");
 n17= Firebase.getInt("YEAREND");



  // handle error
val = n5;
  if (val>0){
          tarBrightness =val;
          Serial.println(tarBrightness);
        }

 if (n1==1) {
      Serial.println("LED 1 IS ON");
      digitalWrite(D5,HIGH);
        
  }
 else
 {

       Serial.println("LED 1 IS OFF");
       digitalWrite(D5,LOW);
  }
  if (n2==1) {
      Serial.println("LED 2 IS ON");
      digitalWrite(D0,HIGH);
       
  }
 else
 {

       Serial.println("LED 2 IS OFF");
       digitalWrite(D0,LOW);
  }
  if (n3==1) {
      Serial.println("LED 3 IS ON");
      digitalWrite(D3,HIGH);
       
  }
else
 {

       Serial.println("LED 3 IS OFF");
       digitalWrite(D3,LOW);
  }
 
RtcDateTime currentTime = rtcObject.GetDateTime();

char str[20]; 
  sprintf(str, "%d/%d/%d %d:%d:%d",     //%d allows to print an integer to the string
          currentTime.Year(),   //get year method
          currentTime.Month(),  //get month method
          currentTime.Day(),    //get day method
          currentTime.Hour(),   //get hour method
          currentTime.Minute(), //get minute method
          currentTime.Second()  //get second method
         );

 
  Serial.println(str);

  if ((n6==currentTime.Hour()) && (n7==currentTime.Minute()) && (n9==currentTime.Day()) && (n10==currentTime.Month()) && (n11==currentTime.Year())) {
  
    Serial.println("Schedule LED ON");
      digitalWrite(D4,HIGH);
     
    }
   if ((n12==currentTime.Hour()) && (n13==currentTime.Minute()) && (n15==currentTime.Day()) && (n16==currentTime.Month()) && (n17==currentTime.Year())) {
  
    Serial.println("Scheduled LED IS OFF");
      digitalWrite(D4,LOW);
     
    }
   
 
 return;
  
}


void dimTimerISR() {
    if (fade == 1) {
      if (curBrightness > tarBrightness || (state == 0 && curBrightness > 0)) {
        --curBrightness;
      }
      else if (curBrightness < tarBrightness && state == 1 && curBrightness < 255) {
        ++curBrightness;
      }
    }
    else {
      if (state == 1) {
        curBrightness = tarBrightness;
      }
      else {
        curBrightness = 0;
      }
    }
    
    if (curBrightness == 0) {
      state = 0;
      digitalWrite(pwmPin, 0);
    }
    else if (curBrightness == 255) {
      state = 1;
      digitalWrite(pwmPin, 1);
    }
    else {
      digitalWrite(pwmPin, 1);
    }
    
    zcState = 0;
}

void zcDetectISR() {
  if (zcState == 0) {
    zcState = 1;
  
    if (curBrightness < 255 && curBrightness > 0) {
      digitalWrite(pwmPin, 0);
      
      int dimDelay = 30 * (255 - curBrightness) + 400;//400
      hw_timer_arm(dimDelay);
    }
  }
}
