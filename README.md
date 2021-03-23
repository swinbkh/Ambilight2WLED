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

### How to compile Standalone
1. Download and install Arduino IDE https://www.arduino.cc/en/software (available for Windopws, Linux, MacOS)
2. Open Arduino IDE, create new sketch by File -> New.
3. Paste the core from Ambilight_to_WLED_STANDALONE.ino
4. Open Library manager by Tools -> Library manager and check whether the following libraries installed or not: (i) Arduino (should be built-in), (ii) ArduinoJson, (iii) WiFi (should be built-in), (iv) WiFiMulti, (v) HTTPClient
If the libraries are not installed - install them.
5. Change within the sketch the (i) SSID name (ii) SSID password (iii) IP address of the TV and (iv) IP address of the WLED device (lines 11-14 in the code);
6. Check that everything is Ok with the code: press Sketch -> Verify/Compile
