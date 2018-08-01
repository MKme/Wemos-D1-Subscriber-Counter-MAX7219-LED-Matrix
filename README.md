# Wemos-D1-Subscriber-Counter-MAX7216-LED-Matrix
Simple Subscriber counter display using WEMOS D1 Mini and MAX7219 LED Matrix for scrolling text

Erics Wemos D1 Mini displaying YouTube Subscriber Count with MAX7219 LED Matrix Displays

Original Library here https://github.com/squix78/MAX7219LedMatrix but contains no function to rotate for my displays

Brian Lough's library contains rotate: https://github.com/witnessmenow/MAX7219LedMatrix

Brians doesnt work with Wemos D1 mini unless you comment out this line https://github.com/witnessmenow/MAX7219LedMatrix/blob/master/LedMatrix.cpp#L34
Done in the cpp file contained with this sketch

Eric originally followed this tutorial here for the YouTube API info etc: http://www.joeybabcock.me/blog/projects/arduino-esp8266-live-subscriber-display/

### Get your YouTube API Key:
https://console.developers.google.com/

### Get Your YouTube Channel URL Here:
https://www.youtube.com/account_advanced

### 3D printed case from Thingiverse:
https://www.thingiverse.com/thing:2988071


### Wiring For WEMOS D1 Mini

It should be wired as followes

| Pin On 7219| Pin on Wemos D1 Mini |
| ------------- |----------------|
| GND     | G |
| VCC     | 3V3 |
| DIN     | D7 |
| CS     | D4 |
| CLK   | D5 |


### Support my projects by picking up the display/board here:

Wemos D1: https://amzn.to/2ACRWRA

LED Matrix: https://amzn.to/2McsuUl

### More Projects and Videos!
My Youtube Channel  : http://www.youtube.com/mkmeorg

My website   : http://www.mkme.org
