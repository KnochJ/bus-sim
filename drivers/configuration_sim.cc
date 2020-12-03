/**
 * @file configuration_sim.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include <iostream>
#include <fstream>

#include "src/config_manager.h"
#include "src/configuration_simulator.h"

/**
  * @brief Configuration_sim is the driver for our configuration simulator. 
  * Through a series of checks, we are able to determine if a user has 
  * provided specific information such as a particular config file to
  * be used to genereate routes. We have error checks in place to be able to
  * determine if the file given is valid,or not. We can also check if the user
  * wants to manually input the number of rounds the simulation should run for.
  * 
  */
int main(int argc, char**argv) {
  std::cout << "Usage: ./build/bin/configuration_sim <config_filename>";
  std::cout << std::endl;
  // check if filename is given in the command line arguments
  if (argc == 2) {
    int rounds = 25;
    //  Create ConfigManager
    ConfigManager * config_man = new ConfigManager();

    std:: string filename = argv[1];
    std::ifstream config_file("config/" + filename);
    // Check to see if the file given can be opened or not.
    // Call ReadConfig
    bool print_error = false;
    if (config_file.is_open()) {
        config_man -> ReadConfig(argv[1]);
        config_file.close();
    } else {
        config_man -> ReadConfig("config.txt");
        print_error = true;
    }
    //  Create ConfigurationSimulator
    ConfigurationSimulator * config_sim = new
      ConfigurationSimulator(config_man);
    //  Call Start on ConfigurationSimulator
    std::vector<int> bus_timings;

    bus_timings.push_back(1);

    config_sim -> Start(bus_timings, 2);

    //  Start for loop, length of simulation (where from?)
    //  Call Update on ConfigurationSimulator
    for (int i = 0; i < rounds; i++) {
      config_sim -> Update();
    }
    if (print_error) {
        std::cout << "Filename provided was invalid, or not found: " << argv[1]
                  << std::endl;
        std::cout << "Used default config file: config.txt " << std::endl;
    }
  } else if (argc == 3) {  // filename arg and number of rounds present
    //  Get the number of rounds from the command line.
    int rounds = std::atoi(argv[2]);
    //  Create ConfigManager
    ConfigManager * config_man = new ConfigManager();

    std:: string filename = argv[1];
    std::ifstream config_file("config/" + filename);
    config_file.open(argv[1]);
    // Check to see if the file given can be opened or not.
    // Call ReadConfig
    bool print_error = false;
    if (config_file.is_open()) {
        config_man -> ReadConfig(argv[1]);
        config_file.close();
    } else {
        config_man -> ReadConfig("config.txt");
        print_error = true;
    }
    //  Create ConfigurationSimulator
    ConfigurationSimulator * config_sim = new
      ConfigurationSimulator(config_man);
    //  Call Start on ConfigurationSimulator
    std::vector<int> bus_timings;

    bus_timings.push_back(1);

    config_sim -> Start(bus_timings, 2);

    //  Start for loop, length of simulation (where from?)
    //  Call Update on ConfigurationSimulator
    for (int i = 0; i < rounds; i++) {
      config_sim -> Update();
    }
    if (print_error) {
        std::cout << "Filename provided was invalid, or not found: " << argv[1]
                  << std::endl;
        std::cout << "Used default config file: config.txt " << std::endl;
    }
  } else {  // no extra command line arguments given, so use defaults.
    int rounds = 25;
    //  Create ConfigManager
    ConfigManager * config_man = new ConfigManager();
    //  Call ReadConfig
    config_man -> ReadConfig("config.txt");
    //  Create ConfigurationSimulator
    ConfigurationSimulator * config_sim = new
      ConfigurationSimulator(config_man);
    //  Call Start on ConfigurationSimulator
    std::vector<int> bus_timings;

    bus_timings.push_back(1);

    config_sim -> Start(bus_timings, 2);

    //  Start for loop, length of simulation (where from?)
    //  Call Update on ConfigurationSimulator
    for (int i = 0; i < rounds; i++) {
      config_sim -> Update();
    }
    //  echo info to the user about needing a config file name
    std::cout << "Only one argument passed in: " << argv[0] << std::endl;
    std::cout << "Used default config file: config.txt " << std::endl;
  }
  return 0;
}
