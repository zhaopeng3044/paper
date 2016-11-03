#include "stdafx.h"
#include "function.h"
#include <windows.h>
#include <fstream>
using namespace std;

void searchFileList(const char* path, const char *saveFilename)
{
	char szFind[MAX_PATH];
	WIN32_FIND_DATA FindFileData;
	strcpy(szFind, path);
	strcat(szFind, "\\*.*");
	HANDLE hFind =::FindFirstFile(szFind, &FindFileData);

	if(INVALID_HANDLE_VALUE == hFind)
		return ;

	ofstream fout(saveFilename);

	do
	{
		/*if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0)
			{
				//发现子目录，递归之
				char szFile[MAX_PATH] = {0};
				strcpy(szFile, lpPath);
				strcat(szFile, "\\");
				strcat(szFile, FindFileData.cFileName);
				find_all_files(szFile);
			}
		}
		else*/
		//{
		if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
			//找到文件，处理之
			fout << FindFileData.cFileName << endl;

		//}
	}
	while(::FindNextFile(hFind, &FindFileData));

	::FindClose(hFind);
}
