#ifndef __Fourier_H__
#define __Fourier_H__
#include "Matrix.h"
#include<cmath>
#include<complex>
#define pi 3.141592653
using namespace std;
int inverse(int n)
{
    int ans;
    std::vector<int> temp;
    while(n>0)
    {
        temp.push_back(n%2);
        n=std::ceil(n/2);
    }
    n=0;
    for(int j=0;j!=temp.size();j++)
    {
        n+=temp[j]*std::pow(2,temp.size()-j-1);

    }
    ans=n;
    return ans;

}
void FFT(std::vector<std::complex<double> >& InData,vector<complex<double> >& OutData,int lenth,int sign)
{
    vector<complex<double> > LData;LData.resize(lenth/2);
    vector<complex<double> > LResult;LResult.resize(lenth/2);
    vector<complex<double> > RData;RData.resize(lenth/2);
    vector<complex<double> > RResult;RResult.resize(lenth/2);
    complex<double> temp;
    int i;
    if(lenth==1){
        OutData[0]=InData[0];
        return;
    }
    for(i=0;i<lenth/2;i++){
        LData[i]=InData[i];
        RData[i]=InData[i+lenth/2];
    }
    for(i=0;i<lenth/2;i++){
        temp=LData[i];
        LData[i]=LData[i]+RData[i];
        RData[i]=(temp-RData[i])* complex<double>(cos(2*pi*i/lenth),sin(sign*2*pi*i/lenth));
    }
    FFT(LData,LResult,lenth/2,sign);
    FFT(RData,RResult,lenth/2,sign);
    for(i=0;i<lenth/2;i++){
        OutData[2*i]=LResult[i];
        OutData[2*i+1]=RResult[i];
    }
    return; 


}
#endif
