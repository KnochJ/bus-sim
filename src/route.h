/**
 * @file route.h
 *
 * @Copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_ROUTE_H_
#define SRC_ROUTE_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <list>
#include <iostream>
#include <string>

#include "src/passenger_generator.h"
#include "src/stop.h"
#include "src/data_structs.h"

class PassengerGenerator;
class Stop;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for the generation of route.
 *
 * Calls to \ref Generate function to get a new instance of a route.
 *  
 */
class Route {
 public:
/**
  * @brief Constructs a route with a standard name, pointer to stop pointers,
  * distances pointer, number of stops, and a passenger generator pointer.
  *
  * @param[in] string holding an id number.
  * @param[in] pointer to Stop holding stops pointers.
  * @param[in] pointer to double holding distances.
  * @param[in] integer holding number of stops
  * @param[in] pointer holding a passenger generator.
  *
  * @return route object with standard name, pointer to stop pointers, pointer
  * to distances, number of stops, and a pointer to the passenger generator.
  */
  Route(std::string name, Stop ** stops, double * distances, int num_stops,
        PassengerGenerator *);
/**
  * @brief Clone is used to create a prototype of the route.
  * 
  * @param[in] none.
  *
  * @return copy of the route as a route pointer.
  */
  Route * Clone();  // Clone prototype route

/**
  * @brief Updates for a Route, in turn, updates each stop that belongs to 
  * the route. After this Update is called, then passengers are generated
  * for the Route's stops.
  *
  * @param[in] none.
  *
  * @return none.
  */
  void Update();

/**
  * @brief Report method can take an ostream object and produce output on the
  * details of the route.
  *
  * @param[in] standard ostream object.
  */
  void Report(std::ostream&);

/**
  * @brief IsAtEnd is used to determine, for a given incoming or outgoing
  * route, has reached the last stop in the route.
  *
  * @param[in] none;
  *
  * @return boolean on whether the end has been reached.
  */
  bool IsAtEnd() const;

/**
  * @brief NextStop handles multiple steps necessary to keep progess on a route
  * accurate. It handles getting the next stop in the route as well as
  * retrieving the new distance to that stop.
  * 
  * @param[in] none;
  *
  * @return none.
  *
  */
  void NextStop();

/**
  * @brief GetSpecificStop is a getter that allows us to specify an element in
  * the Stops list and return that Stop pointer.
  * 
  * @param[in] integer which is the index to find the correct stop in the list;
  *
  * @return Stop pointer which is the specified stop in the route.
  *
  */
  Stop * GetSpecificStop(int);

/**
  * @brief GetSpecificDistance is a getter that allows us to specify which
  * element in the distances_between_ list we want to return. 
  * 
  * @param[in] integer which is the index to find the correct stop's distance
  * in the list;
  *
  * @return double which is the distance specified by the index.
  *
  */
  double GetSpecificDistance(int);

/**
  * @brief GetDestinationStop is a getter to retrieve the current destination
  *        stop. 
  *
  * This method is important for the Unload and Load passenger methods
  * to correctly determine where a bus is in its route.
  *
  * @param[in] none;
  *
  * @return Stop pointer which is the stop the bus is travelling to.
  */
  Stop * GetDestinationStop() const;

/**
  * @brief GetPreviousDestinationStop is a getter to retrieve the previous
  *        destination stop. 
  *
  * @param[in] none;
  *
  * @return Stop pointer which is the previous stop the bus was at.
  */
  Stop * GetPreviousDestinationStop() const;

/**
  * @brief GetNextStopDistance is a getter to retrieve the distance to the
  *        next stop.
  *
  * This method is important for the Move method in Bus since
  * once a stop has been reached we need to get the next distance.
  *
  * @param[in] none;
  *
  * @return double value which is the distance from a stop to the next stop.
  */   
  double GetNextStopDistance() const;

/**
  * @brief GetName is called by the visualizer to obtain the name of the route.
  *
  * @param[in] none;
  *
  * @return string which is the name of the route.
  */ 
  std::string GetName();

/**
  * @brief GetStops is called by the visualizer to obtain the list of Stop
  * pointers.
  *
  * @param[in] none;
  *
  * @return standard list which is a list stop pointers on the route.
  */ 
  std::list<Stop *> GetStops();

/**
  * @brief Called by the visualizer to obtain the RouteData struct.
  *
  * @param[in] none;
  *
  * @return RouteData struct which is contained in route_data_.
  */ 
  RouteData GetRouteData();

/**
  * @brief Called by the visualizer to instruct the Route object to populate
  * the RouteData struct the latest information.
  *
  * @param[in] none;
  *
  * @return none.
  */ 
  void UpdateRouteData();
  // double GetTotalRouteDistance() const;
 private:
/**
  * @brief GenerateNewPassengers is called after the route has been updated.
  *
  * @return integer for successful generation of passengers at stops
  */
  int GenerateNewPassengers();       // generates passengers on its route

/**
  * @brief route_data_ contains the current information for the RouteData struct.
  *
  */
  RouteData route_data_;

/**
  * @brief Route needs a pointer to PassengerGenerator to produce passengers
  * at the stops after it updates.
  *
  */
  PassengerGenerator * generator_;

/**
  * @brief List of stops on either an outgoing route, or incoming route.
  *
  */
  std::list<Stop *> stops_;

/**
  * @brief List of distances between stops on a route. Note: this list is
  * length = num_stops_-1.
  *
  */  
  std::list<double> distances_between_;
  std::string name_;
  int num_stops_;

/**
  * @brief integer destination_stop_index_ is used to keep track of what 
  * is the current stop in the list. Initialized to 0.
  *
  */
  int destination_stop_index_;

/**
  * @brief Stop pointer which is the stop the bus is traveling to.
  *
  */
  Stop * destination_stop_;
/**
  * @brief Stop pointer which is the previous stop the bus was at.
  *
  */
  Stop * previous_destination_stop_;
/**
  * @brief Distance to the stop the bus is traveling to.
  *
  */
  double distance_to_stop_;
  // double trip_time_; // derived data - total distance travelled on route
};
#endif  // SRC_ROUTE_H_
