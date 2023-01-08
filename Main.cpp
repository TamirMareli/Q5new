#include "AD_File.h"
#include "DataFile.h"
#include "Folder.h"
void main() {
	Folder folder_main("folder1", "main");
	Folder folder_main2("folder2", "main2");
	DataFile file1("file1", "empty");
	Folder folder1("folder1", " ");
	DataFile file2("file2", "e");
	Folder folder2("filder2", "  ");
	folder_main.addFileToArray(&file1);
	folder_main.addFileToArray(&folder1);
	folder_main.addFileToArray(&file2);
	folder_main.addFileToArray(&folder2);
	folder_main2.addFileToArray(&file1);
	folder_main2.addFileToArray(&folder1);
	folder_main2.addFileToArray(&file2);
	folder_main2.addFileToArray(&folder2);
	cout << folder_main.getFullPath() << endl;
	folder1.mkDir("file1");
	folder1.mkDir("file2");
	folder1.mkDir("file3");
	folder1.mkfile("file1","data1fdsadvsavsdavdsv");
	folder1.mkfile("file2", "data2ddddddddddddddddddddddddddddddddddddddddd");
	folder1.mkfile("file3", "data3vvvvvvvvvvvvvvvvvvvvvvv");
	folder1.mkfile("file4", "data4vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
	folder1.dir();
	folder_main == folder_main2;


}

