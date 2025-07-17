#include <calendar.h>
#include "interface_graphique.h"
#include "optimization_config.h"
#include "memory_diagnostic.h"
#include "nvs_flash.h"
#include "nvs.h"


#define uS_TO_MIN_FACTOR 60000000ULL
RTC_DATA_ATTR char new_day;
RTC_DATA_ATTR unsigned long long int night_time;
extern RTC_DATA_ATTR char name_room[64];
extern RTC_DATA_ATTR char old_message[400];
extern const char name_room_const[];

void setup() {
  delay(500); // Wait for voltage to stabilize
  Serial.begin(115200);
  delay(500); 
  Serial.println("Boot OK");
  
  // Memory diagnostic at startup
  MEM_CHECK("Setup start");
  MemoryDiagnostic::printDetailedMemory();
  
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

    Serial.println("Entering Deep Sleep mode");
    // ESP32 goes to deep sleep
    esp_deep_sleep_start();
  }

  String message =  mqtt_calendar(new_day); 
  MEM_CHECK("After MQTT");

  char action = message[0];
  char date_buffer[64];
  calendar_string_i(message, 0, date_buffer, sizeof(date_buffer));
  Now actual_date(date_buffer);
  int time_to_sleep = actual_date.timeToSleep();

  if (action == 'c'){
    char event_buffer[256];
    calendar_string_i(message, 1, event_buffer, sizeof(event_buffer));
    CalendarEvent calendar1(event_buffer);
    //definition of time to sleep, depend if there is an event soon
    time_to_sleep = actual_date.timeToSleep(calendar1);
  }
  
  MEM_CHECK("After parsing");


  if (actual_date.nightMode()){
    // Night mode
    action = 'w';
    message[0] = 'w';
    night_time = time_to_sleep - 15;
    time_to_sleep = 30;
    new_day = '1';
  }
  

  else if (checkAndUpdateMessage(message)){
    // Nothing to do
    action = 'n';
  }
    delay(500);
  switch (action) {
    case 'c' : { // Calendar mode
      nvs_flash_init();
      load_name_room_from_flash();
      DEV_Delay_ms(100);
      Serial.println("Initialization and clear");
      init_and_clear();

      Serial.println("Displaying calendar");

      char event_buffer1[256], event_buffer2[256], event_buffer3[256], event_buffer4[256], event_buffer5[256];
      calendar_string_i(message, 1, event_buffer1, sizeof(event_buffer1));
      calendar_string_i(message, 2, event_buffer2, sizeof(event_buffer2));
      calendar_string_i(message, 3, event_buffer3, sizeof(event_buffer3));
      calendar_string_i(message, 4, event_buffer4, sizeof(event_buffer4));
      calendar_string_i(message, 5, event_buffer5, sizeof(event_buffer5));

      CalendarEvent calendar1(event_buffer1);
      CalendarEvent calendar2(event_buffer2);
      CalendarEvent calendar3(event_buffer3);
      CalendarEvent calendar4(event_buffer4);
      CalendarEvent calendar5(event_buffer5);

      display_calendar(actual_date,calendar1,calendar2,calendar3,calendar4,calendar5);

      Serial.println("Clear and close");
      clear_and_close();
      

    break; }

    case 'w' : { // White screen mode (night)
      Serial.println("Displaying white screen");
      DEV_Delay_ms(100);
      init_and_clear();
      display_sleep();
      clear_and_close();
      
    break; }

    case 'o' : { // On Air mode
      Serial.println("Displaying On Air screen");
      DEV_Delay_ms(100);
      init_and_clear();
      display_OnAir();
      clear_and_close();
      
    break; }

    case 'e' :  { // Error with MQTT message
      Serial.println("MQTT Error");
      // Try to reconnect to the server after 5 min
      time_to_sleep = 5;
      
    break;  }  

    case 'u' :{ // Update the room name
      Serial.println("Update name");
      char name_buffer[64];
      calendar_string_i(message, 1, name_buffer, sizeof(name_buffer));
      strncpy(name_room, name_buffer, sizeof(name_room) - 1);
      name_room[sizeof(name_room) - 1] = '\0';  // Ensure string is null-terminated
      save_name_room_to_flash();
      time_to_sleep = 1;

    break;  }

    case 'n' :{ // Nothing to do
      Serial.println("Nothing to do");
    break;}
  }

  Serial.print("Time to sleep ");
  Serial.println(time_to_sleep);

  // ESP32 sleeps in deep mode (it will never enter the loop function)
  esp_sleep_enable_timer_wakeup(uS_TO_MIN_FACTOR*time_to_sleep);
  Serial.println("Entering Deep Sleep mode");

  // ESP32 goes to deep sleep
  esp_deep_sleep_start();
  Serial.println("This message will not be displayed, because the ESP32 is in Deep Sleep!");

}

void loop() {
  // Main code here, runs repeatedly (not used, ESP32 sleeps)
  delay(5000);
}


void check_rtc_data() {
    Serial.println("Check");
    // Check new_day value
    if (new_day != '0' && new_day != '1' && new_day != '2') {
        Serial.println("RTC new_day invalid -> reset to '0'");
        new_day = '0';
    }

    // Check night_time (example: max coherent time)
    if (night_time > 2880ULL ) {  // 2 days in minutes, adjustable
        Serial.println("RTC night_time incoherent -> reset");
        night_time = 0;
    }

    // Check old_message
    if (old_message[0] == '\0') {
        Serial.println("RTC old_message empty -> initialize to empty string");
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
        Serial.println("name_room saved to flash");
    } else {
        Serial.println("NVS save error");
    }
}

void load_name_room_from_flash() {
    nvs_handle_t my_handle;
    esp_err_t err = nvs_open("storage", NVS_READONLY, &my_handle);
    if (err == ESP_OK) {
        size_t required_size = sizeof(name_room);
        err = nvs_get_str(my_handle, "name_room", name_room, &required_size);
        if (err == ESP_OK) {
            Serial.print("name_room loaded: ");
            Serial.println(name_room);
        } else {
            Serial.println("No saved data -> initializing with default");
            strncpy(name_room, name_room_const, sizeof(name_room));
        }
        nvs_close(my_handle);
    } else {
        Serial.println("NVS load error");
    }
}