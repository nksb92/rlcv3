#include <FastLED.h>  // include FastLED *before* Artnet
#include <Adafruit_NeoPixel.h>

// Please include ArtnetWiFi.h to use Artnet on the platform
// which can use both WiFi and Ethernet
#include <ArtnetWifi.h>
// this is also valid for other platforms which can use only WiFi
// #include <Artnet.h>

// WiFi stuff
const char* ssid = "ARTNET_RLCV3";
const char* pwd = "123456789";

ArtnetWifi artnet;
const int startUniverse = 0;

bool sendFrame = 1;
int previousDataLength = 0;

// FastLED
#define NUM_LEDS 144
CRGB leds[NUM_LEDS];
const int numberOfChannels = NUM_LEDS * 3; 
const uint8_t PIN_LED_DATA = 8;
Adafruit_NeoPixel pixels(NUM_LEDS, PIN_LED_DATA, NEO_RGB + NEO_KHZ800);

void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data)
{
  sendFrame = 1;
  // set brightness of the whole strip 
  if (universe == 15)
  {
  }
  Serial.println(length);
  // read universe and put into the right part of the display buffer
  for (int i = 0; i < length / 3; i++)
  {
    int led = i + (universe - startUniverse) * (previousDataLength / 3);
    if (led < NUM_LEDS)
    {
      // leds[led] = CRGB(data[i * 3], data[i * 3 + 1], data[i * 3 + 2]);
      pixels.setPixelColor(led, pixels.Color(data[i * 3], data[i * 3 + 1], data[i * 3 + 2]));
    }
  }
  previousDataLength = length;     
  pixels.show();
}

void setup() {
    Serial.begin(115200);
    delay(2000);
    pixels.begin();

    // WiFi stuff
    WiFi.begin(ssid, pwd);
    // WiFi.config(ip, gateway, subnet);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.print("WiFi connected, IP = ");
    Serial.println(WiFi.localIP());

    artnet.setArtDmxCallback(onDmxFrame);
    // artnet.forward(universe, leds, NUM_LEDS);
    artnet.begin();
}

void loop() {
    artnet.read();  // check if artnet packet has come and execute callback
}