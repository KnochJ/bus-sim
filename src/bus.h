/**
 * @file bus.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_BUS_H_
#define SRC_BUS_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <iostream>
#include <list>
#include <string>

#include "src/passenger.h"
#include "src/route.h"
#include "src/stop.h"
#include "src/data_structs.h"

class Route;
class Stop;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for the generation of buses.
 *
 * Calls to \ref Generate function to get a new instance of a bus.
 * 
 */
class Bus {
 public:
/**
  * @brief Constructs a bus with a standard name, pointer outbound route, 
  * pointer to inbound route, integer with max capacity, and a double for 
  * speed.  
  *
  * @param[in] string holding an name.
  * @param[in] pointer holding outbound route.
  * @param[in] pointer holding inbound route.
  * @param[in] integer holding maxiumum capacity for bus.
  * @param[in] double holding speed of the bus.
  *
  * @return route object with standard name, pointer to outbound route, pointer to 
  * inbound route, integer for maximum capacity, and a double for bus speed.
  */
  Bus(std::string name, Route * out, Route * in, int capacity = 60,
                                                 double speed = 1);

/**
  * @brief LoadPassengers gets a stop pointer that can be used to then
  * call the method in Stop to load each passenger. 
  *
  * @param[in] Pointer to Route.
  *
  * @return boolean value for successful loading of passengers.
  */
  bool LoadPassengers(Route*);

/**
  * @brief LoadPassengers gets a Passenger pointer from the stop to
  * be added to the bus.
  *
  * @param[in] Pointer to Passenger.
  *
  * @return boolean value for successful loading of a passenger.
  */
  bool LoadPassenger(Passenger*);

/**
  * @brief UnloadPassengers simply removes the passenger from the bus 
  * passenger list. These passengers are not added to anything else.
  *
  * @param[in] Pointer to route.
  *
  * @return boolean value for successful unloading of passenger.
  */
  bool UnloadPassenger(Route*);

/**
  * @brief Move is responsible for correctly moving the bus through its 
  * route. 
  *
  *  Beginning with the outbound route, the bus moves until it hits
  * the end and it proceeds back on the inbound route. Inside of move is also
  * where the unloading and loading of passengers is determined.
  *
  * @param[in] none.
  *
  * @return boolean value for successful moving of the bus.
  */
  bool Move();

/**
  * @brief IsTripComplete, like the names suggests, handles whether the bus 
  * is finished with both outbound and inbound routes.
  *
  *
  * @param[in] none.
  *
  * @return boolean value for flagging end of trip.
  */
  bool IsTripComplete();  // checks if both outbound and inbound are done

/**
  * @brief Inside Update is where calls to Move are handled. 
  * 
  * The ordering for update is important since the bus must move first, which
  * then leads to unloading/loading of passengers. After this is complete,
  *  then the bus updates the passengers that are currently riding it. 
  * 
  * @param[in] none.
  * 
  * @return none.
  */
  void Update();

/**
  * @brief Report method can take an ostream object and produce output on the
  * details of the bus.
  *
  * @param[in] standard ostream object.
  *
  * @return none.
  */
  void Report(std::ostream&);

/**
  * @brief Called by the visualizer to get the maxiumum number of passengers
  * that the bus can hold.
  *
  * @param[in] none.
  *
  * @return integer representing max capacity for the bus.
  */
  int GetCapacity();

/**
  * @brief Called by the visualizer to get the maxiumum number of passengers
  * that the bus can hold.
  *
  * @param[in] none.
  *
  * @return size_t which is the size of the passenger list.
  */
  size_t GetNumPassengers();

/**
  * @brief Called by the visualizer to get the name of the bus.
  *
  * @param[in] none.
  *
  * @return string which is the name of the bus.
  */
  std::string GetName() const;

/**
  * @brief Called by the visualizer to get the next stop in the route.
  *
  * @param[in] none.
  *
  * @return Stop pointer which contains the next stop.
  */
  Stop * GetNextStop();

/**
  * @brief Called by the visualizer to get the previous stop in the route.
  *
  * @param[in] none.
  *
  * @return Stop pointer which contains the previous stop.
  */
  Stop * GetPreviousStop();

/**
  * @brief Called by the visualizer to obtain the BusData struct.
  *
  * @param[in] none.
  *
  * @return BusData which is the struct containing bus_data_.
  */
  BusData GetBusData();

  // void AtStop(bool);
  // bool IsBusAtStop();

/**
  * @brief Called by the visualizer to instruct the Bus object to populate the
  * BusData struct with the latest information.
  *
  * @param[in] none.
  *
  * @return none.
  */
  void UpdateBusData();

 private:
/**
  * @brief bus_data_ contains the current information for the BusData struct.
  *
  */
  BusData bus_data_;
/**
  * @brief passengers_ keeps track of the passengers on a given bus.
  *
  */
  std::list<Passenger *> passengers_;
/**
  * @brief passenger_max_capacity_ .
  *
  */
  int passenger_max_capacity_;
  std::string name_;
  double speed_;  // could also be called "distance travelled in one time step"
/**
  * @brief A bus' trip is split into two routes, outgoing and incoming route.
  *
  */
  Route * outgoing_route_;
  Route * incoming_route_;
  double distance_remaining_;  // when negative?, unload/load procedure occurs
                              // AND next stop set
  // double revenue_; // revenue collected from passengers, doesn't include
                      // passengers who pay on deboard
  // double fuel_;   // may not be necessary for our simulation
  // double max_fuel_;
  // bool at_stop_;
};
#endif  // SRC_BUS_H_
