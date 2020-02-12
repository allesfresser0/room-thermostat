#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include "DHT.h"

//defining DHT11 variables
#define DHTTYPE DHT11
#define DHTPIN 2
//defining nRF24L01 pins
#define CEPIN 9
#define CSPIN 10
//defining lcd pins
#define RS 2
#define EN 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7
#define BGLED 
#define POTPIN A0
#define TOLERANCE 2
#define MAXTEMP 30
#define MINTEMP 5

const uint64_t code = 0xE8E9F0F0E1LL;
unsigned int destTemp;
unsigned int preTemp;

DHT dht(DHTPIN, DHTTYPE);
RF24 radio(CEPIN, CSPIN);
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);



void setup() {
  pinMode(BGLED, OUTPUT);
  
  Serial.begin(9600);
  lcd.begin(16, 2);
  radio.begin();
  radio.openWritingPipe(code);
  radio.stopListening();

}

void loop() {
  destTemp = map(analogRead(POTPIN, 0, 1023, MINTEMP, MAXTEMP);
  Serial.println(destTemp);
  if(destTemp != preTemp){
    preTemp = destTemp;
    digitalWrite(BGLED, HIGH);
    sendTemp();
  }

}

void printTemp(){
  
}

void sendTemp(){
  float currentTemp = readTemperature();
  if(currentTemp < (destTemp - TOLERANCE)){
    burnItUp();
  }
  else if(){
    stopTheFire();
  }
}

void burnItUp(){
  const char text[] = "burn";
  radio.write(&text, sizeof(text));
  delay(100);
}

void stopTheFire(){
  const char text[] = "stop";
  radio.write(&text, sizeof(text));
  delay(100);
}
