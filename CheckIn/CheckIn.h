#pragma once
/////////////////////////////////////////////////////////////////////
// CheckIn.h - allows checking in of files                         //
// ver 1.0                                                         //
// Namrata Arkalgud                                                //
/////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package allows checking in of files i.e. changes to be made on latest version of file
*  for the NoSqlDb.
*
*  Required Files:
*  ---------------
*  Browse.h
*  DbCore.h
*  PayLoad.h
*  Query.h
*  Version.h
*
*  Maintenance History:
*  --------------------
*  Ver 1.0 : 2 Mar 2018
*  - first release
*/
#include <string>
#include <iostream>
#include "../DbCore/DbCore.h"
#include "../Query/Query.h"
#include "../Version/Version.h"
#include "../Project1/Browse.h"
#include "../PayLoad/PayLoad.h"
#include <fstream>
#include <Windows.h>
#include <stdlib.h>

using namespace NoSqlDb;

template <typename P>
class CheckIn
{
public:
	//Constructor to initialize class with latest instance of DbCore
	CheckIn(const DbCore<P>& db) { db_ = db; }

	static void identify(std::ostream& out = std::cout);

	//Gets if file has any open dependent files
	bool getOpenDependency() {
		Browse<P> b(db_);
		return b.getOpenDependency(currKey_);
	}

	//Checks if person checking file is author of file
	bool checkAuthor() {
		std::string auth = getAuthor();
		if (auth != "" && dbe_.name() != "" && auth == dbe_.name())
			return true;
		else return false;
	}

	//Adds incremented version of file to closed check-ins
	bool addVersionToFile() {
		Version<P> v(db_);
		int version = v.latestVersion(key_);
		currKey_ = key_ + "." + std::to_string(version);
		std::string status = getStatus();
		if(status != "" && status == "close")
			version += 1;
		newKey_ = key_ + "." + std::to_string(version);
		if (key_ != "")
			return true;
		else return false;
	}

	//Gets author of file
	std::string getAuthor() {
		Query<P> q(db_);
		DbElement<P> e;
		Keys keys = q.selectKeys(key_).keys();
		if(keys.size() > 0)
			e = db_[keys.back()];
		return e.name();
	}

	//Gets file path of file to be checked in
	std::string getFilePath() {
		PayLoad p;
		p = dbe_.payLoad();
		return p.value();
	}

	//Moves file from ClientRepo to its file path
	bool moveFile() {
		std::string src = "../ClientRepo/" + key_;
		std::string dst = getFilePath() + newKey_;

		std::ifstream in(src.c_str());
		std::ofstream out(dst.c_str());

		out << in.rdbuf();

		out.close();
		in.close();

		if (std::remove(src.c_str()) != 0)
			perror("Error deleting file");
		else
			puts("File successfully deleted from ClientRepo and moved to \"../Files\" folder.");

		return true;
	}

	//Checks if file exists in ClientRepo
	bool fileInFolder() {
		std::string filepath = "../ClientRepo/" + key_;
		std::fstream file;
		file.open(filepath.c_str(), std::ios::in);
		if (file.is_open() == true)
		{
			file.close();
			return true;
		}
		file.close();
		return false;
	}

	//Gets status of latest version of file
	std::string getStatus() {
		PayLoad p;
		Query<P> q(db_);
		Keys keys = q.selectKeys(key_).keys();
		DbElement<P> e;
		if(keys.size() > 0)
			e = db_[keys.back()];
		p = e.payLoad();
		return p.status();
	}

	//Allows user to make changes to file
	bool editFile() {
		Browse<P> b(db_);
		b.showFile(key_, "../ClientRepo/");
		return true;
	}

	//Calls all the above method to perform check-in
	bool checkInFile(const Key& key, DbElement<P> dbe) { 
		bool flag = false;
		key_ = key;
		dbe_ = dbe;
		std::string status = getStatus();
		
			if (status != "") {
				if (checkAuthor()) {
					std::cout << "\nAuthor check successful\n";
					if (fileInFolder()) {
						std::cout << "\nFile is present in folder\n";
							if (addVersionToFile()) {
								if (getOpenDependency()) {
									std::cout << "\nThere are no open dependent files\n";
									if (editFile()) {
										std::cout << "\nEditing file..\n";
										if (moveFile()) {
											db_[newKey_] = dbe_;
											flag = true;
										}
									}
								}
							}
					}
				}
			}
		else std::cout << "\nFile status not received or dependent files are open, close them before checking in current file.\n";
		showDb(db_);
		return flag;
	}

private:
	Key key_;
	Key currKey_;
	Key newKey_;
	DbCore<P> db_;
	DbElement<P> dbe_;
};

template<typename P>
void CheckIn<P>::identify(std::ostream & out)
{
	out << "\n  \"" << __FILE__ << "\"";
}
