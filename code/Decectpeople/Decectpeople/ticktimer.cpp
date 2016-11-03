#include "stdafx.h"
#include "ticktimer.h"
#include <iostream>

MyTimer::MyTimer()
{
    m_ckBegin = clock();
}

MyTimer::~MyTimer()
{
    m_ckEnd = clock();
    std::cout << "passed " << (double)((m_ckEnd - m_ckBegin) / CLOCKS_PER_SEC) << " seconds" << std::endl;
}