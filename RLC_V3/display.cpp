#include "display.h"

uint8_t offset = 4;
uint8_t offset_y = 26;

void init_display(Adafruit_SSD1306& dp) {
  dp.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  dp.clearDisplay();
  dp.setTextSize(1);
  dp.setTextColor(WHITE);
  dp.setFont(&FreeMonoBold9pt7b);
  // dp.setRotation(2);
  dp.display();
}

void hsv_display_update(Adafruit_SSD1306& dp, C_HSV out_val) {
  uint8_t hue = out_val.get_hue();
  uint8_t sat_p = out_val.get_sat_p();
  uint8_t val_p = out_val.get_val_p();
  uint8_t current_state = out_val.get_current();
  uint8_t spacing = 44;

  dp.setTextColor(WHITE);
  dp.clearDisplay();
  dp.setCursor(offset, 10);
  dp.print("HUE|SAT|VAL");

  for (int i = 0; i < 3; i++) {
    if (i == current_state) {
      dp.fillRoundRect(i * spacing + offset, offset_y - 13, 33, 16, 3, WHITE);
      dp.setTextColor(BLACK);
      dp.setCursor(i * spacing + offset, offset_y);
      if (i == 0) {
        dp.print(hue);
      } else if (i == 1) {
        dp.print(sat_p);
      } else {
        dp.print(val_p);
      }
    } else {
      dp.setTextColor(WHITE);
      dp.setCursor(i * spacing + offset, offset_y);
      if (i == 0) {
        dp.print(hue);
      } else if (i == 1) {
        dp.print(sat_p);
      } else {
        dp.print(val_p);
      }
    }
  }
  dp.display();
}

void rgb_display_update(Adafruit_SSD1306& dp, C_RGB rgb_val) {
  uint8_t red = rgb_val.get_red();
  uint8_t green = rgb_val.get_green();
  uint8_t blue = rgb_val.get_blue();
  uint8_t current_state = rgb_val.get_current();
  uint8_t spacing = 44;

  dp.setTextColor(WHITE);
  dp.clearDisplay();
  dp.setCursor(offset, 10);
  dp.print(" R | G | B ");

  for (int i = 0; i < 3; i++) {
    if (i == current_state) {
      dp.fillRoundRect(i * spacing + offset, offset_y - 13, 33, 16, 3, WHITE);
      dp.setTextColor(BLACK);
      dp.setCursor(i * spacing + offset, offset_y);
      if (i == 0) {
        dp.print(red);
      } else if (i == 1) {
        dp.print(green);
      } else {
        dp.print(blue);
      }
    } else {
      dp.setTextColor(WHITE);
      dp.setCursor(i * spacing + offset, offset_y);
      if (i == 0) {
        dp.print(red);
      } else if (i == 1) {
        dp.print(green);
      } else {
        dp.print(blue);
      }
    }
  }
  dp.display();
}

void dmx_display_update(Adafruit_SSD1306& dp, rgb_dmx dmx_val) {
  uint16_t start = dmx_val.get_start();
  uint8_t used = dmx_val.get_used_nbr();
  char* current_mode = dmx_val.get_current_txt();
  // first row
  dp.setTextColor(WHITE);
  dp.clearDisplay();
  dp.setCursor(offset, 11);
  dp.print("DMX|");
  dp.print(start);
  dp.print("-");
  dp.print(start + used - 1);
  // seccond row
  dp.setCursor(offset, offset_y);
  dp.print(current_mode);
  dp.display();
}

void pdc_display_update(Adafruit_SSD1306& dp, pdc_page pdc_val) {
  uint8_t offset_center = 27;
  dp.setTextColor(WHITE);
  dp.clearDisplay();
  dp.setCursor(offset, 11);
  dp.print("PDC|");
  dp.print(pdc_val.get_current_name());
  dp.setCursor(offset_center, offset_y);
  dp.print("%: ");
  dp.fillRoundRect(offset_center + 33, offset_y - 13, 33, 16, 3, WHITE);
  dp.setTextColor(BLACK);
  dp.print(pdc_val.get_bright());
  dp.display();
}

void display_saved_status(Adafruit_SSD1306& dp) {
  dp.setTextColor(WHITE);
  dp.clearDisplay();
  dp.setCursor(offset + 10, offset_y - 10);
  dp.print("|>SAVED<|");
  dp.display();
}

void display_startup(Adafruit_SSD1306& dp) {
  dp.setTextColor(WHITE);
  dp.clearDisplay();
  dp.setCursor(offset + 10, offset_y - 10);
  dp.print("Loading...");
  dp.display();
}