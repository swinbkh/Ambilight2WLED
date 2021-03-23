# Ambilight to WLED
This program uses the exposed Jointspace API for Philips TV's featuring Ambilight and replicates the colours on an LED strip using WLED.

## Form factors:
### Standalone
* Flashed on a standalone esp8266, handles communication between the TV and WLED (see detailed instruction how to compile and flash below).

### WLED Usermod
* Built into WLED - requires a custom compile but reduces latency due to network delays. 

___

Rather than syncing WLED to a Philips Hue bulb, this program can capture each of the sides of the TV, and process the colour values to WLED through it's API. 

To check which version of Jointspace your TV uses, go to the System Information page of your TV either by: http://ip-address:1925/1/system or http://ip-address:1925/6/system
If the Major API version is 1, it will be necessary to edit the code to use: http://ip-address:1925/1/ambilight/processed otherwise, use http://ip-address:1925/6/ambilight/processed

### How to compile and flash Standalone (from scratch)
1. Download and install Arduino IDE https://www.arduino.cc/en/software (available for Windopws, Linux, MacOS)
2. Open Arduino IDE. 
3. Got to File -> Preferences -> add "http://arduino.esp8266.com/stable/package_esp8266com_index.json" to Additional Board Manager URL's field.
4. Go to Tools -> Board Manager -> find esp8266 and click Install.
5. Create new sketch by File -> New.
6. Paste the core from Ambilight_to_WLED_STANDALONE.ino
7. Open Library manager by Tools -> Library manager and check whether the following libraries installed or not: (i) ArduinoJson. If the library(ies) are not installed - install them.
5. Change within the sketch the (i) SSID name (ii) SSID password (iii) IP address of the TV and (iv) IP address of the WLED device (lines 11-14 in the code);
6. Check that everything is Ok with the code: press Sketch -> Verify/Compile
7. Connect your ESP8266 (generic, NodeMCU, Wemos etc) in flash mode to your PC where Arduino IDE installed4
8. Check the COM port defined by Arduino IDE at Tools -> Port. Should be your actual COM port for ESP board.
9. Press Upload button.
10. Wait message something like this "Wrote 292832 bytes (214542 compressed) at 0x00000000 in 19.1 seconds (effective 122.8 kbit/s)... Hash of data verified. Leaving... Hard resetting via RTS pin..."
11. Enjoy
