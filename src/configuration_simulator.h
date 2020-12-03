/**
 * @file configuration_simulator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_CONFIGURATION_SIMULATOR_H_
#define SRC_CONFIGURATION_SIMULATOR_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <list>

#include "src/config_manager.h"

class Route;
class Bus;
class Stop;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief ConfigurationSimulator is the main class for running the simulation
 * via a config filename. The filename can be provided via the command line,
 * otherwise a default file will be selected by the simulator.
 *
 *
 */
class ConfigurationSimulator {
 public:
/**
  * @brief Constructs a bus with a standard name, pointer outbound route, 
  * pointer to inbound route, integer with max capacity, and a double for 
  * speed.  
  *
  * @param[in] pointer to ConfigManager.
  *
  * @return ConfigurationSimulator object with a pointer to a
  * ConfigManger object.
  *
  */
  explicit ConfigurationSimulator(ConfigManager*);
  ~ConfigurationSimulator();
/**
  * @brief Start is what begins the simulation using a vector of bus timings
  * to generate buses at the correct timings. It also initializes our 
  * prototype routes for the simulation. 
  *
  * @param[in] standard vector of ints which are the bus start timings.
  * @param[in] const integer which is the number of timesteps.
  *
  * @return none.
  *
  */
  void Start(const std::vector<int>&, const int&);
/**
  * @brief Update takes care of checking if we need to generate a new bus.
  * It also handles displaying the current information on buses and routes
  * as the simulation progresses.
  *
  * @param[in] none
  *
  * @return none.
  *
  */
  void Update();

 private:
/**
  * @brief Pointer to a ConfigManager object which will take in the config
  * file to read the routes that the user has provided.
  *
  */
  ConfigManager* configManager_;
/**
  * @brief Vector filled with timings for when the buses should be 
  * generated in the simulator.
  *
  */
  std::vector<int> busStartTimings_;

/**
  * @brief Vector filled with times since the last bus was generated
  * so that buses are on their routes at the correct times.
  *
  */
  std::vector<int> timeSinceLastBus_;

/**
  * @brief Integer which is the number of time steps that happen every update.
  *
  */
  int numTimeSteps_;

/**
  * @brief Integer which is the time that has elapsed in the simulation.
  *
  */
  int simulationTimeElapsed_;

/**
  * @brief Vector of Route pointers which is used by the simulation to hold and
  * keep track of the route prototypes.
  *
  */
  std::vector<Route *> prototypeRoutes_;

/**
  * @brief Vector of bus pointers which is used by the simulation to hold and
  * keep track of the buses.
  *
  */
  std::vector<Bus *> busses_;
/**
  * @brief Integer which is the inital bus id. We increment this number for
  * the rest of the buses that are generated.
  *
  */
  int busId = 1000;
};

#endif  // SRC_CONFIGURATION_SIMULATOR_H_
