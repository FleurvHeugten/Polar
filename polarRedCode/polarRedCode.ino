// multiple example codes are used to get to this code. summed up below:
// example code oocsi_receiver and oocsi_sender of the oocsi library
// example code at https://www.instructables.com/How-to-use-a-Flex-Sensor-Arduino-Tutorial/
// example code at https://circuitdigest.com/microcontroller-projects/interfacing-ws8211-rgb-led-strip-with-arduino
#include "OOCSI.h"
//name of Wifi network
const char* ssid = "iotroam";
// Password of the Wifi network.
const char* password = "Polar2024";

// name for connecting with OOCSI (unique handle)
const char* OOCSIName = "sleep_dreamcatcher_red";
// the adress of our OOCSI server 
const char* hostserver = "oocsi.id.tue.nl";
OOCSI oocsi = OOCSI();
// the setup for the accelerometer
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

//the setup for the led and sensors
#include <FastLED.h>

#define LED_PIN     5   // The data pin of the LED strip 
#define NUM_LEDS    50  // The number of LEDs in our strip
#define FLEX_PIN_1  34  // Pin for flex sensor 1
#define FLEX_PIN_2  35  // Pin for flex sensor 2
#define FLEX_PIN_3  32  // Pin for flex sensor 3
#define FLEX_PIN_4  33  // Pin for flex sensor 4
#define FLEX_PIN_5  39  // Pin for flex sensor 5

#define COLOR_1     CRGB(255, 0, 0)   // Red color
#define COLOR_2     CRGB(0, 255, 0)   // Green color
#define COLOR_3     CRGB(0, 0, 255)   // Blue color
#define COLOR_4     CRGB(120, 120, 0) // Yellow color
#define COLOR_5     CRGB(255, 255, 0) // Cyan color

unsigned long previousIdleMillis = 0; // Variable to store the previous time when idle color was updated
int idleColorIndex = 0; // Variable to track the current idle color

CRGB leds[NUM_LEDS];

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
   //adding the ledstrip information
  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    // connecting to OOCSI
  oocsi.connect(OOCSIName, hostserver, ssid, password, processOOCSI);
  oocsi.subscribe("dreamcatcher");// subcribing to the channel of dreamcatcher
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }
  accel.setRange(ADXL345_RANGE_16_G);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop() {
    /* Get a new sensor event */ 
  sensors_event_t event; 
  accel.getEvent(&event);
  int yvalue= event.acceleration.y;
  /* Display the results (acceleration is measured in m/s^2) */
//  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
//  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
//  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
//  delay(500);
//  if (event.acceleration.x > 8.0) {
       // Perform your action here
//       Serial.println("X-axis acceleration is higher than 8.0 m/s^2!");
       // Add your action here, such as turning on an LED, triggering an alarm, etc.
//  }
 // reading the values of all flex pins
  int flexValue1 = analogRead(FLEX_PIN_1);
  int flexValue2 = analogRead(FLEX_PIN_2);
  int flexValue3 = analogRead(FLEX_PIN_3);
  int flexValue4 = analogRead(FLEX_PIN_4);
  int flexValue5 = analogRead(FLEX_PIN_5);
  //canging brightness for different flexvalue
  int BRIGHTNESS1 = map(flexValue1, 3000, 0, 0, 255);
  int BRIGHTNESS2 = map(flexValue2, 3000, 0, 0, 255);
  int BRIGHTNESS3 = map(flexValue3, 3000, 0, 0, 255);
  int BRIGHTNESS4 = map(flexValue4, 3000, 0, 0, 255);
  int BRIGHTNESS5 = map(flexValue5, 3000, 0, 0, 255); 
    // the message that is send the receiver
  oocsi.newMessage("dreamcatcher");

  oocsi.addString("greating", "hello world");
  oocsi.addInt("flexvalue1", flexValue1);
  oocsi.addInt("flexvalue2", flexValue2);
  oocsi.addInt("flexvalue3", flexValue3);
  oocsi.addInt("flexvalue4", flexValue4);
  oocsi.addInt("flexvalue5", flexValue5);
  oocsi.addInt("yvalue", yvalue);
  oocsi.sendMessage();// sending the message
  oocsi.check();// making sure the esp can also receive messages
  delay(500);

//next part is for all the different color combination options (combination functions can be found at bottom of code)---------------------------------------------------------------------

    // Check for combinations of two flex sensors being squeezed together
    if (flexValue1 < 3000 && flexValue2 < 3000) {
        // Call the gayy function if flex sensors 1 and 2 are squeezed together
        gayy();
    } else if (flexValue1 < 3000 && flexValue3 < 3000) {
        // Call the eeyore function if flex sensors 1 and 3 are squeezed together
        eeyore();
    } else if (flexValue1 < 3000 && flexValue4 < 3000) {
        // Call the attentionWhore function if flex sensors 1 and 4 are squeezed together
        attentionWhore();
    } else if (flexValue1 < 3000 && flexValue5 < 3000) {
        // Call the sunriseGradient function if flex sensors 1 and 5 are squeezed together
        sunriseGradient();
    } else if (flexValue2 < 3000 && flexValue3 < 3000) {
        // Call the northernLights function if flex sensors 2 and 3 are squeezed together
        northernLights();
    } else if (flexValue2 < 3000 && flexValue4 < 3000) {
        // Call the discoFever function if flex sensors 2 and 4 are squeezed together
        discoFever();
    } else if (flexValue2 < 3000 && flexValue5 < 3000) {
        // Call the galacticGlow function if flex sensors 2 and 5 are squeezed together
        galacticGlow();
    } else if (flexValue3 < 3000 && flexValue4 < 3000) {
        // Call the candyland function if flex sensors 3 and 4 are squeezed together
        candyland();
    } else if (flexValue3 < 3000 && flexValue5 < 3000) {
        // Call the neonPulse function if flex sensors 3 and 5 are squeezed together
        neonPulse();
    } else if (flexValue4 < 3000 && flexValue5 < 3000) {
        // Call the fireAndIce function if flex sensors 4 and 5 are squeezed together
        fireAndIce();
    } else {
        // Check for individual sensor squeezes
        if (flexValue1 < 3000) {
            // Call the cyclone function if flex sensor 1 is squeezed
            cyclone();
        } else if (flexValue2 < 3000) {
            // Call the cylon function if flex sensor 2 is squeezed
            cylon();
        } else if (flexValue3 < 3000) {
            // Call the comet function if flex sensor 3 is squeezed
            comet();
        } else if (flexValue4 < 3000) {
            // Call the oceanWaves function if flex sensor 4 is squeezed
            oceanWaves();
        } else if (flexValue5 < 3000) {
            // Call the lavaShock function if flex sensor 5 is squeezed
            lavaShock();
        } else {
            // If no sensor is being squeezed, show idle effect
            idle();
        }
    }
    delay(100); // Delay for stability
}


void processOOCSI() {


  //receiver code---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //if (oocsi.getRecipient() == "sleep_dreamcatcher_green") {
	// extract data for this direct message
    Serial.print("greating: ");
    Serial.print(oocsi.getString("greating", ""));
    Serial.print("\t flexvalue1: ");
    Serial.print(oocsi.getInt("flexvalue1", -200));
    Serial.print("\t flexvalue2: ");
    Serial.print(oocsi.getInt("flexvalue2", -200));
    Serial.print("\t flexvalue3: ");
    Serial.print(oocsi.getInt("flexvalue3", -200));
    Serial.print("\t flexvalue4: ");
    Serial.print(oocsi.getInt("flexvalue4", -200));
    Serial.print("\t flexValue5: ");
    Serial.print(oocsi.getInt("flexvalue5", -200));
    Serial.print("\t yvalue: ");
    Serial.print(oocsi.getInt("yvalue", -200));
  // receiving the flex values and adding it to an int
    int flexValue1 =oocsi.getInt("flexvalue1", 800);
    int flexValue2 =oocsi.getInt("flexvalue2", 800);
    int flexValue3 =oocsi.getInt("flexvalue3", 800);
    int flexValue4 =oocsi.getInt("flexvalue4", 800);
    int flexValue5 =oocsi.getInt("flexvalue5", 800);
    int yvalue =oocsi.getInt("yvalue", 800);
  
  //changing brightness for different flexvalue
    int BRIGHTNESS1 = map(flexValue1, 3000, 0, 0, 255);
    int BRIGHTNESS2 = map(flexValue2, 3000, 0, 0, 255);
    int BRIGHTNESS3 = map(flexValue3, 3000, 0, 0, 255);
    int BRIGHTNESS4 = map(flexValue4, 3000, 0, 0, 255);
    int BRIGHTNESS5 = map(flexValue5, 3000, 0, 0, 255); 
  // receiving information about the sender
    Serial.print("\t sender: ");
    Serial.print(oocsi.getSender());
    Serial.print("\t recipient: ");
    Serial.print(oocsi.getRecipient());
    Serial.print("\t Timestamp: ");
    Serial.print(oocsi.getTimeStamp());
    Serial.println();

//next part is for all the different color combination options (combination functions can be found at bottom of code)---------------------------------------------------------------------

    // Check for combinations of two flex sensors being squeezed together
    if (flexValue1 < 3000 && flexValue2 < 3000) {
        // Call the gayy function if flex sensors 1 and 2 are squeezed together
        gayy();
    } else if (flexValue1 < 3000 && flexValue3 < 3000) {
        // Call the eeyore function if flex sensors 1 and 3 are squeezed together
        eeyore();
    } else if (flexValue1 < 3000 && flexValue4 < 3000) {
        // Call the attentionWhore function if flex sensors 1 and 4 are squeezed together
        attentionWhore();
    } else if (flexValue1 < 3000 && flexValue5 < 3000) {
        // Call the sunriseGradient function if flex sensors 1 and 5 are squeezed together
        sunriseGradient();
    } else if (flexValue2 < 3000 && flexValue3 < 3000) {
        // Call the northernLights function if flex sensors 2 and 3 are squeezed together
        northernLights();
    } else if (flexValue2 < 3000 && flexValue4 < 3000) {
        // Call the discoFever function if flex sensors 2 and 4 are squeezed together
        discoFever();
    } else if (flexValue2 < 3000 && flexValue5 < 3000) {
        // Call the galacticGlow function if flex sensors 2 and 5 are squeezed together
        galacticGlow();
    } else if (flexValue3 < 3000 && flexValue4 < 3000) {
        // Call the candyland function if flex sensors 3 and 4 are squeezed together
        candyland();
    } else if (flexValue3 < 3000 && flexValue5 < 3000) {
        // Call the neonPulse function if flex sensors 3 and 5 are squeezed together
        neonPulse();
    } else if (flexValue4 < 3000 && flexValue5 < 3000) {
        // Call the fireAndIce function if flex sensors 4 and 5 are squeezed together
        fireAndIce();
    } else {
        // Check for individual sensor squeezes
        if (flexValue1 < 3000) {
            // Call the cyclone function if flex sensor 1 is squeezed
            cyclone();
        } else if (flexValue2 < 3000) {
            // Call the cylon function if flex sensor 2 is squeezed
            cylon();
        } else if (flexValue3 < 3000) {
            // Call the comet function if flex sensor 3 is squeezed
            comet();
        } else if (flexValue4 < 3000) {
            // Call the oceanWaves function if flex sensor 4 is squeezed
            oceanWaves();
        } else if (flexValue5 < 3000) {
            // Call the lavaShock function if flex sensor 5 is squeezed
            lavaShock();
        } else {
            // If no sensor is being squeezed, show idle effect
            idle();
        }
    }
    delay(100); // Delay for stability
}

//now these are just the different color combinations made using the FastLED library-----------------------------------------------------------------------------------------------------

void fadeall() {
  for (int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); }
}

void idle() {
  unsigned long currentMillis = millis(); // Get the current time
  
  // Check if 30 seconds have passed since the last color update
  if (currentMillis - previousIdleMillis >= 30000) {
    // Update the idle color index and reset the timer
    idleColorIndex = (idleColorIndex + 1) % 3; // Cycle between 0, 1, and 2
    previousIdleMillis = currentMillis;
  }
  
  // Set the idle color based on the idleColorIndex
  if (idleColorIndex == 0) {
    // Red color
    fill_solid(leds, NUM_LEDS, CRGB::Red);
  } else if (idleColorIndex == 1) {
    // Green color
    fill_solid(leds, NUM_LEDS, CRGB::Green);
  } else if (idleColorIndex == 2) {
    // Yellow color
    fill_solid(leds, NUM_LEDS, CRGB::Yellow);
  }
  
  FastLED.show(); // Show the LEDs
}

void cyclone() {
  static uint8_t hue = 0;
  Serial.print("x");
  // First slide the led in one direction
  for (int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to red
    leds[i] = CRGB::OrangeRed;
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }
  Serial.print("x");

  // Now go in the other direction.
  for (int i = (NUM_LEDS)-1; i >= 0; i--) {
    // Set the i'th led to red
    leds[i] = CRGB::OrangeRed;
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }
}

void explosion() {
  fadeall();
  for (int i = 0; i < NUM_LEDS / 2; i++) {
    leds[i] = CRGB::Amethyst;
    leds[i + 1] = CRGB::Amethyst;
    leds[i + 2] = CRGB::Amethyst;
    leds[i + 3] = CRGB::Amethyst;
    leds[NUM_LEDS - i] = CRGB::Aqua;
    leds[NUM_LEDS - i - 1] = CRGB::Aqua;
    leds[NUM_LEDS - i - 2] = CRGB::Aqua;
    leds[NUM_LEDS - i - 3] = CRGB::Aqua;

    FastLED.show();
    delay(80);
    leds[i]=CRGB::Black;
    leds[NUM_LEDS-i]=CRGB::Black;
    FastLED.show();
  }
  for (int i = 0; i < NUM_LEDS/2; i++) {
    if (i /22 != 1) {
      leds[25 + i] = CRGB::Aqua;
      leds[25 - i] = CRGB::Aqua;
      FastLED.show();
      delay(12);
    }else{
      leds[25 + i] = CRGB::Amethyst;
      leds[25 - i] = CRGB::Amethyst;
      FastLED.show();
      delay(12);
    }
  }
  for (int i = 255; i > 0; i--) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(10);
  }
}

void twinkle() {
  int randomLed = random(NUM_LEDS);
  leds[randomLed] = CHSV(random(0, 255), 255, 255);
  FastLED.show();
  delay(50);
  leds[randomLed] = CRGB::Black;
}

void rainbowColorShow() {
  for (int i = 0; i < NUM_LEDS - 9; i++) {
    //from leds i to i+8 make it light up like a rainbow
    leds[i] = CRGB::Black;
    leds[i + 1] = CRGB::Red;
    leds[i + 2] = CRGB::Orange;
    leds[i + 3] = CRGB::Yellow;
    leds[i + 4] = CRGB::Green;
    leds[i + 5] = CRGB::Blue;
    leds[i + 6] = CRGB::Indigo;
    leds[i + 7] = CRGB::Violet;
    leds[i + 8] = CRGB::HotPink;
    leds[i + 9] = CRGB::Pink;
    FastLED.show();
    delay(30);
  }
}

void comet() {
  static uint8_t hue = 125;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue, 255, 255);
    FastLED.show();
    fadeall();
    delay(20);
  }
  hue++;
}

void cylon() {
  uint8_t hue = 75;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue, 255, 255);
    FastLED.show();
    fadeall();
    delay(10);
  }
  for (int i = NUM_LEDS - 1; i >= 0; i--) {
    leds[i] = CHSV(hue, 255, 255);
    FastLED.show();
    fadeall();
    delay(10);
  }
  hue++;
}

void oceanWaves() {
  static uint8_t hue = 150; // Initial hue value
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue + (i * 2), 255, 200); // Vary hue gradually across the strip
    FastLED.show();
    fadeall();
    delay(20);
  }
  hue += 2; // Increment hue for next iteration
}

void lavaShock() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Green; // Set all LEDs to red
  }
  FastLED.show();
  delay(100); // Initial delay for full red effect
  for (int flicker = 0; flicker < 10; flicker++) { // Flicker effect
    for (int i = 0; i < NUM_LEDS; i++) {
      if (random(0, 2) == 0) { // Randomly flicker LEDs off
        leds[i] = CRGB::Black;
      }
    }
    FastLED.show();
    delay(random(20, 100)); // Vary flicker speed randomly
  }
}

void gayy() {
  static uint8_t hue = 0; // Initial hue value
  for (int i = 0; i < NUM_LEDS; i++) {
    // Vary hue and saturation to create hyper effect
    leds[i] = CHSV(hue + (i * 10), 255, 255);
  }
  FastLED.show();
  delay(50); // Adjust delay for hyper effect
  hue += 5; // Increment hue for next iteration
}

void eeyore() {
  static uint8_t hue = 160; // Initial hue value for blue
  for (int i = 0; i < NUM_LEDS; i++) {
    if (random(0, 10) < 8) { // Most LEDs stay off most of the time
      leds[i] = CHSV(hue + (i * 2), 100, 50); // Set LEDs to blue-purple shades with lower brightness for a more subdued effect
    } else {
      leds[i] = CRGB::Black; // Occasionally flicker LEDs off for raindrop effect
    }
  }
  FastLED.show();
  delay(100); // Adjust delay for the speed of the rain effect
}

void attentionWhore() {
  static uint8_t phase = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    if ((i + phase) % 4 == 0 || (i + phase) % 4 == 1) {
      leds[i] = CRGB::Green; // Every other LED is red
    } else {
      leds[i] = CRGB::Blue; // Remaining LEDs are blue
    }
  }
  FastLED.show();
  delay(100); // Adjust delay for the speed of the police car lights
  phase = (phase + 1) % 4; // Cycle through 4 phases to create alternating lights
}

void sunriseGradient() {
  static uint8_t hue = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue, 255, 255); // Vary hue across the strip
  }
  FastLED.show();
  delay(50); // Adjust delay for speed of sunrise effect
  hue += 1; // Increment hue for next iteration
}

void northernLights() {
  static uint8_t hue = 100; // Initial hue value
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue + (i * 10), 100, 200); // Vary hue across the strip with lower saturation and higher brightness
  }
  FastLED.show();
  delay(50); // Adjust delay for speed of calm northern lights effect
  hue += 2; // Increment hue for next iteration
}

void discoFever() {
  static uint8_t hue = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue + (i * 10), 255, 255); // Vary hue rapidly across the strip
  }
  FastLED.show();
  delay(20); // Adjust delay for speed of disco effect
  hue += 5; // Increment hue for next iteration
}

void galacticGlow() {
  static uint8_t hue = 160; // Initial hue value
  static uint8_t brightness = 100; // Initial brightness value
  static int8_t direction = 1; // Direction of brightness change
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue + (i * 5), 100, brightness); // Vary hue across the strip with constant saturation and brightness
  }
  FastLED.show();
  delay(50); // Adjust delay for speed of galactic glow effect
  brightness += direction; // Change brightness
  if (brightness == 50 || brightness == 150) { // Change direction at brightness limits
    direction *= -1;
  }
}

void candyland() {
  static uint8_t phase = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    if ((i + phase) % 2 == 0) {
      leds[i] = CRGB::Pink; // Every other LED is pink
    } else {
      leds[i] = CRGB::DeepSkyBlue; // Remaining LEDs are blue
    }
  }
  FastLED.show();
  delay(100); // Adjust delay for speed of candyland effect
  phase = (phase + 1) % 2; // Cycle through 2 phases
}

void neonPulse() {
  static uint8_t hue = 0; // Initial hue value
  static uint8_t position = 0; // Current position of light flow

  // Clear all LEDs
  fill_solid(leds, NUM_LEDS, CRGB::Black);

  // Calculate the hue increment for each LED
  uint8_t hueIncrement = 255 / NUM_LEDS;

  // Set color at current position
  for (int i = 0; i < NUM_LEDS; i++) {
    if (hue >= 0 && hue < 85) {
      leds[i] = CRGB::Pink; // Pastel pink
    } else if (hue >= 85 && hue < 170) {
      leds[i] = CRGB::LightSkyBlue; // Pastel light blue
    } else {
      leds[i] = CRGB::Yellow; // Pastel yellow
    }
    hue += hueIncrement;
  }

  // Show the LEDs
  FastLED.show();

  // Move the light flow position faster
  position += 4; // Adjust the increment for faster movement

  // Reset position when it reaches the end of the strip
  if (position >= NUM_LEDS) {
    position = 0;
    hue += 10; // Change hue for variety
  }

  // Delay for smooth transition
  delay(10); // Adjust delay for faster movement
}

void fireAndIce() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i % 2 == 0) {
      leds[i] = CRGB::Red; // Every other LED is red
    } else {
      leds[i] = CRGB::Blue; // Remaining LEDs are blue
    }
  }
  FastLED.show();
  delay(100); // Adjust delay for speed of fire and ice effect
}