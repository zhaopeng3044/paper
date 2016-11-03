#include "stdafx.h"
#include "train.h"
#include <fstream>
#include "cv.h"
#include "mySvm.h"
#include "highgui.h"
using namespace cv;
using namespace std;

const int WHAT_NUM = 9 * 1764; // 9 * 3528;
void svmTrain(string &posPath, string &posFile, int posNum, string &negPath, string &negFile, int negNum, string &savePathAndName)
{
    int totalFileNum = posNum + negNum;
    CvMat *sampleFeaturesMat = cvCreateMat(totalFileNum , WHAT_NUM, CV_32FC1);
    //64*128的训练样本，该矩阵将是totalSample*3780,64*64的训练样本，该矩阵将是totalSample*1764
    cvSetZero(sampleFeaturesMat);
    CvMat *sampleLabelMat = cvCreateMat(totalFileNum, 1, CV_32FC1);//样本标识
    cvSetZero(sampleLabelMat);
    string curFilename, tmp;
    ifstream finPos(posFile.c_str());
    int i = 0;

    while(finPos >> tmp)
    {
        curFilename = posPath + string("/") + tmp;
        IplImage* tmpImage = cvLoadImage(curFilename.c_str());
        //Mat image = imread(curFilename.c_str());
        Mat image(tmpImage);
        cvReleaseImage(&tmpImage);


        if(NULL == image.data)
        {
            continue;
        }

        HOGDescriptor hog(Size(64, 64), Size(16, 16), Size(8, 8), Size(8, 8), 9);
        vector<float> featureVec;
        hog.compute(image, featureVec, cv::Size(8, 8), Size(0, 0));
        int featureVecSize = featureVec.size();

        for(int j = 0; j < featureVecSize; j++)
        {
            CV_MAT_ELEM(*sampleFeaturesMat, float, i, j) = featureVec[j];
        }

        sampleLabelMat->data.fl[i++] = 1;
    }

    finPos.close();
    //训练负样本
    ifstream finNeg(negFile.c_str());
    i = 0;

    while(finNeg >> tmp)
    {
        curFilename = negPath + string("/") + tmp;
        IplImage* tmpImage = cvLoadImage(curFilename.c_str());
        Mat image(tmpImage);// = imread(curFilename);
        cvReleaseImage(&tmpImage);

        if(NULL == image.data)
            continue;

        cv::HOGDescriptor hog(cv::Size(64, 64), cv::Size(16, 16), cv::Size(8, 8), cv::Size(8, 8), 9);
        vector<float> featureVec;
        hog.compute(image, featureVec, cv::Size(8, 8), Size(0, 0)); //计算HOG特征
        int featureVecSize = featureVec.size();

        for(int j = 0; j < featureVecSize; j ++)
        {
            CV_MAT_ELEM(*sampleFeaturesMat, float, i + posNum, j) = featureVec[ j ];
        }

        sampleLabelMat->data.fl[ i + posNum ] = -1;
        i++;
    }

    CvSVMParams params;
    params.svm_type = CvSVM::C_SVC;
    params.kernel_type = CvSVM::LINEAR;
    params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 1000, FLT_EPSILON);
    params.C = 0.01;
    MySvm svm;
    svm.train(sampleFeaturesMat, sampleLabelMat, NULL, NULL, params);   //用SVM线性分类器训练
    svm.save(savePathAndName.c_str());
    cvReleaseMat(&sampleFeaturesMat);
    cvReleaseMat(&sampleLabelMat);
    int supportVectorSize = svm.get_support_vector_count();
    CvMat *sv, *alp, *re; //所有样本特征向量
    sv  = cvCreateMat(supportVectorSize , WHAT_NUM, CV_32FC1);
    alp = cvCreateMat(1 , supportVectorSize, CV_32FC1);
    re  = cvCreateMat(1 , WHAT_NUM, CV_32FC1);
    CvMat *res  = cvCreateMat(1 , 1, CV_32FC1);
    cvSetZero(sv);
    cvSetZero(re);

    for(int i = 0; i < supportVectorSize; i++)
    {
        memcpy((float*)(sv->data.fl + i * WHAT_NUM), svm.get_support_vector(i), WHAT_NUM * sizeof(float));
    }

    double* alphaArr = svm.get_alpha();
    int alphaCount = svm.get_alpha_count();

    for(int i = 0; i < supportVectorSize; i++)
    {
        alp->data.fl[i] = alphaArr[i];
    }

    cvMatMul(alp, sv, re);
    int posCount = 0;

    for(int i = 0; i < WHAT_NUM; i++)
    {
        re->data.fl[i] *= -1;
    }

    ofstream fout("whateResult.txt");

    for(int i = 0; i < WHAT_NUM; i++)
    {
        //fprintf(fp, "%f \n", re->data.fl[i]);
        fout << re->data.fl[i] << endl;
    }

    float rho = svm.get_rho();
    //fprintf(fp, "%f", rho);
    fout << rho;
    //cout << "c:/hogSVMDetector.txt 保存完毕" << endl; //保存HOG能识别的分类器
    fout.close();
}

