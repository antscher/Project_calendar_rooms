/*
We defined our fonctions to use and import files for doing the printing on the displays
*/


#ifndef _EPD_TEST_H_
#define _EPD_TEST_H_

#include "src/Config/Debug.h"
#include "src/Config/DEV_Config.h"
#include "src/GUI/GUI_Paint.h"
#include "src/Fonts/fonts.h"
#include "src/Image/ImageData.h"
#include <stdlib.h> // malloc() free()
#include "calendar.h"

extern RTC_DATA_ATTR char name_room[64];

//Space for characters in a normal style (Fonts 28)
#define charact_height 28

//Just init the SPI pins of the display
int init_and_clear(void);
//Just close the SPI link and reduce the voltage of the display
int clear_and_close(void);
//display the calendar
int display_calendar(Now actual_date,CalendarEvent calendar1,CalendarEvent calendar2,CalendarEvent calendar3,CalendarEvent calendar4,CalendarEvent calendar5);
//display the screen of the sleeping mode
int display_sleep();
//display the screen of On Air
int display_OnAir();
//Display the title "RESERVED" or "AVAILABLE"
void display_title(Now actual_date, CalendarEvent calendar1);
//Display the date and the room
void display_date_room(Now actual_date);
//Display the information of an event
UWORD diplay_event_info(Now actual_date,CalendarEvent calendar, UWORD Ystart);

#endif