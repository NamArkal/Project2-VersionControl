/////////////////////////////////////////////////////////////////////
// Version.cpp - return latest version of file                     //
// ver 1.0                                                         //
// Namrata Arkalgud                                                //
/////////////////////////////////////////////////////////////////////

#include "Version.h"
#include "../PayLoad/PayLoad.h"
#include <string>

#ifdef TEST_VERSION

//Adding data to DB
bool testR3a(DbCore<PayLoad>& db)
{
	DbElement<PayLoad> demoElem;

	demoElem.name("Jim");
	demoElem.descrip("Instructor for CSE687");
	demoElem.dateTime(DateTime().now());
	demoElem.payLoad(PayLoad("The good news is ..."));

	if (demoElem.name() != "Jim")
		return false;
	if (demoElem.descrip() != "Instructor for CSE687")
		return false;
	if (demoElem.dateTime().now() != DateTime().now())
		return false;
	if (std::string(demoElem.payLoad()) != std::string("The good news is ..."))
		return false;

	db["SomeNS::Fawcett.cpp::3"] = demoElem;
	return true;
}

//Adding data to DB
bool testR3b(DbCore<PayLoad>& db)
{
	DbElement<PayLoad> demoElem = db["Fawcett"];

	demoElem.name("Ammar");
	demoElem.descrip("TA for CSE687");
	demoElem.payLoad(PayLoad("You should try ..."));
	db["Namespace::Salman.java::1"] = demoElem;
	if (!db.contains("Namespace::Salman.java::1"))
		return false;

	demoElem.name("Jianan");
	demoElem.payLoad(PayLoad("Dr. Fawcett said ..."));
	db["Sal"] = demoElem;

	demoElem.payLoad(PayLoad("You didn't demonstrate Requirement #4"));
	demoElem.name("Nikhil");
	db["Prashar"] = demoElem;

	demoElem.payLoad(PayLoad("You didn't demonstrate Requirement #5"));
	demoElem.name("Pranjul");
	db["SomeNS::Fawcett.cpp::7"] = demoElem;

	Keys keys = db.keys();
	db["SomeNS::Fawcett.cpp::7"].children().push_back("Salman");
	db["SomeNS::Fawcett.cpp::7"].children().push_back("Sun");
	db["SomeNS::Fawcett.cpp::7"].children().push_back("Prashar");
	db["SomeNS::Fawcett.cpp::7"].children().push_back("Arora");

	db["Namespace::Salman.java::1"].children().push_back("Sun");
	db["Namespace::Salman.java::1"].children().push_back("Prashar");
	db["Namespace::Salman.java::1"].children().push_back("Arora");

	return true;
}

//Tests the Version class
bool testLatestVersion(DbCore<PayLoad>& db) {
	Version<PayLoad> v(db);
	int res = v.latestVersion("SomeNS::Fawcett.cpp");
	std::cout << "\n\nThe latest version is: " << res << "\n";
	return true;
}

int main() {
	DbCore<PayLoad> db;
	testR3a(db);
	testR3b(db);
	testLatestVersion(db);
	std::cin.get();
	return 0;
}

#endif // TEST_VERSION

