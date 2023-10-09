#ifndef ESP_NOW_H
#define ESP_NOW_H

#include "common.h"
#include <esp_now.h>
#include <WiFi.h>
#include "dmx.h"

void sender_init();

void sender_deinit();

void send(rgb_dmx& dmx_mess);

void receiver_init();

void receiver_deinit();

void receive(const uint8_t *mac, const uint8_t *incoming_data, int len);

void get_received_data(rgb_dmx& dmx_mess);

#endif