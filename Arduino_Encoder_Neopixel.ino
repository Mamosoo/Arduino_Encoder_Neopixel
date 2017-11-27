#include <Encoder.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN            11
#define NUMPIXELS      60

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Encoder myEnc(5, 6);

int oldPosition  = -999;

#define BTN_PIN 7
int buttonState;
int lastButtonState = 0;
bool isOn = false;

long lastDebounceTime = 0;
long debounceDelay = 50;

void setup() {
  Serial.begin(9600);
  pixels.begin();
  pinMode(BTN_PIN, INPUT_PULLUP);
}

void loop() {
  int reading = digitalRead(BTN_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == 1) {
        isOn = !isOn;
      }
    }
  }
  lastButtonState = reading;

  if (isOn == true)
  {
    pixels.setBrightness(255);
  }
  else
  {
    pixels.setBrightness(0);
    pixels.show();
    return;
  }

  ////////////////////////////////////////////////////////
  int newPosition = myEnc.read() / 4;

  if (newPosition % 2 != 0)
    return;

  if (newPosition != oldPosition) {
    oldPosition = newPosition;
  }

  newPosition = abs(newPosition);

  if (newPosition == 24)
  {
    myEnc.write(0);
  }

  if (newPosition == 0)
  {
    setLight(255, 255, 255);
  }
  else if (newPosition == 2)
  {
    setLight(236, 246, 252);
  }
  else if (newPosition == 4)
  {
    setLight(229, 243, 251);
  }
  else if (newPosition == 6)
  {
    setLight(216, 239, 249);
  }
  else if (newPosition == 8)
  {
    setLight(229, 243, 251);
  }
  else if (newPosition == 10)
  {
    setLight(236, 246, 252);
  }
  else if (newPosition == 12)
  {
    setLight(255, 255, 255);
  }
  else if (newPosition == 14)
  {
    setLight(254, 235, 189);
  }
  else if (newPosition == 16)
  {
    setLight(254, 213, 115);
  }
  else if (newPosition == 18)
  {
    setLight(252, 203, 73);
  }
  else if (newPosition == 20)
  {
    setLight(253, 213, 115);
  }

  else if (newPosition == 22)
  {
    setLight(254, 235, 189);
  }


  pixels.show();
}

void setLight(int r, int g, int b) {
  for (int i = 0; i < NUMPIXELS; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(r, g, b));


  }

}
