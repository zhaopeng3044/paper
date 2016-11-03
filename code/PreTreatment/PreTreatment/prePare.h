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

    //���������
    CvPoint* left_point_contour(CvSeq* cs);
    //�������ҵ�
    CvPoint* right_point_contour(CvSeq* cs);
    //�������µ�
    CvPoint* bottom_point_contour(CvSeq* cs);
    //�������ϵ�
    CvPoint* up_point_contour(CvSeq* cs);
    //ɸѡ�Ƕ�
    int contour_selected(CvSeq* c);

};

#endif
