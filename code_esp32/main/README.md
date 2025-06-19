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
const String client_id = "esp32-client-XXXX"; // Unique client ID
const char* mqtt_username = "YOUR_MQTT_USERNAME";
const char* mqtt_password = "YOUR_MQTT_PASSWORD";
const char* topic = "room/calendar/ROOM_NAME";
const char* topic_reponse = "room/calendar/ROOM_NAME/response";

#endif
```

### 2. Hardware Requirements
- ESP32-S2 microcontroller
- Waveshare 7.3" e-Paper display
- See Hardware/README.md for detailed specifications

### 3. Software Dependencies
- Arduino IDE with ESP32 board support (ESP32 S2 Dev kit)
- Required Libraries:
  - PubSubClient (v2.8+)
  - WiFi
  - SPI

### 4. Building and Flashing
1. Open the project in Arduino IDE
2. Select ESP32-S2 Dev kit board
3. Install required libraries
4. Compile and upload to ESP32

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
- 'w': White screen (night mode)
- 'o': On Air mode
- 'e': Error
- 'u': Update room name

## Power Management
- Uses deep sleep between updates
- Wakes up for:
  - Scheduled updates
  - Event start/end times
  - Daily morning activation
