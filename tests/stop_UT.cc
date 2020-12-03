/*
 * Please note, the assessment tests for grading, will use the same include
 * files, class names, and function names for accessing students' code that you
 * find in this file.  So students, if you write your code so that it passes
 * these feedback tests, you can be assured that the auto-grader will at least
 * be able to properly link with your code.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "../src/bus.h"
#include "../src/stop.h"
#include "../src/route.h"
#include "../src/passenger.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class StopTests : public ::testing::Test {

	protected:
  	Bus* bus1;
    Passenger * passengerS;
    Passenger * passengerB;
    Passenger * passengerE;
    Stop * stop;
    Stop * stop1;

  	
	virtual void SetUp() {
      bus1 = new Bus("test-bus-1", NULL, NULL, 60, 1);
      passengerS = new Passenger(15,"Steph");
      passengerB = new Passenger(1,"Bobby");
      passengerE = new Passenger(0,"Dingus");
      stop = new Stop(0);
      stop1 = new Stop(1, 0.0, 0.0);


  	}

  	virtual void TearDown() {
    	delete bus1;
      delete passengerS;
      delete passengerB;
      delete passengerE;
      delete stop;
      delete stop1;
  	}

};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(StopTests, GetId) {
  EXPECT_EQ(stop -> GetId(), 0);
  EXPECT_EQ(stop1 -> GetId(), 1);
};

TEST_F(StopTests, GetLongitude) {
  EXPECT_EQ(stop -> GetLongitude(), 44.973723) << "GetLongitude incorrectly retrieves default longitude";
  EXPECT_EQ(stop1 -> GetLongitude(), 0.0);
};

TEST_F(StopTests, GetLatitude) {
  EXPECT_EQ(stop -> GetLatitude(), -93.235365);
  EXPECT_EQ(stop1 -> GetLatitude(), 0.0);
};

TEST_F(StopTests, PeopleAtStop) {
  EXPECT_EQ(stop1 -> GetNumPeople(), 0);
  stop1 -> AddPassengers(passengerS);
  EXPECT_EQ(stop1 -> GetNumPeople(), 1);
  stop1 -> AddPassengers(passengerB);
  stop1 -> AddPassengers(passengerE);
  EXPECT_EQ(stop1 -> GetNumPeople(), 3);
};

TEST_F(StopTests, LoadPassengers) {
  EXPECT_EQ(stop1 -> GetNumPeople(), 0) << "Start with 0 people";
  stop1 -> AddPassengers(passengerS);
  stop1 -> AddPassengers(passengerB);
  stop1 -> AddPassengers(passengerE);
  EXPECT_EQ(stop1 -> GetNumPeople(), 3) << "Add 3 people to stop";
  stop1 -> LoadPassengers(bus1);
  stop1 -> LoadPassengers(bus1);
  stop1 -> LoadPassengers(bus1);
  EXPECT_EQ(stop1 -> GetNumPeople(), 0) << "Should end with 0 people at stop after loading";
};
