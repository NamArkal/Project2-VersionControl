/////////////////////////////////////////////////////////////////////
// Checkout.cpp - checks out file and copies to ClientRepo folder  //
// ver 1.0                                                         //
// Namrata Arkalgud                                                //
/////////////////////////////////////////////////////////////////////

#include "Checkout.h"
#include <chrono>
#include "../Query/Query.h"
#include "../PayLoad/PayLoad.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../DbCore/DbCore.h"

#ifdef CHECKOUT_TEST

//Adding data to DB
bool testR3a(DbCore<PayLoad>& db)
{

	DbElement<PayLoad> demoElem;

	demoElem.name("Jim");
	demoElem.descrip("Instructor for CSE687");
	demoElem.dateTime(DateTime().now());
	//demoElem.payLoad(PayLoad("The good news is ..."));
	p.value("../Files/");
	p.categories().push_back("cat1");
	p.categories().push_back("cat2");
	p.status("close");
	demoElem.payLoad(p);

	if (demoElem.name() != "Jim")
		return false;
	if (demoElem.descrip() != "Instructor for CSE687")
		return false;
	if (demoElem.dateTime().now() != DateTime().now())
		return false;

	db["name_space-SFileName.cpp.3"] = demoElem;
	return true;
}

//Adding data to DB
bool testR3b(DbCore<PayLoad>& db)
{
	DbElement<PayLoad> demoElem = db["SomeNS-Fawcett.cpp.3"];

	demoElem.name("Ammar");
	demoElem.descrip("TA for CSE687");
	db["Namespace-Salman.cpp.1"] = demoElem;
	if (!db.contains("Namespace-Salman.cpp.1"))
		return false;

	demoElem.name("Jianan");
	db["Sal.cpp.1"] = demoElem;

	demoElem.name("Nikhil");
	db["Prashar.cpp.1"] = demoElem;

	demoElem.name("Pranjul");
	db["SomeNS-Fawcett.cpp.1"] = demoElem;

	Keys keys = db.keys();
	db["SomeNS-Fawcett.cpp.1"].children().push_back("Prashar.cpp.1");

	demoElem = db["Namespace-Salman.cpp.1"];
	db["Namespace-Salman.cpp.1"].children().push_back("Sal.cpp.1");
	db["Namespace-Salman.cpp.1"].children().push_back("SomeNS-Fawcett.cpp.1");


	return true;
}

//Calls the check out method to execute checkout on file
bool fileCheckOut(DbCore<PayLoad>& db) {
	std::cout << "In testing...\n";
	showDb(db);
	Checkout<PayLoad> c(db);
	c.checkOutFile("Namespace-Salman.cpp.1","../ClientRepo/");
	return true;
}
int main() {

	DbCore<PayLoad> db;
	testR3a(db);
	testR3b(db);
	fileCheckOut(db);
	std::cin.get();
	return 0;
}
#endif // CHECKOUT_TEST
