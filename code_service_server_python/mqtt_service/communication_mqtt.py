import os
from dotenv import load_dotenv
import paho.mqtt.client as mqtt
from google_agenda import import_calendar, actualDate
import time
from esp_data import update_esp_info,load_data, update_action
import sys
sys.stdout.reconfigure(line_buffering=True)  

def main():
    # --- Load environment variables ---
    load_dotenv()

    # --- Dynamic configuration via .env ---
    USE_LOCAL = os.getenv("USE_LOCAL", "true").lower() == "true"
    BROKER = os.getenv("BROKER_LOCAL") if USE_LOCAL else os.getenv("BROKER_IP")
    PORT = int(os.getenv("PORT", 1883))
    TOPIC = os.getenv("TOPIC")
    USERMQTT = os.getenv("USERMQTT")
    PASSWORD = os.getenv("PASSWORD")

    
    #******************************************************************************
    # function:    on_connect
    # parameter:
    #    client : MQTT client instance
    #    userdata : Private user data
    #    flags : Response flags sent by broker
    #    rc : Connection result code
    # return:
    #    None
    #******************************************************************************
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Successfully connected to the broker")
            # Subscribe to all topics starting with test
            client.subscribe(TOPIC)
        else:
            print(f"Connection error: code {rc}")

    #******************************************************************************
    # function:    on_message
    # parameter:
    #    client : MQTT client instance
    #    userdata : Private user data
    #    msg : Message received from broker containing topic and payload
    # return:
    #    None
    #******************************************************************************
    def on_message(client, userdata, msg):
        print(f"Message received on {msg.topic} : {msg.payload.decode()}")

        # Check if the message is sent from the ESP32 (b/ for battery)
        if not msg.topic.startswith("resp_"):

            esp_id = msg.topic.split('/')[1]
            esp_key = f"{esp_id}"

            # Mise à jour de la batterie
            battery_value = msg.payload.decode()
            update_esp_info(esp_id=esp_key, battery_value=battery_value)
            
            time.sleep(0.5)  # Mini delay of 0.5 seconds
	

            # Lire le fichier pour obtenir la valeur du screen
            data = load_data()
            if esp_key in data:
                screen_value = data[esp_key].get("screen", "unknown")

                # Switch sur la valeur de "screen"
                if screen_value == "calendar":
                    print(f"Executing Calendar action for {esp_key}")
                    # Ajouter ici le code pour exécuter l'action liée au calendrier
                    data = load_data()
                    calendar_id = data.get(esp_key, {}).get("calendar_id")

                    if calendar_id and (calendar_id!= ' '):
                        response = import_calendar([calendar_id, "#contacts@group.v.calendar.google.com"])
                        client.publish("resp_" + msg.topic, str(response))
                    else:
                        print(f"Aucun calendar_id trouvé pour {esp_key}")

                elif screen_value == "whiteboard":
                    print(f"Executing Dashboard action for {esp_key}")
                    client.publish("resp_" + msg.topic , "w" + actualDate())

                elif screen_value == "on air":
                    print(f"Executing Dashboard action for {esp_key}")
                    client.publish("resp_" + msg.topic , "o" + actualDate())

                elif screen_value == "update":
                    print(f"Executing Status action for {esp_key}")
                    # Ajouter ici le code pour afficher ou mettre à jour des informations de statut
                    name_room= data[esp_key].get("name_room", "unknown")
                    client.publish("resp_" + msg.topic, "u" + actualDate() + "[" + name_room )
                    update_action(esp_id=esp_key, screen_value="calendar")

                else:
                    print(f"Unknown screen type for {esp_key}. No action taken.")
            else:
                print(f"ESP {esp_key} not found in the data.")

    # --- 6. Create the MQTT client ---
    client = mqtt.Client(client_id="broker", protocol=mqtt.MQTTv311)
    client.username_pw_set(USERMQTT, PASSWORD)

    # --- 7. Assign callback functions ---
    client.on_connect = on_connect
    client.on_message = on_message

    # --- 8. Connect to the broker ---
    print(f"Connecting to {BROKER}:{PORT} ...")
    client.connect(BROKER, PORT, 60)

    # --- 9. Start the network loop (infinite listening) ---
    client.loop_forever()

if __name__ == "__main__":
    main()


