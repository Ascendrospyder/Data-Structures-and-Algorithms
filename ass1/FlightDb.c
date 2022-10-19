// Implementation of the Flight DB ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FlightDb.h"
#include "List.h"
#include "Tree.h"

#define MIN_DEPARTURE_DAY 0
#define MAX_DEPARTURE_DAY 6 
#define MIN_DEPARTURE_HOUR 0
#define MAX_DEPARTURE_HOUR 23
#define MIN_DEPARTURE_MINUTE 0
#define MAX_DEPARTURE_MINUTE 59
#define DURATION_MINUTES 0 
#define MIN_FLIGHT_NUMBER "0" 
#define MAXIMUM_FLIGHT_NUMBER "zzzzzzzz"

struct flightDb {
    Tree flightNumber; 
    Tree time; 
    Tree dayOfDeparture; 
};

///////////////////////////////// Function Declarations //////////////////////
static int compareFlightNumber(Record record1, Record record2); 
static int compareTime(Record record1, Record record2); 
static int compareDeparture(Record record1, Record record2); 
///////////////////////////////// Function Declarations //////////////////////
FlightDb DbNew(void) {
    FlightDb database = malloc(sizeof(*database));

    if (database == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for the database.\n"); 
        exit(EXIT_FAILURE); 
    }

    // populate the values for the struct by performing the comparisons 
    database->flightNumber = TreeNew(compareFlightNumber); 
    database->time = TreeNew(compareTime); 
    database->dayOfDeparture = TreeNew(compareDeparture); 

    return database; 
}

void DbFree(FlightDb db) 
{
    // free every element in the struct and finally free the database
    TreeFree(db->flightNumber, false);
    TreeFree(db->time, true); 
    TreeFree(db->dayOfDeparture, false);  
    free(db); 
}

bool DbInsertRecord(FlightDb db, Record r) {
    // start by inserting one thing, if it returns true insert the rest
    if (TreeInsert(db->flightNumber, r))
    {
        TreeInsert(db->time, r); 
        TreeInsert(db->dayOfDeparture, r); 
        return true; // update it as true 
    } else {
        return false; // if it's not been inserted flag it as false
    }
}

List DbFindByFlightNumber(FlightDb db, char *flightNumber) {
    // set up a lower and higher bound dummy to perform the search 
    Record lowerBoundDummy = RecordNew(flightNumber, " ", " ", MIN_DEPARTURE_DAY, MIN_DEPARTURE_HOUR, MIN_DEPARTURE_MINUTE, DURATION_MINUTES);
    Record higherBoundDummy = RecordNew(flightNumber, " ", " ", MAX_DEPARTURE_DAY, MAX_DEPARTURE_HOUR, MAX_DEPARTURE_MINUTE, DURATION_MINUTES);  

    List l = TreeSearchBetween(db->flightNumber, lowerBoundDummy, higherBoundDummy); 

    RecordFree(lowerBoundDummy); 
    RecordFree(higherBoundDummy); 

    return l; 
}


List DbFindByDepartureAirportDay(FlightDb db, char *departureAirport,
                                 int day) {
    Record lowerBoundDummy = RecordNew(MIN_FLIGHT_NUMBER, departureAirport, " ", day, MIN_DEPARTURE_HOUR, MIN_DEPARTURE_MINUTE, DURATION_MINUTES);
    Record higherBoundDummy = RecordNew(MAXIMUM_FLIGHT_NUMBER, departureAirport, " ", day, MAX_DEPARTURE_HOUR, MAX_DEPARTURE_MINUTE, DURATION_MINUTES);  

    List l = TreeSearchBetween(db->dayOfDeparture, lowerBoundDummy, higherBoundDummy); 

    RecordFree(lowerBoundDummy); 
    RecordFree(higherBoundDummy); 

    return l; 
}

/**
 * @brief - Searches for all records with departure times between 
    (day1, hour1, min1) and (day2, hour2, min2) (inclusive), 
    and returns them all in a list in increasing order of (day, hour, minute, flight number). 
    Returns an empty list if there are no such records.
    Note: It is possible for (day1, hour1, min1) to be later in the week than (day2, hour2, min2),
    in which case you should return all records from (day1, hour1, min1) to the end of the week and 
    from the start of the week to (day2, hour2, min2). In this case, the records from (day1, hour1, min1)
    to the end of the week should appear first in the list. 
 * 
 * @param db 
 * @param day1 
 * @param hour1 
 * @param min1 
 * @param day2 
 * @param hour2 
 * @param min2 
 * @return List 
 */
List DbFindBetweenTimes(FlightDb db, 
                        int day1, int hour1, int min1, 
                        int day2, int hour2, int min2) {
                            
    Record lowerBoundDummy = RecordNew(MIN_FLIGHT_NUMBER, " ", " ", day1, hour1, min1, DURATION_MINUTES);
    Record higherBoundDummy = RecordNew(MAXIMUM_FLIGHT_NUMBER, " ", " ", day2, hour2, min2, DURATION_MINUTES); 

    List l; 
    if (day1 <= day2 && hour1 <= hour2 && min1 <= min2)
    {
        l = TreeSearchBetween(db->time, lowerBoundDummy, higherBoundDummy);
    } else {
        
        Record endOfDay = RecordNew(MIN_FLIGHT_NUMBER, " ", " ", MAX_DEPARTURE_DAY, MAX_DEPARTURE_HOUR, MAX_DEPARTURE_MINUTE, DURATION_MINUTES);
        Record beginningOfDay = RecordNew(MAXIMUM_FLIGHT_NUMBER, " ", " ", MIN_DEPARTURE_DAY, MIN_DEPARTURE_HOUR, MIN_DEPARTURE_MINUTE, DURATION_MINUTES); 
        
        l = TreeSearchBetween(db->time, lowerBoundDummy, endOfDay);
        List toBeAdded = TreeSearchBetween(db->time, beginningOfDay, higherBoundDummy); 
        
        // join both the lists 
        ListExtend(l, toBeAdded); 

        // finally free the dummy records and the new list made 
        ListFree(toBeAdded); 
        RecordFree(endOfDay); 
        RecordFree(beginningOfDay); 
    } 

    RecordFree(lowerBoundDummy); 
    RecordFree(higherBoundDummy); 

    return l; 
}

/**
 * @brief - Searches for the earliest next flight with the given flight number, on or after the given (day, hour, minute), or NULL if there is no such flight.
    Note: This function must be able to wrap around to the beginning of the next week if there are no such flights later in the week. Note that the flight schedule is 
    the same every week. 
 * 
 * @param db 
 * @param flightNumber 
 * @param day 
 * @param hour 
 * @param min 
 * @return Record 
 */
Record DbFindNextFlight(FlightDb db, char *flightNumber, 
                        int day, int hour, int min) {

    Record dummy_one = RecordNew(flightNumber, " ", " ", day, hour, min, DURATION_MINUTES);
    Record rec = TreeNext(db->flightNumber, dummy_one);

    RecordFree(dummy_one); 

    if (rec != NULL && strcmp(RecordGetFlightNumber(rec), flightNumber) == 0) // if record is not empty and it matches with the departure airport, we found next airport 
    {
        return rec;  

    } else { // if not found we need to wrap to next week, we will utilise a min dummy for this 
        Record dummy_minimum = RecordNew(flightNumber, " ", " ", MIN_DEPARTURE_DAY, MIN_DEPARTURE_HOUR, MIN_DEPARTURE_MINUTE, DURATION_MINUTES); 
        Record wrap_rec = TreeNext(db->flightNumber, dummy_minimum); 

        RecordFree(dummy_minimum); 

        if (wrap_rec != NULL && (strcmp(RecordGetFlightNumber(wrap_rec), flightNumber) != 0)) // this means that if the flight was not found after wrap return NULL
        {
            return NULL; 
        }
        return wrap_rec; 
    }
}
////////////////////////// Helper Functions ///////////////////////////////////
static int compareFlightNumber(Record record1, Record record2) 
{
    int compareFlightNumber = strcmp(RecordGetFlightNumber(record1), RecordGetFlightNumber(record2)); 

    if (compareFlightNumber != 0)
    {
        return compareFlightNumber; 
    }

    int compareDepartureDay = RecordGetDepartureDay(record1) - RecordGetDepartureDay(record2); 

    if (compareDepartureDay != 0)
    {
        return compareDepartureDay; 
    }


    int compareDepartureHour = RecordGetDepartureHour(record1) - RecordGetDepartureHour(record2);

    if (compareDepartureHour != 0)
    {
        return compareDepartureHour; 
    }

    return RecordGetDepartureMinute(record1) - RecordGetDepartureMinute(record2);  
}

static int compareTime(Record record1, Record record2)
{
    int compareDepartureDay = RecordGetDepartureDay(record1) - RecordGetDepartureDay(record2); 

    if (compareDepartureDay != 0)
    {
        return compareDepartureDay; 
    }

    int compareDepartureHour = RecordGetDepartureHour(record1) - RecordGetDepartureHour(record2);
    
    if (compareDepartureHour != 0)
    {
        return compareDepartureHour;
    }

    int compareDepartureMinute = RecordGetDepartureMinute(record1) - RecordGetDepartureMinute(record2);  
    
    if (compareDepartureMinute != 0)
    {
        return compareDepartureMinute; 
    }
    
    return strcmp(RecordGetFlightNumber(record1), RecordGetFlightNumber(record2)); 
}

static int compareDeparture(Record record1, Record record2)
{
    int compareDepartureAirport = strcmp(RecordGetDepartureAirport(record1), RecordGetDepartureAirport(record2));

    if (compareDepartureAirport != 0)
    {
        return compareDepartureAirport; 
    }


    int compareDepartureDay = RecordGetDepartureDay(record1) - RecordGetDepartureDay(record2); 
    
    if (compareDepartureDay != 0)
    {
        return compareDepartureDay; 
    }


    int compareDepartureHour = RecordGetDepartureHour(record1) - RecordGetDepartureHour(record2);
    
    if (compareDepartureHour != 0)
    {
        return compareDepartureHour; 
    }

    int compareDepartureMinute = RecordGetDepartureMinute(record1) - RecordGetDepartureMinute(record2);  
    
    if (compareDepartureMinute != 0)
    {
        return compareDepartureMinute; 
    }

    return strcmp(RecordGetFlightNumber(record1), RecordGetFlightNumber(record2)); 
}
////////////////////////// Helper Functions ///////////////////////////////////
