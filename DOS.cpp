#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include "Node.h"
#include "File.h"
#include "Directory.h"
using namespace std;


void displayAuthorInformation() {
    cout << "Author: Muhammad Bilal" << endl;
    cout << "Registeration Number: Bscs23146" << endl;
    cout << "Course Name: Data Structures" << endl;
}

void processCommands(Directory& root, Directory*& currentDir, const string& command) {
    cout << endl;
    if (command.substr(0, 6) == "ATTRIB") {
        if (command.length() <= 7) {
            cout << "Usage: ATTRIB <filename>" << endl;
            return;
        }
        string fileName = command.substr(7);
        bool foundFile = false;
        for (TreeNode* i : currentDir->children) {
            if (i->name == fileName) {
                i->displayInformation();
                foundFile = true;
                break;
            }
        }
        if (!foundFile) {
            cout << "Couldn't find the File in Current Directory";
        }
    }
    
    else if (command.substr(0, 2) == "CD") {
        if (command == "CD.") {
            cout << "Current Directory: " << currentDir->getPath() << endl;
        }
        else if (command == "CD..") {
            if (currentDir->parent != nullptr) {
                currentDir = dynamic_cast<Directory*>(currentDir->parent);
            }
            else {
                cout << "Already at the root directory." << endl;
            }
        }
        else if (command == "CD/") {
            currentDir = &root;
        }
        else if (command == "CD") {
            cout << "Current Directory: " << currentDir->name << endl;
            cout << "Contents:" << endl;
            for (TreeNode* child : currentDir->children) {
                cout << " - " << child->name;
                if (dynamic_cast<Directory*>(child)) {
                    cout << " (Directory) ";
                }
                else {
                    cout << " (File) ";
                }
                cout << endl;
            }
        }
        else if (command.length() > 3 && command.substr(0, 3) == "CD ") {
            string dirName = command.substr(3);
            bool found = false;
            for (TreeNode* child : currentDir->children) {
                Directory* dir = dynamic_cast<Directory*>(child);
                if (dir && dir->name == dirName) {
                    currentDir = dir;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Directory " << dirName << " not found in the current directory." << endl;
            }
        }
        else {
            cout << "Invalid CD command." << endl;
        }
    }
    
    else if (command.substr(0, 7) == "CONVERT") {
        int space = command.find(' ', 8);
        if (space == string::npos) {
            cout << "Usage: CONVERT (source_extension) (target_extension)" << endl;
            return;
        }

        string sourceExt = command.substr(8, space - 8);
        string targetExt = command.substr(space + 1);

        bool converted = false;
        for (TreeNode* child : currentDir->children) {
            File* file = dynamic_cast<File*>(child);
            if (file && file->fileType == sourceExt) {
                int lastdot = file->name.find_last_of('.');
                string newName = file->name.substr(0, lastdot) + "." + targetExt;
                file->renameFile(newName);
                file->fileType = targetExt;
                converted = true;
                cout << "Converted: " << file->name << " to ." << targetExt << endl;
            }
        }
        if (!converted) {
            cout << "No files with the extension ." << sourceExt << " were found in the current directory." << endl;
        }
    }

    else if (command.substr(0, 4) == "COPY") { 
        if (command.length() <= 5) { 
            cout << "Usage: COPY <filename> <destination_directory>" << endl; 
            return; 
        } 
        size_t space = command.find(' ', 5); 
        if (space == string::npos) { 
            cout << "Usage: COPY <filename> <destination_directory>" << endl; 
            return; 
        } 
        string fileName = command.substr(5, space - 5); 
        string destDirName = command.substr(space + 1); 
        bool foundFile = false; 
        File* fileToCopy = nullptr; 
        for (TreeNode* i : currentDir->children) { 
            File* file = dynamic_cast<File*>(i); 
            if (file && file->name == fileName) { 
                fileToCopy = file; 
                foundFile = true;
                break; 
            } 
        } 
        if (!foundFile) { 
            cout << "File " << fileName << " not found in current directory." << endl;
            return; 
        } 
        Directory* destDir = nullptr;
        for (TreeNode* i : root.children) { 
            Directory* dir = dynamic_cast<Directory*>(i); 
            if (dir && dir->name == destDirName) { 
                destDir = dir; 
                break; 
            } 
        } if (destDir == nullptr)
        { 
            cout << "Destination directory " << destDirName << " not found." << endl; 
            return; 
        } 
        File* newFile = new File(*fileToCopy); 
        newFile->parent = destDir;
        destDir->children.push_back(newFile);
        cout << "File " << fileName << " copied to " << destDirName << "." << endl;
    }
    
    else if (command.substr(0, 6) == "CREATE") {
        if (command.length() <= 7) {
            cout << "Usage: CREATE <filename>" << endl;
            return;
        }
        string fileName = command.substr(7);
        cout << "Enter the contents of the file (end with an empty line):" << endl;
        string content;
        string line;
        while (getline(cin, line) && !line.empty()) {
            content += line + '\n';
        }
        File* newFile = new File(fileName, "owner", false, true, "txt", content, currentDir);
        currentDir->children.push_back(newFile);
        ofstream write(fileName);
        write << content;
        write.close();
        cout << "File " << fileName << " created." << endl;
    }
    
    else if (command.substr(0, 3) == "DEL") { 
        if (command.length() <= 4) { 
            cout << "Usage: DEL <filename>" << endl;
            return; 
        } 
        string fileName = command.substr(4); 
        auto it = remove_if(currentDir->children.begin(), currentDir->children.end(), [&fileName](TreeNode* child) { 
            File* file = dynamic_cast<File*>(child); 
            if (file && file->name == fileName) { 
                remove(fileName.c_str()); 
                delete file;
                return true; 
            } 
            return false; 
        }); 
        if (it != currentDir->children.end()) { 
            currentDir->children.erase(it, currentDir->children.end()); 
            cout << "File " << fileName << " deleted." << endl; 
        } 
        else { 
            cout << "File " << fileName << " not found." << endl; 
        } 
    }
    
    else {
        cout << "Invalid command." << endl;
    }
}



int main() {
    displayAuthorInformation();
    cout << endl;
    Directory root("V", "owner", false, true);

    Directory* dir1 = new Directory("University", "owner", false, true, &root);
    Directory* dir2 = new Directory("Web Development", "owner", false, true, &root);

    root.addDirectory(dir1);
    root.addDirectory(dir2);

    Directory* subDir1 = new Directory("Data Structures", "owner", false, true, dir1);
    File* subFile1 = new File("LinkedList.txt", "owner", false, true, "txt", "Sample content for LinkedList.txt", subDir1);
    dir1->addDirectory(subDir1);
    subDir1->children.push_back(subFile1);

    Directory* subDir2 = new Directory("HTML", "owner", false, true, dir2);
    File* subFile2 = new File("Tags.txt", "owner", false, true, "txt", "Sample content for Tags.txt", subDir2);
    dir2->addDirectory(subDir2);
    subDir2->children.push_back(subFile2);

    Directory* subDir3 = new Directory("JavaScript", "owner", false, true, dir2);
    File* subFile3 = new File("DOM.txt", "owner", false, true, "txt", "Sample content for DOM.txt", subDir3);
    dir2->addDirectory(subDir3);
    subDir3->children.push_back(subFile3);

    Directory* currentDirectory = dir1;

    string command;
    while (true) {
        cout << currentDirectory->getPath() << "> ";
        getline(cin, command);
        processCommands(root, currentDirectory, command);
        cout << endl;
    }

    return 0;
}
