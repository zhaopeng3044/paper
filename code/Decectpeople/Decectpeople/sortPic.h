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
	// ��¼�ļ��ĵ�ǰĿ¼(ͨ�������)
	string m_strPath;

	// һ�������ļ���Ŀ¼(ѭ������ʱ���)
	string m_strFilePath;

	// ��ȡ����ԭʼͼ���ļ���Ŀ���ļ�������ļ���ȡ
	IplImage* m_psrcImg;

	// ����Ǻ��ʱ����ʱͼ���ļ�
	IplImage* m_ptmpImg;

	//���ձ�����ļ�
	IplImage* m_pDstImg;

	// ��ʾͼƬ�Ĵ�������
	string m_strWindowName;

	// ���һϵ��ͼƬ�����ļ�
	string m_strFileList;

	// ��ǰ������ļ�����������·��)
	string m_strCurName;

	//  ��������ʵλ��
	CvPoint m_pointBegin;

	// ���ձ���ͼƬ�Ŀ��
	int m_ntarWidth;

	// ���ձ���ͼƬ�ĸ߶�
	int m_nTarHei;

	// һ��ͼƬ�����ж���ˣ���ǲ�ͬ������ļ�
	int m_nCounter;

	// ������һ���ļ�ʹ�õ��¼�֪ͨ
	HANDLE m_hEvent;

	//�Ѿ�������ļ����б�
	vector<string> m_vecSortList;

	//��������ļ���¼�ļ�
	string m_strSortedFile;
};
#endif