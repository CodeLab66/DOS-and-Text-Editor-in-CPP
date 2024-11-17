#pragma once
#include <iostream>
#include <vector>
#include "Node.h"


class Directory : public TreeNode {
public:
	vector<TreeNode*> children;

	Directory(const string& Name, const string& Owner, bool ReadOnly, bool ReadWrite, TreeNode* Parent = nullptr) : TreeNode(Name, Owner, ReadOnly, ReadWrite, Parent) {}

	~Directory() {
		for (TreeNode* i : children) {
			delete i;
		}
	}

	void addDirectory(TreeNode* newDir) {
		newDir->parent = this;
		this->children.push_back(newDir);
	}

	void displayInformation() const override {
		cout << "Directory Name: " << name << endl;
		cout << "Owner: " << owner << endl;
		if (readOnly == true) {
			cout << "Read-Only: Yes" << endl;
		}
		else {
			cout << "Read-Only : No" << endl;
		}
		if (readwrite == true) {
			cout << "Read-Write: Yes" << endl;
		}
		else {
			cout << "Read-Write : No" << endl;
		}
		cout << "Creation Time: " << creationTime << endl;
		for (const TreeNode* i : children) {
			i->displayInformation();
		}
	}
};