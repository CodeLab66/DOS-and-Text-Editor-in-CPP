#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Node.h"

class File : public TreeNode {
public:
    int Characters;
    int Lines;
    int CharactersPerLine;
    int priority;
    int timeToPrint;
    string fileType;

    File(const string& Name, const string& Owner, bool ReadOnly, bool ReadWrite, const string& Type, const string& content, TreeNode* parent = nullptr)
        : TreeNode(Name, Owner, ReadOnly, ReadWrite, parent), fileType(Type) {
        Characters = countCharacters(content);
        Lines = countLines(content);
        CharactersPerLine = averageCharactersPerLine();
        priority = 1;
        timeToPrint = calculatePrintingTime();
    }

    int countCharacters(const string& content) {
        return content.length();
    }

    int countLines(const string& content) {
        return count(content.begin(), content.end(), '\n') + 1;
    }

    int averageCharactersPerLine() {
        if (Lines > 0) {
            return Characters / Lines;
        }
        else {
            return 0;
        }
    }

    int calculatePrintingTime() {
        return Characters / 10;
    }

    void updateContent(const string& newContent) {
        Characters = countCharacters(newContent);
        Lines = countLines(newContent);
        CharactersPerLine = averageCharactersPerLine();
        timeToPrint = calculatePrintingTime();
    }

    void displayInformation() const override {
        cout << "File Name: " << name << endl;
        cout << "Owner: " << owner << endl;
        cout << "Read-Only: " << (readOnly ? "Yes" : "No") << endl;
        cout << "Type: " << fileType << endl;
        cout << "Number of Characters: " << Characters << endl;
        cout << "Number of Lines: " << Lines << endl;
        cout << "Average Characters per Line: " << CharactersPerLine << endl;
        cout << "Time to Print: " << timeToPrint << " seconds" << endl;
        cout << "Creation Time: " << creationTime << endl;
    }

    void renameFile(const string& newName) {
        rename(name.c_str(), newName.c_str());
        name = newName;
    }
};

