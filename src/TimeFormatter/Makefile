# See https://github.com/bxparks/EpoxyDuino for documentation about this
# Makefile to compile and run Arduino programs natively on Linux or MacOS.

# Required for Time libraries - otherwise they try to include WProgram.h
EXTRA_CPPFLAGS := -D ARDUINO=123

APP_NAME := TimeFormatterTest
ARDUINO_LIBS := AUnit
ARDUINO_LIB_DIRS := ${ARDUINO_CLI_DIR}/libraries
include ../../libraries/EpoxyDuino/EpoxyDuino.mk
