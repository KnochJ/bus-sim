/**
 * @file bus.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include "src/bus.h"

/**
  * @brief Constructs a Bus object which needs to have a name,
  * outgoing route, incoming route, capacity, and a speed.
  *
  */
Bus::Bus(std::string name, Route * out, Route * in, int capacity,
         double speed) {
  name_ = name;
  outgoing_route_ = out;
  incoming_route_ = in;
  passenger_max_capacity_ = capacity;
  speed_ = speed;
  distance_remaining_ = 0;
}

/**
  * @brief LoadPassengers gets an Stop pointer which is obtained by
  * calling the GetDestinationStop() which returns the current stop
  * in the list of stops on the route. We then call the LoadPassengers
  * method in the Stop class passing the "this" instance of the bus.
  * This is so the Stop object can iterate through its list and call
  * the bus method LoadPassenger on the way back to load the passenger.
  *
  */
bool Bus::LoadPassengers(Route * route) {
  Stop * current_stop = route -> GetDestinationStop();
  current_stop -> LoadPassengers(this);
  return true;
}

/**
  * @brief LoadPassenger receives a single Passenger pointer from the Stop
  * LoadPassengers method. This Passenger pointer is then pushed onto the
  * back of the Bus passenger list. This simulates that the passenger is
  * leaving the stop and boarding the bus.
  *  
  */
bool Bus::LoadPassenger(Passenger * pass) {
  passengers_.push_back(pass);
  pass -> GetOnBus();
  return true;
}

/**
  * @brief UnloadPassenger takes in a pointer to the route it is currently on.
  * Depending on the results of Move() checking which route the bus is on, 
  * UnloadPassenger accesses that route's stops list to retrieve the correct 
  * stop. First the destination stop is retrieved so that we can check the stop
  * id with the passengers destination id so that they are removed at the
  * correct stop. We iterate through the bus passenger list and remove
  * passengers that match the stop id.
  *  
  */
bool Bus::UnloadPassenger(Route * route) {
  // Get a pointer to the stop we are at.
  Stop * current_stop = route -> GetDestinationStop();
  int stop_id = current_stop -> GetId();
  for (std::list<Passenger *>::iterator it = passengers_.begin();
       it != passengers_.end();) {
    // Check if the passenger's destination id matches the stop's id.
    // Remove them from the bus list to simulate that they got off and left.
    int passenger_stop = (*it) -> GetDestination();
    if (stop_id == passenger_stop) {
      it = passengers_.erase(it);
      --it;
    } else {
      it++;
    }
  }
  return true;
}

/**
  * @brief The Move method is split into three parts. The first check is to
  * see if the trip is complete. If the trip is complete then the speed of the
  * bus is set to 0 and the distance_remaining is set 999 so that the bus won't
  * won't update anymore. The next if-else check is to see if the bus is on its
  * incoming route. The last else means the bus is still on its outgoing route.
  * Within both the outgoing and incoming checks, there is a nested if-else
  * that determines whether the bus is at a stop by checking the
  * distance_remaining_ is greater than 0. If the value is greater than zero,
  * we subtract off the speed of the bus from the distance remaining. Else, 
  * we take care of unloading the passengers on the bus and then loading the 
  * passengers from the stop. Next, a call to NextStop handles setting the next
  * destination stop in the list with the new distnace remaining for that stop.
  *
  */
bool Bus::Move() {
  if (IsTripComplete()) {  // outgoing and incoming are complete. Stop updating
    speed_ = 0;
    distance_remaining_ = 999;
    return false;
  } else if (outgoing_route_ -> IsAtEnd()) {  // on incoming route
      if (distance_remaining_> 0) {
        distance_remaining_ = distance_remaining_ - speed_;
      } else {
        incoming_route_ -> NextStop();
        distance_remaining_ = incoming_route_ -> GetNextStopDistance();
        UnloadPassenger(incoming_route_);
        LoadPassengers(incoming_route_);
      }
  } else {  // on outgoing route
      if (distance_remaining_ > 0) {
        distance_remaining_ = distance_remaining_ - speed_;
      } else {
        if (!outgoing_route_ -> IsAtEnd()) {
          outgoing_route_ -> NextStop();
          distance_remaining_ = outgoing_route_ -> GetNextStopDistance();
        }
        UnloadPassenger(outgoing_route_);
        LoadPassengers(outgoing_route_);
        // AtStop(true);
        // UpdateBusData();  // attempt to get bus displayed at stop.
        // AtStop(false);
        if (outgoing_route_ -> IsAtEnd()) {
          incoming_route_ -> NextStop();
          distance_remaining_ = incoming_route_ -> GetNextStopDistance();
        }
        // AtStop(true);
        // UpdateBusData();  // attempt to get bus displayed at stop.
        // AtStop(false);
      }
  }
  return true;
}

/**
  * @brief IsTripComplete checks for if both the incoming and outgoing routes
  * are finished. This is done by calling the route method IsAtEnd()
  *  
  */
bool Bus::IsTripComplete() {
  return outgoing_route_ -> IsAtEnd() && incoming_route_ -> IsAtEnd();
}

// bool Refuel() {
//  // This may become more complex in the future
//  fuel_ = max_fuel_;
//}

/**
  * @brief The ordering for updating the bus is important to accurately
  * represent how long a passenger has been waiting. First we want to take care
  * of moving the bus and handling any unloading and loading of passengers.
  * After this we can iterate through the bus passenger_ list and update the
  * passengers belonging to the bus. Local_simulator updates buses and then
  * updates the routes which in turn, update their stops.
  *  
  */
void Bus::Update() {  // using common Update format
  Move();
  UpdateBusData();
  for (std::list<Passenger *>::iterator it = passengers_.begin();
       it != passengers_.end(); it++) {
    (*it)->Update();
  }
}

/**
  * @brief Report displays information about a given bus and then iterates 
  * through its passenger list to display information about the passengers 
  * belonging to it.
  *  
  */
void Bus::Report(std::ostream & out) {
  out << "Name: " << name_ << std::endl;
  out << "Speed: " << speed_ << std::endl;
  out << "Distance to next stop: " << distance_remaining_ << std::endl;
  out << "\tPassengers (" << passengers_.size() << "): " << std::endl;
  for (std::list<Passenger *>::iterator it = passengers_.begin();
       it != passengers_.end(); it++) {
    (*it)->Report(out);
  }
}

/**
  * @brief GetCapacity is called by the visualizer to get the maximum
  * number of passengers that a bus can hold. The integer value stored
  * in the passenger_max_capacity is returned.
  *  
  */
int Bus::GetCapacity() {
  return passenger_max_capacity_;
}

/**
  * @brief GetNumPassengers is called by the visualizer and returns the size
  * of the passenger list contained by the bus. 
  *  
  */
size_t Bus::GetNumPassengers() {
  return size_t(passengers_.size());  // may have to cast the result
}

/**
  * @brief GetNumPassengers is called by the visualizer and returns the name
  * of the bus 
  *  
  */
std::string Bus::GetName() const {
  return name_;
}

/**
  * @brief GetNextStop is called by the visualizer and returns the Stop pointer
  * which is the next stop in the route. A route is split into two parts,
  * outgoing and incoming. Depending on where the bus currently is we want to
  * access the correct route to get the right stop in the list.
  *  
  */
Stop * Bus::GetNextStop() {
  if (outgoing_route_ -> IsAtEnd()) {
    return incoming_route_ -> GetDestinationStop();
  } else {
    return outgoing_route_ -> GetDestinationStop();
  }
}

/**
  * @brief GetPreviousStop is used to determine the previous stop that a bus 
  * has departed from. This is used to calculate the average longitudes and
  * latitudes for the visualizer.
  *  
  */
Stop * Bus::GetPreviousStop() {
  if (outgoing_route_ -> IsAtEnd()) {
    return incoming_route_ -> GetPreviousDestinationStop();
  } else {
    return outgoing_route_ -> GetPreviousDestinationStop();
  }
}

/**
  * @brief GetBusData is called by the visualizer and returns the BusData
  * struct. The bus_data_ member is initialized and updated when the 
  * UpdateBusData() method is called.
  *
  */
BusData Bus::GetBusData() {
  return bus_data_;
}

/*
void Bus::AtStop(bool bus_at_stop) {
  at_stop_ = bus_at_stop;
}

bool Bus::IsBusAtStop() {
  return at_stop_;
}*/

/**
  * @brief UpdateBusData is called by the visualizer to instruct the Bus object
  * to populate the BusData struct with the latest information. The method
  * calls the getter methods to populate the struct. We use a pointer to a Stop
  * as our current stop. We also have a pointer to a previous stop. From these
  * two, we can determine the average of longitudes and latitudes of the stops
  * to correctly display the bus on the visualizer. These positions utilize the
  * Position struct inside data.h.
  *
  */
void Bus::UpdateBusData() {
  // name of bus stored as id
  bus_data_.id = GetName();

  // Get the long/lat for the current stop.
  Stop * curr_stop = GetNextStop();
  double current_latitude = curr_stop -> GetLatitude();
  double current_longitude = curr_stop -> GetLongitude();

  // Get the long/lat for the previous stop.
  Stop * previous_stop = GetPreviousStop();
  double previous_latitude = current_latitude;
  double previous_longitude = current_longitude;
  if (previous_stop != NULL) {
    previous_latitude = previous_stop -> GetLatitude();
    previous_longitude = previous_stop -> GetLongitude();
  }
  /*
  // we are at a stop
  if (IsBusAtStop()) {
    previous_latitude = current_latitude;
    previous_longitude = current_longitude;
  }*/

  // Get the average for longitude and latitudes.
  double average_latitude = (previous_latitude + current_latitude) / 2;
  double average_longitude = (previous_longitude + current_longitude) / 2;

  // Create a Position struct for our latitudes and longitudes to be stored in.
  Position bus_pos;
  bus_pos.x = average_longitude;
  bus_pos.y = average_latitude;
  bus_data_.position = bus_pos;  // store struct inside position variable.

  bus_data_.num_passengers = GetNumPassengers();  // vs just using size()?
  bus_data_.capacity = GetCapacity();  // vs using passenger_max_capacity_?
}
