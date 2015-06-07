#include<iostream>
#include "ode_solve.h"
#include<cmath>
using namespace std;
Vector f1(double x,const Vector& y){
    Vector ans(1);
    ans[0]=-1.0/x*x-y[0]/x-y[0]*y[0];
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
void output5(int n){
    

}
int main(){
    int n=100;
    output1(100);

}
