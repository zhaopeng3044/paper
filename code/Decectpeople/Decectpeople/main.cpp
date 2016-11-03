// Decectpeople.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "function.h"
#include "sortPic.h"
#include "train.h"
#include "highgui.h"
#include "detect.h"
#include "ticktimer.h"
using namespace cv;

int _tmain(int argc, _TCHAR* argv[])
{
    //testimageMouseSelection();
    /*char *windowName = "µ±Ç°Í¼Æ¬";
    char *picPath = "J:/PersonBase/images";
    char *fieListName = "posFileList.txt";
    SortPic sp(windowName, picPath, fieListName);
    sp.processSort();*/
    //void svmTrain(string &posPath, string posFile, int posNum, string &negPath, string &negFile, int negNum, string savePathAndName)
    /*{
    //ÑµÁ·
    string posPath = "pos";
    string posFile = "posList.txt";
    int posNum = 465;
    string negPath = "neg";
    string negFile = "negList.txt";
    int negNum = 997;
    string savepath = "result1.txt";
    svmTrain(posPath, posFile, posNum, negPath, negFile, negNum, savepath);
    }*/
    {
        //¼ì²â
        //IplImage *psrc = cvLoadImage("M:
        // PersonBase / INRIAPerson / Test / pos / crop_000001.png");
        //   IplImage *psrc = cvLoadImage("pos / crop_000001_1.png");
        // detectPeople(psrc, string("whateResult.txt"));
    }
    testOpencvHog("C:/Users/user/Desktop/20161015164917.png");
    getchar();
    return 0;
}

