#pragma once
///////////////////////////////////////////////////////////////////////
// Version.h - return latest version of file                         //
// ver 1.0                                                           //
// Namrata Arkalgud                                                  //
///////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package returns latest version of file
*  for the NoSqlDb.
*
*  Required Files:
*  ---------------
*  DbCore.h
*  Query.h
*
*  Maintenance History:
*  --------------------
*  Ver 1.0 : 2 Mar 2018
*  - first release
*/
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "../DbCore/DbCore.h"
#include "../Query/Query.h"

using namespace NoSqlDb;

template<typename P>
class Version
{
private:
	DbCore<P> db_;

public:
	static void identify(std::ostream& out = std::cout);

	//Splits file name into parts to obtain the version number
	std::vector<std::string> split(const std::string &s, char delim) {
		std::stringstream ss(s);
		std::string item;
		std::vector<std::string> tokens;
		while (getline(ss, item, delim)) {
			tokens.push_back(item);
		}
		return tokens;
	}

	//Returns latest version of key
	int latestVersion(std::string fileName) {
		Query<P> q1(db_);
		Keys res = q1.selectKeys(fileName).keys();
		int max = 0;
		if (res.size() == 0) {
			return 0;
		}
		else {
			for (Key k : res) {
				std::vector<std::string> tokens = split(k, '-');
				std::string f = tokens.back();
				tokens = split(f, '.');
				int version = std::stoi(tokens.back());
				if (version > max)
					max = version;
			}
			return max; 
		}
	}

	Version(DbCore<P>& db) {
		db_ = db;
	}
};

//Prints path of package
template<typename P>
void Version<P>::identify(std::ostream& out)
{
	out << "\n  \"" << __FILE__ << "\"";
}