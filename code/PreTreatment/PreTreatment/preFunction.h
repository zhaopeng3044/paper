#ifndef __PREFUNCTION_H__
#define __PREFUNCTION_H__

#include "stdafx.h"
#include "cv.h"
#include "highgui.h"

#define MAX_CONTOURS 100;

typedef struct Set_Contours//轮廓集和，记录的是轮廓的编号
{
    int num ;
    int contours[8];
    CvRect rect;

    Set_Contours();

} Set_Contours;

typedef struct Pair_Set_Contours //轮廓集合的配对
{
    Set_Contours* first;
    Set_Contours* second;
    CvRect rect;
    int m;
    int n;
    Pair_Set_Contours();
} Pair_Set_Contours;

typedef struct Edges
{
    Set_Contours* set_contours_ylinked[300];
    int set_contours_num;
    Edges();
} Edges;

typedef struct Rois //拟合对称求的候选区
{
    Pair_Set_Contours* pairs_set_contours[100];
    int pairs_set_contours_num;
    Rois();
} Rois;

typedef struct Rois1 //投票求的的候选
{
    CvRect cr[6];
    int count;
    Rois1();
} Rois1;

typedef struct Contours
{
    CvSeq* contours[500];
    int count;
    Contours();
} Contours;

typedef struct Axes
{
    int elms[20];
    int count;
    Axes();
} Axes;
void roi_contours_x_sort(Contours* roi_contours);
void y_linked_contours(Contours* roi_contours, Edges* edges);

//轮廓矩形框合并
CvRect union_2rect(CvRect cr1, CvRect cr2);

//轮廓集矩形框合并，比union_2rect方法区别在高度的选择上
CvRect set_union_2rect(CvRect cr1, CvRect cr2);

//轮廓矩形框x方向相交判定 c1.x <= c2.x 因为已经排好序 之判断X方向有交集 没有考虑Y
int x_rect_intersect(CvSeq* c1, CvSeq* c2);

//轮廓举行y方向大小判定
int y_rect_cmp(CvSeq* c1, CvSeq* c2);

//轮廓集配对规则：高度 底部  重合
//判断两个矩形在Y方向时候有重合，重合返回1 不重合返回0
int pair_determinant(CvRect cr1, CvRect cr2);

//轮廓集二次配对规则
//轮廓集合有>=2个轮廓，矩形框很高
int second_pair_determinant(int i, Edges* edges);

//一个轮廓集是一个配对的情况规则：轮廓数>=3,矩形框很高,有一定宽度
int single_pair_determinant(int i, Edges* edges);

//轮廓集的配对
void set_contours_pair(Edges* edges, Rois* rois);

//投票求对称中心轴，最大宽度，最小宽度
void getAxesbyVote(IplImage* contour_img, int maxw, int minw, Axes* axes);

//获取分割区域，对找到的中心轴离岸边扩散找最近的y方向拟合轮廓集
void getRois1(IplImage* src, Axes* axes, Contours* roi_contours, Edges* edges, Rois1* rois1, int wmax, int wmin);

void output_pairs_set_contours2(IplImage* frame, Rois* rois);

#endif
