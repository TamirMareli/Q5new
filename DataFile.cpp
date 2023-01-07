#pragma once
#include "DataFile.h"

DataFile::DataFile(string name, string data):AD_File(name)
{
	this->data = data;
}

bool DataFile::operator==(const DataFile& other)
{
	return AD_File::operator==(other) && this->data == other.data;
}

