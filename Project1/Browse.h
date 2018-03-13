#pragma once
///////////////////////////////////////////////////////////////////////
// Browse.h - allows browsing of files in NoSqlDb                    //
// ver 1.0                                                           //
// Namrata Arkalgud                                                  //
///////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package provides a functionality that alllows querying files, view files and check dependency
*  for the NoSqlDb.  
*
*  Required Files:
*  ---------------
*  Browse.h
*  DbCore.h
*  PayLoad.h
*  Query.h
*  GraphWalk.h
*  Process.h
*
*  Maintenance History:
*  --------------------
*  Ver 1.0 : 2 Mar 2018
*  - first release
*/
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include "../Query/Query.h"
#include "../DbCore/DbCore.h"
#include "../Process/Process.h"
#include "../GraphWalk/GraphWalk.h"
#include "../PayLoad/PayLoad.h"

using namespace NoSqlDb;

template <typename P>
class Browse
{
private:
	using Graph = Graph<std::string>;
	using Node = Node<std::string>;
	using Sptr = GraphProcessing::Sptr<std::string>;
	Keys keys_;
	DbCore<P> db_;
	Process p;
	Graph g;
	std::queue<std::string> q;
	bool flag = true;

public:
	static void identify(std::ostream& out = std::cout);

	Browse& queryKeys(const std::string regExp);

	Browse& queryDependency(const std::string regExp);

	void show(std::ostream& out = std::cout);

	void buildDependency(const Key& key);

	void openDependency(const Key& key);

	bool getOpenDependency(const Key& key);

	void showDependency(const Key& key);

	void showFile(Key key, std::string filePath);

	Keys& keys() { return keys_; }

	Browse(DbCore<P>& db) {
		db_ = db;
	}

};

//Queries the keys with the given regular expression for and gets its dependencies
template<typename P>
Browse<P>& Browse<P>::queryKeys(const std::string regExp)
{
	Query<P> q(db_);
	keys_ = q.selectKeys(regExp).keys();
	for (Key k : keys_) {
		std::cout << "For key " << k << " the dependencies are: " << std::endl;
		queryDependency(k);
	}
	return *this;
}

//Gets the key's dependencies
template<typename P>
Browse<P>& Browse<P>::queryDependency(const std::string regExp)
{
	DbElement<P> e = db_[regExp];
	Children children = e.children();
	if (children.size() > 0)
	{
		for (Key k : e.children()) {
			keys_.push_back(k);
			std::cout << k << "\n";
		}
	}
	else std::cout << "\nDoes not contain child keys\n";
	return *this;
}

//Shows record for keys queried in the class' methods
template<typename P>
void Browse<P>::show(std::ostream & out)
{
	showHeader();
	for (Key k : keys_) {
		DbElement<P> temp = db_[k];
		showRecord(k, temp);
	}
}

//Recursively calls using GraphWalk to build dependency graph
template<typename P>
void Browse<P>::buildDependency(const Key & key)
{
	keys_.clear();
	queryDependency(key);
	if (keys_.size() > 0) {
		for (Key k : keys_) {
			q.push(k);
			g.addNode(Sptr(new Node(k)));
			g.addEdge(key, k);
		}
	}

		q.pop();
		if(!q.empty())
			buildDependency(q.front());
}

//Uses GraphWalk to build and display dependency
template<typename P>
void Browse<P>::showDependency(const Key & key)
{
	q.push(key);
	g.addNode(Sptr(new Node(key)));
	buildDependency(key);
	showGraph(g);
}

//Checks if dependent files of a key have open status
template<typename P>
void Browse<P>::openDependency(const Key & key)
{
	keys_.clear();
	queryDependency(key);
	if (keys_.size() > 0) {
		for (Key k : keys_) {
			q.push(k);
			DbElement<P> e = db_[k];
			std::cout << "\nName of key is " << e.name() << "\n";
			PayLoad p = e.payLoad();
			if (p.status() != "" && p.status() == "open") {
				std::cout << "\nDependent key " << k << " has open status!\n";
				flag = false;
			}
		}
	}

	q.pop();
	if (!q.empty())
		openDependency(q.front());
}

//Calls the recursive function which checks for open status in dependent files
template<typename P>
bool Browse<P>::getOpenDependency(const Key & key)
{
	q.push(key);
	openDependency(key);
	return flag;
}

//Allows people to view file
template<typename P>
void Browse<P>::showFile(Key key, std::string filePath)
{
	std::string appPath = "c:/windows/system32/notepad.exe";
	p.application(appPath);

	std::string cmdLine = "/A " + filePath + key;
	p.commandLine(cmdLine);

	std::cout << "\n  starting process: \"" << appPath << "\"";
	std::cout << "\n  with this cmdlne: \"" << cmdLine << "\"";
	p.create();

	CBP callback = []() { std::cout << "\n  --- child process exited with this message ---"; };
	p.setCallBackProcessing(callback);
	p.registerCallback();

	std::cout << "\n  after OnExit";
	std::cout.flush();
	char ch;
	std::cout << "\nPress enter key\n";
	std::cin.read(&ch, 1);
}

//Prints path of package
template<typename P>
void Browse<P>::identify(std::ostream& out)
{
	out << "\n  \"" << __FILE__ << "\"";
}
