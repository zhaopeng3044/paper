#ifndef __MYSVM_H__
#define __MYSVM_H__

#include "stdafx.h"
#include "cv.h"
#include "ml.h"

class MySvm: public CvSVM
{
public:
	int get_alpha_count()
	{
		return this->sv_total;
	}

	int get_sv_dim()
	{
		return this->var_all;
	}

	int get_sv_count()
	{
		return this->decision_func->sv_count;
	}

	double* get_alpha()
	{
		return this->decision_func->alpha;
	}

	float** get_sv()
	{
		return this->sv;
	}

	float get_rho()
	{
		return this->decision_func->rho;
	}
};
#endif