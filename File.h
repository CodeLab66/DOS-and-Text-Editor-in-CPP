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
    string content; 

    File(const string& Name, const string& Owner, bool ReadOnly, bool ReadWrite, const string& Type, const string& Content, TreeNode* Parent = nullptr)
        : TreeNode(Name, Owner, ReadOnly, ReadWrite, Parent), fileType(Type), content(Content) { 
        Characters = countCharacters(content);
        Lines = countLines(content);
        CharactersPerLine = averageCharactersPerLine();
        if (ReadWrite == true) {
            priority = 2;
        }
        else {
            priority = 1;
        }
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
        content = newContent; 
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


