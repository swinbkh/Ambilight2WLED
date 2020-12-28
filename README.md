# Ambilight to WLED
This program uses the exposed Jointspace API for Philips TV's featuring Ambilight and replicates the colours on an LED strip using WLED.

## Form factors:
### Standalone
* Flashed on a standalone esp8266, handles communication between the TV and WLED.

### WLED Usermod
* Built into WLED - requires a custom compile but reduces latency due to network delays. 

___

Rather than syncing WLED to a Philips Hue bulb, this program can capture each of the sides of the TV, and process the colour values to WLED through it's API. 

To check which version of Jointspace your TV uses, go to the System Information page of your TV: http://ip-address:1925/1/system
If the Major API version is 1, it will be necessary to edit the code to use: http://ip-address:1925/1/ambilight/processed otherwise, use http://ip-address:1925/6/ambilight/processed

