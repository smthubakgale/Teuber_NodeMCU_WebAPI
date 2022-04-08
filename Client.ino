/**********
   Thubakgale Mabalane Samuel 
   
**********/
//::::::::: Libraries
//---- Wifi 
    #include <Arduino.h> 
    #include <ESP8266WiFi.h>
    #include <ESP8266WiFiMulti.h> 
    #include <ESP8266HTTPClient.h>
//---- Json-Conversion 
    #include <Arduino_JSON.h>
//:::::::::: Variables     
//---- Wifi 
    ESP8266WiFiMulti WiFiMulti;
//:::::::::: Set up
void setup() 
{ 
  Serial.begin(115200);
  // Wifi Login Credentials
     WiFi.mode(WIFI_STA); 
     const char* ssid = "MAF006B";
     const char* pass = "MAF006BPrivateNetwork"; 
     WiFiMulti.addAP(ssid, pass);
  // ----------------------
}
//:::::::::: Loop 
void loop() 
{
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) 
  { 
     // Requests 
        //-- Read 
          String r = "https://bsite.net/teuberwebapi/Home/Get0?json={'control':'ModelController','func':'get1','param':'{\"Idx\":\"1\",\"FName\":\"Mabalane\",\"LName\":\"Thubakgale\",\"Client\":\"Sam\"}'}";

          Serial.println(r);
        //-- 
     // https client 
         CRUD_Read(r);
     // 
  }
 
    delay(10000);
}

void CRUD_Read(String url)
{ 
       std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure); 
       client->setInsecure();  
       HTTPClient https; 
       
       if (https.begin(*client, url)) 
       {     
           int httpCode = https.GET();  
           if (httpCode > 0) 
           { 
              if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
              {
                 String payload = https.getString();
                 Serial.println(payload);
              }
              else
              { 
                 Serial.println(httpCode );
              }
            } 
            else 
            {
               Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
            }

            https.end();
        } 
        else 
        {
           Serial.printf("[HTTPS] Unable to connect\n");
        }
}
