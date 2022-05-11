# crazyclock

[![clang-format Check](https://github.com/The-Coobaz/crazyclock/actions/workflows/clang-format-check.yml/badge.svg)](https://github.com/The-Coobaz/crazyclock/actions/workflows/clang-format-check.yml)

The main idea of this project is arduino clock with flexible second time.
This would allow to speed up or slow down the time.

## Hardware

You are going to need:
- ESP8266 ([wemos](https://www.aliexpress.com/wholesale?SearchText=wemos+d1+mini) or [nodemcu](https://www.aliexpress.com/wholesale?SearchText=nodemcu) version) 
- [1602 LCD screen with i2c  converter](https://www.aliexpress.com/wholesale?SearchText=lcd+1602+i2c)
- rotary encoder, i.e. [KY-040](https://www.aliexpress.com/wholesale?SearchText=ky-040+rotary+encoder)

### Schema

[![Fritzing Wemos D1 Mini schema](./misc/img/wemos-d1-mini-s.png)](./misc/img/wemos-d1-mini.png)

## Development

### VS Code

#### Setup

See also instructions on the web:

- [How to Use Visual Studio Code for Arduino](https://maker.pro/arduino/tutorial/how-to-use-visual-studio-code-for-arduino)
- [Efficient Arduino Programming with Arduino CLI and Visual Studio Code](https://learn.sparkfun.com/tutorials/efficient-arduino-programming-with-arduino-cli-and-visual-studio-code/all)

#### Formatting

For VS Code with [C/C++ Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
you need to update the settings to [Format Curly Braces on Same Line](https://stackoverflow.com/a/69560647/1823545):

1. Press `[ctlr] + [,]`
2. Search for `C_Cpp.clang_format_fallback`
3. Just change the value in the textfield from `Visual Studio` to `LLVM`

### Working with arduino-cli

#### Arduino CLI setup

1. [Install arduino-cli](https://arduino.github.io/arduino-cli/0.22/installation/)
2. Create configuration file: `arduino-cli config init`
3. Add esp8266 URL for board manager:

    ```
    arduino-cli config add board_manager.additional_urls https://arduino.esp8266.com/stable/package_esp8266com_index.json
    ```
3. Configure the [autocompletion for command-line](https://arduino.github.io/arduino-cli/0.22/command-line-completion/#generate-the-completion-file) (optional step)
3. Install Wemos D1 Mini board:

    ```bash
    arduino-cli core update-index
    arduino-cli core install esp8266:esp8266
    arduino-cli core list
    arduino-cli board listall esp8266:d1
    ```

#### Connecting esp-8266 (or Wemos)

1. Watch for logs with: `sudo dmesg -w | grep USB`
2. Connect your device via USB
3. Write down the ID for the USB device (i.e. *ttyUSB0*)
4. Show permissions for the device: `ls -lah /dev/ttyUSB0`
5. Write down the group of the device (i.e. *uucp*)
6. Add your user to the above group: `sudo usermod -a -G uucp $USER`
7. *logout* and *login* again to apply changes

#### Compile and Upload

In `src` directory:

1. Install required libraries (i.e. [hd44780](https://github.com/duinoWitchery/hd44780)):

    ```bash
    arduino-cli lib install "hd44780"
    ```
2. Compile: `arduino-cli compile --fqbn esp8266:esp8266:d1 crazyclock/`
3. Upload: `arduino-cli upload --fqbn esp8266:esp8266:d1 --port /dev/ttyUSB0 crazyclock/`

## Fritzing Parts

1. [KY-040 Rotary Encoder](https://forum.fritzing.org/t/ky-040-rotary-encoder-breakout-board-part/11073)
2. [Wemos D1 Mini](https://github.com/mcauser/Fritzing-Part-WeMos-D1-Mini/tree/master/dist)
