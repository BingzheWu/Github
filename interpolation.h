#ifndef __interpolation_H__
#define __interpolation_H__
#include<iostream>
#include<cmath>
#include<vector>
#include"Matrix.h"
#include"linear.h"
//lagrange插值
double lagrange(double x,int n,std::vector<double>& X,std::vector<double>& Y)
{
    double ans=0;
    double temp;
    for(int i=0;i!=n;i++)
    {
        temp =Y[i];
        for(int j=0;j!=n;j++)
        {
            if(j!=i)
            {
                temp=temp*(x-X[j]);
                temp=temp/(X[i]-X[j]);
            }
        }
        ans=ans+temp;

    }
    return ans;
    
}
//差商(计算f[x0,x1,...,xi])
double difference(int i,std::vector<double>& X,std::vector<double>& Y)
{
    double f=0.0;
    double temp;
    for(int k=0;k!=i+1;k++)
    {
        temp=Y[k];
        for(int j=0;j!=i+1;j++)
        {
            if(j!=k)
            {
                temp=temp/(X[k]-X[j]);
            }

        }
        f+=temp;
    }
    return f;
}
//newton插值
double newton(double x,int n,std::vector<double>& X,std::vector<double>& Y)
{
    double ans=0;
    double temp;
    for(int i=0;i!=n;i++)
    {
        temp=difference(i,X,Y);
        for(int j=0;j!=i;j++)
        {
            temp*=x-X[j];
        }
        ans+=temp;
    }
    return ans;
}
//二分法搜所
int search(int n,double x,std::vector<double>& X)
{
    int ans=0;
    int low=0,high=n,mid=n/2;
    while(1)
    {
        
        mid=std::floor((high+low)/2);
        if(low==high-1){ans=low;break;}
        else if(x==X[mid])
        {ans=mid;
       break;}
       
        else if(x<X[mid])
        {
            if(x>X[mid-1]||x==X[mid-1])
            {
                ans=mid-1;
                break;
            }
            else
                high=mid-1;
                
        }
        else if(x>X[mid])
        {
            if(x<X[mid+1]||x==X[mid+1])
            {
                ans=mid;
                break;
            }
            else
                low=mid+1;
        }
        

    }
    return ans;
    
    

}
int search1(int n,double x,std::vector<double>& X)
{
    ;
}
//分段线性插值

double piecewise(double x,int n,std::vector<double>& X,std::vector<double>& Y)
{
    double ans;
    int tmp=search(n,x,X);
    std::vector<double> temp_x(2),temp_y(2);
    temp_x[0]=X[tmp];temp_x[1]=X[tmp+1];
    temp_y[0]=Y[tmp];temp_y[1]=Y[tmp+1];
    ans=lagrange(x,2,temp_x,temp_y);
    return ans;
}
//Hermit插值
double Hermit(double x,double x0,double x1,double y0,double y1,double dy0,double dy1)
{
    double alpha0=(1+2*(x-x0)/(x1-x0))*((x-x1)*(x-x1)/((x0-x1)*(x0-x1)));
    double alpha1=(1+2*(x-x1)/(x0-x1))*((x-x0)*(x-x0)/((x1-x0)*(x1-x0)));
    double beta0=(x-x0)*((x-x1)*(x-x1)/((x0-x1)*(x0-x1)));
    double beta1=(x-x1)*((x-x0)*(x-x0)/((x1-x0)*(x1-x0)));
    return y0*alpha0+y1*alpha1+dy0*beta0+dy1*beta1;
}
double piecewise_hermit(double x,int n,std::vector<double>& X,std::vector<double>& Y,std::vector<double>& dY)
{
    int tmp=search(n,x,X);
    return Hermit(x,X[tmp],X[tmp+1],Y[tmp],Y[tmp+1],dY[tmp],dY[tmp+1]);
}
//三次样条
double spline(double x,int n,std::vector<double>& X,std::vector<double>& Y)
{
    std::vector<double> dY(n),a(n),b(n),c(n);Matrix z(n,1);
    for(int i=0;i!=n;i++)
    {
        a[i]=2;
    }
    for(int j=1;j!=n-1;j++)
    {
        double deta0=X[j]-X[j-1],deta1=X[j+1]-X[j],lamda=deta0/(deta0+deta1);
        c[j+1]=lamda;c[1]=1;
        b[j]=1-c[j+1];b[0]=1;
        z[j][0]=3*((1-lamda)/deta0*(Y[j]-Y[j-1])+lamda/deta1*(Y[j+1]-Y[j]));
    }
    z[0][0]=3*((Y[1]-Y[0])/(X[1]-X[0]));
    z[n-1][0]=3*((Y[n-1]-Y[n-2])/(X[n-1]-X[n-2]));
    tridiagonal(n,a,b,c,z,dY);
    return piecewise_hermit(x,n,X,Y,dY);
}

#endif _
