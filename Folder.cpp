#include "Folder.h"
#include <typeinfo>


Folder Folder::root("root", "c:");

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
	DataFile* d = new DataFile(name, data);
	this->addFileToArray(d);
}

void Folder::mkDir(string name) throw(const char*)
{
	Folder* f = new Folder(name, this->Path);
	this->addFileToArray(f);
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
	int folderPlace = 0;
	int cureentPlace = path.find_first_of(92);
	string currentFolder = path.substr(0, cureentPlace);
	path = path.substr(cureentPlace + 1); 
	Folder* pfolder = Folder::root.findFolderPointer(path, cureentPlace, currentFolder, path.size());
	return nullptr;
}

string Folder::intoFolder(string _foldername)
{
	string newpath(this->Path);
	newpath += "\\";
	newpath += this->FileName;
	return newpath;
}

Folder* Folder::findFolderPointer(string path, int currentPlace, string currentFolder, int pathSize) throw(const char*)
{
	if (pathSize == 0)
		return this;
	for (int i = 0; i < this->size; i++)
	{
		if (strcmp(typeid(*this->file[i]).name(), typeid(Folder).name())) {
			if (*this->file[i] == currentFolder)
			{
				currentPlace = path.find_first_of(92);
				currentFolder = path.substr(0, currentPlace);
				path = path.substr(currentPlace + 1);
				findFolderPointer(path, currentPlace, currentFolder, path.size());
			}
			else throw "There is not such path";
		}
	}
	return nullptr;
}

bool Folder::operator==(const AD_File& other) const
{
	bool chack = true;
	chack = AD_File::operator==(other);
	const Folder* ptr = dynamic_cast<const Folder*>(&other);
	if (ptr) {
		if (this->size != ptr->size)
			return false;
		for (int i = 0; i < this->size; i++) {
			if (strcmp(typeid(*this->file[i]).name(), typeid(*ptr->file[i]).name())) {
				if (strcmp(typeid(*this->file[i]).name(), typeid(Folder).name()))
					chack = chack&&(this->file[i]->getName() == ptr->file[i]->getName());
				else
					chack =chack&& (this->file[i]->operator==(other));
			}
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



bool Folder::FC( Folder& currentDir, string source, string dest)
{
	vector<string> s = split(source, '\\');
	vector<string> d = split(source, '\\');
	AD_File* S = rpt(s, &currentDir, 0, s.size());
	AD_File* D = rpt(d, &currentDir, 0, d.size());
	S->operator==(*D);
}

AD_File* Folder::rpt(vector<string> path,Folder* ptr,int i,int size)const
{
	if (ptr->getName() == path[i] && i == size) {
		return ptr;
	}
		const Folder* p = dynamic_cast<const Folder*>(ptr);
		if (p) {
			for (int j = 0; j < p->size; j++) {
				if (p->file[j]->getName() == path[i]) {
					rpt(path, p->file[j], i + 1, size);
				}
			}
		}
		throw "The File/Folder does not exist";
}


