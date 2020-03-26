//Defining the libraries
//Links in the Readme section

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMono9pt7b.h>

//Connect the SCL pin of OLED to D1 of NodeMCU
//Connect the SDA pin of OLED to D2 of NodeMCU

#define OLED_RESET LED_BUILTIN  //4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
    const char* ssid = "XXXXX";  //Enter your SSID of your WiFi (keep it within double quote)
    const char* password = "*********";  //Enter your PASSWORD of your WiFi (keep it within double quote)
    WiFiClient client; 

    // Set your hosting Website (Here it is www.thingspeak.com)
    const char* host = "api.thingspeak.com"; 
    const int httpPortRead = 80;
    // "XXXXXXXXXXXXXXX" represents your 16 digit API Key generated from Thingspeak i.e ThingHTTP
    //ContryData of COVID19
    const char* url = "/apps/thinghttp/send_request?api_key=XXXXXXXXXXXXXXX"; //cases
    const char* url2 = "/apps/thinghttp/send_request?api_key=XXXXXXXXXXXXXXX"; // deaths
    const char* url3 = "/apps/thinghttp/send_request?api_key=XXXXXXXXXXXXXXX"; //recovered
    
    //Statewise data of COVID19
    const char* url4 = "/apps/thinghttp/send_request?api_key=XXXXXXXXXXXXXXX"; //cases
    const char* url5 = "/apps/thinghttp/send_request?api_key=XXXXXXXXXXXXXXX"; // deaths
    const char* url6 = "/apps/thinghttp/send_request?api_key=XXXXXXXXXXXXXXX"; //recovered
    
    HTTPClient http; 

void setup() {
  display.setFont(&FreeMono9pt7b);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  display.setTextSize(0);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("COVIDInfo");
  display.display();
  display.setCursor(0, 26);
  display.println("CoronaVirus");
  display.display();
  display.setCursor(0, 40);
  display.println("In India");
  display.display();
  delay(200);
  display.clearDisplay();
    Serial.begin(115200);
    WiFi.disconnect();
    delay(1000);                                                             
    Serial.println(); 
  display.setCursor(0, 10);
  display.println("COVIDInfo");
  display.display();                                                                                                                                                                                                                                                                                                                                                                                                                                             
  display.setCursor(0, 26);
  display.println("WifiCheck..");
  display.display();
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
    delay(500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
  
   display.display();
   display.clearDisplay();
   display.setCursor(0, 10);
   display.println("COVIDInfo");
   display.display();
   display.setCursor(0, 26);
   display.println("Connected");
   delay(100);
   display.display();
  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());   //You can get IP address assigned to ESP
}

void loop() 
{
 while (WiFi.status() != WL_CONNECTED)                                         
      { 
        WiFi.begin(ssid, password);                                              
        Serial.println("Reconnecting to WiFi..");       
        delay(20000);   
      }
   display.display();
   display.clearDisplay();
   display.setCursor(0, 10);
   display.println("COVID India");
   display.display();
   display.setCursor(0, 26);
   display.println("Geting Data");
   delay(60);
   display.display();
   display.clearDisplay();
   display.setTextColor(WHITE);
   display.setCursor(0, 10);
   display.println("COVID India");
   
    if( http.begin(host,httpPortRead,url))                                              
      {
        int httpCode = http.GET();                                                      
        if (httpCode > 0)                                                               
        {
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
            {
               String payload = http.getString();
               Serial.print("Confirmed Cases: ");
               Serial.println(payload);
              
            display.setCursor(0, 26);
            display.println("Cases:");
            display.setCursor(90, 26);
            display.println(payload);
            }
     if( http.begin(host,httpPortRead,url2))                                              
      {
        int httpCode = http.GET();                                                      
        if (httpCode > 0)                                                               
        {
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
            {
               String payload = http.getString();
               Serial.print("Deaths: ");
               Serial.println(payload);
               
            display.setCursor(0, 40);
            display.println("Deaths:");
            display.setCursor(90, 40);
            display.println(payload);
            }
    if( http.begin(host,httpPortRead,url3))                                               
      {
        int httpCode = http.GET();                                                      
        if (httpCode > 0)                                                               
        {
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
            {
               String payload = http.getString();
               Serial.print("Recovered: ");
               Serial.println(payload);
               
         display.setCursor(0, 54);
         display.println("Recvrd:");
         display.setCursor(90, 54);
         display.println(payload);
         display.display();
         
            }
        }
     }
 delay(3000);
   //COVID Cases in your state
   display.display();
   display.clearDisplay();
   display.setTextColor(WHITE);
   display.setCursor(0, 10);
   display.println("COVIDState");
   
     if( http.begin(host,httpPortRead,url5))                                               
      {
        int httpCode = http.GET();                                                      
        if (httpCode > 0)                                                               
        {
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
            {
               String payload = http.getString();
               Serial.print("Cases: ");
               Serial.println(payload);
               
         display.setCursor(0, 26);
         display.println("Cases:");
         display.setCursor(90, 26);
         display.println(payload);
           }
        }
     }
     if( http.begin(host,httpPortRead,url4))                                               
      {
        int httpCode = http.GET();                                                      
        if (httpCode > 0)                                                               
        {
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
            {
               String payload = http.getString();
               Serial.print("Deaths: ");
               Serial.println(payload);
               
         display.setCursor(0, 40);
         display.println("Deaths:");
         display.setCursor(90, 40);
         display.println(payload);
         display.display();
            }
        }
     }
     if( http.begin(host,httpPortRead,url6))                                               
      {
        int httpCode = http.GET();                                                      
        if (httpCode > 0)                                                               
        {
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
            {
               String payload = http.getString();
               Serial.print("Recvrd: ");
               Serial.println(payload);
               
         display.setCursor(0, 40);
         display.println("Recvrd:");
         display.setCursor(90, 40);
         display.println(payload);
         display.display();
            }
        }
     }
    }
   }
  else
  {
    Serial.println("Error in response");
  }
  http.end();  //Close connection
  delay(3000);  //GET Data at every 5 seconds
  Serial.println("NEW DATA");
}
}
}
