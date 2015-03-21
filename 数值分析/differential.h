#ifndef __differential_H__
#define __differential_H__
#include<iostream>
#include<cmath>
#include"Matrix.h"
#include"linear.h"
//向前差分格式
double Foward_dy(double x,double h,double(*f)(double))
{
    return (f(x+h)-f(x))/h;
}
//中心差分格式
double Center_dy(double x,double h,double(*f)(double))
{
    return (f(x+h)-f(x-h))/(2*h);
}

//三步
double tri_dy(double x,double h,double(*f)(double))
{
    return (f(x-2*h)-8*f(x-h)+8*f(x+h)-f(x+2*h))/(12*h);
}
//二阶中心差分格式
std::vector<double> Center_2_dy(std::vector<double> X,int n,double(*f)(double),double df0,double dfn,double h)
{
    std::vector<double> ans(n);
    ans[0]=df0;ans[n-1]=dfn;
    for(int i=1;i!=n-1;i++)
    {
        ans[i]=(f(X[i+1])-f(X[i-1]))/(2*h);
    }
    return ans;
}
//隐式格式
std::vector<double> implicit (std::vector<double> X,int n,double(*f)(double),double df0,double dfn,double h)
{
    std::vector<double> a(n),b(n),c(n),ans(n);Matrix z(n,1);
    for(int i=0;i!=n-1;i++){c[i+1]=1;a[i]=4;b[i]=1;}
    for(int i=1;i!=n-1;i++){z[i][0]=3*(f(X[i+1])-f(X[i-1]))/h;z[0][0]=df0;z[n-1][0]=dfn;}
    a[0]=1;c[1]=0;b[n-2]=0;
    tridiagonal(n,a,b,c,z,ans);
    return ans;
    
}
#endif//__differential_H__
