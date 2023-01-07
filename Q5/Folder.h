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
	virtual bool operator==(const Folder& other)const;
	static Folder mainFolder;
	Folder(string name, string path) :AD_File(name) { this->Path = path; this->size = 0; };
	string getFullPath() { return this->Path; };
	void addFileToArray(const AD_File* file);
	virtual ~Folder();

};