#ifndef __Fourier_H__
#define __Fourier_H__
#include"Matrix.h"
#include<cmath>
#include<complex>
void inverse(int& n)
{
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
    

}
void FFT(std::vector<std::complex<double> > a)
{
    int N=a.size();
    std::vector<std::complex<double> >temp;
    
    



}
#endif
