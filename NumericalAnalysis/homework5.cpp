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
        ans[i]=f3(2*i*pi/n);
    }
    return ans; 
}
void output1(int n){
    vector<complex<double> > inData,outData;
    inData.resize(n);outData.resize(n);
    inData=initData3(n);
    int sign=1;
    FFT(inData,outData,n,sign);
    for (int i =0;i<n;i++){
        cout<<real(outData[i])<<endl;
    }
}
int main(){
    int lenth=256;
    output1(lenth);

}
