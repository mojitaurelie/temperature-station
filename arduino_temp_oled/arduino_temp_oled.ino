#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <DHT.h>

#define VERSION "1.2.0"

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
DHT dht;

byte i = 0;

void setup(void) {
  u8g2.begin();
  u8g2.enableUTF8Print();
  
  u8g2.setFontDirection(0);
  printBoardInfo();

  pinMode(2, INPUT);
  dht.setup(6);
}

void loop(void) {
  if (i > 5) {
    u8g2.clearBuffer();
    u8g2.sendBuffer();
    if (digitalRead(2) == HIGH) {
      powerScreen();
    }
    delay(50);
  } else {
    u8g2.clearBuffer();
    printTemp();
    printHumidity();
    u8g2.sendBuffer();
    delay(3000);
    i++;
  }
}

void printTemp() {
  u8g2.setFont(u8g2_font_luRS08_tf);
  u8g2.drawUTF8(5, 10, "Température"); 
  u8g2.setFont(u8g2_font_luRS14_tf);
  u8g2.setCursor(5, 27);
  u8g2.print(dht.getTemperature(),1);
  u8g2.print("°C");
  if(dht.getStatus() != 0) {
    u8g2.setFont(u8g2_font_luRS08_tf);
    u8g2.drawStr(80, 10, "[FAILED]");
  }
}

void printHumidity() {
  u8g2.setFont(u8g2_font_luRS08_tf);  // choose a suitable font
  u8g2.drawUTF8(5, 40, "Humidité"); 
  u8g2.setFont(u8g2_font_luRS14_tf);
  u8g2.setCursor(5, 58);
  u8g2.print(int(dht.getHumidity()));
  u8g2.print("%");
  if(dht.getStatus() != 0) {
    u8g2.setFont(u8g2_font_luRS08_tf);
    u8g2.drawStr(80, 40, "[FAILED]");
  }
}

void powerScreen() {
  i = 0;
}

void printBoardInfo() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_luRS08_tf);  // choose a suitable font
  u8g2.drawStr(5, 10, "Board: ATmega328P");
  u8g2.drawStr(5, 25, "Arch:  AVR (8-bit)");
  u8g2.drawUTF8(5, 45, "by Aurélie");
  u8g2.setCursor(5, 55);
  u8g2.print("Version ");
  u8g2.print(VERSION);
  u8g2.sendBuffer();
  delay(1200);
}
