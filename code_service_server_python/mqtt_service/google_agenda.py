#!/usr/bin/python
# -*- coding:utf-8 -*-
# @see https://developers.google.com/calendar/quickstart/python


from __future__ import print_function
import datetime
import unicodedata

from googleapiclient.discovery import build
from httplib2 import Http
from oauth2client import file, client, tools

#******************************************************************************
# function:    import_calendar
# parameter:
#    g_CalendarsID : List of Google Calendar IDs to fetch events from
# return:
#    String : Formatted string containing calendar events, starting with 'c' 
#            followed by current date and event details
#******************************************************************************
def import_calendar(g_CalendarsID):
    Nb_events = 5
    # ======================================================================================================================
    # Define here all the Google agenda you want to display
    # In Google agenda, each calendar is defined by it's ID (right click on a calendar name, select "Settings" and look for "Calendar's ID"

    g_scopes      = 'https://www.googleapis.com/auth/calendar.readonly'

    # The file token.json stores the user's access and refresh tokens, and is
    # created automatically when the authorization flow completes for the first
    # time.
    store = file.Storage('/var/www/mqtt_listener/token.json')
    creds = store.get()
    if not creds or creds.invalid:
        flow = client.flow_from_clientsecrets('/var/www/mqtt_listener/credentials.json', g_scopes)
        creds = tools.run_flow(flow, store)
    service = build('calendar', 'v3', http=creds.authorize(Http()))

    # Call the Calendar API
    #type of data : 2025-04-10T09:15:45.295452+01:00
    now = datetime.datetime.now(datetime.timezone(datetime.timedelta(hours=1))).isoformat()
    hour = int(now[11:13]) + 1
    new_date = now[:11] + f"{hour:02d}" + now[13:16]

    l_TAB_Events=[]
    for calendarID in g_CalendarsID:
        events_result = service.events().list(calendarId=calendarID, timeMin=now,
                                        maxResults=Nb_events, singleEvents=True,
                                        orderBy='startTime').execute()
        events  = events_result.get('items', [])
        l_TAB_Events.append(events)



    # Cration of the string to send to the arduino
    string_events = "c" + new_date # On créé un string pour que les donées soient facile à récupérer sur arduino
    for events in l_TAB_Events:
        for event in events:
            start  = event['start'].get('dateTime', event['start'].get('date'))
            end   = event['end'].get('dateTime', event['end'].get('date'))

            # sometime, the starting date is in short format (2019-04-13) because there is no time set
            # (this is the case for some event longer  than 24 hours)
            if( "T" in start ):
                temp    = start.split("T")  # ['2019-01-27', '13:00:00+01:00']
            if( "T" in end ):
                temp_end    = end.split("T")  # ['2019-01-27', '13:00:00+01:00']

            else:
                temp   = [start, "00:00:00+00:00"]
                temp_end   = [end, "00:00:00+00:00"]
            date    = temp[0].split("-")
            date_end    = temp_end[0].split("-")

            # Verify if the event has a summary
            # If not, we set a default value : "No title"
            summary = event.get('summary', 'No title')
            # Remove the [ and ] characters from the summary to not confuse the arduino 
            # when it will parse the string
            summary = summary.replace('[', '(')
            summary = summary.replace(']', ')')
            #Add the event to the string
            new_event = "[" + summary + "]" + date[2] + "," + date[1]  + ","  + date_end[2] + "," + date_end[1] +  "," + temp[1][:5] + "," + temp_end[1][:5] 
            if(len(string_events) + len(new_event) < 490):
                string_events += new_event
            else:
                break

    return  string_events

#******************************************************************************
# function:    actualDate
# parameter:
#    None
# return:
#    String : Current date and time in ISO format with +1 hour offset
#******************************************************************************
def actualDate():
    now = datetime.datetime.now(datetime.timezone(datetime.timedelta(hours=1))).isoformat()
    hour = int(now[11:13]) + 1
    new_date = now[:11] + f"{hour:02d}" + now[13:16]
    return new_date
