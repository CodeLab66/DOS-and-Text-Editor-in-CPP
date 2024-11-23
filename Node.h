#pragma once
#include <iostream>
#include <string>
using namespace std;

class TreeNode {
public:
	string name;
	string path;
	string creationTime;
	string owner;
	TreeNode* parent;
	bool readOnly;
	bool readwrite;
	
	TreeNode(const string& Name, const string& Owner, bool ReadOnly, bool ReadWrite, TreeNode* Parent = nullptr)
		: name(Name), owner(Owner), readOnly(ReadOnly), readwrite(ReadWrite) {
		time_t currentTime = time(0);
		char buffer[26];
		ctime_s(buffer, sizeof(buffer), &currentTime);
		creationTime = buffer;
	}

	virtual ~TreeNode() {};
	virtual void displayInformation() const = 0;

	string getPath() const {
		if (parent != nullptr) {
			return parent->getPath() + '/' + name;
		}
		else {
			return name;
		}
	}
};
 