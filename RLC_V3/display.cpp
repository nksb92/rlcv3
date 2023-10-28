#include "display.h"
#include "bitmaps.h"

uint8_t offset = 5;
uint8_t offset_y = 26;
uint8_t last_index = 0;

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

void seg_display_update(Adafruit_SSD1306& dp, segments seg){
  uint16_t number_seg = seg.get_num_seg();
  dp.clearDisplay();
  dp.setTextColor(WHITE);
  dp.drawBitmap(X_Y_MATRIX_SUB_MENU[NMBR_SEGMENTS_PAGE][x],
                X_Y_MATRIX_SUB_MENU[NMBR_SEGMENTS_PAGE][y],
                BITMAP_SUB_MENU_ARRAY[NMBR_SEGMENTS_PAGE],
                W_H_MATRIX_SUB_MENU[NMBR_SEGMENTS_PAGE][WIDTH],
                W_H_MATRIX_SUB_MENU[NMBR_SEGMENTS_PAGE][HEIGHT],
                1);
  dp.setCursor(62,29);
  dp.print(number_seg);
  dp.display();
}

void display_saved_status(Adafruit_SSD1306& dp) {
  dp.setTextColor(WHITE);
  dp.clearDisplay();
  dp.setCursor(offset + 10, offset_y - 10);
  dp.print("|>SAVED<|");
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