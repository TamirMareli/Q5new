#include "AD_File.h"
#include "DataFile.h"
#include "Folder.h"
void main() {
	Folder folder_main("folder1", "main");
	DataFile file1("file1", "empty");
	Folder folder1("folder1", " ");
	DataFile file2("file2", "e");
	Folder folder2("filder2", "  ");
	folder_main.addFileToArray(&file1);
	folder_main.addFileToArray(&folder1);
	folder_main.addFileToArray(&file2);
	folder_main.addFileToArray(&folder2);
}