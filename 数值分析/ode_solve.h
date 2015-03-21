#include<iostream>
#include<cmath>
#include<vector>
#include"Vector.h"
class ode_solve
{
    double x_initial;//自变量初始值
    Vector y_initial;//函数初始值
    double x_end;//结束时自变量取值
    void (*sfn)(double x,const Vector& y,Vector& res);//源函数
    public:
        ode_solve(double x0,const Vector y0,double x1,void(*f)(double x,const Vector& y,Vector& res))
        {
            x_initial=x0;
            y_initial=y0;
            x_end=x1;
            sfn=f;
         }
        Vector* RK4(int )const;
 };
Vector* ode_solve::RK4(int n)const
{
    int m=y_initial.size();
    double dx=(x_end-x_initial)/double(n);
    Vector* y=new Vector[n+1];
    y[0].resize(m);
    y[0]=y_initial;
    for(int k=0;k<n;k++)
    {
        double tp=x_initial+dx*k;
        Vector K1(m,0.0),K2(m,0.0),K3(m,0.0),K4(m,0.0);
        y[k+1].resize(m);
        sfn(tp,y[k],K1);
        sfn(tp+dx/2.0,y[k]+dx/2.0*K1,K2);
        sfn(tp+dx/2.0,y[k]+dx/2.0*K2,K3);
        sfn(tp+dx,y[k]+dx*K3,K4);
        y[k+1]=y[k]+dx/6.0*(K1+2*K2+2*K3+K4);
    }
    return y;
}
void RK4_(double x,double dx,const Vector& y0,Vector& y,void(*f)(double x,const Vector& y,Vector& res))

{
    int m=y0.size();
    y.resize(m);
    Vector K1(m,0.0),K2(m,0.0),K3(m,0.0),K4(m,0.0);
    f(x+dx,y0+dx,K1);
    f(x+dx/2.0,y0+dx/2.0*K1,K2);
    f(x+dx/2.0,y0+dx/2.0*K2,K3);
    f(x+dx,y0+dx*K3,K4);
    y=y0+dx/6.0*(K1+2*K2+2*K3,K4);
}

