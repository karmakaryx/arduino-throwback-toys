#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN    1  //Digital IO pin connected to the NeoPixels
#define BUTTON_PIN   2  //Digital IO pin to trigger the NeoPixels

#define PIXEL_COUNT 18  //Number of pixels in strip
#define PIXEL_ROW    6  //Number of pixels per row

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

int showType = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.begin();
  strip.show();  //Initialize all pixels to 'off'
}

void loop() {
  //D2 connection can control the device without unplugging the battery cable
  //To switch off, detach D2 wire and click the black button
  //To resume, attach D2 wire again
  bool currState = digitalRead(BUTTON_PIN);

  if (currState == LOW) {
    if (showType > 4) {
      showType = 0;
    }

    showType++;
    startShow(showType);
  } else {
    strip.show();
  }
}

void startShow(int i) {
  switch (i) {
    case 0: colorWipe(strip.Color(0, 0, 0), 50);  //Black/off
            break;
    case 1: colorWipe(strip.Color(255, 0, 255), 50);  //Magenta
            colorWipe(strip.Color(127, 127, 127), 50);  //White
            colorWipe(strip.Color(0, 0, 255), 50);  //Blue
            break;
    case 2: colorWipeByRows(50);
            colorWipeByRows(50);
            colorWipeByRows(50);
            break;
    case 3: rainbowCycle(20);
            break;
    case 4: theaterChaseRainbow(50);
            break;
  }
}

//Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

//Show colorWipe function with a different color in each line
void colorWipeByRows(uint8_t wait) {
  colorWipe(strip.Color(0, 0, 0), 50);  //init

  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    if (i < PIXEL_ROW) {
      strip.setPixelColor(i, 255, 255, 0);  //Yellow
    } else if (i >= PIXEL_ROW && i < PIXEL_ROW * 2) {
      strip.setPixelColor(i, 255, 255, 255);  //Bright White
    } else {
      strip.setPixelColor(i, 0, 255, 0);  //Green
    }

    strip.show();
    delay(wait);
  }
}

//Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 3; j++) {  //3 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }

    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  uint16_t i, j, k;

  for (k = 0; k < 256; k++) {  //cycle all 256 colors in the wheel
    for (j = 0; j < 3; j++) {
      for (i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + j, Wheel((i + k) % 255));  //turn every third pixel on
      }

      strip.show();
      delay(wait);

      for (i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + j, 0);  //turn every third pixel off
      }
    }
  }
}

//Input a value 0 to 255 to get a color value
//The colours are a transition r - g - b - back to r
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;

  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
