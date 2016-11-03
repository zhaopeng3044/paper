#ifndef __SORTPIC_H__
#define __SORTPIC_H__

#include "stdafx.h"
#include "cv.h"
#include <string>
#include <windows.h>
using namespace std;

class SortPic
{
public:
	SortPic(const char *windowName, const char* path, const char *fileListName, int width = 64, int height = 128);
	~SortPic();
	void processSort();
	void onMouseEvent(int event, int x, int y);

private:
	void initEnv();
private:
	// 记录文件的当前目录(通常不会变)
	string m_strPath;

	// 一个具体文件的目录(循环处理时会变)
	string m_strFilePath;

	// 读取到的原始图像文件，目标文件从这个文件截取
	IplImage* m_psrcImg;

	// 鼠标标记红框时的临时图像文件
	IplImage* m_ptmpImg;

	//最终保存的文件
	IplImage* m_pDstImg;

	// 显示图片的窗口名称
	string m_strWindowName;

	// 存放一系列图片名的文件
	string m_strFileList;

	// 当前处理的文件名（不包含路径)
	string m_strCurName;

	//  鼠标标框的其实位置
	CvPoint m_pointBegin;

	// 最终保存图片的宽度
	int m_ntarWidth;

	// 最终保存图片的高度
	int m_nTarHei;

	// 一张图片可能有多个人，标记不同保存的文件
	int m_nCounter;

	// 处理下一个文件使用的事件通知
	HANDLE m_hEvent;

	//已经处理过文件的列表
	vector<string> m_vecSortList;

	//处理过的文件记录文件
	string m_strSortedFile;
};
#endif