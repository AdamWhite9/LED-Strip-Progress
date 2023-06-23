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
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

int maxBrightness = 200;
int minBrightness = 50;
int currentBrightness;
int fadeAmount = 10;  // how many points to fade the LED by
long delayMs = 150;  // in milliseconds, may need to convert

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
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


