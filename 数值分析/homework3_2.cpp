#include<iostream>
#include<cmath>
#include<iomanip>
#include"integration.h"
using namespace std;
#define Pi 3.141592653589793
double f(double x)
{
    return 4.0/(1+x*x);
}
double f2(double x0,double x1,double y0,double y1){
    return 1.0/std::sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));

}
void output4_2(double a,double b,int maxNum){
    cout.precision(7);
    cout<<"h&"<<" $\\pi$& "<<"复合中点&"<<" 误差"<<"\\\\"<<endl;
    for(int n=1;n<maxNum;n=n*10){
        double h=(b-a)/double(n);
        double center=re_mide_point(a,b,h,f);
        cout<<h<<"& "<<Pi<<"& "<<center<<"& "<<abs(center-Pi)<<"\\\\"<<endl;
    }
    cout<<"h&"<<" $\\pi$& "<<"复合梯形&"<<" 误差"<<"\\\\"<<endl;
    for(int n=1;n<maxNum;n=n*10){
        double h=(b-a)/double(n);
        double center=re_trapezoid(a,b,h,f);
        cout<<h<<"& "<<Pi<<"& "<<center<<"& "<<abs(center-Pi)<<"\\\\"<<endl;
    }
    cout<<"h&"<<" $\\pi$& "<<"复合Simposon&"<<" 误差"<<"\\\\"<<endl;
    for(int n=1;n<maxNum;n=n*10){
       
        double h=(b-a)/double(n);
        double center=re_simposon(a,b,h,f);
        cout<<h<<"& "<<Pi<<"& "<<center<<"& "<<abs(center-Pi)<<"\\\\"<<endl;
    }

}

int main()
{
    //3.4
    double a=0.0,b=1.0;
    output4_2(a,b,10000000);
    //3.9
    //double a1=-1,b1=1,c1=-1,d1=1;
   // std::cout<<double_simposon(a1,b1,c1,d1,2.0,2.0,f2)<<std::endl;

}
