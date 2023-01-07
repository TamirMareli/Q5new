#include "Folder.h"
#include <typeinfo>

bool Folder::operator==(const Folder& other) const
{
	return (AD_File::operator==(other));
}

void Folder::addFileToArray(const AD_File* file)throw(const char*)
{
	for (int i = 0; i < this->size; i++) {
		if (!strcmp(typeid(*this->file[i]).name(), typeid(*file).name())) {
			if (!strcmp(typeid(DataFile).name(), typeid(*file).name()) && file->operator==(*this->file[i])) {
				throw "File allready exists";
			}
			if (!strcmp(typeid(Folder).name(), typeid(*file).name()) && file->operator==(*this->file[i])) {
				throw "File allready exists";
			}
		}
	}
			AD_File** temp = new AD_File * [this->size];
			for (int i = 0; i < this->size; i++) {
				if (!strcmp(typeid(*this->file[i]).name(), typeid(DataFile).name())) {
					temp[i] = new DataFile(*(DataFile*)this->file[i]);
				}
				if (!strcmp(typeid(*this->file[i]).name(), typeid(Folder).name())) {
					temp[i] = new Folder(*(Folder*)this->file[i]);
				}
				delete this->file[i];
			}
			delete[] this->file;
			this->file = new AD_File * [this->size+1];
			for (int i = 0; i < this->size; i++) {
				if (!strcmp(typeid(*temp[i]).name(), typeid(DataFile).name())) {
					this->file[i] = new DataFile(*(DataFile*)temp[i]);
				}
				if (!strcmp(typeid(*temp[i]).name(), typeid(Folder).name())) {
					this->file[i] = new Folder(*(Folder*)temp[i]);
				}
				delete temp[i];
			}
			delete[] temp;
			if (!strcmp(typeid(*file).name(),typeid(DataFile).name())) {
				this->file[this->size] = new DataFile(*(DataFile*)file);
			}
			if (!strcmp(typeid(*file).name(), typeid(Folder).name())) {
				this->file[this->size] = new Folder(*(Folder*)file);
			}
			this->size++;

	}


Folder::~Folder()
{
	for (int i = 0; i < this->size; i++) 
		delete this->file[i];
	delete[] this->file;
}

Folder::Folder(Folder& f,string p):AD_File::AD_File(f.FileName)
{
	this->Path = p;

	for (int i = 0; i < this->size; i++)
		delete this->file[i];
	delete[] this->file;
	for (int i = 0; i < f.size; i++)
		addFileToArray(this->file[i]);
}

void Folder::mkfile(const string name, const string data)
{
	DataFile* d = new DataFile(name, data);
	this->addFileToArray(d);
}

