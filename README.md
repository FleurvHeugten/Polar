<h1 align="left">ReadMe</h1>
<h3 align="left">Team 12 | Polar</h3>
We designed a product in the context of your own bedroom, one or two hours before going to bed. This is everything about the code that we used for the 3 different products products:

<h3 align="left">Libraries</h3>

- The code requires the FastLED library, version 3.1 or later. Make sure to download the latest version from the [FastLED GitHub repository](https://github.com/FastLED/FastLED).

- We also used multiple libraries for the accelerometer sensor: Wire.h, Adafruit_Sensor.h, Adafruit_ADXL345_U.h

<h3 align="left">inputs</h3>

- FLEX_PIN_1 (34), FLEX_PIN_2 (35), FLEX_PIN_3 (32), FLEX_PIN_4 (33), FLEX_PIN_5 (39) : for the 5 flex sensors

- LED_PIN (5) : where the RGB LED strip (WS2811) is connected

- Pins for accelerometer on ESP32 (pin SCL & SDA pin)

<h3 align="left">Functions</h3>

- setup(): initializes the code, sets up the sensor and LED pins, and configures the LED strip.

- loop(): the main loop of the code. Reads the sensor inputs and triggers different lighting effects based on the sensor values.

- idle(): a function that sets the LED strip to a low-level "idle" pattern when no other effects are being triggered.

<h3 align="left">Color combinations</h3>

- gayy() (with flex sensor 1 & 2)

- eeyore() (with flex sensor 1 & 3)

- attentionWhore() (with flex sensor 1 & 4)

- sunriseGradient() (with flex sensor 1 & 5)

- northernLights() (with flex sensor 2 & 3)

- discoFever() (with flex sensor 2 & 4)

- galacticGlow() (with flex sensor 2 & 5)

- candyland() (with flex sensor 3 & 4)

- neonPulse() (with flex sensor 3 & 5)

- fireAndIce() (with flex sensor 4 & 5)

- cyclone() (with flex sensor 1)

- cylon() (with flex sensor 2)

- comet() (with flex sensor 3)
 
- oceanWaves() (with flex sensor 4)
 
- lavaShock() (with flex sensor 5)

<h3 align="left">Languages and Tools:</h3>
<p align="left"> <a href="https://www.w3schools.com/cpp/" target="_blank" rel="noreferrer"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/cplusplus/cplusplus-original.svg" alt="cplusplus" width="40" height="40"/> </a> <a href="https://www.w3.org/html/" target="_blank" rel="noreferrer"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/html5/html5-original-wordmark.svg" alt="html5" width="40" height="40"/> </a> </p>
