//including nRF24L01 libraries
#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <SPI.h>

//defining nRF24L01 pins
#define CE_PIN 9
#define CS_PIN 10
//definin relay pin
#define RELAY_PIN 2

const uint64_t code = 0xE8E9F0F0E1LL; //rf channel key
unsigned int state = 1; //combi boiler state

RF24 radio(CE_PIN, CS_PIN); //creating radio object

void setup() {
  pinMode(RELAY_PIN, OUTPUT); //setting relay pin as output

  Serial.begin(9600); //starting serial communication ...
  radio.begin(); //...and rf communication
  radio.openReadingPipe(1, code); //setting rf module as receiver
  radio.startListening(); //starting to listen
}

void loop() {
  if(radio.available()){ //if rf communication available...
    Serial.println("Radio available");
    bool done = false;
    while(!done)
      done = radio.read(&state, sizeof(state)); //read the message and write to "state"
    Serial.println(state);
    if(state == 1){ //if the message is "1"...
      digitalWrite(RELAY_PIN, HIGH); //... stop
      Serial.println("The combi boiler on");
    }
    else if(state == 2){ //if the message is "2"...
      digitalWrite(RELAY_PIN, LOW); //...burn it up :)
      Serial.println("The combi boiler off");
    }
  }
}
