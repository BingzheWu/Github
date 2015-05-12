#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <vector>
#include<cmath>
class Vector :public std::vector<double>
{
    public:
        Vector(){};
        Vector(int n ) 
        {
            Vector& tmp=*this;
            tmp.resize(n);    
        };
        Vector(int n,double x)
        {
            (*this).resize(n);
            for(int i=0;i<n;i++)
            {
              (*this)[i]=x;
            }
        }
        Vector& operator =(const Vector& v);
        Vector& operator+=(const Vector& v);
        Vector& operator-=(const Vector& v);
        Vector& operator*=(double fac);
        double l1_norm();
        double l2_norm();
        double linf_norm();
};

Vector&  Vector:: operator =(const Vector& v)
{
    Vector& tmp=*this;
    tmp.resize(v.size());
    for(int i=0;i<v.size();i++)
    {
        tmp[i]=v[i];
    }
    return tmp;
}
Vector& Vector::operator +=(const Vector& v)
{
    for(int i=0;i<v.size();i++)
       (*this)[i]+=v[i];
    return *this;
}
Vector& Vector::operator -=(const Vector& v)
{
    for(int i=0;i<v.size();i++)
    {
       (*this)[i]-=v[i];
    }
    return *this;
}
Vector& Vector::operator *=(const double x)
{
    for(int i=0;i<(*this).size();i++)
       (*this)[i]*=x;
    return *this;
}
Vector operator+(const Vector& v1, const Vector& v2)
{
    int n=v1.size();
    Vector ans(n); 
    ans.resize(n);
    for(int i=0;i!=n;i++)
    {
        ans[i]=v1[i]+v2[i];
    }
    return ans;
}
Vector operator -(const Vector& v1,const Vector& v2)
{
    Vector ans;
    int n=v1.size();
    ans.resize(n);
    for(int i=0;i!=n;i++)
    {
        ans[i]=v1[i]-v2[i];
    }
    return ans;
}
Vector operator *(const double x,const Vector& v)
{
    Vector ans;
    int n=v.size();
    ans.resize(n);
    for(int i=0;i<n;i++)
    {
        ans[i]=x*v[i];
    }
    return ans;
}
Vector operator *(const Vector& v,const double x)
{
   int n=v.size();
   Vector ans(n);
   for(int i=0;i<n;i++)
       ans[i]=x*v[i];
   return ans;
}
double MAX_norm(Vector a)
{
    int n=a.size();
    double tmp=fabs(a[0]);
    for(int k=1;k!=n;k++)
    {
        if(tmp<fabs(a[k]))
        {
            tmp=fabs(a[k]);
        }
        else
        {
            ;
        }
    }
    return tmp;
}
#endif //__VECTOR_H__
