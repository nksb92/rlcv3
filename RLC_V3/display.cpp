#include <sys/_stdint.h>
#include <stdint.h>
#include "display.h"
#include "bitmaps.h"

uint8_t offset = 5;
uint8_t offset_y = 26;
uint8_t last_menu_index = BITMAP_MAIN_MENU_LEN;
uint8_t MENU_ORDER[] = { LEFT_END_MENU, HSV_MENU, RGB_MENU, DMX_MENU, ARTNET_REC_MENU, SETTINGS_MENU, RIGHT_END_MENU };
int x_scroll = 0;
int min_x = 0;

void init_display(Adafruit_SSD1306 &dp) {
  dp.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  dp.clearDisplay();
  dp.setTextSize(1);
  dp.setTextColor(WHITE);
  dp.setFont(&FreeMonoBold9pt7b);
  dp.display();
  dp.setTextWrap(false);
  x_scroll = SCREEN_WIDTH / 3;
}

void hsv_display_update(Adafruit_SSD1306 &dp, C_HSV out_val) {
  uint8_t hue = out_val.get_hue();
  uint8_t sat = out_val.get_sat();
  uint8_t val = out_val.get_val();
  uint8_t current_state = out_val.get_current();
  uint8_t spacing = 43;

  dp.setTextColor(WHITE);
  dp.clearDisplay();
  dp.drawBitmap(X_Y_MATRIX_SUB_MENU[NMBR_HSV_PAGE][x],
                X_Y_MATRIX_SUB_MENU[NMBR_HSV_PAGE][y],
                BITMAP_SUB_MENU_ARRAY[NMBR_HSV_PAGE],
                W_H_MATRIX_SUB_MENU[NMBR_HSV_PAGE][WIDTH],
                W_H_MATRIX_SUB_MENU[NMBR_HSV_PAGE][HEIGHT],
                1);
  dp.drawBitmap(X_Y_MATRIX_SUB_MENU[NMBR_SELECTION_BAR_SUB][x] + spacing * current_state,
                X_Y_MATRIX_SUB_MENU[NMBR_SELECTION_BAR_SUB][y],
                BITMAP_SUB_MENU_ARRAY[NMBR_SELECTION_BAR_SUB],
                W_H_MATRIX_SUB_MENU[NMBR_SELECTION_BAR_SUB][WIDTH],
                W_H_MATRIX_SUB_MENU[NMBR_SELECTION_BAR_SUB][HEIGHT],
                1);
  dp.setCursor(offset, offset_y);
  dp.print(hue);
  dp.setCursor(spacing + offset, offset_y);
  dp.print(sat);
  dp.setCursor(2 * spacing + offset, offset_y);
  dp.print(val);
  dp.display();
}

void rgb_display_update(Adafruit_SSD1306 &dp, C_RGB rgb_val) {
  uint8_t red = rgb_val.get_red();
  uint8_t green = rgb_val.get_green();
  uint8_t blue = rgb_val.get_blue();
  uint8_t current_state = rgb_val.get_current();
  uint8_t spacing = 43;

  dp.setTextColor(WHITE);
  dp.clearDisplay();
  dp.drawBitmap(X_Y_MATRIX_SUB_MENU[NMBR_RGB_PAGE][x],
                X_Y_MATRIX_SUB_MENU[NMBR_RGB_PAGE][y],
                BITMAP_SUB_MENU_ARRAY[NMBR_RGB_PAGE],
                W_H_MATRIX_SUB_MENU[NMBR_RGB_PAGE][WIDTH],
                W_H_MATRIX_SUB_MENU[NMBR_RGB_PAGE][HEIGHT],
                1);
  dp.drawBitmap(X_Y_MATRIX_SUB_MENU[NMBR_SELECTION_BAR_SUB][x] + spacing * current_state,
                X_Y_MATRIX_SUB_MENU[NMBR_SELECTION_BAR_SUB][y],
                BITMAP_SUB_MENU_ARRAY[NMBR_SELECTION_BAR_SUB],
                W_H_MATRIX_SUB_MENU[NMBR_SELECTION_BAR_SUB][WIDTH],
                W_H_MATRIX_SUB_MENU[NMBR_SELECTION_BAR_SUB][HEIGHT],
                1);
  dp.setCursor(offset, offset_y);
  dp.print(red);
  dp.setCursor(spacing + offset, offset_y);
  dp.print(green);
  dp.setCursor(2 * spacing + offset, offset_y);
  dp.print(blue);
  dp.display();
}

void dmx_display_update(Adafruit_SSD1306 &dp, rgb_dmx dmx_val) {
  uint16_t start = dmx_val.get_start();
  uint16_t used = dmx_val.get_used_nbr();
  int16_t x1, y1;
  uint16_t w, h;
  String buf = String(start);
  buf = String(buf + "-");
  buf = String(buf + (start + used - 1));

  dp.clearDisplay();
  dp.setTextColor(WHITE);
  dp.drawBitmap(X_Y_MATRIX_SUB_MENU[NMBR_DMX_PAGE][x],
                X_Y_MATRIX_SUB_MENU[NMBR_DMX_PAGE][y],
                BITMAP_SUB_MENU_ARRAY[NMBR_DMX_PAGE],
                W_H_MATRIX_SUB_MENU[NMBR_DMX_PAGE][WIDTH],
                W_H_MATRIX_SUB_MENU[NMBR_DMX_PAGE][HEIGHT],
                1);

  // display the start and end address centered
  dp.getTextBounds(buf, x, y, &x1, &y1, &w, &h);  // calc width of new string
  dp.setCursor((x - w / 2) + (128 / 2), 28);
  dp.print(buf);
  dp.display();
}

void settings_display_update(Adafruit_SSD1306 &dp, segments seg, uint8_t setting_index, uint8_t current_deepness) {
  uint16_t number_seg = seg.get_num_seg();
  dp.clearDisplay();
  dp.setTextColor(WHITE);

  dp.drawBitmap(X_Y_MATRIX_SUB_MENU[NMBR_COLON][x],
                X_Y_MATRIX_SUB_MENU[NMBR_COLON][y],
                BITMAP_SUB_MENU_ARRAY[NMBR_COLON],
                W_H_MATRIX_SUB_MENU[NMBR_COLON][WIDTH],
                W_H_MATRIX_SUB_MENU[NMBR_COLON][HEIGHT],
                1);

  switch (setting_index) {
    case SEGMENTS:
      dp.drawBitmap(X_Y_MATRIX_SETTINGS[NMBR_SEGMENTS_OPTION][x],
                    X_Y_MATRIX_SETTINGS[NMBR_SEGMENTS_OPTION][y],
                    BITMAP_SETTINGS_ARRAY[NMBR_SEGMENTS_OPTION],
                    W_H_MATRIX_SETTINGS[NMBR_SEGMENTS_OPTION][WIDTH],
                    W_H_MATRIX_SETTINGS[NMBR_SEGMENTS_OPTION][HEIGHT],
                    1);
      dp.setCursor(82, 15);
      dp.print(number_seg);
      break;

    case FIRMWARE:
      dp.drawBitmap(X_Y_MATRIX_SETTINGS[NMBR_FIRMWARE_OPTION][x],
                    X_Y_MATRIX_SETTINGS[NMBR_FIRMWARE_OPTION][y],
                    BITMAP_SETTINGS_ARRAY[NMBR_FIRMWARE_OPTION],
                    W_H_MATRIX_SETTINGS[NMBR_FIRMWARE_OPTION][WIDTH],
                    W_H_MATRIX_SETTINGS[NMBR_FIRMWARE_OPTION][HEIGHT],
                    1);
      dp.setCursor(82, 15);
      dp.print(RLCV3_FIRMWARE_VERSION);
      break;
    default:
      break;
  }

  switch (current_deepness) {
    case ITEM_SELECTION:
      draw_circle_menu_orientation(dp, LAST_SETTING, 28, setting_index);
      break;
    case VALUE_SELECTION:
      dp.fillRect(81, 21, 47, 2, WHITE);
      // draw lines around values
      break;
    default:
      break;
  }

  // dp.setCursor(62, 28);
  // dp.print(number_seg);
  dp.display();
}

void display_saved_status(Adafruit_SSD1306 &dp) {
  dp.setTextColor(WHITE);
  dp.clearDisplay();
  dp.drawBitmap(X_Y_MATRIX_SUB_MENU[NMBR_SAVED_SCREEN][x],
                X_Y_MATRIX_SUB_MENU[NMBR_SAVED_SCREEN][y],
                BITMAP_SUB_MENU_ARRAY[NMBR_SAVED_SCREEN],
                W_H_MATRIX_SUB_MENU[NMBR_SAVED_SCREEN][WIDTH],
                W_H_MATRIX_SUB_MENU[NMBR_SAVED_SCREEN][HEIGHT],
                1);
  dp.display();
}

// index 0-4
void display_menu(Adafruit_SSD1306 &dp, uint8_t index) {
  // entry zero is the left arrow for indicating left end of menu
  index++;
  int previos = 0;
  int next = 0;
  previos = index - 1;
  if (previos < 0)
    previos = last_menu_index - 1;
  next = index + 1;
  if (next >= last_menu_index)
    next = 0;

  dp.clearDisplay();

  draw_circle_menu_orientation(dp, MAIN_LAST, 28, index - 1);
  // dp.drawBitmap(2, 30, BITMAP_SCROLLBAR, 123, 1, 1);
  dp.drawBitmap(44, 1, BITMAP_MAIN_MENU_SEL, 40, 23, 1);
  // dp.drawBitmap(6 + previos * 24, 29, BITMAP_SCROLLBAR_HANDLE, 7, 3, 1);

  dp.drawBitmap(X_Y_MATRIX_MAIN_MENU[MENU_ORDER[previos]][x] - 42,
                X_Y_MATRIX_MAIN_MENU[MENU_ORDER[previos]][y],
                BITMAP_MAIN_MENU_ARRAY[MENU_ORDER[previos]],
                W_H_MATRIX_MAIN_MENU[MENU_ORDER[previos]][WIDTH],
                W_H_MATRIX_MAIN_MENU[MENU_ORDER[previos]][HEIGHT],
                1);
  dp.drawBitmap(X_Y_MATRIX_MAIN_MENU[MENU_ORDER[index]][x],
                X_Y_MATRIX_MAIN_MENU[MENU_ORDER[index]][y],
                BITMAP_MAIN_MENU_ARRAY[MENU_ORDER[index]],
                W_H_MATRIX_MAIN_MENU[MENU_ORDER[index]][WIDTH],
                W_H_MATRIX_MAIN_MENU[MENU_ORDER[index]][HEIGHT],
                1);
  dp.drawBitmap(X_Y_MATRIX_MAIN_MENU[MENU_ORDER[next]][x] + 42,
                X_Y_MATRIX_MAIN_MENU[MENU_ORDER[next]][y],
                BITMAP_MAIN_MENU_ARRAY[MENU_ORDER[next]],
                W_H_MATRIX_MAIN_MENU[MENU_ORDER[next]][WIDTH],
                W_H_MATRIX_MAIN_MENU[MENU_ORDER[next]][HEIGHT],
                1);

  dp.display();
}

void display_artnet_rec(Adafruit_SSD1306 &dp, rlc_artnet artnet_var, uint8_t menu_index) {
  uint16_t start_channel = artnet_var.get_start_channel();
  uint16_t end_channel = artnet_var.get_end_channel();
  uint16_t start_universe = artnet_var.get_start_universe();
  uint16_t end_universe = artnet_var.get_end_universe();
  uint8_t mode = artnet_var.get_current_sel();
  uint8_t dots = artnet_var.get_number_dots();
  uint8_t w_start = 48;
  int16_t x1, y1;
  uint16_t w, h;
  uint8_t offset_uni = 8;
  uint8_t offset_chan = 8;

  dp.clearDisplay();
  dp.setTextColor(WHITE);
  dp.stopscroll();

  if (mode != IP_ADDRESS) {
    switch (dots) {
      case 1:
        dp.drawBitmap(X_Y_MATRIX_ICONS[WIFI_SYMBOL_1][x],
                      X_Y_MATRIX_ICONS[WIFI_SYMBOL_1][y],
                      BITMAP_ICONS_ARRAY[WIFI_SYMBOL_1],
                      W_H_MATRIX_ICONS[WIFI_SYMBOL_1][WIDTH],
                      W_H_MATRIX_ICONS[WIFI_SYMBOL_1][HEIGHT],
                      1);
        break;
      case 2:
        dp.drawBitmap(X_Y_MATRIX_ICONS[WIFI_SYMBOL_2][x],
                      X_Y_MATRIX_ICONS[WIFI_SYMBOL_2][y],
                      BITMAP_ICONS_ARRAY[WIFI_SYMBOL_2],
                      W_H_MATRIX_ICONS[WIFI_SYMBOL_2][WIDTH],
                      W_H_MATRIX_ICONS[WIFI_SYMBOL_2][HEIGHT],
                      1);
        break;
      case 3:
        dp.drawBitmap(X_Y_MATRIX_ICONS[WIFI_SYMBOL_3][x],
                      X_Y_MATRIX_ICONS[WIFI_SYMBOL_3][y],
                      BITMAP_ICONS_ARRAY[WIFI_SYMBOL_3],
                      W_H_MATRIX_ICONS[WIFI_SYMBOL_3][WIDTH],
                      W_H_MATRIX_ICONS[WIFI_SYMBOL_3][HEIGHT],
                      1);
        break;
      default:
        dp.drawBitmap(X_Y_MATRIX_ICONS[WIFI_SYMBOL_3][x],
                      X_Y_MATRIX_ICONS[WIFI_SYMBOL_3][y],
                      BITMAP_ICONS_ARRAY[WIFI_SYMBOL_3],
                      W_H_MATRIX_ICONS[WIFI_SYMBOL_3][WIDTH],
                      W_H_MATRIX_ICONS[WIFI_SYMBOL_3][HEIGHT],
                      1);
        break;
    }

    dp.drawBitmap(X_Y_MATRIX_SUB_MENU[NMBR_ARTNET_REC_PAGE][x],
                  X_Y_MATRIX_SUB_MENU[NMBR_ARTNET_REC_PAGE][y],
                  BITMAP_SUB_MENU_ARRAY[NMBR_ARTNET_REC_PAGE],
                  W_H_MATRIX_SUB_MENU[NMBR_ARTNET_REC_PAGE][WIDTH],
                  W_H_MATRIX_SUB_MENU[NMBR_ARTNET_REC_PAGE][HEIGHT],
                  1);

    String buf_uni = String("U:");
    String buf_address = String("C:");

    switch (mode) {
      case UNIVERSE:
        dp.setCursor(2, 28);
        dp.print(buf_uni);
        dp.setCursor(23, 28);
        buf_uni = String(start_universe) + String("-") + String(end_universe);
        dp.print(buf_uni);
        break;

      case CHANNEL:
        dp.setCursor(2, 28);
        dp.print(buf_address);
        dp.setCursor(23, 28);
        buf_address = String(start_channel) + String("-") + String(end_channel);
        dp.print(buf_address);
        break;
    }
  } else {
    String ip = String("IP:");
    if (artnet_var.get_wifi_status()) {
      ip = String(ip + artnet_var.get_wifi_local_ip());
    } else {
      ip = String(ip + "Not Connected");
    }
    min_x = -12 * ip.length() + SCREEN_WIDTH / 2;
    dp.setCursor(x_scroll, 20);
    dp.print(ip);
  }
  dp.display();
}

void scroll() {
  x_scroll -= 5;
  if (x_scroll < min_x) {
    x_scroll = SCREEN_WIDTH / 3;
  }
}

void display_connecting_artnet(Adafruit_SSD1306 &dp, rlc_artnet artnet_var) {
  uint8_t dots = artnet_var.get_number_dots();
  int16_t x1, y1;
  uint16_t w, h;
  dp.clearDisplay();
  dp.setTextColor(WHITE);

  dp.drawBitmap(X_Y_MATRIX_SUB_MENU[NMBR_ARTNET_REC_PAGE][x],
                X_Y_MATRIX_SUB_MENU[NMBR_ARTNET_REC_PAGE][y],
                BITMAP_SUB_MENU_ARRAY[NMBR_ARTNET_REC_PAGE],
                W_H_MATRIX_SUB_MENU[NMBR_ARTNET_REC_PAGE][WIDTH],
                W_H_MATRIX_SUB_MENU[NMBR_ARTNET_REC_PAGE][HEIGHT],
                1);

  String buf = String("");
  for (int i = 1; i <= dots; i++) {
    buf = String(buf + ".");
  }

  dp.getTextBounds(buf, x, y, &x1, &y1, &w, &h);  // calc width of new string
  dp.setCursor((x - w / 2) + (128 / 2), 28);
  dp.print(buf);

  dp.display();
}

void draw_circle_menu_orientation(Adafruit_SSD1306 &dp, uint8_t n, uint8_t y_position, uint8_t menu_pos) {
  uint16_t center_position = SCREEN_WIDTH / 2;
  uint8_t gap_size = 5;
  uint8_t radius = 2;
  uint8_t diameter = 2 * radius;
  uint16_t start_x_pos = center_position - ((n * radius) + ((float)(n / 2) * gap_size)) + 1;
  // alternative
  // uint16_t start_x_pos = center_position - (((diameter * n) + ((n-1)*gap_size)) / 2) + 1;

  for (uint8_t i = 0; i < n; i++) {
    // void drawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);
    if (i == menu_pos) {
      dp.fillCircle(start_x_pos, y_position, radius, WHITE);
    } else {
      dp.drawCircle(start_x_pos, y_position, radius, WHITE);
    }
    start_x_pos += diameter + gap_size;
  }
}