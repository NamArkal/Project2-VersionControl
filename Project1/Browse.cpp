/////////////////////////////////////////////////////////////////////
// Browse.cpp - allows browsing of files in NoSQLDB                //
// ver 1.0                                                         //
// Namrata Arkalgud                                                //
/////////////////////////////////////////////////////////////////////

#include "Browse.h"
#include "../PayLoad/PayLoad.h"

#ifdef TEST_BROWSE

//Adding data to DbCore instance
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

//Adding data to DbCore instance
bool testR3b(DbCore<PayLoad>& db)
{
	DbElement<PayLoad> demoElem = db["SomeNS::Fawcett.cpp::3"];

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

	PayLoad p;
	p.value("C:/Users/Namrata A/Desktop/");
	p.status("open");
	p.categories().push_back("cat1");
	p.categories().push_back("cat2");
	demoElem.payLoad(p);
	demoElem.name("Pranjul");
	db["SomeNS::Fawcett.hs::7"] = demoElem;

	Keys keys = db.keys();
	db["SomeNS::Fawcett.hs::7"].children().push_back("Sanman");
	//db["SomeNS::Fawcett.hs::7"].children().push_back("Sun");
	db["SomeNS::Fawcett.hs::7"].children().push_back("Arora");

	demoElem = db["Namespace::Salman.java::1"];
	db["Namespace::Salman.java::1"].children().push_back("Sal");
	db["Namespace::Salman.java::1"].children().push_back("Prashar");
	db["Namespace::Salman.java::1"].children().push_back("SomeNS::Fawcett.hs::7");

	return true;
}

//Testing all functionlaties in Browse class
bool testLatestVersion(DbCore<PayLoad>& db) {
	//std::cout << "\n\nThe latest version method." << "\n";
	Browse<PayLoad> b(db);
	//b.showFile("SomeNS-Fawcett.cpp", "../ClientRepo/");
	//b.queryKeys("Namespace::Salman").show();
	b.showDependency("Namespace::Salman.java::1");
	//bool res = b.getOpenDependency("Namespace::Salman.java::1");
	//std::cout << res << "\n";
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

#endif // TEST_BROWSE
