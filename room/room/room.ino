#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include "DHT.h"

//defining DHT11 variables
#define DHT_TYPE DHT11
#define DHT_PIN 2
//defining nRF24L01 pins
#define CE_PIN 9
#define CS_PIN 10
//defining lcd pins
#define RS 2
#define EN 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7
#define LED_PIN A1
#define BUTTON_PIN A2
#define POT_PIN A0

#define LIGHT_TIME 3000
#define TEMP_TOLERANCE 2
#define POT_TOLERANCE 3
#define MAX_TEMP 30
#define MIN_TEMP 5

const uint64_t code = 0xE8E9F0F0E1LL;
unsigned int targetTemp = 10;
unsigned int prePot;
unsigned int newPot;
float currentTemp;

DHT dht(DHT_PIN, DHT_TYPE);
RF24 radio(CE_PIN, CS_PIN);
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);



void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  
  Serial.begin(9600);
  lcd.begin(16, 2);
  radio.begin();
  radio.openWritingPipe(code);
  radio.stopListening();

}

void loop() {
  newPot = analogRead(POT_PIN);
  if ((millis() % 2500) == 0)
    currentTemp = dht.readTemperature();
  if((newPot < (prePot - POT_TOLERANCE)) || (newPot > (prePot + POT_TOLERANCE))){
    prePot = potChanged();
  }
  else if(digitalRead(BUTTON_PIN) == HIGH){
    lightOn();
  }
  if(currentTemp < targetTemp)
    burnItUp();
  else if(currentTemp >= targetTemp)
    stopTheFire();
  
}

void printMenu(float currentTemp, unsigned int targetTemp){
  lcd.clear();
  lcd.print(currentTemp);
  lcd.print(" C hisedilen");
  lcd.setCursor(0, 1);
  lcd.print(targetTemp);
  lcd.print(" C istenen");
}

unsigned int potChanged(){
  unsigned long startTime = millis();
  float currentTemp = dht.readTemperature();
  unsigned int potValue = prePot;
  digitalWrite(LED_PIN, HIGH);
  while((digitalRead(BUTTON_PIN) == LOW) && ((millis() - startTime) < 8000)){
    potValue = analogRead(POT_PIN);
    targetTemp = map(potValue, 0, 1023, MIN_TEMP, MAX_TEMP);
    printMenu(currentTemp, targetTemp);
  }
  digitalWrite(LED_PIN, LOW);
  return potValue;
}

void burnItUp(){
  const char text[] = "burn";
  radio.write(&text, sizeof(text));
  Serial.println("Make it hot!");
  delay(100);
}

void stopTheFire(){
  const char text[] = "stop";
  radio.write(&text, sizeof(text));
  Serial.println("Stop it please.");
  delay(100);
}

void lightOn(){
  while(digitalRead(BUTTON_PIN) == HIGH){}
  float currentTemp = dht.readTemperature();
  digitalWrite(LED_PIN, HIGH);
  printMenu(currentTemp, targetTemp);
  delay(LIGHT_TIME);
  digitalWrite(LED_PIN, LOW);
}
