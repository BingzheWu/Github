#ifndef __ode_solve__
#define __ode_solve__
#include<iostream>
#include<cmath>
#include<vector>
#include"Vector.h"
class ode_solve
{
    double xInitial;//自变量初始值
    Vector yInitial;//函数初始值
    double xEnd;//结束时自变量取值
    Vector (*sfn)(double x,const Vector& y);//源函数
    public:
        ode_solve(double x0,const Vector y0,double x1,Vector(*f)(double x,const Vector& y))
        {
            xInitial=x0;
            yInitial=y0;
            xEnd=x1;
            sfn=f;
         }
        std::vector<Vector> RK4(int );
        std::vector<Vector> Euler(int );
        std::vector<Vector> ImproveEuler(int );
        std::vector<Vector> Kutta3(int );
 };
std::vector<Vector> ode_solve::Euler(int n){
    int m=yInitial.size();
    double dx=(xEnd-xInitial)/double(n);
    std::vector<Vector> y ;
    y.resize(n+1);
    y[0].resize(m);
    y[0]=yInitial;
    for(int k=0;k<n;k++){
        double xTemp=xInitial+k*dx;
        y[k+1].resize(m);
        y[k+1]=y[k]+dx*sfn(xTemp,y[k]);
    }
    return y;
    
}
std::vector<Vector> ode_solve::ImproveEuler(int n){
    int m=yInitial.size();
    double dx=(xEnd-xInitial)/double(n);
    std::vector<Vector> y ;
    y.resize(n+1);
    y[0].resize(m);
    y[0]=yInitial;
    for(int k=0;k<n;k++){
        double xTemp=xInitial+k*dx;
        Vector K1(m,0),K2(m,0);
        y[k+1].resize(m);
        K1=sfn(xTemp,y[k]);
        K2=sfn(xTemp+dx,y[k]+dx*K1);
        y[k+1]=y[k]+dx/2.0*(K1+K2);
    }
    return y;
}
std::vector<Vector> ode_solve::RK4(int n)
{
    int m=yInitial.size();
    double dx=(xEnd-xInitial)/double(n);
    std::vector<Vector> y ;
    y.resize(n+1);
    y[0].resize(m);
    y[0]=yInitial;
    for(int k=0;k<n;k++)
    {
        double tp=xInitial+dx*k;
        Vector K1(m,0.0),K2(m,0.0),K3(m,0.0),K4(m,0.0);
        y[k+1].resize(m);
        K1=sfn(tp,y[k]);
        K2=sfn(tp+dx/2.0,y[k]+dx/2.0*K1);
        K3=sfn(tp+dx/2.0,y[k]+dx/2.0*K2);
        K4=sfn(tp+dx/2.0,y[k]+dx*K3);
        y[k+1]=y[k]+dx/6.0*(K1+2*K2+2*K3+K4);
    }
    return y;
}
#endif






