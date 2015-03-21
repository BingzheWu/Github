#include<iostream>
#include<cmath>
#include"extract_root.h"
double f(double x)
{
    return double(std::pow(x,6)-x-1);
}
double df(double x)
{
    return double(6*std::pow(x,5)-1);
}
int main()
{
    double eps=std::pow(0.1,9);
    double x0=2;
    int max=10000;
    std::cout<<newton_solve(x0,max,eps,f,df)<<std::endl;
    return 0;
    
}
