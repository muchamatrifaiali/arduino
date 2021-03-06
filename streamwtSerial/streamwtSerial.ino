/**
   StreamHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

//#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

void setup() {

  //USE_SERIAL.begin(115200);
  // USE_SERIAL.setDebugOutput(true);

  //USE_SERIAL.println();
  //USE_SERIAL.println();
  //USE_SERIAL.println();
  pinMode(2,1);

  for (uint8_t t = 4; t > 0; t--) {
    //USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    //USE_SERIAL.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("cobasaja", "12345678");

}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;

   // USE_SERIAL.print("[HTTP] begin...\n");

    // configure server and url
    http.begin("http://iot.muraproject.com/php/frommikro.php?mId=poiuy&mC=q");
    //http.begin("192.168.1.12", 80, "/test.html");

    //USE_SERIAL.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      //USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {

        // get lenght of document (is -1 when Server sends no Content-Length header)
        int len = http.getSize();

        // create buffer for read
        uint8_t buff[128] = { 0 };

        // get tcp stream
        WiFiClient * stream = http.getStreamPtr();

        // read all data from server
        while (http.connected() && (len > 0 || len == -1)) {
          // get available data size
          size_t size = stream->available();
          String status_;
          if (size) {
            // read up to 128 byte
            int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));

            // write it to Serial
            //USE_SERIAL.write(buff, c);
            for (int i = 0; i < 1; i++) {
                
                //Serial.print((char)buff[i]);
                status_ = (char)buff[i];
                
               
            }
           
            //status_ = String(status_ + buff);
            //Serial.println(status_);
           // status_ +=c;
            
            //digitalWrite(2,c);
          } 
          delay(1);
          //Serial.print(status_);
          int cond_ = status_.toInt();
          //Serial.println("");
          digitalWrite(2,cond_);
         // USE_SERIAL.print("msuk : ");
          //USE_SERIAL.println(status_);
          status_ = "";
        }

       // USE_SERIAL.print("[HTTP] connection closed or file end.\n");

      }
    } else {
      //USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  delay(5000);
}

