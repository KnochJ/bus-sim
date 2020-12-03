/**
 * @file configuration_simulator.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include "src/configuration_simulator.h"
#include "src/bus.h"
#include "src/route.h"

/**
  * @brief Constructs a ConfigurationSimulator object which takes in a pointer
  * to a ConfigManager object which is used to read the config file and use
  * the routes provided by the user.
  *
  *
  */
ConfigurationSimulator::ConfigurationSimulator(ConfigManager* configM) {
    configManager_ = configM;
}

/**
  * @brief Destructor for the ConfigurationSimulator.
  *
  */
ConfigurationSimulator::~ConfigurationSimulator() {
}

/**
  * @brief The Start method initializes our bus start timings and number of
  * time steps. These are stored in a vector. The last major responsibility
  * for the method is to generate the prototype routes for the simulation.
  *
  */
void ConfigurationSimulator::Start(const std::vector<int>& busStartTimings,
    const int& numTimeSteps) {
    busStartTimings_ = busStartTimings;
    numTimeSteps_ = numTimeSteps;

    timeSinceLastBus_.resize(busStartTimings_.size());
    for (int i = 0; i < static_cast<int>(timeSinceLastBus_.size()); i++) {
        timeSinceLastBus_[i] = 0;
    }

    simulationTimeElapsed_ = 0;

    prototypeRoutes_ = configManager_->GetRoutes();
    for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
        prototypeRoutes_[i]->Report(std::cout);
        prototypeRoutes_[i]->UpdateRouteData();
    }
}

/**
  * @brief Update displays the current information in a given round for the
  * simulator. The Update method will check to see when a bus should be
  * generated in the simulation. It will then update the buses and routes
  * so that the correct information is displayed.
  *
  */
void ConfigurationSimulator::Update() {
    simulationTimeElapsed_++;

    std::cout << "~~~~~~~~~~ The time is now " << simulationTimeElapsed_;
    std::cout << "~~~~~~~~~~" << std::endl;

    std::cout << "~~~~~~~~~~ Generating new busses if needed ";
    std::cout << "~~~~~~~~~~" << std::endl;

    // Check if we need to generate new busses
    for (int i = 0; i < static_cast<int>(timeSinceLastBus_.size()); i++) {
        // Check if we need to make a new bus
        if (0 >= timeSinceLastBus_[i]) {
            Route * outbound = prototypeRoutes_[2 * i];
            Route * inbound = prototypeRoutes_[2 * i + 1];

            busses_.push_back(new Bus(std::to_string(busId), outbound->Clone(),
                inbound->Clone(), 60, 1));
            busId++;

            timeSinceLastBus_[i] = busStartTimings_[i];
        } else {
            timeSinceLastBus_[i]--;
        }
    }

    std::cout << "~~~~~~~~~ Updating routes ";
    std::cout << "~~~~~~~~~" << std::endl;
    // Update routes
    for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
        prototypeRoutes_[i]->Update();
        prototypeRoutes_[i]->Report(std::cout);
    }

    std::cout << "~~~~~~~~~ Updating busses ";
    std::cout << "~~~~~~~~~" << std::endl;
    // Update busses
    for (int i = static_cast<int>(busses_.size()) - 1; i >= 0; i--) {
        busses_[i]->Update();

        if (busses_[i]->IsTripComplete()) {
            busses_.erase(busses_.begin() + i);
            continue;
        }
        busses_[i]->Report(std::cout);
    }
}
