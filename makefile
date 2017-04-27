BOARD_TAG    = nano328
ARDUINO_LIBS = FastLED-3.1.3 Adafruit-GFX-Library-master Adafruit-PCD8544-Nokia-5110-LCD-library-master SPI
USER_LIB_PATH := $(realpath .)
MONITOR_BAUDRATE = 115200

include /usr/share/arduino/Arduino.mk
