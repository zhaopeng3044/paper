#include "stdafx.h"
#include "detect.h"
#include <fstream>
#include "highgui.h"
using namespace std;

void detectPeople(IplImage* pImage, string &trainedData)
{
    vector<float> x;
    ifstream fileIn(trainedData.c_str(), ios::in);
    float val = 0.0f;

    while(!fileIn.eof())
    {
        fileIn >> val;
        x.push_back(val);
    }

    fileIn.close();
    vector<cv::Rect>  found;
    //cv::HOGDescriptor hog(cv::Size(64, 64 * 8), cv::Size(16, 16), cv::Size(8, 8), cv::Size(8, 8), 9);
    cv::HOGDescriptor hog;
    hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
    //IplImage* img = NULL;
    cvNamedWindow("img", 0);
    hog.detectMultiScale(Mat(pImage), found, 0, Size(8, 8), cv::Size(32, 32), 1.05, 2);

    if(found.size() > 0)
    {
        for(int i = 0; i < found.size(); i++)
        {
            CvRect tempRect = cvRect(found[i].x, found[i].y, found[i].width, found[i].height);
            cvRectangle(pImage, cvPoint(tempRect.x, tempRect.y),
                        cvPoint(tempRect.x + tempRect.width, tempRect.y + tempRect.height), CV_RGB(255, 0, 0), 2);
        }
    }
}