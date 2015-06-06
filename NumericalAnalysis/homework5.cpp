#include "Fourier.h"
#include "linear.h"
#include "Matrix.h"
#include<cmath>
#include<iostream>
#include<ctime>
#include<iomanip>
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
void output1(int n,int n1){
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
    Matrix A(n1,n1),b1(n1,1),x(n1,1);
    for (int i=0;i<n1;i++){
        A[i][i]=4;
        b1[i][0]=1;
        if (i+1<n1){A[i][i+1]=A[i+1][i]=-1.0;}
    }
    A[0][n1-1]=A[n1-1][0]=-1.0;
    //solve problem
    double startTime=clock();
    PCG(x,A,b1,10,0.000000000001,n1);
    double PCGtime=(clock()-startTime)/CLOCKS_PER_SEC;
    startTime=clock();
    ans=CyclicMatrixSolve(c,b,n);
    double FFTtime=(clock()-startTime)/CLOCKS_PER_SEC;
//    cout<<n<<"& "<<FFTtime<<"& "<<PCGtime<<"\\\\"<<endl<<"\\hline"<<endl;
    cout<<n<<","<<FFTtime<<","<<PCGtime<<endl;
    /*
    for (int j=0;j<n1;j++){
        std::cout<<ans[j].real()<<"==="<<x[j][0]<<endl;
    }
    */
}
void output2( int n,int M,int Q){
   // int k=std::log(M+Q-1)/std::log(2);
   // int n=std::pow(2,k+1);
    //std::cout<<n<<endl; 
    //init data
    vector<complex<double> > x,h;x.resize(n);h.resize(n);
    for(int i=0;i<n;i++){
        if(i<Q&&i>0){
            x[i]=sin(i/2.0);
            h[i]=exp(1.0/double(i));
        }
        else if(i>=Q&&i<M){
            x[i]=sin(i/2.0);
            h[i]=0;
        }
        else{
            x[i]=h[i]=0;
        }
    }
    double startTime=clock();
    vector<complex<double> >ansFFT=ConcolutionFFT(h,x,n);
    double FFTtime=(clock()-startTime)/CLOCKS_PER_SEC;
   // cout<<"FFT卷积时间 "<<(endTime-startTime)/CLOCKS_PER_SEC<<endl;
    startTime=clock();
    vector<complex<double> >ans=Concolution(h,x,n);
    double Contime=(clock()-startTime)/CLOCKS_PER_SEC;
    cout<<n<<","<<FFTtime<<","<<Contime<<endl;
    //cout<<"普通卷积时间 "<<(endTime-startTime)/CLOCKS_PER_SEC<<endl;
    /*
    for(int i=0;i<n;i++){
        cout<<ansFFT[i].real()<<"  "<<ans[i].real()<<endl;
    }
    */
    
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
 //   int length= pow(2,10);
   // output1(length,400);
   // for (int MatrixSize=2;MatrixSize<length+1;MatrixSize=MatrixSize*2){
     //   output1(MatrixSize,MatrixSize);
    
    //}
    for (int size=2;size<5000;size=size*2){
        output2(size,size/3,size/3);
    }
}
