#ifndef __DETECT_H__
#define __DETECT_H__

#include "stdafx.h"
#include "cv.h"
#include <string>
using namespace std;
using namespace cv;
void detectPeople(IplImage* pImage, string &trainedData);
#endif