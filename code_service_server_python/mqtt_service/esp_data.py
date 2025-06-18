# esp_data.py

import json
import datetime
from google_agenda import actualDate


ESP_FILE = "C:/Users/Antoine.Scherpereel/Documents/Mqtt/esp_data.json"

#******************************************************************************
# function:    load_data
# parameter:
#    None
# return:
#    dict : JSON data from ESP_FILE or empty dictionary if file not found
#******************************************************************************
def load_data():
    try:
        with open(ESP_FILE, 'r') as f:
            return json.load(f)
    except FileNotFoundError:
        return {}

#******************************************************************************
# function:    save_data
# parameter:
#    data : Dictionary containing ESP device information to save
# return:
#    None
#******************************************************************************
def save_data(data):
    with open(ESP_FILE, 'w') as f:
        json.dump(data, f, indent=4)

#******************************************************************************
# function:    update_esp_info
# parameter:
#    esp_id : String identifier for the ESP device
#    battery_value : Integer battery status value (1 to increment, 2 to reset)
# return:
#    None
#******************************************************************************
def update_esp_info(esp_id, battery_value):
    data = load_data()

    if esp_id not in data:
        print(f"{esp_id} not found in {ESP_FILE}, creating new entry.")
        data[esp_id] = {
            "name_room": f"{esp_id}",
            "battery": 0,
            "last_update": actualDate(),
            "screen": "whiteboard",
        }
        data = dict(sorted(data.items()))
    else:
        if int(battery_value) == 1 :
            data[esp_id]["battery"] += 1
        elif int(battery_value) == 2:
            data[esp_id]["battery"] = 0
        data[esp_id]["last_update"] = actualDate()

    save_data(data)
    print(f"{esp_id} updated: battery={battery_value}")

#******************************************************************************
# function:    update_action
# parameter:
#    esp_id : String identifier for the ESP device
#    screen_value : String value to update the screen state
# return:
#    None
#******************************************************************************
def update_action(esp_id, screen_value):
    data = load_data()
    data[esp_id]["screen"] = screen_value
    save_data(data)
