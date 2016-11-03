#ifndef __TICK_TIMER_H__
#define __TICK_TIMER_H__

#include "stdafx.h"
#include <time.h>

class MyTimer
{
public:
    MyTimer();
    ~MyTimer();
private:
    clock_t m_ckBegin;
    clock_t m_ckEnd;
};

#endif // !__TICK_TIMER_H__
