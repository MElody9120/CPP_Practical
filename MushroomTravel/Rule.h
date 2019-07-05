#pragma once
#include<graphics.h>
#include<math.h>
#include"mydefine.h"
#include"Scene.h"
class rule
{
public:
	rule(void);
	~rule(void);
	static double move(double &v, double t, double a);
};
rule::rule(void)
{
}
rule::~rule(void)
{
}
double rule::move(double &v, double t, double a) //运动规则
{
	double H = 0;
	H = v * t + 1.0 / 2.0*a*pow(t, 2);
	v = v + a * t;
	return H;
}
