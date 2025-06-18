# 🗓️ Room Control Web App

A local Flask web app by **Antscher** to manage and control multiple calendar-enabled display screens in different rooms.

This app allows you to:
- View info
- Set and update room names
- Assign or change screen display modes
- Configure individual calendar URLs
- Generate and display QR codes for easy mobile access

---

## 🚀 Features

- 📺 **Screen Mode Selector**  
  Choose the display mode for each screen (agenda, standby, status…).

- 🏷️ **Custom Room Names**  
  Easily rename rooms via the web interface.

- 🔗 **Calendar URL Configuration**  
  Assign custom ICS / Google Calendar URLs to each room for event syncing.

- 📱 **QR Code Generator**  
  Automatically generate a QR code for arduino in C++

- 💾 **Data Persistence**  
  All configurations are stored in a JSON file (`esp_data.json`) for consistent behavior after reboot.

---

## ⚙️ Requirements

- Python 3.7+
- Flask
- qrcode
- Pillow

## 🛠️ How It Works
Launch the app:
python app.py

Access the local web interface at:
http://localhost:5000

## 📁 Project Structure

project/
│
├── app.py                 # Main Flask app
├── esp_data.json          # JSON database of all ESP screen data
├── qr_code_generator      # Generate QR code for esp with URls
├── templates/             # HTML templates
├── tmp/                   # Where C++ files are stored
└── static/                # javascript and CSS 


## 🔐 Security
The app is designed for local network use only.

## 🧑‍💻 Author
Made with 🧠 by Antscher

---

# Web Local Console

A Flask web application for managing ESP device configurations and calendars.

## Setup

1. Install required packages:
```bash
pip install flask python-dotenv
```

2. Create a `.env` file in the project root with the following variables:
```
USERNAME=your_username
PASSWORD=your_password
DATA_FILE=/path/to/esp_data.json
FLASK_HOST=0.0.0.0
FLASK_PORT=5000
```

## Environment Variables

- `USERNAME`: Authentication username for accessing the web interface
- `PASSWORD`: Authentication password for accessing the web interface
- `DATA_FILE`: Path to the JSON file storing ESP device data
- `FLASK_HOST`: Host address for the Flask server (default: 0.0.0.0)
- `FLASK_PORT`: Port number for the Flask server (default: 5000)

## Running the Application

Start the server:
```bash
python app.py
```

The web interface will be available at `http://<FLASK_HOST>:<FLASK_PORT>`

## Features

- ESP device management and status monitoring
- Calendar configuration and QR code generation
- Basic authentication for secure access