// Implementation of the Flight DB ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FlightDb.h"
#include "List.h"
#include "Tree.h"

#define MIN_DEPARTURE_DAY     0
#define MAX_DEPARTURE_DAY     6
#define MIN_DEPARTURE_HOUR    0
#define MAX_DEPARTURE_HOUR    23
#define MIN_DEPARTURE_MINUTE  0
#define MAX_DEPARTURE_MINUTE  59
#define DURATION_MINUTES      0
#define MIN_FLIGHT_NUMBER     "0"
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

/**
 * @brief - The following function creates a new flight DB
 * 
 * @return FlightDb - The new FlightDb 
 */
FlightDb DbNew(void) {
	FlightDb database = malloc(sizeof(*database));

	if (database == NULL) {
		fprintf(stderr, "Failed to allocate memory for the database.\n");
		exit(EXIT_FAILURE);
	}

	// populate the values for the struct by performing the comparisons
	database->flightNumber = TreeNew(compareFlightNumber);
	database->time = TreeNew(compareTime);
	database->dayOfDeparture = TreeNew(compareDeparture);

	return database;
}

/**
 * @brief - The following function frees all memory associated with the given DB
 * 
 * @param db - FlightDb db 
 */
void DbFree(FlightDb db) {
	// free every element in the struct and finally free the database
	TreeFree(db->flightNumber, false);
	TreeFree(db->time, true);
	TreeFree(db->dayOfDeparture, false);
	free(db);
}

/**
 * @brief - Inserts a flight record into the given DB if the DB does not already contain a 
 * record with the same flight number and departure day, hour and minute. Returns true if 
 * the record was inserted into the DB, and false if the DB already contained a record with 
 * the same flight number and departure day, hour and minute.
 * 
 * @param db - FlightDb db 
 * @param r - Record r 
 * @return true - if record was successfully inserted into the db 
 * @return false - if the record was not inserted into the db 
 */
bool DbInsertRecord(FlightDb db, Record r) {
	// start by inserting one thing, if it returns true insert the rest
	if (TreeInsert(db->flightNumber, r)) {
		TreeInsert(db->time, r);
		TreeInsert(db->dayOfDeparture, r);
		return true;  // update it as true
	} else {
		return false;  // if it's not been inserted flag it as false
	}
}

/**
 * @brief - Searches for all records with the given flight number, and returns them 
 * all in a list in increasing order of (day, hour, minute). Returns an empty list if 
 * there are no such records.
 * 
 * @param db - FlightDb db 
 * @param flightNumber - char *flightNumber 
 * @return List - new list of all the flights based on the flight number in between 
 * the lower and upper bound inputs (inclusive)
 */
List DbFindByFlightNumber(FlightDb db, char *flightNumber) {
	// set up a lower and higher bound dummy to perform the search
	Record lowerBoundDummy =
	    RecordNew(flightNumber, " ", " ", MIN_DEPARTURE_DAY, MIN_DEPARTURE_HOUR,
	              MIN_DEPARTURE_MINUTE, DURATION_MINUTES);
	Record higherBoundDummy =
	    RecordNew(flightNumber, " ", " ", MAX_DEPARTURE_DAY, MAX_DEPARTURE_HOUR,
	              MAX_DEPARTURE_MINUTE, DURATION_MINUTES);

	List l =
	    TreeSearchBetween(db->flightNumber, lowerBoundDummy, higherBoundDummy);

	RecordFree(lowerBoundDummy);
	RecordFree(higherBoundDummy);

	return l;
}

/**
 * @brief - Searches for all records with the given departure airport and day 
 * of the week, and returns them all in a list in increasing order of 
 * (hour, minute, flight number). Returns an empty list if there are no 
 * such records.
 * 
 * @param db - FlightDb db 
 * @param departureAirport - char *departureAirport 
 * @param day - int day  
 * @return List - list with all flights based on departure airport day between 
 * lower and upper bound (inclusive)
 */
List DbFindByDepartureAirportDay(FlightDb db, char *departureAirport, int day) {
	Record lowerBoundDummy =
	    RecordNew(MIN_FLIGHT_NUMBER, departureAirport, " ", day,
	              MIN_DEPARTURE_HOUR, MIN_DEPARTURE_MINUTE, DURATION_MINUTES);
	Record higherBoundDummy =
	    RecordNew(MAXIMUM_FLIGHT_NUMBER, departureAirport, " ", day,
	              MAX_DEPARTURE_HOUR, MAX_DEPARTURE_MINUTE, DURATION_MINUTES);

	List l = TreeSearchBetween(db->dayOfDeparture, lowerBoundDummy,
	                           higherBoundDummy);

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
 * @param db - Flight db 
 * @param day1 - int day1
 * @param hour1 - int hour1
 * @param min1 - int min1
 * @param day2 - int day2
 * @param hour2 - int hour2
 * @param min2 - int min2 
 * @return List - list will all flights between lower and upper bound times (inclusive)
 */
List DbFindBetweenTimes(FlightDb db, int day1, int hour1, int min1, int day2,
                        int hour2, int min2) {
	Record lowerBoundDummy = RecordNew(MIN_FLIGHT_NUMBER, " ", " ", day1, hour1,
	                                   min1, DURATION_MINUTES);
	Record higherBoundDummy = RecordNew(MAXIMUM_FLIGHT_NUMBER, " ", " ", day2,
	                                    hour2, min2, DURATION_MINUTES);

	List l;
	if (day1 <= day2 && hour1 <= hour2 && min1 <= min2) {
		l = TreeSearchBetween(db->time, lowerBoundDummy, higherBoundDummy);
	} else {
		// keep track of a record at the end of the week and beginning of the week
		Record endOfWeek = RecordNew(MIN_FLIGHT_NUMBER, " ", " ",
		                             MAX_DEPARTURE_DAY, MAX_DEPARTURE_HOUR,
		                             MAX_DEPARTURE_MINUTE, DURATION_MINUTES);
		Record beginningOfWeek = RecordNew(
		    MAXIMUM_FLIGHT_NUMBER, " ", " ", MIN_DEPARTURE_DAY,
		    MIN_DEPARTURE_HOUR, MIN_DEPARTURE_MINUTE, DURATION_MINUTES);

		// if we need to wrap to the next week we need to spilt searches e.g. first check for lower <= flights <= endOfWeek
		// then check beginningOfWeek <= flights <= upper
		l = TreeSearchBetween(db->time, lowerBoundDummy, endOfWeek);
		List toBeAdded =
		    TreeSearchBetween(db->time, beginningOfWeek, higherBoundDummy);

		// join both the lists
		ListExtend(l, toBeAdded);

		// finally free the dummy records and the new list made
		ListFree(toBeAdded);
		RecordFree(endOfWeek);
		RecordFree(beginningOfWeek);
	}

	RecordFree(lowerBoundDummy);
	RecordFree(higherBoundDummy);

	return l;
}

/**
 * @brief - Searches for the earliest next flight with the given flight number, on or after
 * the given (day, hour, minute), or NULL if there is no such flight. 
 * Note: This function must be able to wrap around to the beginning of the next week if there 
 * are no such flights later in the week. Note that the flight schedule is the same every week. 
 * 
 * @param db - FlightDb db 
 * @param flightNumber - char *flightNumber 
 * @param day - int day 
 * @param hour - int hour 
 * @param min - int min 
 * @return Record - Record of the next available flight
 */
Record DbFindNextFlight(FlightDb db, char *flightNumber, int day, int hour,
                        int min) {
	Record dummy_one =
	    RecordNew(flightNumber, " ", " ", day, hour, min, DURATION_MINUTES);
	Record rec = TreeNext(db->flightNumber, dummy_one);

	RecordFree(dummy_one);
	// if record is not empty and it matches with the departure airport,
	// we found next airport
	if (rec != NULL && strcmp(RecordGetFlightNumber(rec), flightNumber) == 0) {
		return rec;

	} else {  // if not found we need to wrap to next week, we will utilise a min dummy for this
		Record dummy_minimum = RecordNew(
		    flightNumber, " ", " ", MIN_DEPARTURE_DAY, MIN_DEPARTURE_HOUR,
		    MIN_DEPARTURE_MINUTE, DURATION_MINUTES);
		Record wrap_rec = TreeNext(db->flightNumber, dummy_minimum);

		RecordFree(dummy_minimum);

		if (wrap_rec != NULL &&
		    (strcmp(RecordGetFlightNumber(wrap_rec), flightNumber) !=
		     0))  // this means that if the flight
		{         // was not found after wrap return NULL
			return NULL;
		}
		return wrap_rec;
	}
}
////////////////////////// Helper Functions ///////////////////////////////////
static int compareFlightNumber(Record record1, Record record2) {
	int compareFlightNumber =
	    strcmp(RecordGetFlightNumber(record1), RecordGetFlightNumber(record2));
	if (compareFlightNumber != 0)
		return compareFlightNumber;

	int compareDepartureDay =
	    RecordGetDepartureDay(record1) - RecordGetDepartureDay(record2);
	if (compareDepartureDay != 0)
		return compareDepartureDay;

	int compareDepartureHour =
	    RecordGetDepartureHour(record1) - RecordGetDepartureHour(record2);
	if (compareDepartureHour != 0)
		return compareDepartureHour;

	return RecordGetDepartureMinute(record1) -
	       RecordGetDepartureMinute(record2);
}

static int compareTime(Record record1, Record record2) {
	int compareDepartureDay =
	    RecordGetDepartureDay(record1) - RecordGetDepartureDay(record2);
	if (compareDepartureDay != 0)
		return compareDepartureDay;

	int compareDepartureHour =
	    RecordGetDepartureHour(record1) - RecordGetDepartureHour(record2);
	if (compareDepartureHour != 0)
		return compareDepartureHour;

	int compareDepartureMinute =
	    RecordGetDepartureMinute(record1) - RecordGetDepartureMinute(record2);
	if (compareDepartureMinute != 0)
		return compareDepartureMinute;

	return strcmp(RecordGetFlightNumber(record1),
	              RecordGetFlightNumber(record2));
}

static int compareDeparture(Record record1, Record record2) {
	int compareDepartureAirport = strcmp(RecordGetDepartureAirport(record1),
	                                     RecordGetDepartureAirport(record2));
	if (compareDepartureAirport != 0)
		return compareDepartureAirport;

	int compareDepartureDay =
	    RecordGetDepartureDay(record1) - RecordGetDepartureDay(record2);
	if (compareDepartureDay != 0)
		return compareDepartureDay;

	int compareDepartureHour =
	    RecordGetDepartureHour(record1) - RecordGetDepartureHour(record2);
	if (compareDepartureHour != 0)
		return compareDepartureHour;

	int compareDepartureMinute =
	    RecordGetDepartureMinute(record1) - RecordGetDepartureMinute(record2);
	if (compareDepartureMinute != 0)
		return compareDepartureMinute;

	return strcmp(RecordGetFlightNumber(record1),
	              RecordGetFlightNumber(record2));
}
////////////////////////// Helper Functions ///////////////////////////////////
