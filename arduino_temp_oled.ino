#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <DHT.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
DHT dht;

byte i = 0;

void setup(void) {
  u8g2.begin();
  u8g2.enableUTF8Print();
  
  u8g2.setFontDirection(0);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_luRS08_tf);  // choose a suitable font
  u8g2.drawStr(40,35,"Welcome !");
  u8g2.sendBuffer();

  pinMode(2, INPUT);
  dht.setup(6);
  delay(1500);
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
    u8g2.drawLine(74, 0, 74, 64);
    printTemp();
    printHumidity();
    u8g2.sendBuffer();
    delay(3000);
    i++;
  }
}

void printTemp() {
  u8g2.setFont(u8g2_font_luRS08_tf);
  u8g2.drawStr(5,10,"Temp");
  u8g2.setFont(u8g2_font_luRS14_tf);
  u8g2.setCursor(5, 60);
  u8g2.print(dht.getTemperature(),1);
  u8g2.print("°C");
}

void printHumidity() {
  u8g2.setFont(u8g2_font_luRS08_tf);  // choose a suitable font
  u8g2.drawStr(80,10,"Humidity");
  u8g2.setFont(u8g2_font_logisoso22_tf);
  u8g2.setCursor(80, 60);
  u8g2.print(int(dht.getHumidity()));
  u8g2.print("%");
}

void powerScreen() {
  i = 0;
}
