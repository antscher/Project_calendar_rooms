#include "calendar.h"
#include <cstring>
#include <cstdlib>

// This function is used to create a calendar event (Class) with all the information necessary to know for this event
// Message is extracted from the global message
CalendarEvent::CalendarEvent(const char* message) {
    // Case of there being fewer events than expected, a new empty event will be created
    if (message == nullptr || strcmp(message, " ") == 0 || strlen(message) == 0) {
        description[0] = '\0';
        beginning_day = 0;
        beginning_month = 0;
        ending_day = 0;
        ending_month = 0;
        beginning_hour = 0;
        ending_hour = 0;
        beginning_minutes = 0;
        ending_minutes = 0;
        vide = true;  // Mark as empty event
        return;
    }

    // Parse the message using sscanf for better memory efficiency
    char desc_temp[MAX_DESCRIPTION_LENGTH];
    int b_day, b_month, e_day, e_month, b_hour, b_minutes, e_hour, e_minutes;
    
    int parsed = sscanf(message, "%127[^]]%*c%d%*c%d%*c%d%*c%d%*c%d%*c%d%*c%d%*c%d",
                       desc_temp, &b_day, &b_month, &e_day, &e_month, 
                       &b_hour, &b_minutes, &e_hour, &e_minutes);
    
    if (parsed == 9) {
        strncpy(description, desc_temp, MAX_DESCRIPTION_LENGTH - 1);
        description[MAX_DESCRIPTION_LENGTH - 1] = '\0';
        beginning_day = b_day;
        beginning_month = b_month;
        ending_day = e_day;
        ending_month = e_month;
        beginning_hour = b_hour;
        ending_hour = e_hour;
        beginning_minutes = b_minutes;
        ending_minutes = e_minutes;
        vide = false;  // Event is not empty
    } else {
        // Invalid format - create empty event
        description[0] = '\0';
        beginning_day = 0;
        beginning_month = 0;
        ending_day = 0;
        ending_month = 0;
        beginning_hour = 0;
        ending_hour = 0;
        beginning_minutes = 0;
        ending_minutes = 0;
        vide = true;
    }
}

Now::Now(const char* message) {
    if (message == nullptr || strlen(message) == 0) {
        year = 0;
        month = 0;
        day = 0;
        hour = 0;
        minutes = 0;
        return;
    }

    // Parse using sscanf for better performance
    int nyear, nmonth, nday, nhour, nminutes;
    int parsed = sscanf(message, "%d%*c%d%*c%d%*c%d%*c%d", 
                       &nyear, &nmonth, &nday, &nhour, &nminutes);
    
    if (parsed == 5) {
        year = nyear;
        month = nmonth;
        day = nday;
        hour = nhour;
        minutes = nminutes;
    } else {
        year = 0;
        month = 0;
        day = 0;
        hour = 0;
        minutes = 0;
    }
}

/******************************************************************************
function:    Check if the given event is currently ongoing (optimized)
parameter:
    event : The calendar event to check
return:
    true  : The event is ongoing at the current time
    false : The event has not yet started
******************************************************************************/
OPTIMIZE_FOR_SPEED bool Now::eventOnGoing(CalendarEvent event){
    // Check if the event has already started based on the current date and time
    if (UNLIKELY(event.isVide())){
        return false;
    }
    if (event.getBeginningMonth() < month) {
        return true;
    } 
    else if (LIKELY(event.getBeginningMonth() == month)) {
        if (event.getBeginningDay() < day) { 
            return true;
        }
        else if (event.getBeginningDay() == day)  {
            if (event.getBeginningHour() < hour ){
                return true;
            }
            else if ((event.getBeginningHour() == hour ) && (event.getBeginningMinutes() - minutes <= 0)){
                return true;
            } 
        }
    }  
    return false;
}

/******************************************************************************
function:    Check if the given event is happening today
parameter:
    event : The calendar event to check
return:
    true  : The event is scheduled for today
    false : The event is not scheduled for today
******************************************************************************/
bool Now::eventIsToday(CalendarEvent event){
    // Check if the event is scheduled for today
    if (event.isVide()){
        return false;
    }
    if (event.getBeginningMonth() == month) {
        if (event.getBeginningDay() <= day) {
            return true;
        }
    }
    if (event.getBeginningMonth() < month) {
        return true;
    }
    return false;
}

/******************************************************************************
function:    Determine time before the next refresh depending on event time and night mode
parameter:
    event : The calendar event to consider
return:
    Minutes before the next required refresh
******************************************************************************/
int Now::timeToSleep(CalendarEvent event){
    // Check if it's time to sleep based on current time and event timing
    if ((beginning_night_hour < hour ) || 
        ((beginning_night_hour == hour ) && (beginning_night_minutes <= minutes))) {

        // Return the time until wake-up, accounting for the night sleep
        return (ending_night_hour + 24 - hour) * 60 +  (ending_night_minutes - minutes);
    }
    
    // Check if the event is close to its starting or ending time
    if ((event.getBeginningMonth() == month) && (!event.isVide())) {
        if (event.getBeginningDay() == day)  {
            if (event.getBeginningHour() == hour){
                if ((event.getBeginningMinutes() - minutes <  TIME_BEFORE_REFRESH) && (!this->eventOnGoing(event))){
                    return  event.getBeginningMinutes() - minutes;  // Time until event begins
                }
            }
            else if ((event.getBeginningHour() - 1  == hour) && (!this->eventOnGoing(event))){
                if (60 + event.getBeginningMinutes() - minutes <  TIME_BEFORE_REFRESH){
                    return  60 + event.getBeginningMinutes() - minutes;  // Time until event begins
                }
            }
        }
    }
    // Check if the event is close to its starting or ending time
    if (event.getEndingMonth() == month) {
        if (event.getEndingDay() == day)  {
            if (event.getEndingHour() == hour){    
                if (event.getEndingMinutes() - minutes <  TIME_BEFORE_REFRESH) {
                    return event.getEndingMinutes() - minutes ;  // Time until event ends
                }
            }
            else if (event.getEndingHour() - 1  == hour ){
                if (60 + event.getEndingMinutes() - minutes <  TIME_BEFORE_REFRESH){
                    return  60 + event.getEndingMinutes() - minutes;  // Time until event ends
                }
            }
        }
    }
    return TIME_BEFORE_REFRESH;  // Return default refresh time
}

/******************************************************************************
function:    Determine sleep duration based on night time configuration
return:
    Minutes before the next wake-up or refresh
******************************************************************************/
int Now::timeToSleep(){
    // Check if it's time to sleep based on current time and event timing
    if ((beginning_night_hour < hour ) || 
        ((beginning_night_hour == hour ) && (beginning_night_minutes <= minutes))) {

        // Return the time until wake-up, accounting for the night sleep
        return (ending_night_hour + 24 - hour) * 60 +  (ending_night_minutes - minutes);
    }
    return TIME_BEFORE_REFRESH;  // Return default refresh time
}

/******************************************************************************
function:    Determine sleep duration based on night time configuration
return:
    true if it is the night display
******************************************************************************/
bool Now::nightMode(){
    // Check if it's time to sleep based on current time and event timing
    if ((beginning_night_hour < hour ) || 
        ((beginning_night_hour == hour ) && (beginning_night_minutes <= minutes))) {

        return true;
    }
    return false;  // Return default refresh time
}

/******************************************************************************
function:    Extract the i-th calendar string from a formatted message
parameter:
    message     : Raw calendar message string (delimited by '[')
    i           : Index of the segment to extract
    output      : Buffer to store the extracted segment
    output_size : Size of the output buffer
******************************************************************************/
void calendar_string_i(const String& message, int i, char* output, size_t output_size) {
    if (output == nullptr || output_size == 0) {
        return;
    }
    
    // Initialize output buffer
    output[0] = '\0';
    
    const char* msg = message.c_str();
    int current_index = 0;
    const char* segment_start = msg;
    const char* segment_end;
    
    // Handle special case for index 0
    if (i == 0) {
        segment_end = strchr(msg, '[');
        if (segment_end == nullptr) {
            segment_end = msg + strlen(msg);
        }
        if (segment_start < segment_end && msg[0] != '\0') {
            size_t len = min((size_t)(segment_end - segment_start - 1), output_size - 1);
            strncpy(output, segment_start + 1, len);
            output[len] = '\0';
        }
        return;
    }
    
    // Find the i-th segment
    const char* current_pos = msg;
    while (current_index < i && (current_pos = strchr(current_pos, '[')) != nullptr) {
        current_index++;
        current_pos++;
        
        if (current_index == i) {
            segment_start = current_pos;
            segment_end = strchr(segment_start, '[');
            if (segment_end == nullptr) {
                segment_end = segment_start + strlen(segment_start);
            }
            
            size_t len = min((size_t)(segment_end - segment_start), output_size - 1);
            strncpy(output, segment_start, len);
            output[len] = '\0';
            return;
        }
    }
    
    // If index i is out of bounds, set output to " "
    if (output_size > 1) {
        output[0] = ' ';
        output[1] = '\0';
    }
}

bool operator==(const CalendarEvent& lhs, const CalendarEvent& rhs) {
    return strcmp(lhs.getDescription(), rhs.getDescription()) == 0 &&
           lhs.getBeginningDay()     == rhs.getBeginningDay() &&
           lhs.getBeginningMonth()   == rhs.getBeginningMonth() &&
           lhs.getEndingDay()        == rhs.getEndingDay() &&
           lhs.getEndingMonth()      == rhs.getEndingMonth() &&
           lhs.getBeginningHour()    == rhs.getBeginningHour() &&
           lhs.getBeginningMinutes() == rhs.getBeginningMinutes() &&
           lhs.getEndingHour()       == rhs.getEndingHour() &&
           lhs.getEndingMinutes()    == rhs.getEndingMinutes() &&
           lhs.isVide()              == rhs.isVide();
}
