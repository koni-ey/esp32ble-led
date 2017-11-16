/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleWrite.cpp
    Ported to Arduino ESP32 by Evandro Copercini
*/
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <string.h>
// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

String valueino;
String valueino0;
String valueino1;
String valueino2;
int brightness=0;


#define PIN            2
#define NUMPIXELS      20
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();

      if (value.length() > 0) {
        
          valueino0=value[0];
          valueino1=value[1];
          valueino2=value[2];
          valueino=valueino0+valueino1+valueino2;
          brightness=valueino.toInt(); 
          
        Serial.println("*********");
        Serial.print("New value (std::string: ");
        for (int i = 0; i < value.length(); i++) {
          Serial.print(value[i]);
          
        }
        Serial.println();
        Serial.println("*********");
        Serial.print("Arduiono String: ");
        Serial.println(valueino);
        Serial.print("Integer: ");
        Serial.println(brightness);
      }
    }
};

void setup() {
  Serial.begin(115200);

  Serial.println("1- Download and install an BLE scanner app in your phone");
  Serial.println("2- Scan for BLE devices in the app");
  Serial.println("3- Connect to SDartBoard");
  Serial.println("4- Go to CUSTOM CHARACTERISTIC in CUSTOM SERVICE and write something");
  Serial.println("5- See the magic =)");

  BLEDevice::init("SDartBoard");
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic->setValue("Set Brightness of LEDS");
  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
  Serial.println("Ready to connect....");
  
  pixels.begin();
}

void loop() {

 if (brightness==123){
  for (int i=0; i<=255; i+=20)  {
    pixels.setPixelColor(0, pixels.Color(0,0,i)); 
    pixels.setPixelColor(1, pixels.Color(0,0,i));
    pixels.setPixelColor(2, pixels.Color(0,0,i));
    pixels.setPixelColor(3, pixels.Color(0,0,i));
    pixels.setPixelColor(4, pixels.Color(0,0,i));
    pixels.setPixelColor(5, pixels.Color(0,0,i));
    pixels.setPixelColor(6, pixels.Color(0,0,i));
    pixels.setPixelColor(7, pixels.Color(0,0,i));
    pixels.setPixelColor(8, pixels.Color(0,0,i));
    pixels.setPixelColor(9, pixels.Color(0,0,i));
    pixels.setPixelColor(10, pixels.Color(0,0,i)); 
    pixels.setPixelColor(11, pixels.Color(0,0,i));
    pixels.setPixelColor(12, pixels.Color(0,0,i));
    pixels.setPixelColor(13, pixels.Color(0,0,i));
    pixels.setPixelColor(14, pixels.Color(0,0,i));
    pixels.setPixelColor(15, pixels.Color(0,0,i));
    pixels.setPixelColor(16, pixels.Color(0,0,i)); 
    pixels.setPixelColor(17, pixels.Color(0,0,i));
    pixels.setPixelColor(18, pixels.Color(0,0,i));
    pixels.setPixelColor(19, pixels.Color(0,0,i));
    pixels.show();
    delay(50);
}
for (int i=255; i>=0; i-=20)   {
    pixels.setPixelColor(0, pixels.Color(0,0,i)); 
    pixels.setPixelColor(1, pixels.Color(0,0,i));
    pixels.setPixelColor(2, pixels.Color(0,0,i));
    pixels.setPixelColor(3, pixels.Color(0,0,i));
    pixels.setPixelColor(4, pixels.Color(0,0,i));
    pixels.setPixelColor(5, pixels.Color(0,0,i));
    pixels.setPixelColor(6, pixels.Color(0,0,i));
    pixels.setPixelColor(7, pixels.Color(0,0,i));
    pixels.setPixelColor(8, pixels.Color(0,0,i));
    pixels.setPixelColor(9, pixels.Color(0,0,i));
    pixels.setPixelColor(10, pixels.Color(0,0,i)); 
    pixels.setPixelColor(11, pixels.Color(0,0,i));
    pixels.setPixelColor(12, pixels.Color(0,0,i));
    pixels.setPixelColor(13, pixels.Color(0,0,i));
    pixels.setPixelColor(14, pixels.Color(0,0,i));
    pixels.setPixelColor(15, pixels.Color(0,0,i));
    pixels.setPixelColor(16, pixels.Color(0,0,i)); 
    pixels.setPixelColor(17, pixels.Color(0,0,i));
    pixels.setPixelColor(18, pixels.Color(0,0,i));
    pixels.setPixelColor(19, pixels.Color(0,0,i));
    pixels.show();
    delay(50);
  }
 }
 else {
 for (int i=0; i<=19; i++) {
 
  pixels.setPixelColor(i, pixels.Color(brightness,brightness,brightness));
  
 }
 pixels.show();
 delay(500);
 
}
}
