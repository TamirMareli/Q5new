#pragma once
#include <iostream>
#include <cstring>
using namespace std;

class AD_File {

protected:
	string FileName;
	tm* lastUpdateTime;

public:
	string getName()const { return this->FileName; };
	void setName(string name) { this->FileName = name; };
  string getTime();
  void setTime();
  AD_File(string name) { this->FileName = name; setTime(); };
  virtual bool operator==(const AD_File& other)const;
  virtual ~AD_File(){};
};