#pragma once

#include "wled.h"

#include <HTTPClient.h>

class Usermod_Ambilight2WLED : public Usermod
{
private:
  unsigned long lastTime = 0;

  const char *AmbilightSource = "http://192.168.1.XXX:1925/6/ambilight/processed";

  int l_0_rgb[3] = {0};
  int l_1_rgb[3] = {0};
  int l_2_rgb[3] = {0};

  int r_0_rgb[3] = {0};
  int r_1_rgb[3] = {0};
  int r_2_rgb[3] = {0};

  int t_0_rgb[3] = {0};
  int t_1_rgb[3] = {0};
  int t_2_rgb[3] = {0};
  int t_3_rgb[3] = {0};
  int t_4_rgb[3] = {0};
  int t_5_rgb[3] = {0};
  int t_6_rgb[3] = {0};

public:
  void setup() {}

  void connected() {}

  void loop()
  {
    if (millis() - lastTime > 200)
    {
      if (WLED_CONNECTED)
      {
        HTTPClient httpAmbilight;
        httpAmbilight.begin(AmbilightSource);

        // start connection and send HTTP header
        int httpCode = httpAmbilight.GET();

        // httpCode will be negative on error
        if (httpCode > 0)
        {
          //if source reached without error:
          if (httpCode == HTTP_CODE_OK)
          {

            String payload = httpAmbilight.getString();

            DynamicJsonDocument doc(1024);
            deserializeJson(doc, payload);

            JsonObject layer1 = doc["layer1"];

            JsonObject layer1_l = layer1["left"];
            JsonObject layer1_l_0 = layer1_l["0"];
            JsonObject layer1_l_1 = layer1_l["1"];
            JsonObject layer1_l_2 = layer1_l["2"];

            JsonObject layer1_r = layer1["right"];
            JsonObject layer1_r_0 = layer1_r["0"];
            JsonObject layer1_r_1 = layer1_r["1"];
            JsonObject layer1_r_2 = layer1_r["2"];

            JsonObject layer1_t = layer1["top"];
            JsonObject layer1_t_0 = layer1_t["0"];
            JsonObject layer1_t_1 = layer1_t["1"];
            JsonObject layer1_t_2 = layer1_t["2"];
            JsonObject layer1_t_3 = layer1_t["3"];
            JsonObject layer1_t_4 = layer1_t["4"];
            JsonObject layer1_t_5 = layer1_t["5"];
            JsonObject layer1_t_6 = layer1_t["6"];

            l_0_rgb[0] = layer1_l_0["r"], l_0_rgb[1] = layer1_l_0["g"], l_0_rgb[2] = layer1_l_0["b"];
            l_1_rgb[0] = layer1_l_1["r"], l_1_rgb[1] = layer1_l_1["g"], l_1_rgb[2] = layer1_l_1["b"];
            l_2_rgb[0] = layer1_l_2["r"], l_2_rgb[1] = layer1_l_2["g"], l_2_rgb[2] = layer1_l_2["b"];

            r_0_rgb[0] = layer1_r_0["r"], r_0_rgb[1] = layer1_r_0["g"], r_0_rgb[2] = layer1_r_0["b"];
            r_1_rgb[0] = layer1_r_1["r"], r_1_rgb[1] = layer1_r_1["g"], r_1_rgb[2] = layer1_r_1["b"];
            r_2_rgb[0] = layer1_r_2["r"], r_2_rgb[1] = layer1_r_2["g"], r_2_rgb[2] = layer1_r_2["b"];

            t_0_rgb[0] = layer1_t_0["r"], t_0_rgb[1] = layer1_t_0["g"], t_0_rgb[2] = layer1_t_0["b"];
            t_1_rgb[0] = layer1_t_1["r"], t_1_rgb[1] = layer1_t_1["g"], t_1_rgb[2] = layer1_t_1["b"];
            t_2_rgb[0] = layer1_t_2["r"], t_2_rgb[1] = layer1_t_2["g"], t_2_rgb[2] = layer1_t_2["b"];
            t_3_rgb[0] = layer1_t_3["r"], t_3_rgb[1] = layer1_t_3["g"], t_3_rgb[2] = layer1_t_3["b"];
            t_4_rgb[0] = layer1_t_4["r"], t_4_rgb[1] = layer1_t_4["g"], t_4_rgb[2] = layer1_t_4["b"];
            t_5_rgb[0] = layer1_t_5["r"], t_5_rgb[1] = layer1_t_5["g"], t_5_rgb[2] = layer1_t_5["b"];
            t_6_rgb[0] = layer1_t_6["r"], t_6_rgb[1] = layer1_t_6["g"], t_6_rgb[2] = layer1_t_6["b"];

            //WLED Segment control goes here!
            //| | | | | | | | | | | | | | | 
            //V V V V V V V V V V V V V V V
          }
          httpAmbilight.end();
        }
      }
      //Serial.println("I'm alive!");
      lastTime = millis();
    }
  }
};
