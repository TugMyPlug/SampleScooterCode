#include <FastLED.h>
#include <OneButton.h>
#include "Arduino.h"

#define NUM_LEDS  21
#define LED_PIN   6
#define BTN_PIN   3
#define BRIGHTNESS 200

CRGB leds[NUM_LEDS];
uint8_t patternCounter = 0;
bool isRunning = false;
bool isPressed = false;
bool isLongPressed = false;

// Push button connected between pin 3 and GND (no resistor required)
OneButton btn = OneButton(BTN_PIN, true, true);

#include "MovingDot.h"
#include "RainbowBeat.h"
#include "RedWhiteBlue.h"

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(57600);

  btn.attachClick(nextPattern);
  btn.attachLongPressStart(stopPattern);
}

void loop() {
  if (isLongPressed = true) {
    stopPattern();
    isRunning = false;
    FastLED.setBrightness(0);
  }
  FastLED.setBrightness(BRIGHTNESS);
  switch (patternCounter) {
    case 0:
      runMovingDot();
      break;
    case 1:
      runRainbowBeat();
      break;
    case 2:
      runRedWhiteBlue();
      break;
  }
  FastLED.show();
  btn.tick();
}

void nextPattern() {
  isRunning = false;
  patternCounter = (patternCounter + 1) % 3;
}

void stopPattern() {
  isPressed = true;
//  delay(1000);
  if (isLongPressed = true){
    FastLED.clear();
    FastLED.setBrightness(0);
    FastLED.show();
    btn.tick();
  }
}

void runMovingDot(){
  isRunning = true;
  MovingDot movingDot = MovingDot();
  while(isRunning) movingDot.runPattern();
}

void runRainbowBeat(){
  isRunning = true;
  RainbowBeat rainbowBeat = RainbowBeat();
  while(isRunning) rainbowBeat.runPattern();
}

void runRedWhiteBlue(){
  isRunning = true;
  RedWhiteBlue redWhiteBlue = RedWhiteBlue();
  while(isRunning) redWhiteBlue.runPattern();
}
