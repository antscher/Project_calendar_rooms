#include <calendar.h>
#include <string>
#include "interface_graphique.h"
#include "nvs_flash.h"
#include "nvs.h"


#define uS_TO_MIN_FACTOR 60000000ULL
RTC_DATA_ATTR char new_day;
RTC_DATA_ATTR unsigned long long int night_time;
extern RTC_DATA_ATTR char name_room[64];
extern RTC_DATA_ATTR char old_message[400];
extern const char name_room_const[];

void setup() {
  delay(500);//for the tension to stabilize
  Serial.begin(115200);
  delay(500); 
  Serial.println("Boot OK");
  check_rtc_data();
  
  if (night_time > 0) {
    Serial.print("Night time : ");
    Serial.println(night_time);
    if (new_day != '0'){
      new_day = '0';
    }
    if (night_time > 30) {
      night_time -= 30;
      Serial.println(night_time);
      esp_sleep_enable_timer_wakeup(uS_TO_MIN_FACTOR*30);
    }
    else {
      esp_sleep_enable_timer_wakeup(uS_TO_MIN_FACTOR*night_time);
      night_time = 0;      
    }

    Serial.println("Passage en mode Deep Sleep");
    //Esp go to deep sleep
    esp_deep_sleep_start();
  }

  String message =  mqtt_calendar(new_day); 

  char action = message[0];
  Now actual_date(calendar_string_i(message,0));
  int time_to_sleep = actual_date.timeToSleep();

  if (action == 'c'){
    CalendarEvent calendar1(calendar_string_i(message,1));
    //definition of time to sleep, depend if there is an event soon
    time_to_sleep = actual_date.timeToSleep(calendar1);
  }


  if (actual_date.nightMode()){
    //mode night
    action = 'w';
    message[0] = 'w';
    night_time= time_to_sleep-15;
    time_to_sleep = 30;
    new_day = '1';
  }
  

  else if (checkAndUpdateMessage(message)){
    //Nothing to do
    action = 'n';
  }
    delay(500);
  switch (action) {
    case 'c' : { //case of calendar
      nvs_flash_init();
      load_name_room_from_flash();
      DEV_Delay_ms(100);
      Serial.println("Inititialisation and clear");
      init_and_clear();

      Serial.println("affichage du calendrier");

      CalendarEvent calendar1(calendar_string_i(message,1));
      CalendarEvent calendar2(calendar_string_i(message,2));
      CalendarEvent calendar3(calendar_string_i(message,3));
      CalendarEvent calendar4(calendar_string_i(message,4));
      CalendarEvent calendar5(calendar_string_i(message,5));

      display_calendar(actual_date,calendar1,calendar2,calendar3,calendar4,calendar5);

      Serial.println("Clear and close");
      clear_and_close();
      

    break; }

    case 'w' : { //case of white scree
      Serial.println("affichage d'un écran blanc");
      DEV_Delay_ms(100);
      init_and_clear();
      display_sleep();
      clear_and_close();
      
    break; }

    case 'o' : { //case of screen on air
      Serial.println("affichage d'un écran on air");
      DEV_Delay_ms(100);
      init_and_clear();
      display_OnAir();
      clear_and_close();
      
    break; }

    case 'e' :  { //case of an error with the message
      Serial.println("Erreur sur MQTT");
      //We try again to reconnect to the server after 5 min
      time_to_sleep = 5;

      new_day= '2';
      
    break;  }  

    case 'u' :{ // Update the name of the Room
      Serial.println("Update name");
      std::string temp = calendar_string_i(message, 1);
      if (temp == "2" ){
        new_day = '2';
      }
      else {
        size_t len = temp.copy(name_room, sizeof(name_room) - 1);
        name_room[len] = '\0';  // Assure the end of the chain
        save_name_room_to_flash();
      }
      time_to_sleep = 1;

    break;  }

    case 'n' :{ //Noting to do case
      Serial.println("Nothing to do");
    break;}
  }

  Serial.print("Time to sleep ");
  Serial.println(time_to_sleep);

  //L'esp sleep in deep mode (L'esp ne passera jamais dans la boucle loop)
  esp_sleep_enable_timer_wakeup(uS_TO_MIN_FACTOR*time_to_sleep);
  Serial.println("Passage en mode Deep Sleep");
  
  //Esp go to deep sleep

  esp_deep_sleep_start();
  Serial.println("Ce message ne s'affichera pas, car l'ESP32 est en Deep Sleep !");

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);
}


void check_rtc_data() {
    Serial.println("Check");
    // Vérification de new_day
  if (new_day != '0' && new_day != '1' && new_day != '2') {
      Serial.println("RTC new_day invalide -> réinitialisation à '2'");
      new_day = '0';
  }

    // Vérification de night_time (exemple : temps max cohérent)
    if (night_time > 2880ULL ) {  // 2 jours en minutes, ajustable
        Serial.println("RTC night_time incohérent -> réinitialisation");
        night_time = 0;
    }

    // Vérification old_message
    if (old_message[0] == '\0') {
        Serial.println("RTC old_message vide -> initialisation à chaîne vide");
        old_message[0] = '\0';
    }
}

void save_name_room_to_flash() {
    nvs_handle_t my_handle;
    esp_err_t err = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (err == ESP_OK) {
        nvs_set_str(my_handle, "name_room", name_room);
        nvs_commit(my_handle);
        nvs_close(my_handle);
        Serial.println("name_room sauvegardé dans la flash");
    } else {
        Serial.println("Erreur NVS save");
    }
}

void load_name_room_from_flash() {
    nvs_handle_t my_handle;
    esp_err_t err = nvs_open("storage", NVS_READONLY, &my_handle);
    if (err == ESP_OK) {
        size_t required_size = sizeof(name_room);
        err = nvs_get_str(my_handle, "name_room", name_room, &required_size);
        if (err == ESP_OK) {
            Serial.print("name_room chargé : ");
            Serial.println(name_room);
        } else {
            Serial.println("Aucune donnée sauvegardée -> initialisation par défaut");
            strncpy(name_room, name_room_const, sizeof(name_room));
        }
        nvs_close(my_handle);
    } else {
        Serial.println("Erreur NVS load");
    }
}