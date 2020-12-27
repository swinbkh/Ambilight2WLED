#include <Arduino.h>
#include <ArduinoJson.h>

#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#define USE_SERIAL Serial

WiFiMulti wifiMulti;
const char* ssid = "SSID";
const char* password = "PASSWORD";
const char* AmbilightSource = "http://192.168.1.XXX:1925/6/ambilight/processed";
const char* WLEDSource = "http://192.168.1.XXX/json";

int left_rgb[3]  ={0, 0, 0}; //the center colour on the left side of the TV
int top_rgb[3]   ={0, 0, 0}; //the center colour on the top side of the TV
int right_rgb[3] ={0, 0, 0};//the center colour on the right side of the TV

void setup() {

  USE_SERIAL.begin(115200);

  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }

  wifiMulti.addAP(ssid, password);

}

void loop() {
  // wait for WiFi connection
  if ((wifiMulti.run() == WL_CONNECTED)) {
    HTTPClient httpAmbilight;
    //USE_SERIAL.print("[HTTP] begin...\n");
    httpAmbilight.begin(AmbilightSource); //HTTP

    //USE_SERIAL.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = httpAmbilight.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      //if source reached without error:
      if (httpCode == HTTP_CODE_OK) {

        String payload = httpAmbilight.getString();
        //USE_SERIAL.println(payload);


        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);
        
        //see http://jointspace.sourceforge.net/projectdata/documentation/jasonApi/1/doc/API-Method-ambilight-processed-GET.html
        //for an example of the Ambilight structure, if needed to adapt to a larger TV
        
        JsonObject layer1 = doc["layer1"];

        JsonObject layer1_left = layer1["left"];
        
        JsonObject layer1_left_1 = layer1_left["1"];
        left_rgb[0] = layer1_left_1["r"]; //RED value of the left-center LED
        left_rgb[1] = layer1_left_1["g"]; //GREEN value of the left-center LED
        left_rgb[2] = layer1_left_1["b"]; //BLUE value of the left-center LED

        JsonObject layer1_top = layer1["top"];
        
        JsonObject layer1_top_3 = layer1_top["3"];
        top_rgb[0] = layer1_top_3["r"]; //RED value of the top-center LED
        top_rgb[1] = layer1_top_3["g"]; //GREEN value of the top-center LED
        top_rgb[2] = layer1_top_3["b"]; //BLUE value of the top-center LED

        JsonObject layer1_right = layer1["right"];
        
        JsonObject layer1_right_1 = layer1_right["1"];
        right_rgb[0] = layer1_right_1["r"]; //RED value of the right-center LED
        right_rgb[1] = layer1_right_1["g"]; //GREEN value of the right-center LED
        right_rgb[2] = layer1_right_1["b"]; //BLUE value of the right-center LED

        HTTPClient httpWLED;
        httpWLED.begin(WLEDSource);
        httpWLED.addHeader("Content-Type", "application/json");
        int httpResponseCode = httpWLED.POST("{ \"on\": true, \"bri\": 25, \"transition\": 7, \"mainseg\": 0, \"seg\": [{ \"id\": 0, \"start\": 0, \"stop\": 9, \"grp\": 1, \"spc\": 0, \"on\": true, \"bri\": 255, \"col\": [ [" + String(left_rgb[0]) + ", " + String(left_rgb[1]) + ", " + String(left_rgb[2]) + "], [0, 0, 0], [0, 0, 0] ], \"fx\": 0, \"sx\": 64, \"ix\": 50, \"pal\": 0, \"sel\": false, \"rev\": false, \"mi\": false }, { \"id\": 1, \"start\": 9, \"stop\": 30, \"grp\": 1, \"spc\": 0, \"on\": true, \"bri\": 255, \"col\": [ [" + String(top_rgb[0]) + ", " + String(top_rgb[1]) + ", " + String(top_rgb[2]) + "], [0, 0, 0], [0, 0, 0] ], \"fx\": 0, \"sx\": 128, \"ix\": 128, \"pal\": 0, \"sel\": false, \"rev\": false, \"mi\": false }, { \"id\": 2, \"start\": 30, \"stop\": 39, \"grp\": 1, \"spc\": 0, \"on\": true, \"bri\": 255, \"col\": [ [" + String(right_rgb[0]) + ", " + String(right_rgb[1]) + ", " + String(right_rgb[2]) + "], [0, 0, 0], [0, 0, 0] ], \"fx\": 0, \"sx\": 128, \"ix\": 128, \"pal\": 0, \"sel\": false, \"rev\": false, \"mi\": false } ] }");
        httpWLED.end();
      }
    }
    else {
      USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", httpAmbilight.errorToString(httpCode).c_str());
    }
    httpAmbilight.end();
  }

  delay(200);
}
