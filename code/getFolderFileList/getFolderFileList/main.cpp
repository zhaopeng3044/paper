// getFolderFileList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "function.h"
#include <string>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc != 3)
		return 0;

	string path = string(argv[1]);
	string saveName = string(argv[2]);
	searchFileList(path.c_str(), saveName.c_str());
	return 0;
}

