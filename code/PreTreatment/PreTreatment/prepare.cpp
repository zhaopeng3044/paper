#include "stdafx.h"
#include "prePare.h"

IplImage* Prepare::getEdges(IplImage *pOri, int erodes, int dilates)
{
    IplImage* src ;
    IplImage* src_gray = cvCreateImage(cvGetSize(pOri), 8, 1);
    cvCvtColor(pOri, src_gray, CV_BGR2GRAY);
    src = src_gray;
    IplConvKernel* element = cvCreateStructuringElementEx(4, 4, 1, 1, CV_SHAPE_RECT, 0);
    cvDilate(src, src, element, dilates);  // 先闭运算
    cvErode(src, src, element, erodes);
    cvErode(src, src, element, erodes); // 然后开运算
    cvDilate(src, src, element, dilates);
    cvSmooth(src, src, CV_MEDIAN, 3, 3);  // 中值滤波
    cvCanny(src, src, 50, 150);
    ss_filter(src);
    return src;
}

void Prepare::ss_filter(IplImage* img)
{
    CvMat cm ;
    float val[] = {2, 0, -2, 3 , 0, -3, 2, 0 , -2 };
    cvInitMatHeader(&cm, 3, 3, CV_32FC1, val);
    cvFilter2D(img, img, &cm);
}

IplImage* Prepare::getInterestCours(IplImage* pOri, Contours* roi_contours)
{
    CvSeq* first_contour = NULL;
    CvMemStorage* storage = cvCreateMemStorage(0);
    IplImage* src_edge = getEdges(pOri); // 先腐蚀，再增强，然后边缘增强（canny）,最后利用线性滤波加强Y方向轮廓
    IplImage* src_marked = cvCreateImage(cvGetSize(src_edge), 8, 3);
    int count = cvFindContours(src_edge, storage, &first_contour, sizeof(CvContour), CV_RETR_LIST);

    int n = 0;
    cvCvtColor(src_edge, src_marked, CV_GRAY2BGR);

    for(CvSeq* c = first_contour; c != NULL; c = c->h_next)
    {
        if(!contour_selected(c))continue;

        cvDrawContours(src_marked, c, cvScalar(0, 0, 255), cvScalar(255, 0, 0), 0, 2, 8);
        cvWaitKey(0);

        /*for(int i = 0 ; i < c->total; ++i)
        {
            CvPoint* p = CV_GET_SEQ_ELEM(CvPoint, c, i);
        }*/

        n++;
        roi_contours->contours[roi_contours->count] = c;
        roi_contours->count++;
    }

    return src_marked;
}


//轮廓极左点
CvPoint* Prepare::left_point_contour(CvSeq* cs)
{
    int pos = 0;
    int x_min = 10000;

    for(int i = 0 ; i < cs->total; ++i)
    {
        CvPoint* p = CV_GET_SEQ_ELEM(CvPoint, cs, i);

        if(p->x < x_min)
        {
            x_min = p->x;
            pos = i;
        }
    }

    return CV_GET_SEQ_ELEM(CvPoint, cs, pos);
}
//轮廓极右点
CvPoint* Prepare::right_point_contour(CvSeq* cs)
{
    int pos = 0;
    int x_max = -1;

    for(int i = 0 ; i < cs->total; ++i)
    {
        CvPoint* p = CV_GET_SEQ_ELEM(CvPoint, cs, i);

        if(p->x > x_max)
        {
            x_max = p->x;
            pos = i;
        }
    }

    return CV_GET_SEQ_ELEM(CvPoint, cs, pos);
}
//轮廓最下点
CvPoint* Prepare::bottom_point_contour(CvSeq* cs)
{
    int pos = 0;
    int y_max = -1;

    for(int i = 0 ; i < cs->total; ++i)
    {
        CvPoint* p = CV_GET_SEQ_ELEM(CvPoint, cs, i);

        if(p->y > y_max)
        {
            y_max = p->y;
            pos = i;
        }
    }

    return CV_GET_SEQ_ELEM(CvPoint, cs, pos);
}
//轮廓最上点
CvPoint* Prepare::up_point_contour(CvSeq* cs)
{
    int pos = 0;
    int y_min = 1000;

    for(int i = 0 ; i < cs->total; ++i)
    {
        CvPoint* p = CV_GET_SEQ_ELEM(CvPoint, cs, i);

        if(p->y < y_min)
        {
            y_min = p->y;
            pos = i;
        }
    }

    return CV_GET_SEQ_ELEM(CvPoint, cs, pos);
}

int Prepare:: contour_selected(CvSeq* c)
{
    double tan = 10;

    if(bottom_point_contour(c)->x != up_point_contour(c)->x)
        tan = abs(bottom_point_contour(c)->y - up_point_contour(c)->y) / abs(bottom_point_contour(c)->x - up_point_contour(c)->x);

    if(abs(bottom_point_contour(c)->y - up_point_contour(c)->y) > 30 && tan > 2)
        return 1;

    return 0;
}

void Prepare::roiDetect(IplImage* psrc)
{
    Contours roi_contours;
    Edges edges;
    Rois rois;

    getInterestCours(psrc, &roi_contours);
    y_linked_contours(&roi_contours, &edges);
    set_contours_pair(&edges, &rois);
    output_pairs_set_contours2(psrc, &rois);
}