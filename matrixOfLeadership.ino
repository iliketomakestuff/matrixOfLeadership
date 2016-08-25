//This is just a modified version of
//https://learn.adafruit.com/animated-neopixel-gemma-glow-fur-scarf/the-code

//This code powers the lighting in the Matrix of Leadership prop build
//http://www.iliketomakestuff.com/3d-printing-prop-transformers-matrix-leadership/

#include <FastLED.h>

#define LED_PIN      0   // which pin your pixels are connected to
#define NUM_LEDS    16   // how many LEDs you have
#define BRIGHTNESS 255   // 0-255, higher number is brighter. 
#define SATURATION 255   // 0-255, 0 is pure white, 255 is fully saturated color
#define SPEED       30   // How fast the colors move.  Higher numbers = faster motion
#define STEPS        1   // How wide the bands of color are.  1 = more like a gradient, 10 = more like stripes

#define COLOR_ORDER GRB  // Try mixing up the letters (RGB, GBR, BRG, etc) for a whole new world of color combinations

CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
CRGBPalette16 targetPalette( PartyColors_p );
int ledMode = 0;

int inPin = 3;         // the number of the input pin
int reading;           // the current reading from the input pin
int readyToFadeUp = 0;
const TProgmemPalette16 PurpleColors_p PROGMEM =
{
  CRGB::MidnightBlue,
  CRGB::White, 
  CRGB::Blue,
  CRGB::BlueViolet,

  CRGB::Blue,
  CRGB::White,
  CRGB::BlueViolet,
  CRGB::MidnightBlue,
  
  CRGB::Aqua,
  CRGB::Purple, 
  CRGB::MidnightBlue,
  CRGB::White,

  CRGB::Blue,
  CRGB::White,
  CRGB::BlueViolet,
  CRGB::MidnightBlue,
};


void setup() {
  delay( 2000 ); // power-up safety delay
  FastLED.addLeds<WS2812B, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  pinMode(inPin, INPUT);
  digitalWrite(inPin, HIGH);
}

void loop() {

 reading = digitalRead(inPin);
if (reading == LOW) {
    if(readyToFadeUp == 0){
      readyToFadeUp = 1;
     for(int dot = 0; dot < NUM_LEDS; dot++) { 
            leds[dot] = CRGB::MidnightBlue;
            FastLED.show();
            delay(40);
        }
    }
    
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; 
    
    currentPalette = PurpleColors_p;  //My custom palette from above
    
    FillLEDsFromPaletteColors( startIndex);
    FastLED.show();
    FastLED.delay(1000 / SPEED);  
  } else {
    for(int dot = 0; dot < NUM_LEDS; dot++) { 
        leds[dot] = CRGB::Black;
        FastLED.show();
        delay(30);
    }
    readyToFadeUp = 0;

  }

}
void FillLEDsFromPaletteColors( uint8_t colorIndex) {
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, BRIGHTNESS);
    colorIndex += STEPS;              
  }
}

