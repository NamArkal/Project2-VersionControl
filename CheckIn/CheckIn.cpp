/////////////////////////////////////////////////////////////////////
// CheckIn.cpp - allows checking in of files                       //
// ver 1.0                                                         //
// Namrata Arkalgud                                                //
/////////////////////////////////////////////////////////////////////
#include "CheckIn.h"
#include <Windows.h>
#include <stdlib.h>
#include <iostream>

#ifdef TEST_CHECKIN

//Adding test data to DB
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

	db["SomeNS-Fawcett.cpp-3"] = demoElem;
	return true;
}

//Adding test data to DB
bool testR3b(DbCore<PayLoad>& db)
{
	DbElement<PayLoad> demoElem = db["SomeNS-Fawcett.cpp-3"];

	demoElem.name("Ammar");
	demoElem.descrip("TA for CSE687");
	demoElem.payLoad(PayLoad("You should try ..."));
	db["Namespace-Salman.cpp-1"] = demoElem;
	if (!db.contains("Namespace-Salman.cpp-1"))
		return false;

	demoElem.name("Jianan");
	demoElem.payLoad(PayLoad("Dr. Fawcett said ..."));
	db["Sal"] = demoElem;

	PayLoad p;
	p.value("C:/Users/Namrata A/Desktop/");
	p.categories().push_back("cat1");
	p.categories().push_back("cat2");
	p.status("open");
	demoElem.payLoad(p);

	//demoElem.payLoad(PayLoad("You didn't demonstrate Requirement #4"));
	demoElem.name("Nikhil");
	db["Prashar"] = demoElem;

	//PayLoad p;
	/*p.value("C:/Users/Namrata A/Desktop/");
	p.categories().push_back("cat1");
	p.categories().push_back("cat2");
	p.status("open");
	demoElem.payLoad(p);*/
	demoElem.name("Pranjul");
	db["SomeNS-Fawcett.cpp-7"] = demoElem;

	Keys keys = db.keys();
	db["SomeNS-Fawcett.hs-7"].children().push_back("Prashar");

	demoElem = db["Namespace-Salman.cpp-1"];
	db["Namespace-Salman.cpp-1"].children().push_back("Sal");
	db["Namespace-Salman.cpp-1"].children().push_back("Prashar");
	db["Namespace-Salman.cpp-1"].children().push_back("SomeNS-Fawcett.cpp-7");

	return true;
}

//Testing checking in of file
bool testLatestVersion(DbCore<PayLoad>& db) {
	CheckIn<PayLoad> c(db);
	DbElement<PayLoad> demoElem = db["SomeNS-Fawcett.cpp-3"];
	demoElem.name("Pranjul");
	demoElem.descrip("Student of CSE687");
	PayLoad p;
	p.value("C:/Users/Namrata A/Desktop/");
	p.status("close");
	p.categories().push_back("cat1");
	p.categories().push_back("cat2");
	demoElem.payLoad(p);
	bool res = c.checkInFile("SomeNS-Fawcett.cpp",demoElem);
	std::cout << "\nThe result is: " << res << "\n";
	return true;
}

int main() {
	DbCore<PayLoad> db;
	testR3a(db);
	testR3b(db);
	testLatestVersion(db);
	CheckIn<PayLoad>::identify();

	std::cin.get();
	return 0;
}

#endif // TEST_CHECKIN
