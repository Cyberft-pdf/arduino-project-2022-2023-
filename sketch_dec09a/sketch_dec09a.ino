#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space


#define OLED_RESET 4 // not used / nicht genutzt bei diesem Display
Adafruit_SSD1306 display(OLED_RESET);

 char inChar;
 String string;



// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "222cc4afd9a8475fbc7ddeb5210f0e0c"; //Enter the Auth code which was send by Blink asi senzor kotel




// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";  //Enter your WIFI Name
char pass[] = "";  //Enter your WIFI Password


SimpleTimer timer;


void setup()   { 

  pinMode(13, OUTPUT);
  
 // initialize with the I2C addr 0x3C / mit I2C-Adresse 0x3c initialisieren
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
                 
  Serial.begin(115200);
  string.reserve(200);

  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(0.5);
  display.setTextColor(INVERSE); 

  Serial.begin(9600);              //  setup serial
  Blynk.begin(auth, ssid, pass, IPAddress(192, 168, 197, 70), 8080);
}

void loop()
{ 
  
  if (Serial.available())  {
    
                display.clearDisplay();
                inChar = Serial.read();
                string+=inChar;               
                display.setCursor(0,0); 
                display.print(string);               
                display.display();   

           

          
              if( inChar == '\r'){
                    Serial.println("End");                
                    delay(4000);
                    string="";
                  
              }  
             
        
    }  

   
  display.display(); 
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer

 

  Serial.println(analogRead(A0));
  delay(1000); // Print value every 1 sec.
}
