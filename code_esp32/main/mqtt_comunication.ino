#include <WiFi.h>
#include <PubSubClient.h>
//Tested with the version 2.8 of "PubSubClient" by Nick O'Leary
#include "wifi_data.h"

WiFiClient espClient; // WiFi client
PubSubClient client(espClient); // MQTT client

String message = ""; // Message received via MQTT
RTC_DATA_ATTR char old_message[400] = ""; 


/******************************************************************************
function:    Send a message via MQTT and wait for a response
parameter:
    battery : String containing battery information to send
return:
    String  : The message received from the MQTT broker in response
******************************************************************************/
String mqtt_calendar(char battery) {
  // Connect to the MQTT server
  if (connect_MQTT()) {
    return "e"; // WiFi or MQTT error
  }

  message = ""; // Reset the message

  // Publish the message to the topic
  char payload[2] = { battery, '\0' };
  bool success = client.publish(topic, payload);

  if (success) {
    Serial.println("Message successfully published!");
  } else {
    Serial.println("Error while publishing.");
    return "e";  
  }
  // Subscribe to the response topic and wait for a reply
  bool sub_ok = client.subscribe(topic_reponse); 
  Serial.println(sub_ok ? "OK" : "FAIL");

  int compteur_erreur = 0;

  // Wait until the message is received or 30 seconds pass
  while (message.isEmpty() && compteur_erreur++<1000) {
    client.loop();      // Handles MQTT communication
    delay(20);          // Wait between iterations
  }
  if (compteur_erreur>=200) {  // If 8 seconds passed
    return "e";                // Return default value (error)
  }

  // Disconnect after receiving the message
  disconnect_MQTT();

  return message; // Return the received message
}

/******************************************************************************
function:    MQTT callback triggered upon message reception
parameter:
    topic   : Topic on which the message was received
    payload : Message content (as byte array)
    length  : Message length
return:
    bool  : True if repeated errors occurred (WiFi or broker connection)
******************************************************************************/
void callback(char *topic, byte *payload, unsigned int length) { 
  Serial.print("Message arrived in topic: "); 
  Serial.println(topic); 
  Serial.print("Message: ");
  
  // Concatenate message data into the "message" variable
  for (int i = 0; i < length; i++) {
    Serial.print((char) payload[i]);
    message += (char) payload[i];
  }

  Serial.println();
  Serial.println("-----------------------");
}

/******************************************************************************
function:    Compare the current message with the previous one 
parameter:
    message : String containing the received message
return:
    true : if nothing needs to be done (refr)
******************************************************************************/
bool checkAndUpdateMessage(String message) {
  String old_msg_str = String(old_message);
  if ((message[0] == 'c') && (old_message[0] == 'c')){
    Now actual_date(calendar_string_i(message,0));
    CalendarEvent calendar1(calendar_string_i(message,1));
    CalendarEvent calendar2(calendar_string_i(message,2));
    CalendarEvent calendar3(calendar_string_i(message,3));
    Now old_date(calendar_string_i(old_msg_str,0));
    CalendarEvent calendar1_old(calendar_string_i(old_msg_str,1));
    CalendarEvent calendar2_old(calendar_string_i(old_msg_str,2));
    CalendarEvent calendar3_old(calendar_string_i(old_msg_str,3));
    if ((calendar1 == calendar1_old) 
        && (actual_date.eventOnGoing(calendar1) == old_date.eventOnGoing(calendar1_old) )
        && (calendar3 == calendar3_old )
        && (calendar2 == calendar2_old)){
      return true;
    }

  }
  else if (message[0] == old_message[0] ){
    return true;
  }

  strncpy(old_message, message.c_str(), sizeof(old_message));
  old_message[sizeof(old_message) - 1] = '\0'; // Ensure proper string termination
  return false;
}

/******************************************************************************
function:    Connect to the MQTT broker and the WiFi network
return:
    bool  : true if it failed to connect
******************************************************************************/
bool connect_MQTT() {
  // Connect to a Wi-Fi network
  WiFi.persistent(false);         // Sauvegarde config Wi-Fi
  WiFi.setAutoReconnect(false);   // Reconnexion automatique
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);  // Première connexion
  
  int compteur_erreur = 0;
  delay(300); 
  while (WiFi.status() != WL_CONNECTED && compteur_erreur++<25) { 
    delay(300); 
    Serial.println("Connecting to WiFi.."); 
  } 
  if (compteur_erreur>=25){
    Serial.println("Failed to connect to WiFi after multiple attempts"); 
    return true;
  }
  Serial.println("Connected to the Wi-Fi network");  

  // Connect to the MQTT broker
  client.setServer(mqtt_broker, mqtt_port); 
  client.setBufferSize(512);
  client.setCallback(callback); 
  compteur_erreur = 0;
  while (!client.connected() && compteur_erreur++<10) { 
    Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str()); 
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) { 
      Serial.println("Public EMQX MQTT broker connected"); 
    } else { 
      // If the connection fails, print the state and retry
      Serial.print("Failed with state "); 
      Serial.println(client.state()); 
      delay(200); 
    }
  }
  if (compteur_erreur>=10){
    Serial.println("Failed to connect to broker after multiple attempts"); 
    return true;
  }
  return false;
}

/******************************************************************************
function:    Disconnect from the MQTT broker and WiFi network
******************************************************************************/
void disconnect_MQTT() {
  delay(20);
  client.disconnect(); // Disconnect from the MQTT client
  Serial.println("Broker disconnected");
  WiFi.disconnect(true); // Disconnect from the WiFi network
  WiFi.mode(WIFI_OFF);    // Turn everything off to save power
  Serial.println("WiFi disconnected");

}

