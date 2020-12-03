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

class BusTests : public ::testing::Test {

	protected:
  	Bus* bus1;
    Stop** CC_EB_stops;
    Stop** CC_WB_stops;
    Stop* stop_CC_EB_1; //West bank station
    Stop* stop_CC_EB_2;
    Stop* stop_CC_EB_3;
    Stop* stop_CC_WB_1;
    Stop* stop_CC_WB_2;
    Stop* stop_CC_WB_3;
    double* CC_EB_distances;
    double* CC_WB_distances;
    Route* CC1_EB;
    Route* CC1_WB;
    Route* route1;
    Route* route2;
    Passenger* passengerS;
    Passenger* passengerB;
    Passenger* passengerE;

  	
	virtual void SetUp() {
    CC_EB_stops = new Stop *[3];
    CC_WB_stops = new Stop *[3];

    stop_CC_EB_1 = new Stop(0, 43, -92.5); //West bank station
    stop_CC_EB_2 = new Stop(1); //student union station
    stop_CC_EB_3 = new Stop(2, 44.973820, -93.227117); //Oak St & Washington Ave
    stop_CC_WB_1 = new Stop(2, 44.973820, -93.227117); //Oak St & Washington Ave
    stop_CC_WB_2 = new Stop(1); //student union station
    stop_CC_WB_3 = new Stop(0, 43, -92.5); //West bank station
    CC_EB_stops[0] = stop_CC_EB_1;
    CC_EB_stops[1] = stop_CC_EB_2;
    CC_EB_stops[2] = stop_CC_EB_3;
    CC_WB_stops[0] = stop_CC_WB_1;
    CC_WB_stops[1] = stop_CC_WB_2;
    CC_WB_stops[2] = stop_CC_WB_3;

    CC_EB_distances = new double[3];
    CC_WB_distances = new double[3];
    CC_EB_distances[0] = 3;
    CC_EB_distances[1] = 2;
    CC_EB_distances[2] = 1;
    CC_WB_distances[0] = 1;
    CC_WB_distances[1] = 2;
    CC_WB_distances[2] = 3;

    CC1_EB = new Route("Campus Connector 1- Eastbound", CC_EB_stops, CC_EB_distances, 3, NULL);
    CC1_WB = new Route("Campus Connector 1- Westbound", CC_WB_stops, CC_WB_distances, 3, NULL);
    route1 = CC1_EB -> Clone();
    route2 = CC1_WB -> Clone();
    bus1 = new Bus("bus-1", route1, route2, 60, 1);
    passengerS = new Passenger(2,"Steph");
    passengerB = new Passenger(2,"Bobby");
    passengerE = new Passenger(2,"Dingus");

  }

  virtual void TearDown() {
    delete CC_EB_stops;
    delete CC_WB_stops;
    delete stop_CC_EB_1; 
    delete stop_CC_EB_2;
    delete stop_CC_EB_3;
    delete stop_CC_WB_1;
    delete stop_CC_WB_2;
    delete stop_CC_WB_3;
    delete CC_EB_distances;
    delete CC_WB_distances;
    delete CC1_EB;
    delete CC1_WB;
    delete bus1;
    delete passengerS;
    delete passengerB;
    delete passengerE;

  }

};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(BusTests, IsTripComplete) {
  EXPECT_FALSE(bus1 -> IsTripComplete()) << "IsTripComplete returns incorrect boolean" << std::endl;
  route1 -> NextStop();
  EXPECT_FALSE(bus1 -> IsTripComplete()) << "IsTripComplete returns incorrect boolean" << std::endl;
  route1 -> NextStop();
  EXPECT_FALSE(bus1 -> IsTripComplete()) << "IsTripComplete returns incorrect boolean" << std::endl;
  route1 -> NextStop();
  EXPECT_FALSE(bus1 -> IsTripComplete()) << "IsTripComplete returns incorrect boolean" << std::endl;
  route1 -> NextStop();
  EXPECT_FALSE(bus1 -> IsTripComplete()) << "IsTripComplete returns incorrect boolean" << std::endl;
  route2 -> NextStop();
  EXPECT_FALSE(bus1 -> IsTripComplete()) << "IsTripComplete returns incorrect boolean" << std::endl;
  route2 -> NextStop();
  EXPECT_FALSE(bus1 -> IsTripComplete()) << "IsTripComplete returns incorrect boolean" << std::endl;
  route2 -> NextStop();
  EXPECT_FALSE(bus1 -> IsTripComplete()) << "IsTripComplete returns incorrect boolean" << std::endl;
  route2 -> NextStop();
  EXPECT_TRUE(bus1 -> IsTripComplete()) << "IsTripComplete returns incorrect boolean" << std::endl;
}; 


TEST_F(BusTests, GetNextStop) {
  bus1 -> Move();
  Stop * next_stop = bus1->GetNextStop();
  EXPECT_EQ(next_stop -> GetId(), 0) << "GetNextStop gives incorrect stop after moving" << std::endl;
  bus1 -> Move();
  Stop * next_stop2 = bus1->GetNextStop();
  EXPECT_EQ(next_stop2 -> GetId(), 0) << "GetNextStop gives incorrect stop after moving" << std::endl;
  bus1 -> Move();
  bus1 -> Move();
  Stop * next_stop3 = bus1->GetNextStop();
  EXPECT_EQ(next_stop3 -> GetId(), 0) << "GetNextStop gives incorrect stop after moving" << std::endl;
  bus1 -> Move();
  Stop * next_stop4 = bus1->GetNextStop();
  EXPECT_EQ(next_stop4 -> GetId(), 1) << "GetNextStop gives incorrect stop after moving" << std::endl;
  bus1 -> Move();
  bus1 -> Move();
  bus1 -> Move();
  Stop * next_stop5 = bus1->GetNextStop();
  EXPECT_EQ(next_stop5 -> GetId(), 2) << "GetNextStop gives incorrect stop after moving" << std::endl;

  bus1 -> Move();
  Stop * next_stop6 = bus1->GetNextStop();
  EXPECT_EQ(next_stop6 -> GetId(), 2) << "GetNextStop gives incorrect stop after moving" << std::endl;
  bus1 -> Move();
  Stop * next_stop7 = bus1->GetNextStop();
  EXPECT_EQ(next_stop7 -> GetId(), 2) << "GetNextStop gives incorrect stop after moving" << std::endl;
  bus1 -> Move();
  bus1 -> Move();
  Stop * next_stop8 = bus1->GetNextStop();
  EXPECT_EQ(next_stop8 -> GetId(), 1) << "GetNextStop gives incorrect stop after moving" << std::endl;
  bus1 -> Move();
  bus1 -> Move();
  bus1 -> Move();
  Stop * next_stop9 = bus1->GetNextStop();
  EXPECT_EQ(next_stop9 -> GetId(), 0) << "GetNextStop gives incorrect stop after moving" << std::endl;

  bus1 -> Move();
  bus1 -> Move();
  bus1 -> Move();
  Stop * next_stop10 = bus1->GetNextStop();
  EXPECT_EQ(next_stop10 -> GetId(), 0) << "Moving after trip is complete gives incorrect stop" << std::endl;
};


TEST_F(BusTests, GetPreviousStop) {
  bus1 -> Move();
  Stop * next_stop = bus1 -> GetPreviousStop();
  EXPECT_EQ(next_stop -> GetId(), 0) << "GetPreviousStop gives incorrect stop after moving" << std::endl;
  bus1 -> Move();
  Stop * next_stop2 = bus1 -> GetPreviousStop();
  EXPECT_EQ(next_stop2 -> GetId(), 0) << "GetPreviousStop gives incorrect stop after moving" << std::endl;
  bus1 -> Move();
  bus1 -> Move();
  bus1 -> Move();
  Stop * next_stop3 = bus1->GetPreviousStop();
  EXPECT_EQ(next_stop3 -> GetId(), 0) << "GetPreviousStop gives incorrect stop after moving" << std::endl;
  bus1 -> Move();
  Stop * next_stop4 = bus1->GetPreviousStop();
  EXPECT_EQ(next_stop4 -> GetId(), 0) << "GetPreviousStop gives incorrect stop after moving" << std::endl;
  bus1 -> Move();
  Stop * next_stop5 = bus1->GetPreviousStop();
  EXPECT_EQ(next_stop5 -> GetId(), 0) << "GetPreviousStop gives incorrect stop after moving" << std::endl;
  bus1 -> Move();
  Stop * next_stop6 = bus1->GetPreviousStop();
  EXPECT_EQ(next_stop6 -> GetId(), 1) << "GetPreviousStop gives incorrect stop after moving" << std::endl;
  bus1 -> Move();
  bus1 -> Move();
  Stop * next_stop7 = bus1->GetPreviousStop();
  EXPECT_EQ(next_stop7 -> GetId(), 2) << "GetPreviousStop gives incorrect stop after moving" << std::endl;
  bus1 -> Move();
  bus1 -> Move();
  Stop * next_stop8 = bus1->GetPreviousStop();
  EXPECT_EQ(next_stop8 -> GetId(), 2) << "GetPreviousStop gives incorrect stop after moving" << std::endl;
  bus1 -> Move();
  bus1 -> Move();
  Stop * next_stop9 = bus1->GetPreviousStop();
  EXPECT_EQ(next_stop9 -> GetId(), 1) << "GetPreviousStop gives incorrect stop after moving" << std::endl;
  bus1 -> Move();
  bus1 -> Move();
  bus1 -> Move();
  bus1 -> Move();
  Stop * next_stop10 = bus1->GetPreviousStop();
  EXPECT_EQ(next_stop10 -> GetId(), 1) << "GetPreviousStop gives incorrect after trip is complete" << std::endl;
  EXPECT_NE(next_stop10 -> GetId(), 0) << "GetPreviousStop gives incorrect after trip is complete" << std::endl;
};


TEST_F(BusTests, GetCapacity) {
  EXPECT_EQ(bus1 -> GetCapacity(), 60) << "GetCapacity not working correctly." << std::endl;
};


TEST_F(BusTests, GetNumPassengers) {
  EXPECT_EQ(bus1 -> GetNumPassengers(), 0) << "GetNumPassengers not working correctly." << std::endl;
};

  
TEST_F(BusTests, GetName) {
  EXPECT_EQ(bus1 -> GetName(), "bus-1") << "GetName not working correctly." << std::endl;
};


TEST_F(BusTests, LoadPassengers) {
  stop_CC_EB_1 -> AddPassengers(passengerS);
  stop_CC_EB_1 -> AddPassengers(passengerB);
  stop_CC_EB_2 -> AddPassengers(passengerE);
  bus1 -> Move();
  bus1 -> LoadPassengers(route1);
  EXPECT_EQ(bus1 -> GetNumPassengers(), 2) << "LoadPassengers not working correctly." << std::endl;
  bus1 -> Move();
  bus1 -> Move();
  bus1 -> Move();
  bus1 -> Move();
  bus1 -> LoadPassengers(route1);
  EXPECT_EQ(bus1 -> GetNumPassengers(), 3) << "LoadPassengers not working correctly." << std::endl;
};


TEST_F(BusTests, UnloadPassengers) {
  stop_CC_EB_1 -> AddPassengers(passengerS);
  stop_CC_EB_1 -> AddPassengers(passengerB);
  stop_CC_EB_2 -> AddPassengers(passengerE);
  bus1 -> Move();
  bus1 -> LoadPassengers(route1);
  EXPECT_EQ(bus1 -> GetNumPassengers(), 2) << "UnloadPassengers not working correctly." << std::endl;
  bus1 -> Move();
  bus1 -> Move();
  bus1 -> Move();
  bus1 -> Move();
  bus1 -> LoadPassengers(route1);
  EXPECT_EQ(bus1 -> GetNumPassengers(), 3) << "UnloadPassengers not working correctly." << std::endl;
  bus1 -> Move();
  bus1 -> Move();
  bus1 -> Move();
  bus1 -> UnloadPassenger(route1);
  EXPECT_EQ(bus1 -> GetNumPassengers(), 1) << "UnloadPassengers not working correctly." << std::endl;
};
