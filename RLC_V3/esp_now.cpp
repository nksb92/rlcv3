#include "esp_now.h"
#define BYTES_TRANSMIT_NMBR 41

uint8_t broadcast_addresses[10][6] = {
  { 0x34, 0x85, 0x18, 0x26, 0xE2, 0xB8 },
  { 0x34, 0x85, 0x18, 0x26, 0x45, 0x78 },
  { 0x34, 0x85, 0x18, 0x25, 0x31, 0xE8 },
  { 0x34, 0x85, 0x18, 0x26, 0x29, 0xC0 },
  { 0x34, 0x85, 0x18, 0x26, 0xE9, 0xDC },
  { 0x34, 0x85, 0x18, 0x25, 0x3A, 0x7C },
  { 0x34, 0x85, 0x18, 0x26, 0xE1, 0xC8 },
  { 0x34, 0x85, 0x18, 0x25, 0x68, 0xBC },
  { 0x34, 0x85, 0x18, 0x26, 0x2D, 0x98 },
  { 0x34, 0x85, 0x18, 0x26, 0xEA, 0x3C }
};
uint8_t sending_data[BYTES_TRANSMIT_NMBR];  // byte 0 is not used for DMX therefore we need a length of 41 for the first 40 Bytes
uint8_t receiving_data[BYTES_TRANSMIT_NMBR];
esp_now_peer_info_t peer_info;

#define NUMBER_BYTES_SENDING (sizeof(sending_data) / sizeof(sending_data[0]))

void sender_init() {
  // station mode
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ERROR: initializing ESP-NOW as SENDER.");
  } else {
    Serial.println("INFO: initialized ESP-NOW as SENDER.");
    peer_info.channel = 0;
    peer_info.encrypt = false;

    for (uint8_t* address : broadcast_addresses) {
      memcpy(peer_info.peer_addr, address, 6);

      // print the current mac address
      char macStr[18];
      snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", address[0], address[1], address[2], address[3], address[4], address[5]);
      Serial.println(macStr);

      if (esp_now_add_peer(&peer_info) != ESP_OK) {
        Serial.println("ERROR: Adding peer to ESP-NOW.");
      }
    }
  }
}

void sender_deinit() {
  if (esp_now_deinit() != ESP_OK) {
    Serial.println("ERROR: deinitializing ESP-NOW SENDER.");
  } else {
    Serial.println("INFO: deinitialized ESP-NOW SENDER.");
  }
}

void send(rgb_dmx& dmx_mess) {
  for (uint8_t i = 0; i < NUMBER_BYTES_SENDING; i++) {
    sending_data[i] = dmx_mess.get_data(i);
  }
  // for (uint8_t data : sending_data){
  //   Serial.print(data);
  //   Serial.print(", ");
  // }
  // Serial.println("");

  // with peer Addr 0: send to all -> broadcast
  esp_now_send(0, (uint8_t*)&sending_data, sizeof(sending_data));
}

void receiver_init() {
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ERROR: initializing ESP-NOW as RECEIVER.");
  } else {
    Serial.println("INFO: initialized ESP-NOW as RECEIVER.");
    esp_now_register_recv_cb(receive);
    for (uint8_t i = 0; i < NUMBER_BYTES_SENDING; i++) {
      receiving_data[i] = 0;
    }
  }
}

void receiver_deinit() {
  if (esp_now_deinit() != ESP_OK) {
    Serial.println("ERROR: deinitializing ESP-NOW RECEIVER.");
  } else {
    Serial.println("INFO: deinitialized ESP-NOW RECEIVER.");
  }
}

void receive(const uint8_t* mac, const uint8_t* incoming_data, int len) {
  memcpy(&receiving_data, incoming_data, sizeof(receiving_data));
}

void get_received_data(rgb_dmx& dmx_mess) {
  for (uint8_t i = 0; i < NUMBER_BYTES_SENDING; i++) {
    dmx_mess.set_data(receiving_data[i], i);
  }
}