# ArduinoPcap
Create and send .pcap files using ESP8266/ESP32 and Arduino.

[![Sniffing WiFi with ESP32 & ESP8266 in Wireshark](https://img.youtube.com/vi/3Ac6X6ZBQ0g/0.jpg)](https://www.youtube.com/watch?v=3Ac6X6ZBQ0g)  

## Please Note

This is a proof of concept! The included examples are only for ESP8266 and ESP32, but the library can be used for other Arduinos as well. The packet output in the examples is unfiltered and maybe malformed, **errors can occur!**  

Also a big thanks to [xdavidhu](http://github.com/xdavidhu) for writing the python script to connect to Wireshark!  

## Installation

Download this project and extract the .zip file to the Arduino `libraries` folder.  
For more information please read [Installing Additional Arduino Libraries](https://www.arduino.cc/en/Guide/Libraries).  

### Dependencies

Following Arduino libraries are required for the included examples:
- [Arduino Time Library](https://github.com/PaulStoffregen/Time) (for all examples)  
- [ESP32](https://github.com/espressif/arduino-esp32) (for the `esp32_*` examples)  

For the Serialshark script (the script located in `extras`):
  - [python3](https://www.python.org/downloads/)
  - [pyserial](https://github.com/pyserial/pyserial)  
  - [Wireshark](https://www.wireshark.org/#download)

**Please be aware that the Serialshark script doesn't work on Windows!**

## Usage

### General

To open one of the examples open Arduino and go to `File`>`Examples`>`Arduino Pcap`.  
You might want to adjust the settings in the sketch (settings may be different depending on the example):  
```
//===== SETTINGS =====//
#define CHANNEL 1
#define FILENAME "esp32"
#define SAVE_INTERVAL 30 //save new file every 30s
#define CHANNEL_HOPPING true //if true it will scan on all channels
#define MAX_CHANNEL 11 //(only necessary if channelHopping is true)
#define HOP_INTERVAL 214 //in ms (only necessary if channelHopping is true)
```
### Live capture using Wireshark

You also live capture the packets in Wireshark over the serial connection!  
For that be sure to have everything installed - see [Dependencies](#dependencies).  

Flash your device and be sure it is connected.  
Then start the `SerialShark.py` (it's in the `extras` folder) with `python3 SerialShark.py`.  
It will ask you about about the serial port (you have to find that out), the baud rate (be sure it's the same as in your sketch) and where to save the pcap file (wherever you want).  

The baudrate for the ESP32 example is `921600`.

## License

This project is licensed under the MIT License - see the [license file](LICENSE) for details.
