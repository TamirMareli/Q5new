#define _CRT_SECURE_NO_WARNINGS
#include "AD_File.h"

string AD_File::getTime()
{
	char buf[80];
	strftime(buf, sizeof(buf), "%d/%m/%Y %X", lastUpdateTime);
	return buf;
}

void AD_File::setTime()
{
	time_t now = time(0);
	lastUpdateTime = localtime(&now);
}

bool AD_File::operator==(const AD_File& other) const
{
	return this->FileName == other.FileName;
}

