#ifndef __TEST_FUNCTION_H__
#define __TEST_FUNCTION_H__
#include "stdafx.h"
#include "cv.h"
/*
����ͼ��ָ����С
*/
IplImage* imageResetSize(IplImage* src, int newWidth, int newHeight);


/*
��������϶��ľ�������ָ����Сͼ��
*/
IplImage* imageMouseSelection(IplImage *src, int x, int y, int width, int height, int creWidth, int creHeight);

void testOpencvHog(char* path);

#endif
