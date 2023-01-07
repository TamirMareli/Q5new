#pragma once
#include "AD_File.h"
#include <iostream>
#include <cstring>
using namespace std;

class DataFile:public AD_File {
	string data;
public:

	DataFile(string name, string data);
	virtual bool operator==(const DataFile& other);
	int getSize()const { return this->data.size(); };
	virtual ~DataFile() {};
};