#include "Fourier.h"
#include<cmath>
#include<iostream>
#define pi 3.141592653
using namespace std;
double f3(double t){
    return exp(-t*t/10)*(sin(2*t)+2*cos(4*t)+0.4*sin(t)*sin(50*t));
}
vector<complex<double> > initData3(int n){
    vector<complex<double> > ans;
    ans.resize(n);
    for(int i=0;i<n;i++){
        ans[i].real(f3(2*i*pi/n));
        ans[i].imag(0);
    }
    return ans; 
}
void output1(int n){
    //init data
    vector<complex<double> > c,b;c.resize(n);b.resize(n);
    for ( int i=0;i<n;i++){
        b[i]=1;
        if (i==0){
            c[i]=4;
        }
        else if (i==n-1||i==1){
            c[i]=-1;
        }
        else{
            c[i]=0;
        }
    }
    vector<complex<double> > ans;ans.resize(n);
    ans=CyclicMatrixSolve(c,b,n);
    for (int j=0;j<n;j++){
        std::cout<<ans[j].real()<<endl;
    }
}
void output3(int n){
    vector<complex<double> > inData,inData0,outData,outData1;
    inData.resize(n);outData.resize(n);outData1.resize(n);
    inData0=initData3(n);
    inData=initData3(n);
    FFT(inData,outData,n,-1);

    for (int i=6;i<251;i++){
       outData[i]=0;
    } 

    FFT(outData,outData1,n,1);
    for (int i =0;i<n;i++){
        cout<<real((inData0[i]))<<","<<real((outData1[i]))/256<<endl;
    }
}
int main(){
    int lenth=256;
//    output3(lenth);
    int length= pow(2,10);
    output1(length);

}
