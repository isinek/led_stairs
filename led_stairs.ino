#include <Arduino.h>
#include <FastLED.h>

// #define DEBUG
// #define RAINBOW

#define N_STAIRS      15
#define N_LEDS        26

#define COLOR_ORDER   GRB
#define CHIPSET       WS2812B
#define BRIGHTNESS    75
#define VOLTS         5
#define MAX_MAMPS     500

#define SENSOR_PIN_1  A5
#define SENSOR_PIN_2  A4

#define LIGHT_SPREAD  20.0
#define PROGRESS_STEP 0.3

CRGB stairs[N_STAIRS][N_LEDS];
uint8_t pins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0, A1, A2};
double progress = 0;


void nextInColorWheel(CRGB *color, uint8_t step=15) {
  if (color->blue == 0 && color->red < 255) {
    color->red = (((int)color->red) + step > 255) ? 255: color->red + step;
    color->green = (((int)color->green) - step < 0) ? 0: color->green - step;
  } else if ((*color)[1] == 0 && (*color).blue < 255) {
    color->blue = (((int)color->blue) + step > 255) ? 255: color->blue + step;
    color->red = (((int)color->red) - step < 0) ? 0: color->red - step;
  } else {
    color->red = 0;
    color->green = (((int)color->green) + step > 255) ? 255: color->green + step;
    color->blue = (((int)color->blue) - step < 0) ? 0: color->blue - step;
  }
}

void initHorizontalRainbow() {
  CRGB color;

  for (uint8_t i = 0; i < N_STAIRS; ++i) {
    color = CRGB(255, 0, 0);
    for (uint8_t j = 0; j < N_LEDS; ++j) {
      stairs[i][j] = color;
      nextInColorWheel(&color);
    }
  }
}


void setup()
{
#ifdef DEBUG
  Serial.begin(9600);
#endif

  for (uint8_t i = 0; i < N_STAIRS; ++i)
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
  FastLED.setBrightness(30);
  FastLED.clear();
  FastLED.show();

#ifdef RAINBOW
  initHorizontalRainbow();
  FastLED.show();
#endif

#ifdef DEBUG
  Serial.println("Init done");
#endif
}

void loop()
{
  uint8_t i, j, stair_perc;
  int sens;
  int8_t brightness = 0;

#ifdef RAINBOW
  for (i = 0; i < N_STAIRS; ++i)
    for (j = 0; j < N_LEDS; ++j)
      nextInColorWheel(&stairs[i][j]);

  FastLED.show();
  delay(25);
#else
  sens = digitalRead(SENSOR_PIN_1);
#ifdef DEBUG
  Serial.print("sens: ");
  Serial.println(sens);
#endif
  if (sens == HIGH || (progress > 0 && progress < 100))
    progress += PROGRESS_STEP;
  else
    progress = 0;

  for (i = 0; i < N_STAIRS; ++i) {
    stair_perc = i*100/(N_STAIRS + 2);
    brightness = LIGHT_SPREAD - abs(progress - stair_perc);
    brightness = (brightness > 0 && progress)*brightness;

    for (j = 0; j < N_LEDS; ++j)
      stairs[i][j] = CRGB(255*(brightness/LIGHT_SPREAD), 255*(brightness/LIGHT_SPREAD), 255*(brightness/LIGHT_SPREAD));
  }

  FastLED.show();
  if (progress == PROGRESS_STEP)
    delay(2000);
  else if (progress > 45 && progress < 47)
    delay(30);
  delay(15);
#endif
}
