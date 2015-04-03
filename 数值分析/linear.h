#include"Matrix.h"
#include<math.h>
void Back_Sub(Matrix A,Matrix& b)/*Back Substitution:To solve upper-triangular system Ax=b*/
{
    int n=b.size();
    for(int k=n-1;k!=0;k--)
    {
        b[k][0]=b[k][0]/A[k][k];
        for(int l=0;l!=k;l++)
        {
            b[l][0]=b[l][0]-b[k][0]*A[l][k];
        }
    }
    b[0][0]=b[0][0]/A[0][0];
}
void Forward_Sub(Matrix A,Matrix& b,Vector& a)/*Foward Substitution:To solve lowwer-triangular system Ax=b*/
{
    int n=b.size();
    a.resize(n);
    for(int k=0;k!=n-1;k++)
    {
        b[k][0]=b[k][0]/A[k][k];
        for(int l=k+1;l!=n;l++)
        {
            b[l][0]=b[l][0]-b[k][0]*A[l][k];
        }
    }
    b[n-1][0]=b[n-1][0]/A[n-1][n-1];
    for(int i=0;i!=n;i++)
    {
        a[i]=b[i][0];

    }
}
void LUfact(Matrix A,Matrix& L,Matrix& U,Matrix& P)
{
    
    int n=A.size();
   // L=U=P=A;
   
    Matrix temp=eyes(n);
    for(int k=0;k!=n-1;k++)
    {
        
        double tmp,tmp1;
        int trans;/*记录交换行下标*/
        Max_column(A,k,trans);
        for(int l=0;l!=n;l++)
        {
            tmp=A[k][l];
            A[k][l]=A[trans][l];
            A[trans][l]=tmp;
            tmp1=temp[k][l];
            temp[k][l]=temp[trans][l];
            temp[trans][l]=tmp1;
            
            
        }
       
        if(A[k][k]!=0)
        {
            for(int i=k+1;i!=n;i++)
            {
                A[i][k]=A[i][k]/A[k][k];
            }
            for(int i=k+1;i!=n;i++)
            {
                for(int j=k+1;j!=n;j++)
                {
                    A[i][j]=A[i][j]-A[i][k]*A[k][j];
                }
            }
           

        }
        else
        {
            break;
        }
    }
    
             for(int i=0;i!=n;i++)
        {
            for(int j=0;j!=n;j++)
            {
                if(i>j)
                {
                    L[i][j]=A[i][j];
                }
                else if(i<j)
                {
                    L[i][j]=0;
                }
                else
                {
                    L[i][j]=1;
                }
            }
        }
        
        for(int i=0;i!=n;i++)
        {
            for(int j=0;j!=n;j++)
            {
                if(i<j)
                {
                    U[i][j]=A[i][j];
                }
                else if(i==j)
                {
                    U[i][j]=A[i][j];
                }
                else
                {
                    U[i][j]=0;
                }
            }
        }
        for(int i=0;i!=n;i++)
        {
           for(int j=0;j!=n;j++)
            {
                P[i][j]=temp[i][j];
            }
        }

}

     
/* void tridiagonal(int n,std::vector<double> a,std::vector<double> b,std::vector<double> c,Matrix z,std::vector<double>& ans)
{
    Matrix temp1,temp2;Vector tmp;
    Matrix A(n,n),L(n,n),P(n,n),U(n,n);
    for(int i=0;i!=n;i++)
    {A[i][i]=a[i];}
    for(int i=0;i!=(n-1);i++)
    {
        A[i][i+1]=c[i];
    }
    for(int j=1;j!=n;j++)
    {A[j][j-1]=b[j+1];}
    LUfact(A,L,U,P);
    temp1=P*z;
    Forward_Sub(L,temp1,tmp);
    Back_Sub(U,temp1);
    for(int j=0;j!=n;j++)
    {
        ans[j]=temp1[j][0];
    }
}*/
Matrix LUsolve(Matrix A,Matrix b)
{
    int n=A.size();
    Matrix L(A.size(),A.size()),U(n,n),P(n,n),ans(A.size(),1);
    Vector tmp(n);
    LUfact(A,L,U,P);
    Matrix temp1=P*b;
    Forward_Sub(L,temp1,tmp);
    Back_Sub(U,temp1);
    for(int j=0;j!=A.size();j++)
    {
        ans[j][0]=temp1[j][0];
    }
return ans;
}
Matrix inv(Matrix A)
{
    int n=A.size();
    Matrix ans(n,n);
    for(int i=0;i!=n;i++)
    {
        Matrix temp(n,1);
        for(int j=0;j!=n;j++)
        {
            temp[j][0]=eyes(n)[j][i];
            

        }
        for(int j=0;j!=n;j++)
        {
            ans[j][i]=LUsolve(A,temp)[j][0];
        }

        
    }
    return ans;
}
void tridiagonal(int n,std::vector<double>a,std::vector<double>b,std::vector<double> c,Matrix z,std::vector<double>& ans)
{
    std::vector<double> y(n),u(n);
    y[0]=z[0][0]/a[0];
    u[0]=b[0]/a[0];
    double l;
    for(int i=1;i!=n-1;i++)
    {
        l=a[i]-c[i]*u[i-1];
        y[i]=(z[i][0]-y[i-1]*c[i])/l;
        u[i]=b[i]/l;
    }
    l=a[n-1]-c[n-1]*u[n-2];
    y[n-1]=(z[n-1][0]-y[n-2]*c[n-1])/l;
    ans[n-1]=z[n-1][0];
    for(int i=n-2;i!=-1;i--)
    {
        ans[i]=y[i]-u[i]*ans[i+1];
    }

}
