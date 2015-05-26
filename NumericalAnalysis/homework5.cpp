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
    vector<complex<double> > inData,inData0,outData,outData1;
    inData.resize(n);outData.resize(n);outData1.resize(n);
    inData0=initData3(n);
    inData=initData3(n);
    FFT(inData,outData,n,-1);
/*
    for (int i=100;i<256-100;i++){
       outData[i]=0;
    } 
*/
    FFT(outData,outData1,n,1);
    for (int i =0;i<n;i++){
        cout<<real((inData0[i]))<<"==========="<<real((outData1[i]))/256<<endl;
    }
}
int main(){
    int lenth=256;
    output1(lenth);

}
