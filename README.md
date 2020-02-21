# room-thermostat
* Arduino based room thermostat for combi boiler.
* You can set combi temperature from room.
* Saves your money!

## Prerequisites
### Software
**DHT sensor library by Adafruit**
```
Arduino IDE > Sketch > Include Library > Manage Lbraries > Search "DHT" > download "DHT sensor library by Adafruit"
```
**RF24 library by maniacbug**
* [RF24](https://github.com/maniacbug/RF24)
```
Clone or Download > Download ZIP > Arduino IDE > Sketch > Include Library > Add .ZIP Library
```
### Hardware
* 2 x nRF24L01
* 2 x Arduino(Nano, Uno, Mega etc.)
* 2x16 LCD
* Push button
* DHT11 or DHT22
* Potentiometer
* Relay

## Circuits
***Room-side circuit***

[![ROOM-SIDE CIRCUIT](https://github.com/mucahitkurtlar/room-thermostat/blob/master/room_circuit.jpg)]()

***Boiler-side circuit***

[![ROOM-SIDE CIRCUIT](https://github.com/mucahitkurtlar/room-thermostat/blob/master/boiler_circuit.jpg)]()
