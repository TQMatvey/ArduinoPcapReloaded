/*
  ===========================================
       Copyright (c) 2017 Stefan Kremser
              github.com/spacehuhn
  ===========================================
*/


/* include all necessary libraries */ 
#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_wifi_internal.h"
#include "lwip/err.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

#include <Arduino.h>
#include <TimeLib.h>
#include <PCAP.h>


//===== SETTINGS =====//
#define CHANNEL 1
#define BAUD_RATE 921600
#define CHANNEL_HOPPING false //if true it will scan on all channels
#define MAX_CHANNEL 11 //(only necessary if channelHopping is true)
#define HOP_INTERVAL 214 //in ms (only necessary if channelHopping is true)

//===== Run-Time variables =====//
PCAP pcap = PCAP();
int ch = CHANNEL;
unsigned long lastChannelChange = 0;

//===== FUNCTIONS =====//

/* will be executed on every packet the ESP32 gets while beeing in promiscuous mode */
void sniffer(void *buf, wifi_promiscuous_pkt_type_t type){
  wifi_promiscuous_pkt_t* pkt = (wifi_promiscuous_pkt_t*)buf;
  wifi_pkt_rx_ctrl_t ctrl = (wifi_pkt_rx_ctrl_t)pkt->rx_ctrl;
  
  uint32_t timestamp = now(); //current timestamp 
  uint32_t microSeconds = micros(); // e.g. 45200400 => 45s 200ms 400us
  uint32_t seconds = (microSeconds/1000)/1000; // e.g. 45200400/1000/1000 = 45200 / 1000 = 45s

  microSeconds -= seconds*1000*1000; // e.g. 45200400 - 45*1000*1000 = 45200400 - 45000000 = 400us (because we only need the offset)
  
  pcap.newPacketSerial(timestamp, microSeconds, ctrl.sig_len, pkt->payload); //send packet via Serial 
}

esp_err_t event_handler(void *ctx, system_event_t *event){ return ESP_OK; }


//===== SETUP =====//
void setup() {

  /* start Serial */
  Serial.begin(BAUD_RATE);
  delay(2000);
  Serial.println();
  
  Serial.println("<<START>>");
  pcap.startSerial();
  
  wifi_second_chan_t secondCh = (wifi_second_chan_t)NULL;
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  esp_wifi_init(&cfg);
  esp_wifi_set_storage(WIFI_STORAGE_RAM);
  esp_wifi_set_mode(WIFI_MODE_NULL);
  esp_wifi_start();
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_promiscuous_rx_cb(sniffer);
  esp_wifi_set_channel(ch,secondCh);
}

//===== LOOP =====//
void loop() {
  
  /* Channel Hopping */
  if(CHANNEL_HOPPING){
    unsigned long currentTime = millis();
    if(currentTime - lastChannelChange >= HOP_INTERVAL){
      lastChannelChange = currentTime;
      ch++; //increase channel
      if(ch > MAX_CHANNEL) ch = 1;
      wifi_second_chan_t secondCh = (wifi_second_chan_t)NULL;
      esp_wifi_set_channel(ch,secondCh);
    }
  }
  
}