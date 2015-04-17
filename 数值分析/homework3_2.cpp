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
void output4_1(double a,double b,int maxNum){
    cout.precision(9);
    cout<<"h&"<<" $\\pi$& "<<"复合中点&"<<" 误差"<<"\\\\"<<endl;
    for(int n=1;n<maxNum;n=n*10){
        double h=(b-a)/double(n);
        double center=re_mide_point(a,b,h,f);
        cout<<h<<"& "<<Pi<<"& "<<center<<"& "<<abs(center-Pi)<<"\\\\"<<endl;
        cout<<"\\hline"<<endl;
    }
    cout<<"h&"<<" $\\pi$& "<<"复合梯形&"<<" 误差"<<"\\\\"<<endl;
    for(int n=1;n<maxNum;n=n*10){
        double h=(b-a)/double(n);
        double center=re_trapezoid(a,b,h,f);
        cout<<h<<"& "<<Pi<<"& "<<center<<"& "<<abs(center-Pi)<<"\\\\"<<endl;
        cout<<"\\hline"<<endl;
    }
    cout<<"h&"<<" $\\pi$& "<<"复合Simposon&"<<" 误差"<<"\\\\"<<endl;
    for(int n=1;n<maxNum;n=n*10){
       
        double h=(b-a)/double(n);
        double center=re_simposon(a,b,h,f);
        cout<<h<<"& "<<Pi<<"& "<<center<<"& "<<abs(center-Pi)<<"\\\\"<<endl;
        cout<<"\\hline"<<endl;
    }

}
void output4_2(double a,double b,long int maxNum){
    int count;
    double h0=0.1;
    cout.precision(8);
    cout<<"精度& "<<"达到精度步长& "<<"Romberg折合步长次数"<<"\\\\"<<endl;
    cout<<"\\hline"<<endl;
    for(long int n=100;n<maxNum;n=100*n){
        long double err0=1.0/n;
        long double rom=romberg(a,b,h0,f,err0,count);
        cout<<err0<<"& "<<h0<<"& "<<count<<"\\\\"<<endl;
        cout<<"\\hline"<<endl;
    }

    cout<<"精度& "<<"达到精度步长& "<<"自适应方法调整次数"<<"\\\\"<<endl;
    cout<<"\\hline"<<endl;
    int n0=10;
    for(long int n=100;n<maxNum;n=100*n){
        long double err0=1.0/n;
        long double rom=auto_fit(a,b,n0,f,err0,count);
        cout<<err0<<"& "<<1.0/n0<<"& "<<count<<"\\\\"<<endl;
        cout<<"\\hline"<<endl;
    }
    
}

int main()
{
    //3.4
    double a=0.0,b=1.0;
    long int  n0=pow(10,15);
    output4_2(a,b,n0);
   // output4_1(a,b,10000000);
   //3.9
   //double a1=-1,b1=1,c1=-1,d1=1;
   // std::cout<<double_simposon(a1,b1,c1,d1,2.0,2.0,f2)<<std::endl;

}
