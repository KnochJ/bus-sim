/**
 * @file route.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include <vector>

#include "src/route.h"

/**
  * @brief The route needs to have a list of pointers to stop pointers and
  * a list of pointers to a double for the distances. We iterate through
  * the lists stops and distances lists given in the parameters and these
  * are added to the route.
  *
  */
Route::Route(std::string name, Stop ** stops, double * distances,
  int num_stops, PassengerGenerator * generator) {
  for (int i = 0; i < num_stops; i++) {
    stops_.push_back(stops[i]);
  }
  for (int i = 0; i < num_stops - 1; i++) {
    distances_between_.push_back(distances[i]);
  }
  name_ = name;
  num_stops_ = num_stops;
  generator_ = generator;
  destination_stop_index_ = 0;
  // UpdateRouteData();  // causes segfault in testing when updating here
}

/**
  * @brief Clone is used to create Route prototypes. Copies a Route 
  * and returns the new cloned Route pointer.
  *
  */
Route * Route::Clone() {
  // Copy the list of stops
  Stop ** clone_stops = new Stop *[stops_.size()];
  int stop_index = 0;
  for (std::list<Stop *>::iterator it = stops_.begin();
       it != stops_.end(); it++) {
    clone_stops[stop_index] = (*it);
    stop_index++;
  }
  // Copy our distance list.
  double * clone_dist = new double[distances_between_.size()];
  int dist_index = 0;
  for (std::list<double>::iterator it = distances_between_.begin();
       it != distances_between_.end(); it++) {
    clone_dist[dist_index] = (*it);
    dist_index++;
  }
  // Create the new Route pointer to return
  Route * clone_route = new Route(name_, clone_stops, clone_dist, num_stops_,
                                  generator_);

  return clone_route;
}

/**
  * @brief Route iterates through its stops and calls update of them. After they 
  * have updated, then the GenerateNewPassengers method is called to generate 
  * passengers at the stops.
  *
  */
void Route::Update() {
  for (std::list<Stop *>::iterator it = stops_.begin();
       it != stops_.end(); it++) {
    (*it)->Update();
  }
  UpdateRouteData();
  // Generate our passengers for the stops after updating
  GenerateNewPassengers();
}

/**
  * @brief The destination_stop_index incremented in the NextStop method is
  * used here to check if there are any more stops left in the route.
  * The index is initialized to 0 and the number of stops starts its
  * count at 1.
  */
bool Route::IsAtEnd() const {
  if (destination_stop_index_ <= num_stops_) {
    return false;  // was <= - 1
  } else {
    return true;
  }
}

/**
  * @brief NextStop takes care of setting the destination_stop_ and the 
  * distance_to_stop_ by utilizing the methods GetSpecificStop() and
  * GetSpecificDistance(). We use a if-else to check whether we still have
  * more stops to progress to, or if we are at the end of a route. We can 
  * determine where were are in a given route by having an index called
  * destination_stop_index_. We increment this index to move to the next stop
  * in the list of stops. If this index is greater than the number of stops a
  * route, then we have reached the end of the route. Setting the index to the 
  * number of stops signals to the function IsAtEnd() that this route is done.
  *
  */
void Route::NextStop() {
  if (destination_stop_index_ <= num_stops_ - 1) {  // was <=
    destination_stop_ = GetSpecificStop(destination_stop_index_);
    distance_to_stop_ = GetSpecificDistance(destination_stop_index_);
    // set the previous stop as long as we are past the first stop.
    if (destination_stop_index_ > 0) {
      previous_destination_stop_ = GetSpecificStop(destination_stop_index_ - 1);
    } else {
      previous_destination_stop_ = destination_stop_;
    }
    destination_stop_index_++;
    // implement triptotal
  } else {
      destination_stop_index_ = num_stops_ + 5;  // Signals the end of a route.
  }
}

/**
  * @brief GetSpecificStop takes in an integer which represents the index for
  * finding a particular stop in the list. The stop_counter is used to keep
  * track of where we are in the list. As we iterate through the list, this 
  * counter is incremented. We check to see when the counter and index are 
  * equal. If they are, this is the specific Stop we want to return. If the 
  * counter never equals the index then we return NULL since the Stop doesn't
  * exist in the list.
  */
Stop * Route::GetSpecificStop(int specific_index) {
  int stop_counter = 0;
  for (std::list<Stop *>::const_iterator it = stops_.begin();
       it != stops_.end(); it++) {
    if (specific_index != stop_counter) {
      stop_counter++;
    } else {
      return (*it);
    }
  }
  return NULL;  // We didn't find the specific Stop
}

/**
  * @brief GetSpecificDistance takes in an integer which represents the index
  * for finding a particular distance in the list. The distance_counter is used
  * to keep track of where we are in the list. As we iterate through the list, 
  * this counter is incremented. We check to see when the counter and index are 
  * equal. If they are, this is the specific distnace we want to return. If the 
  * counter never equals the index then we return NULL since the distance
  * doesn't exist in the list.
  */
double Route::GetSpecificDistance(int specific_index) {
  int distance_counter = 0;
  for (std::list<double>::iterator it = distances_between_.begin();
       it != distances_between_.end(); it++) {
    if (specific_index != distance_counter) {
      distance_counter++;;
    } else {
      return (*it);
    }
  }
  return -1;  // We didn't find the specific distance bewteen stops.
}

/**
  * @brief Used to get a Stop pointer, which is the destination.
  *
  */
Stop * Route::GetDestinationStop() const {
  return destination_stop_;
}

/**
  * @brief Used to get a Stop pointer, which is the previous stop.
  *
  */
Stop * Route::GetPreviousDestinationStop() const {
  return previous_destination_stop_;
}

/**
  * @brief Used to determine how close a bus is to reaching the current stop.
  *
  */
double Route::GetNextStopDistance() const {
  return distance_to_stop_;
}

/**
  * @brief Report displays important information about stops on a route.
  *
  */
void Route::Report(std::ostream & out) {
  out << "Name: " << name_ << std::endl;
  out << "Num stops: " << num_stops_ << std::endl;
  int stop_counter = 0;
  for (std::list<Stop *>::const_iterator it = stops_.begin();
       it != stops_.end(); it++) {
    (*it)->Report(out);
    stop_counter++;
  }
}

/**
  * @brief Used to generate passengers after all of the stops in the route have
  * been updated.
  *
  */
int Route::GenerateNewPassengers() {
  int result = generator_ -> GeneratePassengers();
  return result;
}

/**
  * @brief GetName is called by the visualizer to obtain the name of the route.
  *
  */
std::string Route::GetName() {
  return name_;
}

/**
  * @brief GetStops is called by the visualizer to obtain the list of Stop
  * pointers.
  *
  */
std::list<Stop *> Route::GetStops() {
  return stops_;
}

/**
  * @brief GetRouteData is called by the visualizer to to populate the
  * RouteData struct with the lastest information.
  *
  */
RouteData Route::GetRouteData() {
  return route_data_;
}

/**
  * @brief UpdateRouteData is called by the visualizer to instruct the Route
  * object to populate the RouteData struct with the latest information. The
  * method uses the getter methods to populate the struct. To get info on the
  * Stop objects in the list, we iterate through the stop list and create a new
  * Stop struct for each Stop. These Stop structs are populated with their
  * latest info. Once a struct has been created and populated, it is then 
  * pushed onto a vector that is stored in the Route struct.
  *
  */
void Route::UpdateRouteData() {
  // Populate the RouteData struct id with Route name.
  route_data_.id = GetName();
  // Create a vector of StopData structs.
  std::vector<StopData> stops_vector;
  for (std::list<Stop *>::const_iterator it = stops_.begin();
       it != stops_.end(); it++) {
    StopData stop_data_;
    stop_data_.id = std::to_string((*it) -> GetId());
    Position stop_pos;
    stop_pos.y = (*it) -> GetLatitude();
    stop_pos.x = (*it) -> GetLongitude();
    stop_data_.position = stop_pos;
    stop_data_.num_people = (*it) -> GetNumPeople();
    stops_vector.push_back(stop_data_);
  }
  route_data_.stops = stops_vector;
}
