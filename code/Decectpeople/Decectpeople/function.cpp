#include "stdafx.h"
#include "function.h"
#include "highgui.h"
#include <math.h>
#include <iostream>
#include "ticktimer.h"
using namespace std;
using namespace cv;

IplImage* imageResetSize(IplImage* src, int newWidth, int newHeight)
{
    CvSize newSize;
    newSize.width = newWidth;
    newSize.height = newHeight;
    IplImage *dst = cvCreateImage(newSize, src->depth, src->nChannels);
    cvResize(src, dst);
    return dst;
}


IplImage* imageMouseSelection(IplImage *src, int x, int y, int width, int height, int creWidth, int creHeight)
{
    CvSize cvSize;
    cvSize.width = src->width;
    cvSize.height = src->height;
    IplImage* dst = cvCreateImage(cvSize, src->depth, src->nChannels);
    cvResize(src, dst);
    cvSetImageROI(dst, cvRect(x, y, width, height));
    return imageResetSize(dst, creWidth, creHeight);
}

void testOpencvHog(char *path)
{
    Mat image = imread(path);
    HOGDescriptor hog;
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
    vector<Rect> found, found_filtered;//矩形框数组

    {
        MyTimer timer;
        hog.detectMultiScale(image, found, 0, Size(8, 8), Size(32, 32), 1.05, 2);//对图像进行多尺度检测，检测窗口移动步长为(8,8)
    }

    if(found.size() > 0)
    {
        std::cout << "get it" << endl;

        // 显示
        for(size_t i = 0; i < found.size(); i++)
        {
            cv::rectangle(image, found[i], cv::Scalar(0, 0, 255), 2);
        }

        cv::imshow("hog", image);
        cv::waitKey(0);
    }
    else
        std::cout << "fail" << endl;
}


