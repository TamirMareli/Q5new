//#include "AD_File.h"
//#include "DataFile.h"
//#include "Folder.h"
//void main() {
//	Folder folder_main("root", "\\C:folder1:\\folder2");
//	cout << "check the getFullPath function:" << endl;
//	cout << folder_main.getFullPath()<<endl;
//	Folder folder_main2("folder2", "main2");
//	DataFile file1("file1", "empty");
//	Folder folder1("folder1", " ");
//	DataFile file2("file2", "e");
//	Folder folder2("filder2", "  ");
//	cout << "check the addFileToArray function:" << endl;
//	folder_main.addFileToArray(&file1);
//	folder_main.addFileToArray(&folder1);
//	folder_main.addFileToArray(&file2);
//	folder_main.addFileToArray(&folder2);
//	folder_main2.addFileToArray(&file1);
//	folder_main2.addFileToArray(&folder1);
//	folder_main2.addFileToArray(&file2);
//	folder_main2.addFileToArray(&folder2);
//	folder_main2.dir();
//	cout << "check the mkfile function:" << endl;
//	folder1.mkfile("file1","data1fdsadvsavsdavdsv");
//	folder1.mkfile("file2", "data2ddddddddddddddddddddddddddddddddddddddddd");
//	folder1.mkfile("file3", "data3vvvvvvvvvvvvvvvvvvvvvvv");
//	folder1.mkfile("file4", "data4vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
//	folder1.dir();
//	cout << "check the mkDir function:" << endl;
//	folder1.mkDir("folder");
//	folder1.mkDir("folder2");
//	folder1.mkDir("folder3");
//	folder1.dir();
//	cout << "check the operator== function:" ;
//	cout << folder1.operator==(folder2)<<endl;
//	cout << "check the FC function:";
//	string source = "c:\\Folder";
//	string dest = "c:\\file";
//	cout << folder1.fc(folder2, source, dest) << endl;
//  
//
//}
//
#pragma once
#include <iostream>
#include "DataFile.h"
#include "Folder.h"
#include <iostream>
#include <typeinfo>
using namespace std;
void main() {
	Folder* root = &Folder::root;
	root->mkDir("C:");
	root->mkDir("D:");
	Folder* curr = Folder::cd("C:");
	bool quit = false; string path;
	string command, p_command;
	char echoStream[256];
	do {
		std::cout << curr->getFullPath() << ">";//deletes Root Folder Name
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> command;
		try {
			if (command == "cd") {
				cin.ignore(1);
				cin >> p_command;
				curr = Folder::cd(p_command);
				continue;
			}
			if (command == "mkdir") {
				cin.ignore(1);
				cin >> p_command;
				curr->mkDir(p_command);
				continue;
			}
			if (command == "dir") {
				curr->dir();
				continue;
			}
			if (command == "echo") {
				cin.ignore(1);
				std::cin.getline(echoStream, 256);
				command = echoStream;
				curr->mkfile(command.substr(command.find('<') + 2), command.substr(0, command.find('<') - 1));
				continue;
			}
			if (command == "FC") {
				cin.ignore(1);
				cin >> p_command;
				cin.ignore(1);
				cin >> command;
				if (fc(*curr, p_command, command) == true)
					cout << " equals\n";
				else
					cout << " not equals\n";
				continue;
			}
		}
		catch (const char* msg) { cout << msg << endl; }
		catch (...) {
			std::cout << "unhandeled eception";
		};
		break;
	} while (!quit);
}
