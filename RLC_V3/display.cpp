#include <algorithm>
#include "WString.h"
#include "display.h"
#include "bitmaps.h"

uint8_t offset = 5;
uint8_t offset_y = 26;
uint8_t last_index = 0;
int x_scroll = 0;
int min_x = 0;

void init_display(Adafruit_SSD1306& dp) {
  dp.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  dp.clearDisplay();
  dp.setTextSize(1);
  dp.setTextColor(WHITE);
  dp.setFont(&FreeMonoBold9pt7b);
  dp.display();
  dp.setTextWrap(false);
  x_scroll = SCREEN_WIDTH / 3;
}

void hsv_display_update(Adafruit_SSD1306& dp, C_HSV out_val) {
  uint8_t hue = out_val.get_hue();
  uint8_t sat_p = out_val.get_sat_p();
  uint8_t val_p = out_val.get_val_p();
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
  dp.print(sat_p);
  dp.setCursor(2 * spacing + offset, offset_y);
  dp.print(val_p);
  dp.display();
}

void rgb_display_update(Adafruit_SSD1306& dp, C_RGB rgb_val) {
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

void dmx_display_update(Adafruit_SSD1306& dp, rgb_dmx dmx_val) {
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
  dp.getTextBounds(buf, x, y, &x1, &y1, &w, &h);  //calc width of new string
  dp.setCursor((x - w / 2) + (128 / 2), 28);
  dp.print(buf);
  dp.display();
}

void seg_display_update(Adafruit_SSD1306& dp, segments seg) {
  uint16_t number_seg = seg.get_num_seg();
  dp.clearDisplay();
  dp.setTextColor(WHITE);
  dp.drawBitmap(X_Y_MATRIX_SUB_MENU[NMBR_SEGMENTS_PAGE][x],
                X_Y_MATRIX_SUB_MENU[NMBR_SEGMENTS_PAGE][y],
                BITMAP_SUB_MENU_ARRAY[NMBR_SEGMENTS_PAGE],
                W_H_MATRIX_SUB_MENU[NMBR_SEGMENTS_PAGE][WIDTH],
                W_H_MATRIX_SUB_MENU[NMBR_SEGMENTS_PAGE][HEIGHT],
                1);
  dp.setCursor(62, 28);
  dp.print(number_seg);
  dp.display();
}

void display_saved_status(Adafruit_SSD1306& dp) {
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

void display_menu(Adafruit_SSD1306& dp, uint8_t index) {
  int previos = 0;
  int next = 0;
  previos = index - 1;
  if (previos < 0) previos = BITMAP_MAIN_MENU_LEN - 1;
  next = index + 1;
  if (next >= BITMAP_MAIN_MENU_LEN) next = 0;

  dp.clearDisplay();

  dp.drawBitmap(2, 30, BITMAP_SCROLLBAR, 123, 1, 1);
  dp.drawBitmap(44, 2, BITMAP_MAIN_MENU_SEL, 40, 26, 1);
  dp.drawBitmap(6 + index * 22, 29, BITMAP_SCROLLBAR_HANDLE, 7, 3, 1);

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

void display_artnet_rec(Adafruit_SSD1306& dp, rlc_artnet artnet_var) {
  uint16_t start_channel = artnet_var.get_start_channel();
  uint16_t end_channel = artnet_var.get_end_channel();
  uint16_t start_universe = artnet_var.get_start_universe();
  uint16_t end_universe = artnet_var.get_end_universe();
  uint8_t mode = artnet_var.get_current_sel();
  uint8_t w_start = 48;
  int16_t x1, y1;
  uint16_t w, h;
  uint8_t offset_uni = 8;
  uint8_t offset_chan = 8;

  dp.clearDisplay();
  dp.setTextColor(WHITE);
  dp.stopscroll();

  if (mode != IP_ADDRESS) {
    if (start_universe > 9 || end_universe > 9) {
      offset_uni = 20;
    }

    if (start_channel > 9 || end_channel > 9) {
      offset_chan = 20;
    }
    if (start_channel > 99 || end_channel > 99) {
      offset_chan = 32;
    }

    String buf_end = String("END");
    String start = String("STRT ");

    switch (mode) {
      case UNIVERSE:
        dp.setCursor(3, 12);
        dp.print(start);
        dp.fillRoundRect(w_start + 3, 0, 25, 14, 3, WHITE);
        dp.setTextColor(BLACK);
        dp.getTextBounds(String(start_universe), x, y, &x1, &y1, &w, &h);
        dp.setCursor(w_start + (14 - offset_uni / 2), 12);
        dp.print(String(start_universe));
        dp.setTextColor(WHITE);
        dp.setCursor(w_start + 3 + 25, 12);
        dp.print(":");
        dp.setCursor(w_start + 5 + 25 + 2 + 3 + 2 + (18 - offset_chan / 2), 12);
        dp.print(start_channel);
        break;
      case CHANNEL:
        dp.setCursor(3, 12);
        dp.print(start);
        dp.getTextBounds(String(start_universe), x, y, &x1, &y1, &w, &h);
        dp.setCursor(w_start + (14 - offset_uni / 2), 12);
        dp.print(String(start_universe));
        dp.setCursor(w_start + 3 + 25, 12);
        dp.print(":");
        dp.fillRoundRect(w_start + 5 + 25 + 3 + 2 + 3, 0, 35, 14, 3, WHITE);
        dp.setTextColor(BLACK);
        dp.setCursor(w_start + 5 + 25 + 2 + 3 + 2 + (18 - offset_chan / 2), 12);
        dp.print(start_channel);
        dp.setTextColor(WHITE);
        break;
    }
    dp.setCursor(3, 28);
    dp.print(buf_end);
    dp.getTextBounds(String(end_universe), x, y, &x1, &y1, &w, &h);
    dp.setCursor(w_start + (14 - offset_uni / 2), 28);
    dp.print(String(end_universe));
    dp.setCursor(w_start + 3 + 25, 28);
    dp.print(":");
    dp.setCursor(w_start + 5 + 25 + 2 + 3 + 2 + (18 - offset_chan / 2), 28);
    dp.print(end_channel);
  } else {
    String ip = String("IP:");
    ip = String(ip + artnet_var.get_wifi_local_ip());
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

void display_connecting_artnet(Adafruit_SSD1306& dp, rlc_artnet artnet_var) {
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

  dp.getTextBounds(buf, x, y, &x1, &y1, &w, &h);  //calc width of new string
  dp.setCursor((x - w / 2) + (128 / 2), 28);
  dp.print(buf);

  dp.display();
}
