#include "interface_graphique.h"
#include "src/e-Paper/EPD_7in3e.h"

RTC_DATA_ATTR char name_room[64];

// Declare a pointer for the image to be displayed
UBYTE *BlackImage;

/******************************************************************************
function:    Initialize the e-Paper display and clear the screen
return:
    0   : Success
    -1  : Failure to initialize the device module
******************************************************************************/
int init_and_clear(void) {
    Debug("EPD_7IN3E_test Demo\r\n");

    // Initialize the device module and check if everything is ready
    if (DEV_Module_Init() != 0) {
        return -1;  // Return -1 in case of failure
    }

    Debug("e-Paper Init and Clear...\r\n");
    // Initialize the e-Paper display
    EPD_7IN3E_Init();
    
    // Clear the screen to white (commented out here but can be used if needed)
    //EPD_7IN3E_Clear(EPD_7IN3E_WHITE);

    //DEV_Delay_ms(1000); // Wait for 1 second after initialization
    return 0;  // Return 0 on success
}

/******************************************************************************
function:    Clear and shut down the e-Paper display
return:
    0   : Success
******************************************************************************/
int clear_and_close(void) {
    Debug("Clear...\r\n");

    // Clear the screen to white
    //EPD_7IN3E_Clear(EPD_7IN3E_WHITE);

    Debug("Goto Sleep...\r\n");
    // Put the e-Paper display into sleep mode to reduce power consumption
    EPD_7IN3E_Sleep();

    DEV_Delay_ms(200); // Optional wait to ensure proper shutdown

    // Turn off the 5V power supply for minimal consumption
    Debug("close 5V, Module enters 0 power consumption ...\r\n");
    DEV_Module_Exit();
    
    return 0;  // Return 0 when complete
}

/******************************************************************************
function:    Display the calendar area with up to five events
parameter:
    actual_date      : The current date and time
    calendar1-5      : Calendar events to be displayed in sequence
******************************************************************************/
int display_calendar(Now actual_date, CalendarEvent calendar1, CalendarEvent calendar2, CalendarEvent calendar3,CalendarEvent calendar4,CalendarEvent calendar5) {
    // Calculate the required memory size for the image
    UDOUBLE ImagesizeTitle = ((EPD_7IN3E_HEIGHT % 2 == 0) ? (EPD_7IN3E_HEIGHT / 2) : (EPD_7IN3E_HEIGHT / 2 + 1)) * EPD_7IN3E_WIDTH;

    // Use PSRAM if available, otherwise regular memory
    UBYTE *BlackImage = (UBYTE *)ps_malloc(ImagesizeTitle);
    if (BlackImage == NULL) {
        // Fallback to regular malloc if PSRAM fails
        BlackImage = (UBYTE *)malloc(ImagesizeTitle);
        if (BlackImage == NULL) {
            Debug("Failed to apply for black memory...\r\n");
            return -1;
        }
    }

    // Initialize the image and drawing context
    Paint_NewImage(BlackImage, EPD_7IN3E_WIDTH, EPD_7IN3E_HEIGHT, 0, EPD_7IN3E_WHITE);
    Paint_SetScale(6);
    Paint_SelectImage(BlackImage);
    Paint_Clear(EPD_7IN3E_WHITE);

    display_title(actual_date, calendar1);
    display_date_room(actual_date);
    int Ystart = 150;
    Ystart = diplay_event_info(actual_date,calendar1, Ystart);
    Ystart = diplay_event_info(actual_date,calendar2, Ystart);
    Ystart = diplay_event_info(actual_date,calendar3, Ystart);
    Ystart = diplay_event_info(actual_date,calendar4, Ystart);
    Ystart = diplay_event_info(actual_date,calendar5, Ystart);

    // Display the image on the screen
    EPD_7IN3E_DisplayPart(BlackImage, 0, 0,  EPD_7IN3E_WIDTH,EPD_7IN3E_HEIGHT);

    // Free allocated memory
    free(BlackImage);
    BlackImage = NULL;
    return 0;
}

/******************************************************************************
function:    Display the screen for night-time sleep mode
******************************************************************************/
int display_sleep() {
    UDOUBLE ImagesizeTitle = ((EPD_7IN3E_HEIGHT % 2 == 0) ? (EPD_7IN3E_HEIGHT / 2) : (EPD_7IN3E_HEIGHT / 2 + 1)) * EPD_7IN3E_WIDTH;

    static UBYTE *BlackImage IRAM_ATTR;

    if ((BlackImage = (UBYTE *)malloc(ImagesizeTitle)) == NULL) {
        Debug("Failed to apply for black memory...\r\n");
        return -1;
    }

    Paint_NewImage(BlackImage, EPD_7IN3E_WIDTH, EPD_7IN3E_HEIGHT, 0, EPD_7IN3E_WHITE);
    Paint_SetScale(6);
    Paint_SelectImage(BlackImage);
    Paint_Clear(EPD_7IN3E_WHITE);

    Paint_DrawBitMap_PasteColor(&ISU_logo_big, 200, 100, 0, EPD_7IN3E_BLUE, EPD_7IN3E_WHITE);
    
    EPD_7IN3E_DisplayPart(BlackImage, 0, 0,  EPD_7IN3E_WIDTH,EPD_7IN3E_HEIGHT);

    free(BlackImage);
    BlackImage = NULL;
    return 0;
}

/******************************************************************************
function:    Display the "On Air" screen
******************************************************************************/
int display_OnAir() {
    UDOUBLE ImagesizeTitle = ((EPD_7IN3E_HEIGHT % 2 == 0) ? (EPD_7IN3E_HEIGHT / 2) : (EPD_7IN3E_HEIGHT / 2 + 1)) * EPD_7IN3E_WIDTH;

    static UBYTE *BlackImage IRAM_ATTR;

    if ((BlackImage = (UBYTE *)malloc(ImagesizeTitle)) == NULL) {
        Debug("Failed to apply for black memory...\r\n");
        return -1;
    }

    Paint_NewImage(BlackImage, EPD_7IN3E_WIDTH, EPD_7IN3E_HEIGHT, 0, EPD_7IN3E_WHITE);
    Paint_SetScale(6);
    Paint_SelectImage(BlackImage);
    Paint_Clear(EPD_7IN3E_WHITE);

    Paint_DrawBitMap_PasteColor(&On_Air, 0, 0, 0, EPD_7IN3E_RED, EPD_7IN3E_WHITE);
    
    EPD_7IN3E_DisplayPart(BlackImage, 0, 0,  EPD_7IN3E_WIDTH,EPD_7IN3E_HEIGHT);

    free(BlackImage);
    BlackImage = NULL;
    return 0;
}

/******************************************************************************
function:    Display the title area with status and timing
parameter:
    actual_date      : The current date and time
    calendar1        : The current calendar event to check availability
******************************************************************************/
void display_title(Now actual_date, CalendarEvent calendar1){
    bool onGoing = actual_date.eventOnGoing(calendar1);
    if (onGoing){
        // Draw red rectangle for title
        Paint_DrawRectangle(0, 40, 580, 145, EPD_7IN3E_RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawString_EN(20, 40, "RESERVED", &Font56_b, EPD_7IN3E_RED, EPD_7IN3E_WHITE);
        char endingHour[12];
        snprintf(endingHour, sizeof(endingHour), "Until %02d:%02d", calendar1.getEndingHour(), calendar1.getEndingMinutes());
        Paint_DrawString_EN(20, 100, endingHour, &Font38, EPD_7IN3E_RED, EPD_7IN3E_WHITE);
    }
    else {
        // Draw green rectangle for title
        Paint_DrawRectangle(0, 40, 580, 145, EPD_7IN3E_GREEN, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawString_EN(20, 40, "AVAILABLE", &Font56_b, EPD_7IN3E_GREEN, EPD_7IN3E_WHITE);
        if (actual_date.eventIsToday(calendar1)){
            char beginnigHour[12];
            snprintf(beginnigHour, sizeof(beginnigHour), "Until %02d:%02d", calendar1.getBeginningHour(), calendar1.getBeginningMinutes());
            Paint_DrawString_EN(20, 100, beginnigHour, &Font38, EPD_7IN3E_GREEN, EPD_7IN3E_WHITE);            
        }
    }
    // Draw top and bottom borders
    Paint_DrawLine(1, 40, 579, 40, EPD_7IN3E_BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
    Paint_DrawLine(1, 145, 579, 145, EPD_7IN3E_BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
    Paint_DrawBitMap_PasteColor(&ISU_logo, 610, 40, 0, EPD_7IN3E_BLUE, EPD_7IN3E_WHITE);
    Paint_DrawBitMap_PasteColor(&qr_code, 680, 360, 0, EPD_7IN3E_WHITE, EPD_7IN3E_BLACK);
}


/******************************************************************************
function:    Display the current date and the room name
parameter:
    actual_date      : The current date and time
******************************************************************************/
void display_date_room(Now actual_date){
    char date[11];
    snprintf(date, sizeof(date), "%02d/%02d/%04d", actual_date.getDay(), actual_date.getMonth(),actual_date.getYear());
    Paint_DrawString_EN(675, 0, date, &Font38, EPD_7IN3E_WHITE, EPD_7IN3E_BLACK); // a inverser avec room
    Paint_DrawString_EN(5, 0,name_room, &Font38, EPD_7IN3E_WHITE, EPD_7IN3E_BLACK);
}

/******************************************************************************
function:    Display calendar event info and return updated vertical position
parameter:
    actual_date      : The current date and time
    calendar         : The calendar event to display
    Ystart           : Starting Y coordinate
return:
    Updated Y position after printing the event
******************************************************************************/
UWORD diplay_event_info(Now actual_date,CalendarEvent calendar, UWORD Ystart){
    if (calendar.isVide() || !(actual_date.eventIsToday(calendar))){
        return Ystart;
    }
    if (Ystart + 2*charact_height > EPD_7IN3E_HEIGHT){
        return Ystart;
    }
    char date_info[36];
    //Case of an event in more than one day
    if ((calendar.getBeginningDay() != calendar.getEndingDay()) || (calendar.getBeginningMonth() != calendar.getEndingMonth())){
        if ((calendar.getBeginningMonth() == actual_date.getMonth()) && (calendar.getBeginningDay() == actual_date.getDay())) {
            snprintf(date_info, sizeof(date_info), "From %02d:%02d (today) to %02d:%02d (%02d/%02d)",calendar.getBeginningHour(), calendar.getBeginningMinutes()
                                                                                                ,calendar.getEndingHour(), calendar.getEndingMinutes()
                                                                                                ,calendar.getEndingDay(), calendar.getEndingMonth());

        }
        else {
            snprintf(date_info, sizeof(date_info), "From 00:00 (today) to %02d:%02d (%02d/%02d)",calendar.getEndingHour(), calendar.getEndingMinutes()
                                                                                    ,calendar.getEndingDay(), calendar.getEndingMonth());
        }
    }
    else {
        snprintf(date_info, sizeof(date_info), "From %02d:%02d to %02d:%02d", calendar.getBeginningHour(), calendar.getBeginningMinutes()
                                                                            ,calendar.getEndingHour(), calendar.getEndingMinutes());
    
    }
    Paint_DrawString_EN(10, Ystart, date_info, &Font28_b, EPD_7IN3E_WHITE, EPD_7IN3E_BLACK);

    const char * desc = calendar.getDescription();
    int line = Paint_DrawLongString(10, Ystart+charact_height, desc, &Font28, EPD_7IN3E_WHITE, EPD_7IN3E_BLACK);
    Paint_DrawLine(0, Ystart+(1+line)*charact_height+5, 680, Ystart+(1+line)*charact_height+5, EPD_7IN3E_BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

    return Ystart+(1+line)*charact_height+10;
}

