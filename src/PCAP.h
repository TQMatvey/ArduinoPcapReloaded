#ifndef PCAP_h
#define PCAP_h

#include <Arduino.h>

class PCAP
{
  public:
    PCAP();
	
    void startSerial();
    void newPacketSerial(uint32_t ts_sec, uint32_t ts_usec, uint32_t len, uint8_t* buf);

    uint32_t magic_number = 0xa1b2c3d4;
    uint16_t version_major = 2;
    uint16_t version_minor = 4;
    int32_t thiszone = 0;
    uint32_t sigfigs = 0;
    uint32_t snaplen = 2324;
    uint32_t network = 105;

  private:

    void escape32_int32_t(int32_t n, uint8_t* buf);
    void escape32(uint32_t n, uint8_t* buf);
    void escape16(uint16_t n, uint8_t* buf);
    
    void serialwrite_16(uint16_t n);
    void serialwrite_32(uint32_t n);
    void serialwrite_32_int32_t(int32_t n);
};

#endif