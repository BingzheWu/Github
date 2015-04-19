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
 double f3( double x){
    return (pow(x,3))/(exp(x)-1.0);
}
double f3temp(double x){
    return f3(x)*exp(x);
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
    int count=1;
    double h0=0.1;
    cout.precision(8);
    cout<<"误差& "<<"计算结果& "<<"Romberg迭代次数"<<"\\\\"<<endl;
    cout<<"\\hline"<<endl;
    for(long int n=100;n<maxNum;n=100*n){
        long double err0=1.0/n;
        long double rom=Romberg(a,b,h0,f,err0,count);
        double err=abs(rom-Pi);
        cout<<err<<"& "<<rom<<"& "<<count<<"\\\\"<<endl;
        cout<<"\\hline"<<endl;
    }

    cout<<"精度& "<<"达到精度步长& "<<"自适应方法调整次数"<<"\\\\"<<endl;
    cout<<"\\hline"<<endl;
    int n0=10;
    for(long int n=100;n<maxNum;n=100*n){
        n0=10;
        long double err0=1.0/n;
        double rom=auto_fit(a,b,n0,f,err0,count);
        double err=abs(rom-Pi);
        cout<<err<<"& "<<1.0/n0<<"& "<<count<<"\\\\"<<endl;
        cout<<"\\hline"<<endl;
    }
    
}
void output3_9(int n,double a1,double b1,double c1,double d1){
    double h=8.0/n;
    double tmp1;
    double tmp2;
    double h0=2.0/15;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++){
            tmp1=2+i*h;
            tmp2=2+j*h;
            cout<<tmp1<<","<<tmp2<<","<<CdoubleSimposon(a1,b1,c1,d1,tmp1,tmp2,f2,h)<<endl;
        }
    }
}
void output3_7(double err,int maxNum){
    cout<<infSimpson(err,maxNum,f3)<<endl;
    cout<<GaussLaguerre(f3temp)<<endl; 

}
int main()
{
    //3.4
    double a=0.0,b=1.0;
    long int  n0=pow(10,14);
    output4_2(a,b,n0);
   // output4_1(a,b,10000000);
   //3.9
   double a1=-1,b1=1,c1=-1,d1=1;
   //output3_9(20,a1,b1,c1,d1);
//   output3_7(0.000000001,2);
   // std::cout<<double_simposon(a1,b1,c1,d1,2.0,2.0,f2)<<std::endl;

}
