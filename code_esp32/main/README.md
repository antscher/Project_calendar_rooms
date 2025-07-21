## Overview
An ESP32-based e-paper display system for room availability and scheduling. This system connects to WiFi, communicates via MQTT, and displays room booking information on a Waveshare 7.3" e-Paper display.

## Directory Structure
```
main/
├── src/
│   ├── Config/         # Configuration files
│   ├── e-Paper/       # E-paper display drivers
│   ├── Fonts/         # Font definitions
│   ├── GUI/           # Graphics interface
│   └── Image/         # Image resources
├── calendar.cpp       # Calendar logic implementation
├── calendar.h         # Calendar class definitions
├── interface_graphique.cpp  # Display interface
├── interface_graphique.h    # Display definitions
├── main.ino          # Main program
├── mqtt_communication.ino    # MQTT handling
└── wifi_data.h       # WiFi credentials (to be created)

```
src/ is the library from https://www.waveshare.com/wiki/7.3inch_e-Paper_HAT_(E)_Manual#ESP32.2F8266 -> demo code but it is modified to use dynamics fonts and all of the ASCII characters table

## Setup Instructions

### 1. Create wifi_data.h
Create a new file `/main/wifi_data.h` with your network credentials:

```cpp
#ifndef WIFI_DATA_H
#define WIFI_DATA_H

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_broker = "YOUR_MQTT_BROKER_ADDRESS";
const int mqtt_port = 1883;
const String client_id = "esp32-client-XXXX"; 

// Unique client ID
const char* mqtt_username = "YOUR_MQTT_USERNAME";
const char* mqtt_password = "YOUR_MQTT_PASSWORD";
const char* topic = "room/ROOM_NAME";
const char* topic_reponse = "resp_room/ROOM_NAME";

// Variable of referency
const char name_room_const[] = "ROOM_NAME TO DISPLAY";

#endif
```

### 2. Hardware Requirements
- ESP32-S2 microcontroller
- Waveshare 7.3" e-Paper display
- See Hardware/README.md for detailed specifications

### 3. Software Dependencies
Install this librairies if needed 
- Arduino IDE with ESP32 by espressif in the board manage (especially ESP32 S2 Dev Module) (tested v3.2.0)
- Required Libraries:
  - PubSubClient (tested v2.8)
  - WiFi (built in)
  - SPI (built in)

### 4. Building and Flashing
1. Open the project in Arduino IDE
2. Select ESP32-S2 Dev Module board
3. Install required libraries
4. Compile and upload to ESP32 with parameters of esp 32 as : 
- USB CDC on boot : "Enabeled"
- CPU frequency : "160MHz"
- Core debug "None"
- Erase all flash : "Enabeled" (or "Disabled" for saving NVS memory)
- Flash frequency : "40 MHz"
- Flash Mode : "QIO"
- JTAG Adapter : "Disabeled"
- USB Firmware MSC : "Huge APP (3MB No OTA/1 MB SPIFFS)"
- PSRAM : "Enabeled"
- Upload Mode "UART0"
- Upload Speed : "921600"
- Zigbee Mode : "Disabeled"

## Operation Modes
- **Normal Mode**: Displays room availability and upcoming events
- **Night Mode**: Shows logo and enters deep sleep (20:00-7:00)
- **On Air Mode**: Displays "On Air" sign for broadcasting
- **Error Mode**: Handles connection failures

## MQTT Message Format
Messages follow this structure :
- for a calendar
```
cYYYY-MM-DDTHH:MM[Event1 Description]DD,MM,DD,MM,HH,MM,HH,MM[Event2...]
```
- for other  (the first letter is the screen mode)
```
wYYYY-MM-DDTHH:MM
```
First character indicates mode:
- 'c': Calendar mode
- 'w': White screen (or night mode)
- 'o': On Air mode
- 'e': Error
- 'u': Update room name

## Power Management
- Uses deep sleep between updates
- Wakes up for:
  - Scheduled updates
  - Event start/end times
  - Daily morning activation

## Memory Optimization

To maximize battery life and reliability, the ESP32 firmware now uses RTC memory (`RTC_DATA_ATTR`) to store key variables such as `name_room` and `new_day`. This allows the device to retain these values even during deep sleep cycles, minimizing unnecessary writes to flash and saving power.

- `name_room`: The room name is stored in RTC memory and updated only when needed.
- `new_day`: This variable tracks the battery status and is also stored in RTC memory.

### Battery Reset Procedure

To reset the battery status after a replacement or maintenance:
1. Open the Mosquitto MQTT app.
2. Mode reset battery
3. Press "Save" in the app and then refresh .

