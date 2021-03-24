# Ambilight to WLED
This program uses the exposed Jointspace API for Philips TV's featuring Ambilight and replicates the colours on an LED strip using WLED.

## Form factors:
### Standalone
* Flashed on a standalone esp8266 / esp32, handles communication between the TV and WLED (see detailed instruction how to compile and flash below).

### WLED Usermod
* Built into WLED - requires a custom compile but reduces latency due to network delays. 

___

Rather than syncing WLED to a Philips Hue bulb, this program can capture each of the sides of the TV, and process the colour values to WLED through it's API. 

To check which version of Jointspace your TV uses, go to the System Information page of your TV either by: 
http://ip-address:1925/1/system or 
http://ip-address:1925/6/system
If the Major API version is 1, it will be necessary to edit the code to use: http://ip-address:1925/1/ambilight/processed otherwise, use http://ip-address:1925/6/ambilight/processed

___

## How to compile and flash Standalone (from scratch)
 

 If using ESP8266:
- Stable release link: `https://arduino.esp8266.com/stable/package_esp8266com_index.json`

 If using ESP32: 
- Stable release link: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`

1. Download and install Arduino IDE https://www.arduino.cc/en/software (available for Windows, Linux, MacOS)
2. Start Arduino and open File -> Preferences window.
3. Enter one of the release links above into *Additional Board Manager URLs* field. You can add multiple URLs, separating them with commas.
4. Open Boards Manager from Tools > Board menu and install *esp32* or *esp8266* platform (and don't forget to select your ESP32/ESP8266 board from Tools > Board menu after installation).
  
5. Create new sketch by File -> New.
6. Paste the core from Ambilight_to_WLED_STANDALONE.ino
7. Open Library manager by Tools -> Library manager and check whether the following libraries installed or not: (i) ArduinoJson. If the library(ies) are not installed - install them.
8. Change within the sketch the (i) SSID name (ii) SSID password (iii) IP address of the TV and (iv) IP address of the WLED device (lines 21-24 in the code);
9. Check that everything is Ok with the code: press Sketch -> Verify/Compile
10. Connect your ESP8266/ESP32 (generic, NodeMCU, Wemos etc) in flash mode to your PC where Arduino IDE installed4
11. Check the COM port defined by Arduino IDE at Tools -> Port. Should be your actual COM port for ESP board.
12. Press Upload button.
13. Wait message something like this "Wrote 292832 bytes (214542 compressed) at 0x00000000 in 19.1 seconds (effective 122.8 kbit/s)... Hash of data verified. Leaving... Hard resetting via RTS pin..."
14. Enjoy
