#include "stdafx.h"
#include "sortPic.h"
#include "function.h"
#include <fstream>
#include "cv.h"
#include "highgui.h"
#include <math.h>
#include <algorithm>

using namespace std;
using namespace cv;
const int MAX_FILE_NAME_LENGTH = 100;

SortPic::SortPic(const char *windowName, const char* path, const char* fileListName, int width, int height)
{
    this->m_strWindowName = string(windowName);
    this->m_strPath = string(path);
    this->m_strFileList = string(fileListName);
    m_nTarHei = height;
    m_ntarWidth = width;
    m_hEvent = ::CreateEvent(NULL, false, false, NULL);
    m_strSortedFile = "sortedList.txt";
}

void SortPic::initEnv()
{
    ifstream fin(m_strSortedFile.c_str());
    string tmp;

    while(fin >> tmp)
    {
        m_vecSortList.push_back(tmp);
    }

    fin.close();
}


void on_mouseAgent(int event, int x, int y, int flags, void *param)
{
    SortPic *p = (SortPic*)param;
    p->onMouseEvent(event, x, y);
}
template<class type>
bool isSorted(vector<type> vec, type &value)
{
    vector<type>::iterator it;
    it = find(vec.begin(), vec.end(), value);
    return it != vec.end();
}
void getDesFileName(string const & srcName, string & dstname, int index)
{
    char strIndex[4];
    sprintf(strIndex, "_%d", index);
    int i = srcName.find_last_of('.');
    dstname += srcName.substr(0, i) + string(strIndex) + srcName.substr(i, srcName.length() - 1);
}
void SortPic::processSort()
{
    initEnv();
    ofstream sortOut(m_strSortedFile.c_str(), ios::app);
    ifstream fin(m_strFileList.c_str());
    char tmpFileName[MAX_FILE_NAME_LENGTH + 1];
    cvNamedWindow(m_strWindowName.c_str(), 1);

    cvSetMouseCallback(m_strWindowName.c_str(), on_mouseAgent, this);
    int couNum = 0;

    while(fin.getline(tmpFileName, 101))
    {
        m_strCurName = string(tmpFileName);
        couNum++;

        if(isSorted(m_vecSortList, m_strCurName))
        {
            continue;
        }

        m_nCounter = 0;
        m_strFilePath = m_strPath + "/" + string(tmpFileName);
        printf("current pic name %s\n", m_strFilePath.c_str());
        m_psrcImg = cvLoadImage(m_strFilePath.c_str(), CV_LOAD_IMAGE_UNCHANGED);
        m_ptmpImg = cvCloneImage(m_psrcImg);
        cvShowImage(m_strWindowName.c_str(), m_ptmpImg);
//       cvSetMouseCallback(m_strWindowName.c_str(), on_mouseAgent, this);

        int c =  cvWaitKey(-1);

        if(c >= 'A' && c <= 'Z')
            c += 'a' - 'A';

        switch(c)
        {
            case ' ':
            case 'n':
                {
                    //重置事件
                    SetEvent(m_hEvent);
                    break;
                }
        }

        //等待标记完才继续
        ::WaitForSingleObject(m_hEvent, INFINITE);
        cvReleaseImage(&m_ptmpImg);
        cvReleaseImage(&m_psrcImg);
        sortOut << m_strCurName << endl;
    }

    fin.close();
    sortOut.close();
    printf("all pic sorted done\n");
    cvDestroyWindow(m_strWindowName.c_str());
}
void SortPic::onMouseEvent(int event, int x, int y)
{
    static bool isBegin = false;

    switch(event)
    {
        case CV_EVENT_LBUTTONDOWN:
            {
                isBegin = true;
                m_pointBegin.x = x;
                m_pointBegin.y = y;
                break;
            }

        case CV_EVENT_MOUSEMOVE:
            {
                if(isBegin)
                {
                    m_ptmpImg = cvCloneImage(m_psrcImg);
                    Mat tmpMat(m_ptmpImg);
                    rectangle(tmpMat, m_pointBegin, cvPoint(x, y), cvScalar(0, 0, 255));
                    cvShowImage(m_strWindowName.c_str(), m_ptmpImg);
                    //cvWaitKey(5);
                    cvReleaseImage(&m_ptmpImg);
                }

                break;
            }

        case CV_EVENT_LBUTTONUP:
            {
                m_nCounter++;
                m_pDstImg = imageMouseSelection(m_psrcImg, m_pointBegin.x, m_pointBegin.y, abs(x - m_pointBegin.x), abs(y - m_pointBegin.y), m_ntarWidth, m_nTarHei);
                string destName = "pos/";
                getDesFileName(m_strCurName, destName, m_nCounter);
                cvSaveImage(destName.c_str(), m_pDstImg);
                cvReleaseImage(&m_pDstImg);
                isBegin = false;
                //重置事件
                SetEvent(m_hEvent);
                break;
            }
    }
}
SortPic::~SortPic()
{
}