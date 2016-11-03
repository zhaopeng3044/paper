#ifndef __PREFUNCTION_H__
#define __PREFUNCTION_H__

#include "stdafx.h"
#include "cv.h"
#include "highgui.h"

#define MAX_CONTOURS 100;

typedef struct Set_Contours//�������ͣ���¼���������ı��
{
    int num ;
    int contours[8];
    CvRect rect;

    Set_Contours();

} Set_Contours;

typedef struct Pair_Set_Contours //�������ϵ����
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

typedef struct Rois //��϶Գ���ĺ�ѡ��
{
    Pair_Set_Contours* pairs_set_contours[100];
    int pairs_set_contours_num;
    Rois();
} Rois;

typedef struct Rois1 //ͶƱ��ĵĺ�ѡ
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

//�������ο�ϲ�
CvRect union_2rect(CvRect cr1, CvRect cr2);

//���������ο�ϲ�����union_2rect���������ڸ߶ȵ�ѡ����
CvRect set_union_2rect(CvRect cr1, CvRect cr2);

//�������ο�x�����ཻ�ж� c1.x <= c2.x ��Ϊ�Ѿ��ź��� ֮�ж�X�����н��� û�п���Y
int x_rect_intersect(CvSeq* c1, CvSeq* c2);

//��������y�����С�ж�
int y_rect_cmp(CvSeq* c1, CvSeq* c2);

//��������Թ��򣺸߶� �ײ�  �غ�
//�ж�����������Y����ʱ�����غϣ��غϷ���1 ���غϷ���0
int pair_determinant(CvRect cr1, CvRect cr2);

//������������Թ���
//����������>=2�����������ο�ܸ�
int second_pair_determinant(int i, Edges* edges);

//һ����������һ����Ե��������������>=3,���ο�ܸ�,��һ�����
int single_pair_determinant(int i, Edges* edges);

//�����������
void set_contours_pair(Edges* edges, Rois* rois);

//ͶƱ��Գ������ᣬ����ȣ���С���
void getAxesbyVote(IplImage* contour_img, int maxw, int minw, Axes* axes);

//��ȡ�ָ����򣬶��ҵ����������밶����ɢ�������y�������������
void getRois1(IplImage* src, Axes* axes, Contours* roi_contours, Edges* edges, Rois1* rois1, int wmax, int wmin);

void output_pairs_set_contours2(IplImage* frame, Rois* rois);

#endif
