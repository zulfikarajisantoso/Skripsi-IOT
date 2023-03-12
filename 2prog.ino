
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
//#include <WiFiClientSecure.h>
//#include <UniversalTelegramBot.h>
#include <DHT.h>
#include "CTBot.h";

#define DHTPIN 13 // DHT11
#define DHTTYpe DHT11
DHT dht(DHTPIN, DHTTYpe);

CTBot mybot;

char ssid[] = "bukanapart";                    // Enter your WIFI name
char pass[] = "12qw12qw";                      // Enter your WIFI password
  
//var token dan id tele
String token = "6111511620:AAHeZkpQ9XlZeSS8Ydq_zMEaGYoIKJ_ltec";
const int id = 1196474960;
int datasuhu;

String status;

void setup() 
{
    Serial.begin(9600); 
//   pinMode(DHTPIN, INPUT);
    Serial.println("Masuk Sistem");

// koneksi ke wifi
   mybot.wifiConnect(ssid, pass);
  
//  set token tele
  mybot.setTelegramToken(token);
//  
//  cek koneksi wifi my bot
  if(mybot.testConnection())
    Serial.println("Koneksi Berhasil");
  else
    Serial.println("koneksi gagal");

//  coba();
  dht.begin();  
}

void pesan(){
   TBMessage tMessage;
  int h = dht.readHumidity();
  int t = dht.readTemperature(); 
  if(mybot.getNewMessage(tMessage))
  { 
    if(tMessage.messageType == CTBotMessageText)
    {
      if(tMessage.text.equalsIgnoreCase("/start"))
      {
        String reply = "";
        reply += "Hi " + tMessage.sender.firstName + "\n";
        reply += "Pilih Menu Dibawah : \n";
        reply += "Lihat Suhu : /suhu";
        mybot.sendMessage(tMessage.sender.id, reply);
      }
      
      if(tMessage.text.equalsIgnoreCase("/suhu"))
      {
        String temp = "Suhu: ";
         temp += int(t);
         temp += " *C";
      
        mybot.sendMessage(tMessage.sender.id, temp);
      }
    }
  } 
    
}

void loop(){  
  pesan();

  int t = dht.readTemperature(); 
  TBMessage tMessage;
  delay(120000);
//   Serial.println(int(t));
  if(t > 24){
     Serial.println("fafas");
     mybot.sendMessage(tMessage.sender.id, "panas");
  }
  else {
     mybot.sendMessage(tMessage.sender.id, "Aman");
  }
} 
