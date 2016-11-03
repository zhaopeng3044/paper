#include "stdafx.h"
#include "preFunction.h"

Set_Contours::Set_Contours()
{
    this->num = 0;

    for(int i = 0; i < 8; i++)
    {
        this->contours[i]  = -1;
    }
}

Pair_Set_Contours::Pair_Set_Contours()
{
    m = -1;
    n = -1;
    first = second = NULL;
}

Edges::Edges()
{
    this->set_contours_num = 0;
}

Rois::Rois()
{
    this->pairs_set_contours_num = 0;
}


Rois1::Rois1()
{
    this->count = 0;

}


Contours::Contours()
{
    this->count = 0;
}

Axes::Axes()
{
    this->count = 0;
}

void roi_contours_x_sort(Contours* roi_contours)
{
    {
        for(int i = 1; i < roi_contours->count; i++)
        {
            for(int j = i - 1; j >= 0; j--)
            {
                if(cvBoundingRect(roi_contours->contours[j + 1]).x < cvBoundingRect(roi_contours->contours[j]).x)
                {
                    CvSeq* temp = roi_contours->contours[j + 1];
                    roi_contours->contours[j + 1] = roi_contours->contours[j];
                    roi_contours->contours[j] = temp;
                }
                else
                    break;
            }
        }
    }
}
void y_linked_contours(Contours* roi_contours, Edges* edges)
{
    CvPoint* pp;
    //int pos = -1;
    Set_Contours* sc = 0;
    int n = roi_contours->count - 1;
    CvRect cr1 ;
    CvRect cr2 ;

    for(int i = 0; i < n; i++)
    {
        if(x_rect_intersect(roi_contours->contours[i], roi_contours->contours[i + 1])) //�ཻ�����������κϲ���һ������
        {
            if(!sc) //���ϵĵ�һ��
            {
                sc = new Set_Contours();
                sc->contours[sc->num++] = i;
                sc->contours[sc->num++] = i + 1;
                cr1 = cvBoundingRect(roi_contours->contours[i]);
                cr2 = cvBoundingRect(roi_contours->contours[i + 1]);
                sc->rect = union_2rect(cr1, cr2);  //�ϲ���������
            }
            else //�����Ѵ���
            {
                sc->contours[sc->num++] = i + 1;
                sc->rect = union_2rect(sc->rect, cvBoundingRect(roi_contours->contours[i + 1]));

                if(i + 1 == n)
                {
                    edges->set_contours_ylinked[edges->set_contours_num++] = sc;
                    sc = 0;
                }
            }
        }
        else
        {
            if(!sc) //�ཻ����ֻ��һ����
            {
                printf("dddd\n");
                sc = new Set_Contours();
                sc->contours[sc->num++] = i;
                sc->rect = cvBoundingRect(roi_contours->contours[i]);
                edges->set_contours_ylinked[edges->set_contours_num++] = sc;
                sc = 0;
            }
            else //�ཻ�����ж����
            {
                edges->set_contours_ylinked[edges->set_contours_num++] = sc;
                sc = 0;
            }
        }

    }

    //���һ�������Ĵ���
    if(!x_rect_intersect(roi_contours->contours[roi_contours->count - 2], roi_contours->contours[roi_contours->count - 1]))
    {
        sc = new Set_Contours();
        sc->contours[sc->num++] = roi_contours->count - 1;
        sc->rect = cvBoundingRect(roi_contours->contours[roi_contours->count - 1]);
        edges->set_contours_ylinked[edges->set_contours_num++] = sc;
    }

}

//�������ο�ϲ�
CvRect union_2rect(CvRect cr1, CvRect cr2)
{
    CvRect cr;
    cr.x = cr1.x < cr2.x ? cr1.x : cr2.x;
    cr.y = cr1.y < cr2.y ? cr1.y : cr2.y;
    CvPoint pp1 ;
    pp1.x = cr1.x + cr1.width > cr2.x + cr2.width ? cr1.x + cr1.width : cr2.x + cr2.width;
    pp1.y = cr1.y + cr1.height > cr2.y + cr2.height ? cr1.y + cr1.height : cr2.y + cr2.height;
    cr.width = pp1.x - cr.x;
    cr.height = pp1.y - cr.y;
    return cr;
}

//���������ο�ϲ�����union_2rect���������ڸ߶ȵ�ѡ����
CvRect set_union_2rect(CvRect cr1, CvRect cr2)
{
    CvRect cr;
    cr.x = cr1.x < cr2.x ? cr1.x : cr2.x;
    cr.y = (cr1.y + cr2.y) / 2;
    CvPoint pp1 ;
    pp1.x = cr1.x + cr1.width > cr2.x + cr2.width ? cr1.x + cr1.width : cr2.x + cr2.width;
    pp1.y = cr1.y + cr1.height > cr2.y + cr2.height ? cr1.y + cr1.height : cr2.y + cr2.height;
    cr.width = pp1.x - cr.x;
    cr.height = pp1.y - cr.y;
    return cr;
}

//�������ο�x�����ཻ�ж� c1.x <= c2.x ��Ϊ�Ѿ��ź��� ֮�ж�X�����н��� û�п���Y
int x_rect_intersect(CvSeq* c1, CvSeq* c2)
{
    CvRect cr1 = cvBoundingRect(c1);
    CvRect cr2 = cvBoundingRect(c2);

    if(cr1.x + cr1.width + 12 > cr2.x)
        return 1;

    return 0;
}

//��������y�����С�ж�
int y_rect_cmp(CvSeq* c1, CvSeq* c2)
{
    CvRect cr1 = cvBoundingRect(c1);
    CvRect cr2 = cvBoundingRect(c2);

    if(cr1.y < cr2.y)
        return 1;

    return 0;
}

//��������Թ��򣺸߶� �ײ�  �غ� �ж�����������Y����ʱ�����غϣ��غϷ���1 ���غϷ���0
int pair_determinant(CvRect cr1, CvRect cr2)
{
    CvRect left = cr1.x <= cr2.x ? cr1 : cr2;
    CvRect right = cr1.x > cr2.x ? cr1 : cr2;
    CvRect up = cr1.y <= cr2.y ? cr1 : cr2;
    CvRect down = cr1.y > cr2.y ? cr1 : cr2;
    int y_union = up.y + up.height > down.y + down.height ? down.height : up.y + up.height - down.y;

    if(left.x + left.width + 80 > right.x && y_union > 30 && abs(up.height - down.height) < 80 && abs(up.y + up.height - down.y - down.height) < 40)
        return 1;

    return 0;
}

//������������Թ���
//����������>=2�����������ο�ܸ�
int second_pair_determinant(int i, Edges* edges)
{
    if(edges->set_contours_ylinked[i]->num > 2 && edges->set_contours_ylinked[i]->rect.height > 150)
        return 1;

    return 0;
}

//һ����������һ����Ե��������������>=3,���ο�ܸ�,��һ�����
int single_pair_determinant(int i, Edges* edges)
{
    if(edges->set_contours_ylinked[i]->num >= 3 && edges->set_contours_ylinked[i]->rect.height > 100 && edges->set_contours_ylinked[i]->rect.width > 10)
        return 1;

    return 0;
}

//�����������
void set_contours_pair(Edges* edges, Rois* rois)
{
    Pair_Set_Contours* psc = NULL;
    int last_dealed = 0;

    for(int i = 0; i < edges->set_contours_num - 1; i ++)
    {
        if(pair_determinant(edges->set_contours_ylinked[i]->rect, edges->set_contours_ylinked[i + 1]->rect)) //��Գɹ�
        {
            psc = new Pair_Set_Contours;
            psc->first = edges->set_contours_ylinked[i];
            psc->second = edges->set_contours_ylinked[i + 1];
            psc->rect = union_2rect(edges->set_contours_ylinked[i]->rect, edges->set_contours_ylinked[i + 1]->rect);
            psc->m = i;
            psc->n = i + 1;
            rois->pairs_set_contours[rois->pairs_set_contours_num++] = psc;
            psc = 0;

            if(i + 1 == edges->set_contours_num - 1)
                last_dealed = 0;

            i++;
        }
        //������Ի��ᣬi��i+2
        else if(second_pair_determinant(i, edges) && i + 2 <= edges->set_contours_num - 1)
        {

            if(pair_determinant(edges->set_contours_ylinked[i]->rect, edges->set_contours_ylinked[i + 2]->rect)) //��Գɹ�
            {
                psc = new Pair_Set_Contours();
                psc->first = edges->set_contours_ylinked[i];
                psc->second = edges->set_contours_ylinked[i + 2];
                psc->rect = union_2rect(edges->set_contours_ylinked[i]->rect, edges->set_contours_ylinked[i + 2]->rect);
                psc->m = i;
                psc->n = i + 2;
                rois->pairs_set_contours[rois->pairs_set_contours_num++] = psc;
                psc = 0;

                if(i + 2 == edges->set_contours_num - 1)
                    last_dealed = 0;

                i++;
            }
        }
        else if(single_pair_determinant(i, edges)) //һ����������һ����Ե����
        {
            printf("һ����������һ����Ե������%d\n", i);
            psc = new Pair_Set_Contours();
            psc->first = edges->set_contours_ylinked[i];
            psc->second = edges->set_contours_ylinked[i];
            psc->rect = edges->set_contours_ylinked[i]->rect;
            psc->m = i;
            psc->n = i;
            rois->pairs_set_contours[rois->pairs_set_contours_num++] = psc;
            psc = 0;
        }

    }

    if(!last_dealed && single_pair_determinant(edges->set_contours_num - 1, edges)) //һ����������һ����Ե����,�������һ������ �����ظ�������
    {
        printf("�������һ������\n");
        psc = new Pair_Set_Contours();
        psc->first = edges->set_contours_ylinked[edges->set_contours_num - 1];
        psc->second = edges->set_contours_ylinked[edges->set_contours_num - 1];
        psc->rect = edges->set_contours_ylinked[edges->set_contours_num - 1]->rect;
        psc->m = edges->set_contours_num - 1;
        psc->n = edges->set_contours_num - 1;
        rois->pairs_set_contours[rois->pairs_set_contours_num++] = psc;
        psc = 0;
    }
}

//ͶƱ��Գ������ᣬ����ȣ���С���
void getAxesbyVote(IplImage* contour_img, int maxw, int minw, Axes* axes)
{
    uchar* uc1;
    int n = contour_img->width;
    int* votes = (int*)malloc(n * sizeof(int));
    int* sort_votes = (int*)malloc(contour_img->width * sizeof(int));
    IplImage* axes_img = cvCreateImage(cvGetSize(contour_img), 8, 3);
    cvCvtColor(contour_img, axes_img, CV_GRAY2BGR);

    for(int m = 0; m < n; m++)
    {
        sort_votes[m] = m;
        votes[m] = 0;
    }

    for(int r = 0; r < contour_img->height; r++)
    {
        for(int c = 0; c < contour_img->width; c++)
        {
            uc1 = (uchar*)contour_img->imageData + r * contour_img->widthStep + c;

            if(*uc1 != 255)continue;

            for(int dc = minw; dc <= maxw && c + dc < contour_img->width; dc++)
            {
                if(uc1[dc] == 255)
                {
                    votes[(2 * c + dc) / 2]++;
                }
            }
        }
    }

    int wx = 31;

    for(int i = wx / 2; i < n - wx / 2 - 1; i++) //�ϲ����ĶԳ���9
    {
        int max = 0, pos = -1;

        for(int j = -wx / 2; j < wx / 2; j++)
        {
            if(max <= votes[i + j])
            {
                max = votes[i + j];
                pos = i + j;;
            }
        }

        for(int q = -wx / 2; q < wx / 2; q++)
        {
            if(pos != i + q)
            {
                votes[i + q] = 0;
            }
        }
    }

    axes_img = cvLoadImage("d:\\Ped\\�ָ�\\1501.jpg", 1);

    for(int m = 0; m < n; m++)
    {
        if(votes[m] < 10)
            continue;

        cvLine(axes_img, cvPoint(m + 5, 0), cvPoint(m + 5, contour_img->height - 1), cvScalar(0, 0, 255));
    }

    for(int i = 1; i < n; i++)
    {
        for(int j = i - 1; j >= 0; j--)
        {
            if(votes[sort_votes[j + 1]] < votes[sort_votes[j]])
            {
                int temp = sort_votes[j + 1];
                sort_votes[j + 1] = sort_votes[j];
                sort_votes[j] = temp;
            }
            else
                break;
        }
    }

    for(int m = 0; m < 10; m++)
    {
        axes->elms[axes->count++] = sort_votes[n - m - 1];
    }

    cvNamedWindow("Axes", 1);
    cvShowImage("Axes", axes_img);
}

//��ȡ�ָ����򣬶��ҵ����������밶����ɢ�������y�������������
void getRois1(IplImage* src, Axes* axes, Contours* roi_contours, Edges* edges, Rois1* rois1, int wmax, int wmin)
{
    /*IplImage* img = cvCreateImage(cvSize(src->width, src->height), 8, 3);
    cvResize(src, img);
    IplImage* edge = getInterestContoursImg(img, roi_contours, edges);
    getAxesbyVote(edge, wmax, wmin, axes);
    rois1->count = axes->count;

    cvNamedWindow("ROIS1", 1);
    cvShowImage("ROIS1", src);*/
}

void output_pairs_set_contours2(IplImage* frame, Rois* rois)
{
    CvPoint cp1, cp2;
    IplImage* img = frame;
    IplImage* rect_img = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
    cvCopy(img, rect_img);
    //printf("��Լ�������%d\n", rois->pairs_set_contours_num);

    for(int i = 0; i < rois->pairs_set_contours_num; i ++)
    {
        //printf("--%d-%d--\n", rois->pairs_set_contours[i]->m, rois->pairs_set_contours[i]->n);
        cp1.x = rois->pairs_set_contours[i]->rect.x - 5;
        cp1.y = rois->pairs_set_contours[i]->rect.y - 10 < 1 ? 1 : rois->pairs_set_contours[i]->rect.y - 10;
        cp2.x = rois->pairs_set_contours[i]->rect.x + rois->pairs_set_contours[i]->rect.width + 30;
        cp2.y = rois->pairs_set_contours[i]->rect.y + rois->pairs_set_contours[i]->rect.height + 40;
        CvRect cr;
        cr.x = cp1.x;
        cr.y = cp1.y;
        cr.width = cp2.x - cp1.x;
        cr.height = cp2.y - cp1.y;
        //roi_cut(img,cr);
        cvRectangle(rect_img, cp1, cp2, cvScalar(0, 0, 255), 2);
    }

    cvNamedWindow("Rois", 1);
    cvShowImage("Rois", rect_img);
    //return rect_img;
}