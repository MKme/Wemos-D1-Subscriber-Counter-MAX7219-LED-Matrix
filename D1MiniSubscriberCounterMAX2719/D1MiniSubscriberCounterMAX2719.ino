/* 
Erics Wemos D1 Mini displaying YouTube Subscriber Count with MAX7219 LED Matrix Displays

Original Library here https://github.com/squix78/MAX7219LedMatrix but contains no function to rotate for my displays
Brian Lough's library contains rotate: https://github.com/witnessmenow/MAX7219LedMatrix
Brians doesnt work with Wemos D1 mini unless you comment out this line https://github.com/witnessmenow/MAX7219LedMatrix/blob/master/LedMatrix.cpp#L34
Done in the cpp file contained with this sketch
Eric originally followed this tutorial here for the YouTube API info etc: http://www.joeybabcock.me/blog/projects/arduino-esp8266-live-subscriber-display/
Wiring for Wemos D1 Mini:
| Pin On 7219| Pin on Wemos D1 Mini |
| ------- |----------------|
| GND     | G |
| VCC     | 3V3 |
| DIN     | D7 |
| CS      | D4 |
| CLK     | D5 |

Support my projects by picking up the display/board here:
Wemos D1: https://amzn.to/2ACRWRA
LED Matrix: https://amzn.to/2McsuUl

My Youtube Channel  : http://www.youtube.com/mkmeorg
My website   : http://www.mkme.org

*/
#include <SPI.h>
#include "LedMatrix.h"
#define NUMBER_OF_DEVICES 4
#define CS_PIN 2
LedMatrix ledMatrix = LedMatrix(NUMBER_OF_DEVICES, CS_PIN);
int x = 0;
#include <YoutubeApi.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h> // This Sketch doesn't technically need this, but the library does so it must be installed.

//------- Replace the following! ------
char ssid[] = "xxxxx";       // your network SSID (name)
char password[] = "xxxxx";  // your network key
#define API_KEY "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"  // your google apps API Token
#define CHANNEL_ID "U456j5-kBvyy5Y1X_DTgrTOQ" // Channel URL text - get from YT advanced Dashboard

WiFiClientSecure client;
YoutubeApi api(API_KEY, client);

unsigned long api_mtbs = 60000; //mean time between api requests
unsigned long api_lasttime;   //last time api request has been done
long subs = 0;

void setup() {
  ledMatrix.init();
    ledMatrix.setRotation(true);  //This is Brians MAGICAL rotation function for these displays!
    ledMatrix.setText("MKME Lab YouTube Sub Count");
  Serial.begin(115200);
  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
   WiFi.hostname("ESP8266SubscriberCounter"); //This changes the hostname of the ESP8266 to display neatly on the network router.
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

}
void loop() {
  ledMatrix.clear();
  ledMatrix.scrollTextLeft();
  ledMatrix.drawText();
  ledMatrix.commit();
  delay(100);
   
if (millis() - api_lasttime > api_mtbs)  {
    if(api.getChannelStatistics(CHANNEL_ID))
    {
      Serial.println("---------Stats---------");
      Serial.print("Subscriber Count: ");
      Serial.println(api.channelStats.subscriberCount);
      Serial.print("View Count: ");
      Serial.println(api.channelStats.viewCount);
      Serial.print("Comment Count: ");
      Serial.println(api.channelStats.commentCount);
      Serial.print("Video Count: ");
      Serial.println(api.channelStats.videoCount);
      // Probably not needed :)
      //Serial.print("hiddenSubscriberCount: ");
      //Serial.println(api.channelStats.hiddenSubscriberCount);
      Serial.println("------------------------");
      SaveStats();
    }
    api_lasttime = millis();
  }
}

void SaveStats() {
  ledMatrix.setText(String(api.channelStats.subscriberCount));
  }
