#ifndef __integration_H__
#define __integration_H__
#include<iostream>
#include<cmath>
#include"Matrix.h"
#include"linear.h"
//复合中点公式
double mid_point(double a,double b,double(*f)(double))
{
    return f((a+b)/2.0)*(b-a);
}
double re_mide_point(double a,double b,double h,double(*f)(double))
{
    double ans=0;
    int n=(b-a)/h;
    for(int i=0;i!=n;i++)
    {
        ans+=mid_point(a+i*h,a+(i+1)*h,f);
    }
    return ans;
}
//复合梯形公式
double trapezoid(double a,double b,double(*f)(double))
{
    return (f(a)+f(b))/2.0*(b-a);
}
double re_trapezoid(double a,double b,double h,double(*f)(double))
{
    double ans=0;
    int n=(b-a)/h;
    for(int i=0;i!=n;i++)
    {
        ans+=trapezoid(a+i*h,a+(i+1)*h,f);
    }
    return ans;
}
//复合simposon
double simposon(double a,double b,double(*f)(double))
{
    return 1/6.0*(b-a)*(f(a)+4*f((a+b)/2.0)+f(b));
}
double re_simposon(double a,double b,double h,double(*f)(double))
{
    double ans=0;
    int n=(b-a)/h;
    for(int i=0;i!=n;i++)
    {
        ans+=simposon(a+i*h,a+(i+1)*h,f);
    }
    return ans;
}
//romberg
double romberg(double a,double b,double h0,double(*f)(double),double err)
{
    int k=1;
    double T0=0,T1=1;
    while(std::abs(T1-T0)>err&&k++)
    {
        T0=re_trapezoid(a,b,h0,f);
        h0/=2;
        double tmp0=re_trapezoid(a,b,h0,f);
        T1=(tmp0-std::pow(0.25,k)*T0)/(1-std::pow(0.25,k));
        

    }
    return T1;
}
//自适应方法
double auto_fit(double a,double b,int n0,double(*f)(double),double err)
{
    double h0=(b-a)/double(n0);
    double T0,T1;
    int k=1;
    while(std::abs(T1-3.1415926)>err&&k++)
    {

        T1=T0+re_mide_point(a,b,h0,f);
        h0=h0/2;
    }
    return T1;
}
//二重积分的simposon公式
double 2_simposon(double a,double b,double c,double d,double(*f)(double double))
{

}
/*广义积分的数值求法*/
//Gauss_Chebyshev
//Gauss_Laguerre
//Gauss_Hermit
#endif// __integration_H__
