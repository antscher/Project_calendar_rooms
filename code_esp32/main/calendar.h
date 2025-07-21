/* This file contains all the events in memory from the string (from MQTT) */
#include "Arduino.h"

#ifndef CALENDAR_H
#define CALENDAR_H

#include <string>
#include "optimization_config.h"

#define nb_events 5  // Define the number of events
#define MAX_DESCRIPTION_LENGTH 128  // Maximum length for event descriptions

//Time between each refresh
#define TIME_BEFORE_REFRESH  5  // Time interval in minutes before refresh

//hours for the sleeping, the night 
#define beginning_night_hour 20  // The start hour of the night
#define beginning_night_minutes 0  // The start minute of the night

//hours for the waking up after the night sleeping,take 15 minutes of margin
#define ending_night_hour 7  // The wake-up hour after the night
#define ending_night_minutes 0  // The wake-up minute after the night

// Class to represent a calendar event
class CalendarEvent {
public:
    // Constructor with detailed parameters for event timings and description
    CalendarEvent(const char* description, int beginning_day, int beginning_month,
                  int ending_day, int ending_month,
                  int beginning_hour, int ending_hour,int beginning_minutes, int ending_minutes,bool vide) {
        strncpy(this->description, description, MAX_DESCRIPTION_LENGTH - 1);
        this->description[MAX_DESCRIPTION_LENGTH - 1] = '\0';
        this->beginning_day = beginning_day;
        this->beginning_month = beginning_month;
        this->ending_day = ending_day;
        this->ending_month = ending_month;
        this->beginning_hour = beginning_hour;
        this->ending_hour = ending_hour;
        this->beginning_minutes = beginning_minutes;
        this->ending_minutes = ending_minutes;
        this->vide = vide;
    }

    // Constructor with message (parses the string to extract event details)
    CalendarEvent(const char* message);

    // Accessor methods to retrieve event details (optimized inline functions)
    FORCE_INLINE const char* getDescription() const { return description; }  // Get event description (returns const char*)
    FORCE_INLINE int getBeginningDay() const { return beginning_day; }  // Get event beginning day
    FORCE_INLINE int getBeginningMonth() const { return beginning_month; }  // Get event beginning month
    FORCE_INLINE int getEndingDay() const { return ending_day; }  // Get event ending day
    FORCE_INLINE int getEndingMonth() const { return ending_month; }  // Get event ending month
    FORCE_INLINE int isVide() const { return vide; }  // Check if event is empty
    FORCE_INLINE int getBeginningHour() const { return beginning_hour; }  // Get event beginning hour
    FORCE_INLINE int getBeginningMinutes() const { return beginning_minutes; }  // Get event beginning minute
    FORCE_INLINE int getEndingHour() const { return ending_hour; }  // Get event ending hour
    FORCE_INLINE int getEndingMinutes() const { return ending_minutes; }  // Get event ending minute
    //Founction to compare 2 calendar 
    friend bool operator==(const CalendarEvent& lhs, const CalendarEvent& rhs);

private:
    char description[MAX_DESCRIPTION_LENGTH];  // Event description (fixed size)
    int beginning_day;  // Day when the event begins
    int beginning_month;  // Month when the event begins
    int ending_day;  // Day when the event ends
    int ending_month;  // Month when the event ends
    int beginning_minutes;  // Minute when the event begins
    int beginning_hour;  // Hour when the event begins
    int ending_minutes;  // Minute when the event ends
    int ending_hour;  // Hour when the event ends
    bool vide;  // Indicates if the event is empty or not
};

// Class to represent the current time
class Now {

public :
    // Constructor with detailed parameters for current date and time
    Now(int day, int month, int year, int hour, int minutes)
        : day(day), month(month), year(year), hour(hour) {}

    // Constructor with message (parses the string to extract current time)
    Now(const char* message);

    // Accessor methods to retrieve current time details (optimized inline)
    FORCE_INLINE int getDay() const { return day; }  // Get the current day
    FORCE_INLINE int getMonth() const { return month; }  // Get the current month
    FORCE_INLINE int getYear() const { return year; }  // Get the current year
    FORCE_INLINE int getHour() const { return hour; }  // Get the current hour
    FORCE_INLINE int getMinutes() const { return minutes; }  // Get the current minute

    // Method to verify if an event is ongoing based on current time
    bool eventOnGoing(CalendarEvent event);
    // Method to verify if an event is today based on current time
    bool eventIsToday(CalendarEvent event);
    // Method to determine if it's time to sleep (based on current time and event)
    // Return TimeOfRefresh if false, return the time to sleep before the end of the night if true
    int timeToSleep(CalendarEvent event);
    //the same if ther is no next event
    int timeToSleep();
    //Return true if it is the display of night mode
    bool nightMode();

private:
    int day;  // Current day
    int month;  // Current month
    int year;  // Current year
    int minutes;  // Current minute
    int hour;  // Current hour
};

// Function to separate the message and return the i-th part (for event parsing)
void calendar_string_i(const String& message, int i, char* output, size_t output_size);


#endif // CALENDAR_H
