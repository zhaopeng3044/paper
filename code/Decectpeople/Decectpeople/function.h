#ifndef __TEST_FUNCTION_H__
#define __TEST_FUNCTION_H__
#include "stdafx.h"
#include "cv.h"
/*
剪裁图像到指定大小
*/
IplImage* imageResetSize(IplImage* src, int newWidth, int newHeight);


/*
根据鼠标拖动的矩形生成指定大小图像
*/
IplImage* imageMouseSelection(IplImage *src, int x, int y, int width, int height, int creWidth, int creHeight);

void testOpencvHog(char* path);

#endif
