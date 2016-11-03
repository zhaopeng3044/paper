#ifndef __PREPAPER_H__
#define __PREPAPER_H__

#include "stdafx.h"
#include "cv.h"
#include "highgui.h"
#include "preFunction.h"

class Prepare
{
public:
    IplImage* getEdges(IplImage *pOri, int erodes = 0, int dilates = 0);
    IplImage* getInterestCours(IplImage* pOri, Contours* roi_contours);
    void roiDetect(IplImage* psrc);

private:
    void ss_filter(IplImage* img);

    //轮廓极左点
    CvPoint* left_point_contour(CvSeq* cs);
    //轮廓极右点
    CvPoint* right_point_contour(CvSeq* cs);
    //轮廓最下点
    CvPoint* bottom_point_contour(CvSeq* cs);
    //轮廓最上点
    CvPoint* up_point_contour(CvSeq* cs);
    //筛选角度
    int contour_selected(CvSeq* c);

};

#endif
