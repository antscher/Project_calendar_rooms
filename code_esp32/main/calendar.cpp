#include "calendar.h"
#include <sstream> // Pour std::istringstream
#include <stdexcept> // Pour std::invalid_argument

// This function is used to create a calendar event (Class) with all the information necessary to know for this event
// Message is extracted from the global message
CalendarEvent::CalendarEvent(std::string message) {
    std::istringstream stream(message);
    std::string desc;
    int b_day, b_month;
    int e_day, e_month;
    int b_hour, b_minutes;
    int e_hour, e_minutes;

    // Case of there being fewer events than expected, a new empty event will be created
    if (message == " ") {
        description = "";
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

    // Separate all the information from message to populate the class
    if (std::getline(stream, desc, ']') &&
        (stream >> b_day) && stream.ignore(1) &&
        (stream >> b_month) && stream.ignore(1) &&
        (stream >> e_day) && stream.ignore(1) &&
        (stream >> e_month) && stream.ignore(1) &&
        (stream >> b_hour) && stream.ignore(1) &&
        (stream >> b_minutes) && stream.ignore(1) &&
        (stream >> e_hour) && stream.ignore(1) &&
        (stream >> e_minutes)) {
        
        // Assign the extracted values to class attributes
        description = desc;
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
        throw std::invalid_argument("Invalid message format for CalendarEvent");
    }
}

Now::Now(std::string message) {
    std::istringstream stream(message);
    int nyear, nmonth, nday, nhour, nminutes;
    if (message == ""){
        year = 0;
        month = 0;
        day = 0;
        hour = 0;
        minutes = 0;
    }


    // Extraction of the date (year-month-day-hour-minute)
    else if ((stream >> nyear) && stream.ignore(1) &&   // Read the year and ignore the '-'
        (stream >> nmonth) && stream.ignore(1) &&  // Read the month and ignore the '-'
        (stream >> nday) && stream.ignore(1) &&   // Read the day
        (stream >> nhour) && stream.ignore(1) &&  
        (stream >> nminutes))  {                        

        year = nyear;
        month = nmonth;
        day = nday;
        hour = nhour;
        minutes = nminutes;

    } else {
        throw std::invalid_argument("Invalid message format for CalendarEvent (invalid date format)");
    }
}

/******************************************************************************
function:    Check if the given event is currently ongoing
parameter:
    event : The calendar event to check
return:
    true  : The event is ongoing at the current time
    false : The event has not yet started
******************************************************************************/
bool Now::eventOnGoing(CalendarEvent event){
    // Check if the event has already started based on the current date and time
    if (event.isVide()){
        return false;
    }
    if (event.getBeginningMonth() < month) {
        return true;
    } 
    else if (event.getBeginningMonth() == month) {
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
    message : Raw calendar message string (delimited by '[')
    i       : Index of the segment to extract
return:
    std::string : The extracted segment or " " if not found
******************************************************************************/
std::string calendar_string_i(String message, int i) {
    std::string msg = std::string(message.c_str());
    std::istringstream stream(msg);
    std::string segment;
    int current_index = 0;

    // Iterate through the segments separated by '['
    while (std::getline(stream, segment, '[')) {
        if (current_index == i) {
            if (i == 0) {
                return segment.substr(1);  // Return segment after the first character
            }
            return segment;  // Return the segment at index i
        }
        current_index++;
    }

    // If index i is out of bounds
    return " ";
}

bool operator==(const CalendarEvent& lhs, const CalendarEvent& rhs) {
    return lhs.getDescription()      == rhs.getDescription() &&
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
