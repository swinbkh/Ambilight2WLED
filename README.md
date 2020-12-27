# Ambilight to WLED
ESP8266 based conversion from Philips Ambilight to WLED

This program uses the exposed Jointspace API for Philips TV's featuring Ambilight. 

Rather than syncing WLED to a Philips Hue bulb, this program can capture each of the sides of the TV, and send the colour values to WLED through it's API. 

To check which version of Jointspace your TV uses, go to the System Information page of your TV: http://ip-address:1925/1/system
If the Major API version is 1, it will be necessary to edit the code to use: http://ip-address:1925/1/ambilight/processed otherwise, use http://ip-address:1925/6/ambilight/processed

