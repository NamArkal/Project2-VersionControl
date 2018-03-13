///////////////////////////////////////////////////////////////////////
// TestClass.cpp - defines all testing for NoSqlDb                   //
// ver 1.0                                                           //
// Author: Namrata Arkalgud                                          //
// Source:Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018  //
///////////////////////////////////////////////////////////////////////

#include "TestClass.h"
#include "../DbCore/DbCore.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Edit/Edit.h"
//#include "../Executive/Executive.h"
#include <functional>
#include "../CheckIn/CheckIn.h"
#include "../CheckOut/Checkout.h"

using namespace NoSqlDb;

//----< reduce the number of characters to type >----------------------

auto putLine = [](size_t n = 1, std::ostream& out = std::cout)
{
  Utilities::putline(n, out);
};
//----< make PayLoad Test database >-----------------------------------

DbCore<PayLoad> makeTestDb()
{
  DbCore<PayLoad> db;
  PayLoad pl;
  // first record
  pl.value() = "test value1";
  pl.categories().push_back("cat1");
  pl.categories().push_back("cat2");
  DbElement<PayLoad> elem;
  elem.name("elem1");
  elem.descrip("descrip1");
  elem.children().push_back("elem2");
  elem.children().push_back("elem3");
  elem.payLoad(pl);
  db["one"] = elem;

  // second record
  pl.value() = "test value2";
  pl.categories().clear();
  pl.categories().push_back("cat1");
  pl.categories().push_back("cat3");
  elem.name("elem2");
  elem.descrip("descrip2 - a very long and boring description of virtually nothing");
  elem.children().clear();
  elem.children().push_back("elem1");
  elem.children().push_back("elem3");
  elem.payLoad(pl);
  db["two"] = elem;

  // third record
  pl.value() = "test value3 with some extra not very interesting trivia";
  pl.categories().clear();
  pl.categories().push_back("cat2");
  elem.name("elem3");
  elem.descrip("descrip3");
  elem.children().clear();
  elem.children().push_back("elem2");
  elem.payLoad(pl);
  db["three"] = elem;

  return db;
}
//----< R1 >-----------------------------------------------------------
/*
*  - Demonstrate that solution uses C++11
*/
bool TestDb::testR1()
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
bool TestDb::testR2()
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
bool TestDb::testR3a()
{
  //Utilities::title("Demonstrating Requirement #3a - creating DbElement");
  //std::cout << "\n  Creating a db element with key \"Fawcett\":";

  // create some demo elements and insert into db

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

  //showHeader(false);
  //showElem(demoElem);

  db_["SomeNS-Fawcett.cpp-3"] = demoElem;
  return true;
}
//----< R3b >----------------------------------------------------------
/*
*  - Demonstrate creation of Database
*/
bool TestDb::testR3b()
{
  //Utilities::title("Demonstrating Requirement #3b - creating DbCore");

  DbElement<PayLoad> demoElem = db_["SomeNS-Fawcett.cpp-3"];

  demoElem.name("Ammar");
  demoElem.descrip("TA for CSE687");
  demoElem.payLoad(std::string("You should try ..."));
  db_["Namespace-Salman.cpp-1"] = demoElem;
  if (!db_.contains("Namespace-Salman.cpp-1"))
    return false;

  demoElem.name("Jianan");
  demoElem.payLoad(std::string("Dr. Fawcett said ..."));
  db_["Sal"] = demoElem;

  PayLoad p;
  p.value("C:/Users/Namrata A/Desktop/");
  p.categories().push_back("cat1");
  p.categories().push_back("cat2");
  p.status("open");
  demoElem.payLoad(p);

  //demoElem.payLoad(std::string("You didn't demonstrate Requirement #4"));
  demoElem.name("Nikhil");
  db_["Prashar"] = demoElem;

  demoElem.payLoad(std::string("You didn't demonstrate Requirement #5"));
  demoElem.name("Pranjul");
  db_["SomeNS-Fawcett.cpp-7"] = demoElem;

  Keys keys = db_.keys();
  db_["SomeNS-Fawcett.hs-7"].children().push_back("Prashar");

  demoElem = db_["Namespace-Salman.cpp-1"];
  db_["Namespace-Salman.cpp-1"].children().push_back("Sal");
  db_["Namespace-Salman.cpp-1"].children().push_back("Prashar");
  db_["Namespace-Salman.cpp-1"].children().push_back("SomeNS-Fawcett.cpp-7");

  return true;
}

//----< R3 >----------------------------------------------------------
/*
*  - Demonstrate use of required packages
*/
bool TestDb::myTest3()
{
  Utilities::Title("Demonstrating Requirement #3 - required packages");
  //Executive::identify();
  CheckIn<PayLoad>::identify();
  Checkout<PayLoad>::identify();
  Version<PayLoad>::identify();
  Browse<PayLoad>::identify();
  return true;
}

//----< R7 >----------------------------------------------------------
/*
*  - Demonstrate use of Executive package
*/
bool TestDb::testR12()
{
  Utilities::Title("Demonstrate Requirement #7 - Executive Package");
  
  std::cout << "\n  You will find the executive package here: C:\\Users\\Namrata A\\Desktop\\NoSqlDb\\Executive";
  //Executive::identify();

  Utilities::putline();

  std::cout << "\n  Executive is used to demonstrate a deployable structure.";

  return true;
}

//----< R4 >----------------------------------------------------------
/*
*  - Demonstrate check-in and check-out of file
*/
bool TestDb::myTest4()
{
	Utilities::Title("Demonstrate Requirement #4  - File check-in");
	CheckIn<PayLoad> c(db_);
	DbElement<PayLoad> demoElem = db_["SomeNS-Fawcett.cpp-3"];
	demoElem.name("Pranjul");
	demoElem.descrip("Student of CSE687");
	PayLoad p;
	p.value("C:/Users/Namrata A/Desktop/");
	p.status("close");
	p.categories().push_back("cat1");
	p.categories().push_back("cat2");
	demoElem.payLoad(p);
	bool res = c.checkInFile("SomeNS-Fawcett.cpp", demoElem);
	std::cout << "\nThe result is: " << res << "\n";
	return true;
}

//----< R5 >----------------------------------------------------------
/*
*  - Demonstrate browsing of files
*/
bool TestDb::myTest5()
{
	Utilities::Title("Demonstrate Requirement #5 - Browse files");
	Browse<PayLoad> b(db_);
	std::cout << "\nBrowsing files with name \"SomeNS-Fawcett.cpp\"" << "\n";
	b.queryKeys("SomeNS-Fawcett.cpp").show();
	std::cout << "\n";
	std::cout << "\nShowing file SomeNS-Fawcett.cpp\n";
	b.showFile("SomeNS-Fawcett.cpp", "../ClientRepo/");
	std::cout << "\n";
	std::cout << "\nPrinting dependency graph for file \"Namespace::Salman.java::1\" and its related dependencies\n";
	b.showDependency("Namespace-Salman.cpp-1");
	return true;
}

//----< R6 >----------------------------------------------------------
/*
*  - Demonstrate submitting of project with some closed check-ins and some open
*/
bool TestDb::myTest6()
{
	Utilities::Title("Demonstrate Requirement #6 - Submitting some with open and some with close check-ins");
	std::cout << "\nThe PayLoad status shows open or close for each record.\n";
	showDb(db_);
	return true;
}

#include <sstream>
//----< implement requirements testing >-------------------------------

int main()
{
  std::cout << "\n  Testing DbCore<PayLoad>";
  std::cout << "\n =========================";

  //Original Tests
  NoSqlDb::DbCore<PayLoad> db;
  TestDb tdb(db);
  tdb.invoke(&TestDb::testR1);
  tdb.invoke(&TestDb::testR2);
  tdb.invoke(&TestDb::testR3a);
  tdb.invoke(&TestDb::testR3b);

  //Addded Tests
  tdb.invoke(&TestDb::myTest3);
  tdb.invoke(&TestDb::myTest4);
  tdb.invoke(&TestDb::myTest5);
  tdb.invoke(&TestDb::myTest6);
  tdb.invoke(&TestDb::testR12);
  std::cout << "\n\n";
}