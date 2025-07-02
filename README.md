# Room Calendar Management System

## Project Overview
The Room Calendar Management System is a modern solution for managing meeting room availability using IoT devices. The system combines hardware displays mounted outside each room with a centralized software management platform.

## Project Goals
- Eliminate double-bookings and confusion around room availability
- Provide real-time room status information
- Reduce energy consumption with e-ink displays
- Enable easy room booking directly from the display (by Qr code) or web interface
- Integrate with existing calendar systems

## System Architecture

### Hardware Components
1. **Room Displays**
   - ESP32-S2 microcontroller
   - Waveshare E-ink display
   - Non - Rechargeable battery system
   - QR code for booking

2. **Server Infrastructure**
   - Central management server
   - WiFi network integration

### Software Components
1. **Backend System**
   - Room management
   - Booking system
   - User authentication
   - Calendar integration

2. **Frontend Interfaces**
   - Web dashboard for administrators
   - Display interface for e-ink screens

## Key Features
- Real-time room availability display
- Direct booking from room displays
- Low-power operation with years of battery life
- Calendar synchronization
- Administrative dashboard

## Expected Benefits
- Improved room utilization
- Reduced booking conflicts
- Enhanced user experience
- Energy-efficient operation

## Project Structure
```
Project_calendar_rooms/
├── code_esp32/                      # ESP32 firmware and related tools
|   ├── font2bytes-dynamics/         # Tool for converting fonts to byte arrays
│   └── main/                        # Main ESP32 application code
├── Hardware/                        # Hardware design files
│   ├── cadre room V_.svg/           # Display frame design (version _)
│   ├── Support cadre V_.stl/        # Support of the cadre to be print in 3d (version _)
│   └── esp32 room pcb/              # Custom PCB design for ESP32
└── code_service_server_python/      # Server-side Python applications
    ├── mqtt_service/                # MQTT broker and message handling service
    └── web_local_consol/            # Local web console for room management
```

## License
This project is licensed under GNU GENERAL PUBLIC LICENSE V3 - see the LICENSE.md file for details.

## Main Contributor
This project was developed by Antoine Scherpereel as part of an intership project at ISU (International Space University).

For questions or support, contact:
- Antoine Scherpereel
- Email: antoine.scherpereel@isunet.edu
