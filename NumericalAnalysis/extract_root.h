#ifndef __extract_root__H_
#define __extract_root__H_
#include<cmath>
#include<iostream>
#include"Vector.h"
#include"linear.h"
#include"Matrix.h"
double newton_solve(double x0,int max,double eps,double(*f)(double),double(*df)(double))
{
    double y=f(x0);double x1;
    if(std::abs(y)<eps){return x0;}
    else
    {
        int k=1;
        while(k<max&&k++)
        {
            x1=x0-y/df(x0);
            y=f(x1);
            if(std::abs(x1-x0)<eps||std::abs(y)<eps)
            {
                break;
            }x0=x1;

        }
    }
    return x1;
}
Matrix Newton_solve(Matrix x0,int max,double eps,Matrix(*f)(Matrix),Matrix(*df)(Matrix))
{
    Matrix y=f(x0);Matrix x1(x0.size(),1);
    if(Norm_Matrix(y)<eps){return x0;}
    else
    {
        int k=1;
        while(k<max&&k++)
            {
               x1=x0-LUsolve(df(x0),f(x0));
               y=f(x1);
               if(Norm_Matrix(x1-x0)<eps&&Norm_Matrix(y)<eps){break;}
               x0=x1;
            }
    }
    
    return x1;
}
Matrix Broyden(Matrix x0,int max,double eps,Matrix(*f)(Matrix),Matrix(*df)(Matrix))
{
    Matrix inv0=inv(df(x0));Matrix inv1;
    Matrix x1=x0-inv0*f(x0);
    Matrix y;
    if(Norm_Matrix(f(x1))<eps){return x1;}
    int k=1;Matrix g;
    while(k<max&&k++)
    {
        g=f(x1)-f(x0);
        y=x1-x0;
        double tmp=1.0/((trans(y)*inv0*g)[0][0]);
        inv1=inv0-tmp*((inv0*g-y)*trans(y)*inv0);
        x0=x1;
        x1=x1-inv1*f(x1);
        if(Norm_Matrix(x1-x0)<eps&&Norm_Matrix(f(x1))<eps){break;}
        inv0=inv1;

    }
    //std::cout<<"迭代次数："<<k<<std::endl;
    return x1;
}
#endif// __extract_root__H_
