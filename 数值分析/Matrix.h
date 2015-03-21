/*author:Bingzhe Wu*/
#ifndef __Matrix_H__
#define __Matrix_H__
#include<iostream>
#include<vector>
#include<cmath>
#include"Vector.h"
class Matrix:public std::vector< Vector >
    {
        public:
            Matrix(){};
            Matrix(int m,int n)/*m*n Matrix*/
            {
                (*this).resize(m);
               
                for(int i=0;i!=m;i++)
                {
                   (*this)[i].resize(n);
                }
            }

            

          
            Matrix& operator =(const Matrix& c);
            Matrix& operator =(const Vector& c);
 
            
            
    };
Matrix& Matrix::operator =(const Matrix& c)
{
    (*this).resize(c.size());
    for(int i=0;i<c.size();i++)
    {
        (*this)[i].resize(c[0].size());
        for(int j=0;j<c[0].size();j++)
        {
            (*this)[i][j]=c[i][j];
        }
    }
    return *this;
}
Matrix& Matrix::operator =(const Vector& c)
{
    (*this).resize(c.size());
    for(int i=0;i<c.size();i++)
    {
        (*this)[i].resize(1);
        (*this)[i][0]=c[i];
    }
    return *this;

}

Matrix operator + (const Matrix& a,const Matrix& b)
{
    int m=a.size();
    int n=a[0].size();
    Matrix ans(m,n);
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
        {
            ans[i][j]=a[i][j]+b[i][j];
        }
    return ans;
}
Matrix operator -(const Matrix& a,const Matrix& b)
{
    int m=a.size();int n=a[0].size();
    Matrix ans(m,n);
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            ans[i][j]=a[i][j]-b[i][j];
    return ans;
}
Matrix operator *(const double x,const Matrix& a)
{
    int m=a.size();
    int n=a[0].size();
    Matrix ans(m,n);
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            ans[i][j]=x*a[i][j];
    return ans;
}
Matrix operator *(const Matrix& a,const Matrix& b)
{
    int m=a.size();int n=a[0].size();
    int l=b[0].size();
    Matrix ans(m,l);
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<l;j++)
        {
            for(int k=0;k<n;k++)
            {
              
             
             ans[i][j]=ans[i][j]+a[i][k]*b[k][j];
            }
            
        }
    }
    return ans;

}
void Max_column(Matrix A,int k,int& a)/*To give the biggest number of the column*/
{
    int n=A.size();
    int tmp_a=k;
    double tmp=fabs(A[k][k]);
    for(int l=k+1;l!=n;l++)
    {
        if(tmp<fabs(A[l][k]))
        {
            tmp=fabs(A[l][k]);
            tmp_a=l;
        }
        else
        {
            ;
        }
            
    }
    a=tmp_a;
    

}
Matrix trans(Matrix A)
{
    int n= A.size();
    int m=A[0].size();
    Matrix ans(m,n);
    for(int i=0;i!=m;i++)
    {
        for(int j=0;j!=n;j++)
        {
            ans[i][j]=A[j][i];
        }
    }
    return ans;
}
Vector get_cloumn(Matrix A,int k)
{
    int n=A.size();
    int m=A[0].size();
    Vector ans(n);
    for(int i=0;i!=n;i++)
    {
        ans[i]=A[i][k];
    }
    return ans;
}
Matrix eyes(int n)
{
    Matrix ans(n,n);
    for(int i=0;i!=n;i++)
    {
        for(int j=0;j!=n;j++)
        {
            if(i==j)
            {
                ans[i][j]=1;
            }
            else
            {
                ans[i][j]=0;
            }
        }
    }
    return ans;
}
double Norm_Matrix(Matrix A)
   {
       int n=A.size();int m=A[0].size();
       double ans=0;
        for(int i=0;i!=n;i++)
        {
            for(int j=0;j!=m;j++)
            {
               
                    ans+=fabs(A[i][j]);
              
              


            }
            
        }
        
        return ans;
   }
Matrix ones(int n)
{
    Matrix A(n,n);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            A[i][j]=1;
    }
    return A;
}
#endif
