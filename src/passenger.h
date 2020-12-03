
/**
 * @file passenger.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_PASSENGER_H_
#define SRC_PASSENGER_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <string>
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for the generation of passengers.
 *
 * Calls to \ref Generate function to get a new instance of a passenger.
 *  This is a static call, not requiring an instance to invoke the method.
 */

class Passenger {  // : public Reporter {
 public:
/**
  * @brief Constructs a passenger with a standard name and id.
  *
  *
  * @param[in] int holding an id number
  * @param[in] string holding a name of a created passenger.
  *
  * @return Passenger object with name and destination.
  */
  explicit Passenger(int = -1, std::string = "Nobody");

/**
  * @brief Inside Update is where the passenger has their time incremented
  * depending what object they belong to (Bus or Stop).
  *
  * @param[in] none.
  *
  * @return none.
  */
  void Update();

/**
  * @brief GetOnBus changes the status of a passenger from waiting at stop
  * to on bus.
  *
  * @param[in] none.
  *
  * @return none.
  */
  void GetOnBus();
/**
  * @brief GetTotalWait is a const method that returns an integer corresponding
  * to the total amount of time waiting at stop and time on bus.
  *
  * @param[in] none.
  *
  * @return integer of total time.
  */
  int GetTotalWait() const;

/**
  * @brief IsOnBus is a simple method checking if a passenger is riding a bus.
  *
  * @param[in] none.
  *
  * @return boolean signaling passenger is on a bus.
  */
  bool IsOnBus() const;

/**
  * @brief GetDestination returns the stop that the passenger needs to get
  * off at.
  *
  * @param[in] none.
  *
  * @return integer representing the stop id.
  */
  int GetDestination() const;

/**
  * @brief Report method can take an ostream object and produce output on the
  * details of the given passenger.
  *
  * @param[in] standard ostream object.
  *
  * @return none.
  */
  void Report(std::ostream&) const;

 private:
 /**
  * @brief Generation of randomized passenger name from prefix, stems and suffixes.
  *
  * @return Randomized passenger name.
  */
  std::string name_;
  int destination_stop_id_;
  int wait_at_stop_;
  int time_on_bus_;
  int id_;
/**
  * @brief Global count used to set ID for new instances.
  *
  */
  static int count_;
};
#endif  // SRC_PASSENGER_H_
