#include "Folder.h"
#include <typeinfo>


Folder Folder::root("root", "");

void Folder::addFileToArray(const AD_File* file)throw(const char*)
{
	for (int i = 0; i < this->size; i++) {
		if (!strcmp(typeid(*this->file[i]).name(), typeid(*file).name())) {
			if (!strcmp(typeid(DataFile).name(), typeid(*file).name()) && file->operator==(*this->file[i])) {
				throw "File allready exists";
			}
			if (!strcmp(typeid(Folder).name(), typeid(*file).name()) && file->getName() == this->getName()) {
				throw "Folder allready exists";
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
	DataFile d(name, data);
	this->addFileToArray(&d);
}

void Folder::mkDir(string name) throw(const char*)
{
	string newp = this->Path;
	if (newp.size()!=0)
		newp += "\\";
		newp += name;
	Folder f(name, newp);
	this->addFileToArray(&f);
}

void Folder::dir() const
{
	cout << "Files in folder " << this->FileName << ":" << endl;
	for (int i = 0; i < this->size; i++) {
		if (!strcmp(typeid(*this->file[i]).name(), typeid(DataFile).name())) {
			float size = (float)(((DataFile*)this->file[i])->DataFile::getSize()) / 1024;
			cout << this->file[i]->getTime() << "\t\t";
			cout << fixed << setprecision(2) << size << " KB " << this->file[i]->AD_File::getName() << endl;
		}
		if (!strcmp(typeid(*this->file[i]).name(), typeid(Folder).name())) {
			cout << this->file[i]->getTime() << "   <DIR>\t     " << this->file[i]->AD_File::getName() << endl;
		}
	}	
}
Folder* Folder::cd(string path) throw(const string)
{
	int next = path.find_first_of(92);
	string inF = path.substr(0, next); 
	Folder* pr = &Folder::root;
	path = path.substr(next + 1);
	return Folder::root.findFolderPointer(path, next, inF, pr);
}

Folder* Folder::findFolderPointer(string path, int next, string inF, Folder* Fptr)
{
	if (next == -1)
	{
		Fptr = Fptr->intoFolder(inF);
		return Fptr;
	}
	Fptr = Fptr->intoFolder(inF);
	next = path.find_first_of(92);
	inF = path.substr(0, next);
	path = path.substr(next + 1);
	Fptr = Fptr->findFolderPointer(path, next, inF, Fptr);
	return Fptr;
}

Folder* Folder::intoFolder(string name) throw (const string)
{
	for (int i = 0; i < this->size; i++)
	{
		if (!strcmp(typeid(*this->file[i]).name(), "class Folder"))
			if (this->file[i]->getName() == name)
			{
				return (Folder*)this->file[i];
			}
	}
	throw "folder does not exist in this folder";
}



bool Folder::operator==(const AD_File& other) const
{
	bool chack = true;
	const Folder* ptr = dynamic_cast<const Folder*>(&other);
	if (ptr) {
		if (this->size != ptr->size)
			return false;
		for (int i = 0; i < this->size; i++) {
			if (!strcmp(typeid(*this->file[i]).name(), typeid(*ptr->file[i]).name())) {
				if (!strcmp(typeid(*this->file[i]).name(), typeid(Folder).name()))
					chack = chack&&(this->file[i]->getName() == ptr->file[i]->getName());
				else
					chack =chack&& (this->file[i]->operator==(other));
			}
			else
			return false;
		}
		return chack;
	}
	return false;
}


vector<string> Folder::split(string str, char delimiter)
{
	vector<string> components;
	string currentComponent;
	for (char c : str) {
		if (c == delimiter) {
			components.push_back(currentComponent);
			currentComponent = "";
		}
		else {
			currentComponent += c;
		}
	}
	components.push_back(currentComponent);
	return components;
}



bool fc( Folder& currentDir, string source, string dest)
{

	AD_File* S = currentDir.rpt(source, currentDir);
	AD_File* D = currentDir.rpt(dest, currentDir);
	if (S==NULL || D == NULL)
		return 0;

	return S->operator==(*D);

}
AD_File* Folder::rpt(string path, Folder& currentDir) throw(const string)
{
	Folder* temp = new Folder(currentDir);
	int next = path.find_first_of(92);
	string inF = path.substr(0, next);
	Folder* pr = &Folder::root;
	path = path.substr(next + 1);
	return temp->findFolderPointer(path, next, inF, pr);
}


