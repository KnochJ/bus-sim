/**
 * @file passenger.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#include "src/passenger.h"

#include <iostream>
#include <string>


int Passenger::count_ = 0;

// Passenger::Passenger(Stop * dest = NULL, std::string name = "Nobody") {
Passenger::Passenger(int destination_stop_id, std::string name): name_(name),
        destination_stop_id_(destination_stop_id), wait_at_stop_(0),
        time_on_bus_(0), id_(count_) {
  count_++;
}

/**
  * @brief Update method simply checks if the time on bus is equal to zero,
  * which means they are still at the stop. If true, then we increment the 
  * wait_at_stop_. Else, we that means we are on a bus so we increment the
  * time_on_bus_.
  *
  */
void Passenger::Update() {
  if (time_on_bus_ == 0) {
    wait_at_stop_++;
  } else {
    time_on_bus_++;
  }
}

/**
  * @brief GetOnBus sets the time_on_bus_ to 1 which essential enables
  * Update() to start incrementing time_on_bus_.
  *
  */

void Passenger::GetOnBus() {
  time_on_bus_ = 1;
}

/**
  * @brief GetTotalWait takes the sum of time at a stop and time on a 
  * bus and returns it.
  *
  */
int Passenger::GetTotalWait() const {
  return wait_at_stop_ + time_on_bus_;
}

/**
  * @brief IsOnBus returns a boolean to check if a passenger is on a bus.
  * Important note here is that time_on_bus starts at 0 to prevent
  * incrementing twice when getting on the bus and then the bus updating after
  * that.
  *
  */
bool Passenger::IsOnBus() const {
  return time_on_bus_ > 0;
}

/**
  * @brief GetDestination is Used to determine when a passenger should get
  * off the bus at a given stop.
  *
  */

int Passenger::GetDestination() const {
  return destination_stop_id_;
}

/**
  * @brief Report function takes in an ostream object which allows us to
  * use different forms of output.
  *
  */
void Passenger::Report(std::ostream & out) const {
  out << "Name: " << name_ << std::endl;
  out << "Destination: " << destination_stop_id_ << std::endl;
  out << "Total Wait: " << GetTotalWait() << std::endl;
  out << "\tWait at Stop: " << wait_at_stop_ << std::endl;
  out << "\tTime on bus: " << time_on_bus_ << std::endl;
}
