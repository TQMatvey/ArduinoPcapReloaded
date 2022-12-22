#include "PCAP.h"

/* Create PCAP instance */
PCAP::PCAP() {
}

/* send file header to Serial */
void PCAP::startSerial(){
  serialwrite_32(magic_number);
  serialwrite_16(version_major);
  serialwrite_16(version_minor);
  serialwrite_32_int32_t(thiszone);
  serialwrite_32(sigfigs);
  serialwrite_32(snaplen);
  serialwrite_32(network);
}

/* write packet to Serial */
void PCAP::newPacketSerial(uint32_t ts_sec, uint32_t ts_usec, uint32_t len, uint8_t* buf){
  uint32_t orig_len = len;
  uint32_t incl_len = len;
  
#if defined(ESP32)
  if(incl_len > snaplen) incl_len = snaplen; /* safty check that the packet isn't too big (I ran into problems with the ESP8266 here) */
#endif
  serialwrite_32(ts_sec);
  serialwrite_32(ts_usec);
  serialwrite_32(incl_len);
  serialwrite_32(orig_len);
  
  Serial.write((uint8_t*)buf, incl_len);
}

/* converts a 32 bit integer into 4 bytes */
void PCAP::escape32_int32_t(int32_t n, uint8_t* buf){
  buf[0] = n;
  buf[1] = n >>  8;
  buf[2] = n >> 16;
  buf[3] = n >> 24;
}

/* converts a 32 bit integer into 4 bytes */
void PCAP::escape32(uint32_t n, uint8_t* buf){
  buf[0] = n;
  buf[1] = n >>  8;
  buf[2] = n >> 16;
  buf[3] = n >> 24;
}

/* converts a 16 bit integer into 2 bytes */
void PCAP::escape16(uint16_t n, uint8_t* buf){
  buf[0] = n;
  buf[1] = n >>  8;
}

/* writes a 32 bit integer to Serial */
void PCAP::serialwrite_32_int32_t(int32_t n){
  uint8_t _buf[4];
  escape32_int32_t(n, _buf);
  Serial.write(_buf, 4);
}

/* writes a 32 bit integer to Serial */
void PCAP::serialwrite_32(uint32_t n){
  uint8_t _buf[4];
  escape32(n, _buf);
  Serial.write(_buf, 4);
}

/* writes a 16 bit integer to Serial */
void PCAP::serialwrite_16(uint16_t n){
  uint8_t _buf[2];
  escape16(n, _buf);
  Serial.write(_buf, 2);
}

