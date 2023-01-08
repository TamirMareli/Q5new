#pragma once
#include <iomanip>
#include <string>
#include "AD_File.h"
#include "DataFile.h"

class Folder :public AD_File {
	AD_File** file;
	int size;
	string Path;
public:
	static Folder root;
	Folder(string name, string path) :AD_File(name) { this->Path = path; this->size = 0; };
	string getFullPath() { return this->Path; };
	void addFileToArray(const AD_File* file)throw(const char*);
	virtual ~Folder();
	Folder(Folder& f, string p);
	void mkfile(const string name, const string data)throw(const char*);
	void mkDir(string name)throw(const char*);
	void dir()const;
	static Folder* cd(string path)throw(const string);
	string intoFolder(string _foldername);
	Folder* findFolderPointer(string path, int currentPlace, string currentFolder, int pathSize) throw(const char*);
	virtual bool operator==(const AD_File& other)const;

};