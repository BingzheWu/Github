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
double romberg(double a,double b,double& h0,double(*f)(double),double err,int& k)
{
    k=1;
    double T0=0,T1=1;
    T0=re_trapezoid(a,b,h0,f);
    while(std::abs(T1-T0)>err&&k++)
    {
        h0/=2.0;
        double tmp0=re_trapezoid(a,b,h0,f);
        T1=(tmp0-std::pow(0.25,k)*T0)/(1-std::pow(0.25,k));
        T0=T1;
        

    }
    
    return T1;
}
//自适应方法
double auto_fit(double a,double b,int& n0,double(*f)(double),double err,int& k)
{
    long double h0=(b-a)/double(n0);
    double T0,T1;
    k=1;
    while(std::abs(T1-T0)>err&&k++)
    {
        h0=double(b-a)/n0;
        T1=T0+re_mide_point(a,b,h0,f);
        n0=2*n0;
        T0=T1;
    }
    return T1;
}
//二重积分的simposon公式
double double_simposon(double a,double b,double c,double d,double x0,double y0,double(*f)(double,double,double,double))
{
    double temp=(d-c)*(b-a)/36.0;
    double tmp1=f(x0,a,y0,c)+4*f(x0,(a+b)/2.0,y0,c)+f(x0,b,y0,c)+4*f(x0,a,y0,(c+d)/2.0)+16*f(x0,(a+b)/2.0,y0,(c+d)/2.0)+4*f(x0,b,y0,(c+d)/2.0)+f(x0,a,y0,d)+4*f(x0,(a+b)/2.0,y0,d)+f(x0,b,y0,d);
    return temp*tmp1;
}
double CdoubleSimposon(double a,double b,double c,double d,double x0,double y0,double(*f)(double,double ,double,double),double h){
    int n=(b-a)/h;
    double ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            double tmp1=a+i*h;double tmp2=c+i*h;
            ans+=double_simposon(tmp1,tmp1+h,tmp2,tmp2+h,x0,y0,f);
            
        }
    }
    return ans;

}
/*广义积分的数值求法*/
//Gauss_Chebyshev
//Gauss_Laguerre
//Gauss_Hermit
#endif// __integration_H__
