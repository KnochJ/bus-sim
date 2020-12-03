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

class RouteTests : public ::testing::Test {

	protected:
  	// Bus* bus1;
    Stop** CC_EB_stops;
    Stop** CC_WB_stops;
    Stop * stop_CC_EB_1; //West bank station
    Stop * stop_CC_EB_2;
    Stop * stop_CC_EB_3;
    Stop * stop_CC_WB_1;
    Stop * stop_CC_WB_2;
    Stop * stop_CC_WB_3;
    double* CC_EB_distances;
    double* CC_WB_distances;
    Route* CC1_EB;
    Route* CC1_WB;
    Route * route1;
    Route * route2;

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
    // bus1 = new Bus("bus-1", route1, route2, 60, 1);

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
    // delete bus1;

  	}

};
/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(RouteTests, IsAtEnd) {
  EXPECT_FALSE(route1 -> IsAtEnd()) << "IsAtEnd for route clone not working." << std::endl;
  EXPECT_FALSE(route2 -> IsAtEnd()) << "IsAtEnd for route clone not working." << std::endl;
  EXPECT_FALSE(route1 -> IsAtEnd()) << "IsAtEnd for route not working." << std::endl;
  EXPECT_FALSE(route2 -> IsAtEnd()) << "IsAtEnd for route not working." << std::endl;

  route1 -> NextStop();
  EXPECT_FALSE(route1 -> IsAtEnd()) << "IsAtEnd for route clone not working after first stop." << std::endl;
  route1 -> NextStop();
  EXPECT_FALSE(route1 -> IsAtEnd()) << "IsAtEnd for route clone not working after second stop." << std::endl;
  route1 -> NextStop();
  EXPECT_FALSE(route1 -> IsAtEnd()) << "IsAtEnd for route clone not working after third stop." << std::endl;
  route1 -> NextStop();
  EXPECT_TRUE(route1 -> IsAtEnd()) << "IsAtEnd for route clone not working reaching end." << std::endl;
  route1 -> NextStop();
  EXPECT_TRUE(route1 -> IsAtEnd()) << "IsAtEnd for route clone not working when already at end." << std::endl;
};


TEST_F(RouteTests, GetSpecificStop) {
  Stop * test0 = CC1_EB -> GetSpecificStop(0);
  int id0 = test0 -> GetId();
  EXPECT_EQ(id0, 0) << "GetSpecificStop not working" << std::endl;

  Stop* test1 = CC1_EB -> GetSpecificStop(-1);
  EXPECT_EQ(test1, nullptr) << "GetSpecificStop index -1 out of bounds not working" << std::endl;

  Stop* test2 = CC1_EB -> GetSpecificStop(3);
  EXPECT_EQ(test2, nullptr) << "GetSpecificStop index 3 out of bounds not working" << std::endl;
};


TEST_F(RouteTests, GetSpecificDistance) {
  double test0 = CC1_EB -> GetSpecificDistance(0);
  EXPECT_EQ(test0, 3) << "GetSpecificDistance not working" << std::endl;

  double test1 = CC1_EB -> GetSpecificDistance(-1);
  EXPECT_EQ(test1, -1) << "GetSpecificDistance index -1 out of bounds not working" << std::endl;

  double test2 = CC1_EB -> GetSpecificDistance(3);
  EXPECT_EQ(test2, -1) << "GetSpecificDistance index 3 out of bounds not working" << std::endl;
};


TEST_F(RouteTests, GetDestinationStop) {
  Stop * test0 = CC1_EB -> GetDestinationStop();
  EXPECT_EQ(test0, nullptr) << "Getting destination when not initialized is not working." << std::endl;

  CC1_EB -> NextStop();
  Stop * test1 = CC1_EB -> GetDestinationStop();
  EXPECT_EQ(test1 -> GetId(), 0) << "Getting destination for first stop is not working." << std::endl;

  CC1_EB -> NextStop();
  Stop * test2 = CC1_EB -> GetDestinationStop();
  EXPECT_EQ(test2 -> GetId(), 1) << "Getting destination for second stop is not working." << std::endl;

  CC1_EB -> NextStop();
  Stop * test3 = CC1_EB -> GetDestinationStop();
  EXPECT_EQ(test3 -> GetId(), 2) << "Getting destination for third stop is not working." << std::endl;
};


TEST_F(RouteTests, GetPreviousDestinationStop) {
  Stop * test0 = CC1_EB -> GetPreviousDestinationStop();
  EXPECT_EQ(test0, nullptr) << "Getting previous destination when not initialized is not working." << std::endl;

  CC1_EB -> NextStop();
  Stop * test1 = CC1_EB -> GetPreviousDestinationStop();
  EXPECT_EQ(test1 -> GetId(), 0) << "Getting previous destination for first stop is not working." << std::endl;

  CC1_EB -> NextStop();
  Stop * test2 = CC1_EB -> GetPreviousDestinationStop();
  EXPECT_EQ(test2 -> GetId(), 0) << "Getting previous destination for second stop is not working." << std::endl;

  CC1_EB -> NextStop();
  Stop * test3 = CC1_EB -> GetPreviousDestinationStop();
  EXPECT_EQ(test3 -> GetId(), 1) << "Getting previous destination for third stop is not working." << std::endl;

  CC1_EB -> NextStop();
  Stop * test4 = CC1_EB -> GetPreviousDestinationStop();
  EXPECT_EQ(test4 -> GetId(), 1);

  CC1_EB -> NextStop();
  Stop * test5 = CC1_EB -> GetPreviousDestinationStop();
  EXPECT_EQ(test5 -> GetId(), 1);
};


TEST_F(RouteTests, GetNextStopDistance) {
  double test0 = CC1_EB -> GetNextStopDistance();
  EXPECT_EQ(test0, -1) << "GetNextStopDistance is not setup properly" << std::endl;

  CC1_EB -> NextStop();
  double test1 = CC1_EB -> GetNextStopDistance();
  EXPECT_EQ(test1, 3);

  CC1_EB -> NextStop();
  double test2 = CC1_EB -> GetNextStopDistance();
  EXPECT_EQ(test2, 2);

  CC1_EB -> NextStop();
  double test3 = CC1_EB -> GetNextStopDistance();
  EXPECT_EQ(test3, -1);
};


TEST_F(RouteTests, GetName) {
  EXPECT_EQ(CC1_EB -> GetName() , "Campus Connector 1- Eastbound") << "GetName not setup properly." << std::endl;
  EXPECT_EQ(CC1_WB -> GetName() , "Campus Connector 1- Westbound") << "GetName not setup properly." << std::endl;
};
