///////////////////////////////////////////////////////////////////////
// TestNoSqlDb.h - Contains tests for each requirement of solution   //
// ver 1.0                                                           //
// Author : Namrata Arkalgud                                         //
///////////////////////////////////////////////////////////////////////

/*
* Package Operations:
* -------------------
* This package contains tests for each requirement.
* It calls the different packages mentioned below to execute requirement.
*
* Required Files:
* ---------------
* DbCore.h, DbCore.cpp
* Utilities.h, Utilities.cpp
* Persistence.h
* Query.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 5 Feb 2018
* - first release
*/

#pragma once
#include <iostream>
#include <iomanip>
#include <functional>
#include <unordered_map>
#include"../DbCore/DbCore.h"
#include"../Utilities/TestUtilities/TestUtilities.h"
#include"../Utilities/StringUtilities/StringUtilities.h"
#include "../PayLoad/PayLoad.h"
#include "../RepositoryCore/RepositoryCore.h"

using namespace NoSqlDb;

//----< reduce the number of characters to type >----------------------

auto putLine = [](size_t n = 1, std::ostream& out = std::cout)
{
	Utilities::putline(n, out);
};


/////////////////////////////////////////////////////////
//////////////// DbProvider class
// - provides mechanism to share a test database between test functions
//   without explicitly passing as a function argument.

class DbProvider
{
public:
	DbCore<PayLoad>& db() { return db_; }
private:
	static DbCore<PayLoad> db_;
};

DbCore<PayLoad> DbProvider::db_;

///////////////////////////////////////////////////////////////////////
// test functions

inline void identity(std::ostream& out)
{
	out << "\n  \"" << __FILE__ << "\"";
}

//----< R1 >-----------------------------------------------------------
/*
*  - Demonstrate that solution uses C++11
*/
bool testR1()
{
	Utilities::title("Demonstrating Requirement #1");
	std::cout << "\n  " << typeid(std::function<bool()>).name()
		<< ", declared in this function, "
		<< "\n  is only valid for C++11 and later versions.";
	return true; // would not compile unless C++11
}
//----< R2 >-----------------------------------------------------------
/*
*  - Cite use of streams and operators new and delete
*/
bool testR2()
{
	Utilities::title("Demonstrating Requirement #2");
	std::cout << "\n  A visual examination of all the submitted code "
		<< "will show only\n  use of streams and operators new and delete.";
	return true;
}
//----< R3a >----------------------------------------------------------
/*
*  - Demonstrate creation of DbElement
*/
bool testR3a()
{
	DbCore<PayLoad> db_;
	DbProvider dbp;
	dbp.db() = db_;
	DbElement<PayLoad> demoElem;

	demoElem.name("Jim");
	demoElem.descrip("Instructor for CSE687");
	demoElem.dateTime(DateTime().now());
	PayLoad p;
	p.value("../Files/");
	p.categories().push_back("cat1");
	p.categories().push_back("cat2");
	p.status("open");
	demoElem.payLoad(p);

	if (demoElem.name() != "Jim")
		return false;
	if (demoElem.descrip() != "Instructor for CSE687")
		return false;
	if (demoElem.dateTime().now() != DateTime().now())
		return false;

	db_["name_space-SFileName.cpp.3"] = demoElem;
	dbp.db() = db_;
	return true;
}
//----< R3b >----------------------------------------------------------
/*
*  - Demonstrate creation of Database
*/
bool testR3b()
{
	DbProvider dbp;
	DbCore<PayLoad> db_ = dbp.db();

	DbElement<PayLoad> demoElem = db_["SomeNS-Fawcett.cpp.3"];

	PayLoad p;
	p.value("../Files/");
	p.categories().push_back("cat1");
	p.categories().push_back("cat2");
	p.status("open");
	demoElem.payLoad(p);

	demoElem.name("Ammar");
	demoElem.descrip("TA for CSE687");
	demoElem.payLoad().status("close");
	db_["Namespace-Salman.cpp.1"] = demoElem;

	demoElem.name("Jianan");
	demoElem.payLoad().status("close");
	db_["Sal.cpp.1"] = demoElem;

	demoElem.name("Nikhil");
	demoElem.payLoad().status("close");
	db_["Prashar.cpp.1"] = demoElem;

	demoElem.name("Pranjul");
	demoElem.payLoad().status("close");
	db_["SomeNS-Fawcett.cpp.4"] = demoElem;

	Keys keys = db_.keys();
	db_["SomeNS-Fawcett.cpp.4"].children().push_back("Prashar.cpp.1");

	demoElem = db_["Namespace-Salman.cpp.1"];
	db_["Namespace-Salman.cpp.1"].children().push_back("Sal.cpp.1");
	db_["Namespace-Salman.cpp.1"].children().push_back("SomeNS-Fawcett.cpp.4");
	showDb(db_);
	dbp.db() = db_;

	return true;
}

//----< R3 >----------------------------------------------------------
/*
*  - Demonstrate use of required packages
*/
bool myTest3()
{
	Utilities::Title("Demonstrating Requirement #3 - required packages");
	repoCoreTest3();
	return true;
}

//----< R7 >----------------------------------------------------------
/*
*  - Demonstrate use of Executive package
*/
bool testR12()
{
	Utilities::Title("Demonstrate Requirement #7 - Executive Package");
	std::cout << "\n  You will find the executive package here: C:\\Users\\Namrata A\\Desktop\\NoSqlDb\\Executive";
	Utilities::putline();
	std::cout << "\nExecutive calls TestExecutive class: ";
	identity(std::cout);
	std::cout << "\n  Executive is used to demonstrate a deployable structure.";

	return true;
}

//----< R4 >----------------------------------------------------------
/*
*  - Demonstrate check-in and check-out of file
*/
bool myTest4()
{
	DbProvider dbp;
	DbCore<PayLoad> db_ = dbp.db();
	Utilities::Title("Demonstrate Requirement #4  - File check-in and check-out");
	repoCoreTest4(db_);
	dbp.db() = db_;
	return true;
}

//----< R5 >----------------------------------------------------------
/*
*  - Demonstrate browsing of files
*/
bool myTest5()
{
	DbProvider dbp;
	DbCore<PayLoad> db_ = dbp.db();
	Utilities::Title("Demonstrate Requirement #5 - Browse files");
	repoCoreTest5(db_);
	dbp.db() = db_;
	return true;
}

//----< R6 >----------------------------------------------------------
/*
*  - Demonstrate submitting of project with some closed check-ins and some open
*/
bool myTest6()
{
	DbProvider dbp;
	DbCore<PayLoad> db_ = dbp.db();
	Utilities::Title("Demonstrate Requirement #6 - Submitting some with open and some with close check-ins");
	std::cout << "\nThe PayLoad status shows open or close for each record.\n";
	showStatus(db_);
	dbp.db() = db_;
	return true;
}

//----< test stub >----------------------------------------------------
