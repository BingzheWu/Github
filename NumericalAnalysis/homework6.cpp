#include<iostream>
#include "ode_solve.h"
#include<cmath>
#include<iomanip>
#include<stdio.h>
#define pi 3.141592653589793
#define deta 10.0
#define rho 28.0
#define beta 0.375 
using namespace std;
Vector f1(double x,const Vector& y){
    Vector ans(1);
    ans[0]=-1.0/(x*x)-y[0]/x-y[0]*y[0];
    return ans;
}
Vector f4(double t ,const Vector& y){
    Vector ans(3);
    ans[0]=deta*(y[1]-y[0]);
    ans[1]=rho*y[0]-y[1]-y[0]*y[2];
    ans[2]=y[0]*y[1]-beta*y[2];
    return ans;

}
Vector f5(double t,const Vector& y){
    int n=1000;
    double h=(2*pi)/n;
    Vector ans(n+1);
    ans[0]=-cos(t);
    for(int i=1;i<n;i++){
        ans[i]=(y[i-1]-y[i+1])/(2*h);
    }
    ans[n]=-cos(t);
    return ans;
}
Vector f2(double t,const Vector& y){
    Vector ans(2);
    ans[0]=-0.013*y[0]-1000.0*y[0]*y[1];
    ans[1]=-2500.0*y[0]*y[1]-2500*y[1]*y[1]+5000.0*y[1];
    return ans;
}
void output1(int n){
    double xInitial=1;
    Vector yInitial(1,-1);
    double xEnd=2;
    ode_solve solve1(xInitial,yInitial,xEnd,f1);
    std::vector<Vector> EulerResult =solve1.Euler(n);
    vector<Vector> ImproveEulerResult=solve1.ImproveEuler(n);
    for (int i=0;i<n+1;i++){
        std::cout<<xInitial+i*1.0/n<<","<<EulerResult[i][0]<<","<<ImproveEulerResult[i][0]<<endl;
    }
    
}
void output2(int n){
    double tInitial=0;double tEnd=10;
    double dt=(tEnd)/double(n);
    Vector yInitial(2);
    yInitial[0]=1.0;yInitial[1]=1.0;
    ode_solve solve1(tInitial,yInitial,tEnd,f2);
    double startTime=clock();
    vector<Vector> EulerResult=solve1.Euler(n);
    double EulerTime=(clock()-startTime)/CLOCKS_PER_SEC;
    startTime=clock();
    vector<Vector> improveEulerResult=solve1.ImproveEuler(n);
    double ImproveEulerTime=(clock()-startTime)/CLOCKS_PER_SEC;
    startTime=clock();
    for(int i=0;i<100+1;i++){
        printf("%f,%f,%f,%f\n",i*dt,improveEulerResult[i][0],improveEulerResult[i][1],improveEulerResult[i][0]+improveEulerResult[i][1]-2);
    }

}
void output4(int n,double tInitial,double tEnd,Vector yInitial){
    ode_solve solve1(tInitial,yInitial,tEnd,f4);

}
void output5(int n,double tEnd){
    int m=1000;
    double h=(2*pi)/m;
    double tInitial=0;Vector uInitial(m+1);
    for(int i=0;i<m+1;i++){
        uInitial[i]=sin(i*h);
    }
    ode_solve solve1(tInitial,uInitial,tEnd,f5);
    vector<Vector> RK4Result=solve1.Kutta3(n);
    for(int i=0;i<m;i++){
        for(int j=0;j<n+1;j++){
            cout<<j*(tEnd)/m<<","<<i*h<<","<<RK4Result[j][i]<<endl;
        }
    }
}
int main(){
    int n=1000;
    //output1(10);
    output5(n,6);
   //output2(1000);

}
