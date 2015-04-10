#include<iostream>
#include<cmath>
#include<iomanip>
#include"integration.h"
using namespace std;
double f(double x)
{
    return 4.0/(1+x*x);
}
double f2(double x0,double x1,double y0,double y1){
    return 1.0/std::sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));

}
int main()
{
    //3.4
    double a=0.0,b=1.0;
    double h=0.00001;double err=0.0000001;int n0=(b-a)/h;
    std::cout<<"中点 "<<re_mide_point(a,b,h,f)<<"梯形 "<<
        re_trapezoid(a,b,h,f)<<"simposon: "<<re_simposon(a,b,h,f)<<std::endl;
    cout<<"romberg"<<setprecision(8)<<romberg(a,b,h,f,err)<<"自适应方法 "<<auto_fit(a,b,n0,f,err)<<std::endl;
    //3.9
    double a1=-1,b1=1,c1=-1,d1=1;
    std::cout<<double_simposon(a1,b1,c1,d1,2.0,2.0,f2)<<std::endl;
}
