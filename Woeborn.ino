#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif

#define LED_PIN    6

#define LED_COUNT 57

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:

int maxBrightness = 200;
int minBrightness = 50;
int currentBrightness;
int fadeAmount = 10;  // how many points to fade the LED by
long delayMs = 150;  // in milliseconds, may need to convert

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  strip.begin();           
  strip.show();            
  strip.setBrightness(maxBrightness); // Set BRIGHTNESS to about 1/5 (max = 255)
  currentBrightness = maxBrightness;

  for(int i = 0; i < LED_COUNT; i++){
    strip.setPixelColor(i, strip.Color(255, 0, 0)); //this sets pixel color
    strip.show();
  }
}

//reduces or increases brightness amount of strip between min and max amount:
void loop() { 
  currentBrightness -= fadeAmount;
  strip.setBrightness(currentBrightness);
  strip.show();

  // reverse the direction of the fading at the ends of the fade:
  if (currentBrightness <= minBrightness || currentBrightness >= maxBrightness) {
    fadeAmount = -fadeAmount;
  }
  delay(delayMs);
}


