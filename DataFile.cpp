#pragma once
#include "DataFile.h"

DataFile::DataFile(string name, string data):AD_File(name)
{
	this->data = data;
}

 bool DataFile::operator==(const AD_File& other)const
{
	bool chack = true;
	chack = AD_File::operator==(other);
	const DataFile* ptr = dynamic_cast<const DataFile*>(&other);
	if (ptr) 
		chack = chack && this->data == ptr->data;
	return chack;

}

