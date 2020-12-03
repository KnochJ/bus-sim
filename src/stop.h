/**
 * @file stop.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_STOP_H_
#define SRC_STOP_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <list>
#include <iostream>

#include "src/bus.h"
#include "src/passenger.h"
#include "src/data_structs.h"

class Bus;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for the generation of stop.
 *
 * Calls to \ref Generate function to get a new instance of a stop.
 *  
 */

class Stop {
 public:
/**
  * @brief Constructs a stop with an id and longitude/latitude coordinates.
  *
  *
  * @param[in] int holding an id number
  * @param[in] double holding a longitude value.
  * @param[in] double holding a latitude value.
  *
  * @return stop object with id, longitude, and latitude.
  */
  explicit Stop(int, double = 44.973723, double = -93.235365);

/**
  * @brief GetID is an important getter used to determine
  * when a passenger has reached their stop destination.
  *
  * It is also used in displaying Report information, but this 
  * method is very useful for comparing against a passengers 
  * destination id.
  *
  * @param[in] none.
  *
  * @return integer which is the stop id.
  */
  int GetId() const;

/**
  * @brief GetLatitude returns the latitude associated with the Stop.
  *
  * @param[in] none.
  *
  * @return double which is the Stop's latitude value.
  */
  double GetLatitude();  // const?

/**
  * @brief GetLongitude returns the longitude associated with the Stop.
  *
  * @param[in] none.
  *
  * @return double which is the Stop's longitude value.
  */
  double GetLongitude();  // const?

/**
  * @brief GetNumPeople is called by UpdateRouteData to determine the number
  * of people waiting at a given stop.
  *
  * @param[in] none.
  *
  * @return integer which is the number of people at a stop.
  */
  int GetNumPeople();

/**
  * @brief AddPassengers adds the passengers generated to the stop.
  *
  *
  * @param[in] pointer to Passenger.
  *
  * @return integer flagging for successful adding.
  */
  int AddPassengers(Passenger *);

/**
  * @brief LoadPassengers takes in a Bus pointer and sends the passengers
  * in the stop list to the bus list.
  *
  * @param[in] pointer to Bus.
  *
  * @return integer flagging for successful adding.
  */
  int LoadPassengers(Bus *);

/**
  * @brief Update: Stop is responsible for updating all the Passengers waiting
  * at the given stop.
  *
  * @param[in] none.
  *
  * @return none.
  */
  void Update();

/**
  * @brief Report displays current information about the passengers waiting at
  * at the stop.
  *
  * @param[in] std::ostream&.
  *
  * @return none.
  */
  void Report(std::ostream&) const;
  // int GetSizeList(); //

 private:
  int id_;

/**
  * @brief passenger_ list keeps track of the passengers at a stop. Considered
  * array, vector, queue, list.
  */
  std::list<Passenger *> passengers_;  // considered array, vector, queue, list
  double longitude_;
  double latitude_;
  StopData stop_data_;
  // derived information - not needed depending on passengers_
  // data structure implementation?
  // int passengers_present_;
};
#endif  // SRC_STOP_H_
