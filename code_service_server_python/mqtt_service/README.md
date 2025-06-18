# 📡 MQTT Calendar Service

A Python-based MQTT service by **Antscher** that manages communication between ESP32 devices and Google Calendar.

This service handles:
- MQTT broker communication
- Google Calendar integration
- ESP32 device state management
- Screen mode control

---

## 🚀 Features

- 🔄 **MQTT Communication**  
  Handles bi-directional communication with ESP32 devices.

- 📅 **Google Calendar Integration**  
  Fetches and formats calendar events for display.

- 🔋 **Battery Management**  
  Tracks and stores ESP32 device battery status.

- 🖥️ **Screen Mode Control**  
  Manages different display modes (calendar, whiteboard, on air).

---

## ⚙️ Requirements

- Python 3.7+
- paho-mqtt
- google-api-python-client
- oauth2client
- python-dotenv

## 🛠️ Configuration

1. Set up `.env` file with MQTT broker details
2. Configure `credentials.json` for Google Calendar API
3. Ensure `token.json` is present for OAuth2 authentication

### Environment Variables (.env)

Create a `.env` file with the following configuration:

```properties
# MQTT Broker Configuration
USE_LOCAL=false           # Set to true for local broker, false for remote
BROKER_LOCAL=localhost    # Local broker address
BROKER_IP=your.broker.ip  # Remote broker IP/hostname
PORT=1883                 # MQTT broker port
TOPIC=room/#             # Topic pattern to subscribe to
USERMQTT=your_username   # MQTT authentication username
PASSWORD=your_password   # MQTT authentication password
```

- `USE_LOCAL`: Toggle between local and remote broker
- `BROKER_LOCAL`: Address for local MQTT broker
- `BROKER_IP`: Address for remote MQTT broker
- `PORT`: Port number for MQTT connection
- `TOPIC`: MQTT topic pattern for device communication
- `USERMQTT`: Username for MQTT authentication
- `PASSWORD`: Password for MQTT authentication

## 📁 Project Structure

mqtt_service/
│
├── communication_mqtt.py   # Main MQTT handler
├── google_agenda.py       # Google Calendar integration
├── esp_data.py           # ESP device state management
├── credentials.json      # Google API credentials
├── token.json           # OAuth2 tokens
└── .env                 # Environment configuration

## 🔐 Security
- Secure MQTT credentials
- OAuth2 authentication for Google Calendar
- Local JSON storage for device data

## 🧑‍💻 Author
Made with 🧠 by Antscher
