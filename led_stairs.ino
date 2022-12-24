#include <Arduino.h>
#include <FastLED.h>

// define DEBUG

#define N_STAIRS      15
#define N_LEDS        26

#define COLOR_ORDER   GRB
#define CHIPSET       WS2812B
#define BRIGHTNESS    75
#define VOLTS         5
#define MAX_MAMPS     500

#define SENSOR_PIN_1  A5
#define SENSOR_PIN_2  A4

#define MAX_COUNTER(step)     ((255/step)*2 - 1)
#define LIGHT_INT(n, c, step) (n > 255/step ? c - (n*c/(255/step) - c): n*c/(255/step))
#define COLOR(n, step)        CRGB(LIGHT_INT(n, 255, step), LIGHT_INT(n, 120, step), LIGHT_INT(n, 20, step))

CRGB stairs[N_STAIRS][N_LEDS];
uint8_t pins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0, A1, A2};
uint32_t counter = 0;
uint8_t loops = 1;
uint8_t step = 5;
bool odd = false;

void xmas_loop()
{
  uint32_t i, j;

  for (i = 0; i < N_STAIRS; ++i) {
    for (j = 0; j < N_LEDS; j += 2) {
      if ((j/2 + i)%2 == odd)
        stairs[i][j] = COLOR(counter, step);
      else
        stairs[i][j] = CRGB(0, 0, 0);
    }
  }

  FastLED.show();
  delay(5);
}

void setup()
{
  uint32_t i, j;
  uint32_t r;
#ifdef DEBUG
  Serial.begin(9600);
#endif

  for (i = 0; i < N_STAIRS; ++i)
    pinMode(pins[i], OUTPUT);

  pinMode(SENSOR_PIN_1, INPUT);

  FastLED.addLeds<CHIPSET, 2, COLOR_ORDER>(stairs[0], N_LEDS);
  FastLED.addLeds<CHIPSET, 3, COLOR_ORDER>(stairs[1], N_LEDS);
  FastLED.addLeds<CHIPSET, 4, COLOR_ORDER>(stairs[2], N_LEDS);
  FastLED.addLeds<CHIPSET, 5, COLOR_ORDER>(stairs[3], N_LEDS);
  FastLED.addLeds<CHIPSET, 6, COLOR_ORDER>(stairs[4], N_LEDS);
  FastLED.addLeds<CHIPSET, 7, COLOR_ORDER>(stairs[5], N_LEDS);
  FastLED.addLeds<CHIPSET, 8, COLOR_ORDER>(stairs[6], N_LEDS);
  FastLED.addLeds<CHIPSET, 9, COLOR_ORDER>(stairs[7], N_LEDS);
  FastLED.addLeds<CHIPSET, 10, COLOR_ORDER>(stairs[8], N_LEDS);
  FastLED.addLeds<CHIPSET, 11, COLOR_ORDER>(stairs[9], N_LEDS);
  FastLED.addLeds<CHIPSET, 12, COLOR_ORDER>(stairs[10], N_LEDS);
  FastLED.addLeds<CHIPSET, 13, COLOR_ORDER>(stairs[11], N_LEDS);
  FastLED.addLeds<CHIPSET, A0, COLOR_ORDER>(stairs[12], N_LEDS);
  FastLED.addLeds<CHIPSET, A1, COLOR_ORDER>(stairs[13], N_LEDS);
  FastLED.addLeds<CHIPSET, A2, COLOR_ORDER>(stairs[14], N_LEDS);

  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_MAMPS);
  FastLED.setBrightness(40);
  FastLED.clear();
  FastLED.show();

#ifdef DEBUG
  Serial.println("Init done");
#endif
}

void loop()
{
  counter = (counter + 1)%MAX_COUNTER(step);
  odd = (odd + !counter)%2;
  loops -= !odd && !counter;
  
  if (!counter && !loops) {
    step = random(5, 64);
    loops = step/4;
  }

  xmas_loop();
}
