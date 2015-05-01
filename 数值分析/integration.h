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
double romberg(double a,double b,double h0,double(*f)(double),int step){
    if(step==1){return re_trapezoid(a,b,h0,f);}
    else{
        return ((romberg(a,b,h0/2,f,step - 1) -std::pow(4,-(step-1)) * romberg(a,b,h0,f,step-1)) / (1 - std::pow(4, -(step-1))) );
    }
}
double Romberg(double a,double b,double h0,double(*f)(double),double err,int& k){
    while(++k){
        if(std::abs(romberg(a,b,h0,f,k)-romberg(a,b,h0,f,k-1))<err){
        return romberg(a,b,h0,f,k);
        break;
        }
    }
}
//自适应方法
double auto_fit(double a,double b,int& n0,double(*f)(double),double err,int& k)
{
     double h0=(b-a)/double(n0);
    double T0,T1;
    k=1;
    T1=3;
    T0=re_trapezoid(a,b,h0,f);
    while(k++)
    {
        h0=double(b-a)/n0;
        double tmp=T1;
        T1=0.5*T0+0.5*re_mide_point(a,b,h0,f);
        n0=2*n0;
        if(std::abs(T1-T0)<err){break;}

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
double infSimpson( double err,long int maxNum, double(*f)( double)){
     int k0=0;
     double T0=0,T1=1;
     while(std::abs(T0-T1)>err&&k0++<maxNum){
        T0=T1;
        double a=std::pow(10.0,-k0); double b=std::pow(10.0,k0);
        double h=(b-a)/1000.0;
        T1=re_simposon(a,b,h,f);
     }
     return T1;


}
double GaussLaguerre(double(*f)(double)){
    double temp=(2+std::sqrt(2))/4.0;
    return temp*f(2-std::sqrt(2))+(1-temp)*f(2+std::sqrt(2));
}
double GaussLaguerre3(double(*f)(double)){
    return 0.711093*f(0.415755)+0.278518*f(2.29428)+0.0103893*f(6.28995);
}
double GaussLaguerre4(double(*f)(double)){
    return 0.6031541043*f(0.3225476896)+0.3574186924*f(1.7457611012)+0.0388879085*f(4.5366202969)+0.0005392947*f(9.3950709123);
}
double GaussLaguerre5(double(*f)(double)){
    return 0.5217556106*f(0.2635603197)+0.3986668111*f(1.41340305091)+0.0759424497*f(3.596425771)+0.0036117587*f(7.0858100059)+0.000023370*f(12.640800844);
}
//Gauss_Chebyshev
//Gauss_Laguerre
//Gauss_Hermit
#endif// __integration_H__
