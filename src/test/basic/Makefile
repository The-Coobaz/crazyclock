# See https://github.com/bxparks/EpoxyDuino for documentation about this
# Makefile to compile and run Arduino programs natively on Linux or MacOS.

APP_NAME := basic
ARDUINO_LIBS := AUnit
ARDUINO_LIB_DIRS := \
	$(arduino_ide_dir)/portable/packages/arduino/hardware/avr/1.8.2/libraries \
	$(arduino_ide_dir)/libraries \
	$(arduino_ide_dir)/hardware/arduino/avr/libraries
include ../../../libraries/EpoxyDuino/EpoxyDuino.mk
