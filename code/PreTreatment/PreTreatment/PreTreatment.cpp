// PreTreatment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cv.h"
#include "highgui.h"
#include "prePare.h"
#include "preFunction.h"
using namespace cv;

int _tmain(int argc, _TCHAR* argv[])
{
    char *path = "J:/PersonBase/images/000003072.jpg";
    IplImage *pImage = cvLoadImage(path);
    // cvNamedWindow("demo");

    Prepare preTreat;
    cv::imshow("src", Mat(pImage));
    preTreat.roiDetect(pImage);
    Contours contour;
    cv::imshow("demo", Mat(preTreat.getInterestCours(pImage, &contour)));
    cvWaitKey(-1);
    getchar();
    return 0;
}

