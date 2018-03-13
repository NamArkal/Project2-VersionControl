#pragma once
///////////////////////////////////////////////////////////////////////////
// RepositoryCore.h - test file for newly added Project 2 functionlity   //
// ver 1.0                                                               //
// Author : Namrata Arkalgud                                             //
///////////////////////////////////////////////////////////////////////////

/*
* Package Operations:
* -------------------
* This package contains tests for each requirement.
* It calls the different packages mentioned below to execute requirement.
*
* Required Files:
* ---------------
* DbCore.h
* Checkout.h
* CheckIn.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 9 Mar 2018
* - first release
*/
#include "../DbCore/DbCore.h"
#include "../CheckIn/CheckIn.h"
#include "../CheckOut/Checkout.h"

void identify(std::ostream & out)
{
	out << "\n  \"" << __FILE__ << "\"";
}

bool repoCoreTest3() {
	identify(std::cout);
	CheckIn<PayLoad>::identify();
	Checkout<PayLoad>::identify();
	Version<PayLoad>::identify();
	Browse<PayLoad>::identify();
	return true;
}


bool repoCoreTestCheckOut(DbCore<PayLoad>& db_) {
	Checkout<PayLoad> co(db_);
	co.checkOutFile("Namespace-Salman.cpp.1", "../ClientRepo/");
	std::cout << "\nPlease check the ClientRepo folder to ensure that files have been copied!\n";
	std::cout.flush();
	char ch;
	std::cin.read(&ch, 1);
	return true;
}

bool repoCoreTest4(DbCore<PayLoad>& db_) {
	repoCoreTestCheckOut(db_);
	CheckIn<PayLoad> c(db_);
	DbElement<PayLoad> demoElem = db_["SomeNS-Fawcett.cpp.4"];
	demoElem.name("Pranjul");
	demoElem.descrip("Student of CSE687");
	PayLoad p;
	p.value("../Files/");
	p.status("close");
	p.categories().push_back("cat1");
	p.categories().push_back("cat2");
	demoElem.payLoad(p);
	bool res = c.checkInFile("SomeNS-Fawcett.cpp", demoElem);
	std::cout << "\nThe result is: " << res << "\n";
	showDb(db_);
	return true;
}

bool repoCoreTest5(DbCore<PayLoad>& db_) {
	Browse<PayLoad> b(db_);
	std::cout << "\nBrowsing files with file name like \"SomeNS-Fawcett.cpp\"" << "\n";
	b.queryKeys("SomeNS-Fawcett.cpp").show();
	std::cout << "\n\nShowing file \"Prashar.cpp\"\n";
	b.showFile("Prashar.cpp", "../ClientRepo/");
	std::cout << "\n\nPrinting dependency graph for file \"Namespace-Salman.cpp.1\" and its related files.\n";
	b.showDependency("Namespace-Salman.cpp.1");
	return true;
}