# src

## Connecting

1. Watch for logs with: `sudo dmesg -w | grep USB`
2. Connect Wemos via USB
3. Write down the ID for the USB device (i.e. *ttyUSB0*)
4. Show permissions for the device: `ls -lah /dev/ttyUSB0`
5. Write down the group of the device (i.e. *uucp*)
6. Add your user to the above group: `sudo usermod -a -G uucp $USER`
7. *logout* and *login* again to apply changes

## arduino-cli

1. [Install arduino-cli](https://arduino.github.io/arduino-cli/0.21/installation/)
2. Create configuration file: `arduino-cli config init`
3. Add esp8266 URL for board manager [in your config file](https://arduino.github.io/arduino-cli/0.21/getting-started/#adding-3rd-party-cores):

    ```
    https://arduino.esp8266.com/stable/package_esp8266com_index.json
    ```
3. Configure the [autocompletion for command-line](https://arduino.github.io/arduino-cli/0.21/command-line-completion/#generate-the-completion-file)
3. Install Wemos D1 Mini board:

    ```bash
    arduino-cli core update-index
    arduino-cli board list
    arduino-cli board listall esp8266:d1
    arduino-cli core  install esp8266:esp8266
    arduino-cli core  list
    ```

## 01-lcd

1. Install required library [LCDIC2](https://github.com/offcircuit/LCDIC2):

    ```bash
    arduino-cli lib install "LCDIC2"
    ```
2. Compile: `arduino-cli compile --fqbn esp8266:esp8266:d1 01-lcd/`
3. Upload: `arduino-cli upload --fqbn esp8266:esp8266:d1 --port /dev/ttyUSB0 01-lcd/`

## 02-lcd

1. Install required library [hd44780](https://github.com/duinoWitchery/hd44780):

    ```bash
    arduino-cli lib install "hd44780"
    ```
2. Compile: `arduino-cli compile --fqbn esp8266:esp8266:d1 02-lcd/`
3. Upload: `arduino-cli upload --fqbn esp8266:esp8266:d1 --port /dev/ttyUSB0 02-lcd/`
