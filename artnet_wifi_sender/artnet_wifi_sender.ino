// Please include ArtnetWiFi.h to use Artnet on the platform
// which can use both WiFi and Ethernet
#include <ArtnetWiFi.h>
// this is also valid for other platforms which can use only WiFi
// #include <Artnet.h>
#include <FastLED.h>
// WiFi stuff
const char* ssid = "ARTNET_RLCV3";
const char* pwd = "123456789";
const IPAddress ip(192, 168, 1, 201);
const IPAddress gateway(192, 168, 1, 1);
const IPAddress subnet(255, 255, 255, 0);
unsigned long last_color_update = 0;
CHSV color(0, 180, 255);
CHSV temp_hsv(0, 180, 255);
CRGB temp(255, 255, 255);

ArtnetWiFi artnet;
const String target_ip = "192.168.1.200";
const String target_ips[] = {
  "192.168.0.100",
  "192.168.0.101",
  "192.168.0.102",
  "192.168.0.103",
  "192.168.0.104",
  "192.168.0.105",
  "192.168.0.106",
  "192.168.0.107",
  "192.168.0.108",
};
uint8_t universe = 0;  // 0 - 15

const uint16_t size = 512;
uint8_t data[size];

void setup() {
  Serial.begin(115200);

  // WiFi stuff
  WiFi.begin(ssid, pwd);
  // WiFi.config(ip, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("WiFi connected, IP = ");
  Serial.println(WiFi.localIP());

  artnet.begin();
  // artnet.begin(net, subnet);     // optionally you can change net and subnet
  last_color_update = millis();
}

void set_bytes(CRGB col, int start) {
  data[start + 0] = col.r;
  data[start + 1] = col.g;
  data[start + 2] = col.b;
  data[start + 3] = 255;
}

void loop() {
  // artnet.parse();  // check if artnet packet has come and execute callback
  if (millis() - last_color_update > 200) {
    temp_hsv = color;
    hsv2rgb_rainbow(temp_hsv, temp);
    set_bytes(temp, 0);
    temp_hsv.hue += 64;

    hsv2rgb_rainbow(temp_hsv, temp);
    set_bytes(temp, 4);
    temp_hsv.hue += 64;

    hsv2rgb_rainbow(temp_hsv, temp);
    set_bytes(temp, 8);

    temp_hsv.hue += 64;
    hsv2rgb_rainbow(temp_hsv, temp);
    set_bytes(temp, 12);
    
    Serial.println(color.hue);

    color.hue++;
    last_color_update = millis();
  }

  for (String ip : target_ips) {
    artnet.streaming_data(data, size);
    artnet.streaming(ip, universe);
  }
}
