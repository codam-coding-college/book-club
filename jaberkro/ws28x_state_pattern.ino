#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    36
#define BRIGHTNESS  64
#define LED_TYPE    WS2813
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

/* voorbeeld met een knop. Iedere keer als de knop is ingedrukt komt er een ander patroon
 *  Je kan de snelheid van patronen veranderen door:
 *  1. de UPDATES_PER_SECOND hierboven hoger of lager te zetteb
 *  2. de random range groter en kleiner te maken
 *  3. een delay in te bouwen in je loop
 */
const int button = 8;     // de knop zit aan pin 8
int buttonState = 0;      // hierin gaan we opslaan of de knop is ingedrukt of niet
int lastState = 0;        // hierin slaan we op of de knop net was ingedrukt of niet
int pattern = 0;          // hierin slaan we het huidige patroon op
int amountOfPatterns = 4; // dit wil je zelf aanpassen naar het aantal patronen dat je hebt

int hues[NUM_LEDS];        // hierin slaan we alle felheden op van de blauwe glow
int purplePinkColours[NUM_LEDS];  // hierin slaan we alle paars en roze tinten op

void setup() {
  // put your setup code here, to run once:
  delay(3000); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  pinMode(button, INPUT);

  //initialize hues for blueGlowPattern and purplePinkPattern:
  for (int i = 0; i < NUM_LEDS; i++)
  {
    hues[i] = random(0, 255);
    purplePinkColours[i] = random(192, 224);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(button);

  if (buttonState == 1 && lastState == 0) // als de knop nu is ingedrukt maar net niet,
  {
    pattern = random(0, amountOfPatterns);  // verander dan het patroon
  }
  
  displayPattern();  //laat het huidige patroon zien
  
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
  lastState = buttonState;
}

void  displayPattern()
{
  // dit is een switch case. Het 'kiest' een optie aan de hand van de waarde die 'pattern' nu heeft. (voorbeeld: als het pattern 0 is wordt case 0 uitgevoerd)
  switch(pattern) 
  {
    case 0:
      purplePinkPattern();
      break;
    case 1:
      blueGlowPattern();
      break;
    case 2:
      redGlitterPattern();
      break;
     case 3:
      rainbowPattern();
      break;
    // hier onder kan je de namen van andere patronen die je maakt toevoegen
  }
}

/*
 * hier onder staan de codes van de verschillende patronen, je kunt er meer aan toevoegen.
 * Ze zijn expres op verschillende manieren gemaakt zodat je een paar mogelijkheden ziet
 */

void  purplePinkPattern()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CHSV(purplePinkColours[i], 255 ,255);
    purplePinkColours[i] += random (-2, 3); // maak de kleur random iets meer of minder
    if (purplePinkColours[i] > 224)
    {
      purplePinkColours[i] = 224; // maximale waarde (roze)
    }
    else if (purplePinkColours[i] < 192)
    {
      purplePinkColours[i] = 192; // minimale waarde (paars)
    }
  }
}

void  blueGlowPattern()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CHSV(160, hues[i], 255);
    hues[i] += random (-12, 13); // maak de helderheid random iets meer of minder
    if (hues[i] > 255)
    {
      hues[i] = 255; // maximale waarde
    }
    else if (hues[i] < 0)
    {
      hues[i] = 0; // minimale waarde
    }
  }
}

void  redGlitterPattern()
{         
  int glitterLed;
  int redLed;
          
  for (int i = 0; i < NUM_LEDS; i++) //maak alle lampjes rood
  {
    leds[i] = CHSV(0, 255, 225); 
  }
  for (int i = 0; i < 1; i++) // maak 1 random lampjes wit als 'glitters'
  {
    glitterLed = random(0, NUM_LEDS);
    leds[glitterLed] = CRGB(200, 200, 200);
  }
}

void  rainbowPattern()
{
  static int  rainbowStart = 0; // we gaan onthouden wat de laatste i was

  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CHSV((rainbowStart + i) % 255, 255, 255);
  }
  rainbowStart++; // volgende keer als we hier terug komen schuift de plek van de rainbowstart 1 plekje op
  if (rainbowStart > 255)
  {
    rainbowStart = 0;
  }
  
}
