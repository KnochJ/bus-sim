/* STUDENTS: YOU MUST ADD YOUR PASSENGER UNIT TESTS TO THIS FILE. FORMAT YOUR
 * TESTS TO FIT THE SPECIFICATIONS GIVEN BY THE TESTS PROVIDED IN THIS FILE.
 *
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
#include "../src/passenger.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class PassengerTests : public ::testing::Test {

	protected:
  	
  	Passenger* passenger;
    Passenger* passengerS;
    Passenger* passengerB;
    Passenger* passengerE;

  	
	virtual void SetUp() {
    	passenger = new Passenger();
      passengerS = new Passenger(15,"Steph");
      passengerB = new Passenger(1,"Bobby");
      passengerE = new Passenger(0,"Dingus");
  	}

  	virtual void TearDown() {
    	delete passenger;
      delete passengerS;
      delete passengerB;
      delete passengerE;
  	}

};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(PassengerTests, Constructor) {
  	EXPECT_EQ(passenger->IsOnBus(), false);
  	passenger->GetOnBus();
  	EXPECT_EQ(passenger->IsOnBus(), true);
};

TEST_F(PassengerTests, IsOnBus) {
    EXPECT_EQ(passenger->IsOnBus(), false);
    passenger->GetOnBus();
    EXPECT_EQ(passenger->IsOnBus(), true);
    passenger->Update();
    EXPECT_EQ(passenger->IsOnBus(), true);
};

TEST_F(PassengerTests, GetTotalWait) {
    EXPECT_EQ(passenger->GetTotalWait(), 0);
    passenger->Update();
    EXPECT_GT(passenger->GetTotalWait(),0);
    EXPECT_EQ(passenger->GetTotalWait(), 1);
    EXPECT_EQ(passengerS->GetTotalWait(), 0);
    passenger->Update();
    passengerS->Update();
    EXPECT_EQ(passenger->GetTotalWait(), 2);
    EXPECT_EQ(passengerS->GetTotalWait(), 1);
};


TEST_F(PassengerTests, GetDestination) {
    EXPECT_EQ(passenger->GetDestination(),-1);
    EXPECT_EQ(passengerS->GetDestination(), 15);
    EXPECT_EQ(passengerB->GetDestination(), 1);
    EXPECT_EQ(passengerE->GetDestination(), 0);
};

TEST_F(PassengerTests, Report) {
    testing::internal::CaptureStdout();
    passengerS->Report(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected_output = "Name: Steph\nDestination: 15\nTotal Wait: 0\n\tWait at Stop: 0\n\tTime on bus: 0\n";
    EXPECT_EQ(output, expected_output);

    testing::internal::CaptureStdout();
    passengerB->Report(std::cout);
    std::string output2 = testing::internal::GetCapturedStdout();
    std::string expected_output2 = "Name: Bobby\nDestination: 1\nTotal Wait: 0\n\tWait at Stop: 0\n\tTime on bus: 0\n";
    EXPECT_EQ(output2, expected_output2);

    testing::internal::CaptureStdout();
    passenger->Report(std::cout);
    std::string output3 = testing::internal::GetCapturedStdout();
    std::string expected_output3 = "Name: Nobody\nDestination: -1\nTotal Wait: 0\n\tWait at Stop: 0\n\tTime on bus: 0\n";
    EXPECT_EQ(output3, expected_output3);

    testing::internal::CaptureStdout();
    passengerE->Report(std::cout);
    std::string output4 = testing::internal::GetCapturedStdout();
    std::string expected_output4 = "Name: Dingus\nDestination: 0\nTotal Wait: 0\n\tWait at Stop: 0\n\tTime on bus: 0\n";
    EXPECT_EQ(output4, expected_output4);
};

TEST_F(PassengerTests, Update) {
    EXPECT_EQ(passengerS->GetTotalWait(),0);
    passengerS->Update();
    EXPECT_EQ(passengerS->GetTotalWait(),1);
    passengerS->Update();
    EXPECT_EQ(passengerS->GetTotalWait(),2);
    passengerS->GetOnBus();
    EXPECT_EQ(passengerS->GetTotalWait(),3);
    passengerS->Update();
    EXPECT_EQ(passengerS->GetTotalWait(),4);

    EXPECT_EQ(passenger->GetTotalWait(),0);
    passenger->GetOnBus();
    passenger->Update();
    EXPECT_EQ(passenger->GetTotalWait(),2);
};
