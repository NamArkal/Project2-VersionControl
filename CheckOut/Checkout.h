#pragma once
/////////////////////////////////////////////////////////////////////
// Chckout.h - allows checking out of files                         //
// ver 1.0                                                         //
// Namrata Arkalgud                                                //
/////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package allows checking out of files i.e. brings a file from the file system in to the local repository
*  for the NoSqlDb.
*
*  Required Files:
*  ---------------
*  FileSystem.h
*  DbCore.h
*  PayLoad.h
*
*  Maintenance History:
*  --------------------
*  Ver 1.0 : 2 Mar 2018
*  - first release
*/
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sys/types.h>
#include <sys/stat.h>
#include "../DbCore/DbCore.h"
#include "../PayLoad/PayLoad.h"
#include "../FileSystem/FileSystem.h"

#define MAX_FILE_NAME_LEN 256

	using namespace NoSqlDb;
	using namespace FileSystem;

	template <typename P>
	class Checkout
	{
	public:

		Checkout(DbCore<P>& db) : db_(db) {};
		static void identify(std::ostream& out = std::cout);
		void checkOutFile(const Key& filename, const std::string& destination);
		void getDependencyKeys(const Key& filename, Keys& tempResultSet);
		void copyToDestination(const std::string& source, const std::string& destination);

	private:
		DbCore<P>& db_;
		std::string fileName;
	};

	//Function to print the keys of the result set
	void PrintKeys(Keys FinalKeys)
	{
		std::cout << "\n";
		for (auto key : FinalKeys)
		{
			std::cout << key << "\n";
		}

	}

	//Function to get dependent keys for a file
	template <typename P>
	void Checkout<P> ::getDependencyKeys(const Key& filename, Keys& tempResultSet)
	{
		if (std::find(tempResultSet.begin(), tempResultSet.end(), filename) != tempResultSet.end())
		{
			std::cout << "\nNo dependent keys found.\n";
			return;
		}
		tempResultSet.push_back(filename);
		DbElement<P> temp = db_[filename];
		Children children = temp.children();
		size_t i = 0;
		while (children.size() > i)
		{
			if (children.size() > 0)
			{
				for (auto key : children)
				{
					getDependencyKeys(key, tempResultSet);
					i++;
				}
			}
		}

	}

	//Moves file to destination path from source
	template <typename P>
	void Checkout<P> ::copyToDestination(const std::string& source, const std::string& destination)
	{
		bool ret = true;
		if (ret == false)
		{
			std::cout << "\nSource path or Destination path.\n";
			return;
		}
		else
		{
			if (destination.empty())
			{
				std::cout << "\nDestination path can't be empty.\n";
				return;
			}
			else
			{
				std::string command;
				std::string key = fileName;
				fileName.pop_back();
				fileName.pop_back();
				command = "copy" + source + " " + destination;
				system(command.c_str());
				std::cout << "\nCopying from source to destination: " << source+key << " " << destination + fileName << "\n";
				ret = FileSystem::File::copy(source+key, destination+fileName, false);
			}
		}
	}

	template<typename P>
	void Checkout<P>::identify(std::ostream & out)
	{
		out << "\n  \"" << __FILE__ << "\"";
	}

	//Main interface to checkout file
	template <typename P>
	void Checkout<P> ::checkOutFile(const Key& filename, const std::string& destination)
	{
		Keys resultKey;
		DbElement<P> temp;
		PayLoad p1;
		getDependencyKeys(filename, resultKey);
		std::sort(resultKey.begin(), resultKey.end());
		resultKey.erase(std::unique(resultKey.begin(), resultKey.end()), resultKey.end());
		for (auto key : resultKey) {
			temp = db_[key];
			fileName = key;
			p1 = temp.payLoad();
			copyToDestination(p1.value(), destination);
		}
	}