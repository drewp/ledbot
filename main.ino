#include <SoftwareSerial.h>
#include "FastLED.h"
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"

#define pin_wheel_l_fwd 14
#define pin_wheel_l_rev 16
#define pin_wheel_r_fwd 15
#define pin_wheel_r_rev 17
#define pin_rgb 8
#define pin_lcd_ce 7
#define pin_lcd_rst 6
#define pin_lcd_dc 5
#define pin_lcd_di 11
#define pin_lcd_clk 13
#define pin_lcd_led 9 // not yet
#define pin_ir_rx 10
#define pin_ir_tx 12

SoftwareSerial irSerial(pin_ir_rx, pin_ir_tx); // RX, TX
const char _h[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void lcd_print(Adafruit_PCD8544 lcd, char* s) {
  for (unsigned int i=0; i<strlen(s); i++) {
    lcd.write(s[i]);
  }
}

void setup() {
  irSerial.begin(57600);
  Serial.begin(115200);
  Serial.print(F("Hello\n"));

  Adafruit_PCD8544 lcd(pin_lcd_clk, pin_lcd_di, pin_lcd_dc, pin_lcd_ce, pin_lcd_rst);

  lcd.begin();
  lcd.display();

  lcd.setTextSize(1);
  lcd.setTextColor(BLACK);

  CRGB leds[8];
  FastLED.addLeds<WS2812B, pin_rgb>(leds, sizeof(leds));
  byte t = 0;
  unsigned char c = 255;
  while (1) {
    t++;
    for(byte i=0; i < 8; i++) {
      leds[i].setHSV(i == 2 ? (255-t) : t, 255, i == 2 ? 255 : 50);
    }
    FastLED.show();
    delay(30);

    lcd.clearDisplay();
    lcd.setCursor(0,0);

    lcd.write('h');
    lcd.write('u');
    lcd.write('e');
    lcd.write(':');
    lcd.write(' ');
    lcd.write('0' + (t / 100) % 10);
    lcd.write('0' + (t / 10) % 10);
    lcd.write('0' + (t / 1) % 10);

    lcd.write('I');
    if (irSerial.available()) {
      lcd.write('R');
      unsigned char r = irSerial.read();
      Serial.println(r, HEX);
      if (r == 0) {
        lcd.write('0');
      } else {
        c = r;
      }
    }
    lcd.write('\n');
    lcd.write('I');
    lcd.write('R');
    lcd.write(':');
    lcd.write(' ');
    lcd.write('0');
    lcd.write('x');
    if (c >= 16) {
      lcd.write(_h[c / 16]);
    }else{
      lcd.write('0');
    }
    lcd.write(_h[c % 16]);

  lcd.display();
}
}
void loop() {
}
