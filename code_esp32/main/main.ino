#include <calendar.h>
#include <string>
#include "interface_graphique.h"

#define uS_TO_MIN_FACTOR 1000000 * 60
RTC_DATA_ATTR  char new_day= '2';

void setup() {
  delay(500);
  Serial.begin(115200);
  //for the tension to stabilize

  String message =  mqtt_calendar(new_day); 
  if (new_day != '0'){
      new_day = '0';
  } 

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
    new_day = '1';
  }

  else if (checkAndUpdateMessage(message)){
    //Nothing to do
    action = 'n';
  }

  switch (action) {
    case 'c' : { //case of calendar
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
      
    break;  }  

    case 'u' :{ // Update the name of the Room
      Serial.println("Update name");
      std::string temp = calendar_string_i(message, 1);
      size_t len = temp.copy(name_room, sizeof(name_room) - 1);
      name_room[len] = '\0';  // Assure the end of the chain
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
  delay(500);
  esp_deep_sleep_start();
  Serial.println("Ce message ne s'affichera pas, car l'ESP32 est en Deep Sleep !");

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);
}
