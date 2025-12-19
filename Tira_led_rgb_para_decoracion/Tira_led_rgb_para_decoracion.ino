#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMPIXELS 8

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
  pixels.setBrightness(60); // Baja el brillo (muy importante para decoración)
}

void loop() {
  arcoirisSuave(40);
}

void arcoirisSuave(int wait) {
  static int j = 0;

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, Wheel((i * 256 / NUMPIXELS + j) & 255));
  }

  pixels.show();
  j++;
  delay(wait);
}

uint32_t Wheel(byte pos) {
  pos = 255 - pos;
  if (pos < 85) {
    return pixels.Color(255 - pos * 3, 0, pos * 3);
  }
  if (pos < 170) {
    pos -= 85;
    return pixels.Color(0, pos * 3, 255 - pos * 3);
  }
  pos -= 170;
  return pixels.Color(pos * 3, 255 - pos * 3, 0);
}
