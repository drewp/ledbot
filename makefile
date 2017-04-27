#BOARD_TAG    = nano328
BOARD_TAG    = nano
BOARD_SUB = atmega328
ARDUINO_LIBS = FastLED Adafruit-GFX-Library Adafruit-PCD8544-Nokia-5110-LCD-library SPI
USER_LIB_PATH := $(realpath .)
MONITOR_BAUDRATE = 115200

include /Users/cbhl/homebrew/opt/arduino-mk/Arduino.mk
#include /usr/share/arduino/Arduino.mk
