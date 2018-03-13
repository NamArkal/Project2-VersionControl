///////////////////////////////////////////////////////////////////////
// Executive.cpp - used to set up deployment process                 //
// ver 1.0                                                           //
// Author: Namrata Arkalgud                                          //
// Source: Jim Fawcett                                               //
///////////////////////////////////////////////////////////////////////
/*
* - This project is compiled as a static library after setting its property
*   C/C++ > Proprocessor > Preprocessor Definitions to noTEST_EXECUTIVE
* - Clients will include NoSqlDb.h, their own PayLoad.h, and link with
*   Executive.lib by making a reference to the Executive project.
*/
#ifdef TEST_EXECUTIVE

#include "Executive.h"
#include "../TestApplication/TestNoSqlDb.h"

using namespace NoSqlDb;

/*
* - This code is an example of how a client will use the NoSqlDb library.
*/
int main()
{
  Utilities::Title("Testing DbCore - He said, she said database");
	Utilities::putline();

	TestExecutive ex;

	// define test structures with test function and message
	
	TestExecutive::TestStr ts1{testR1, "Use C++11"};
	TestExecutive::TestStr ts2{testR2, "Use streams and new and delete"};
	TestExecutive::TestStr tsData1{testR3a, "Adding test data"};
	TestExecutive::TestStr tsData2{ testR3b, "Adding test data" };
	TestExecutive::TestStr ts3{ myTest3, "C++ packages provided" };
	TestExecutive::TestStr ts4{ myTest4, "Supporting check-in" };
	TestExecutive::TestStr ts5{ myTest5, "Supporting browsing of files" };
	TestExecutive::TestStr ts6{myTest6, "Files with open and closed check-ins"};
	TestExecutive::TestStr ts7{testR12, "All requirements are satisfied"};

	// register test structures with TestExecutive instance, ex

	ex.registerTest(ts1);
	ex.registerTest(ts2);
	ex.registerTest(tsData1);
	ex.registerTest(tsData2);
	ex.registerTest(ts3);
	ex.registerTest(ts4);
	ex.registerTest(ts5);
	ex.registerTest(ts6);
	ex.registerTest(ts7);

	// run tests

	bool result = ex.doTests();
	if (result == true)
		std::cout << "\n  all tests passed";
	else
		std::cout << "\n  at least one test failed";

	Utilities::putline(2);
	std::cin.get();
	return 0;

  return 0;
}

#endif
