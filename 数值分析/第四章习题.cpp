#include<iostream>
#include<cmath>
#include"extract_root.h"
//4.3
Matrix f3(Matrix x)
{
    Matrix ans(2,1);
    ans[0][0]=(x[0][0]+3)*(std::pow(x[1][0],3)-7)+18;
    ans[1][0]=std::sin(x[1][0]*std::exp(x[0][0])-1);
    return ans;

}
Matrix df3(Matrix x)
{
    Matrix ans(2,2);
    ans[0][0]=std::pow(x[1][0],3)-7;
    ans[0][1]=(x[0][0]+3)*3*x[1][0]*x[1][0];
    ans[1][0]=std::cos(x[1][0]*std::exp(x[0][0])-1)*x[1][0]*std::exp(x[0][0]);
    ans[1][1]=std::cos(x[1][0]*std::exp(x[0][0])-1)*std::exp(x[0][0]);
    return ans;
}
int main()
{
    Matrix x0(2,1);
    x0[0][0]=-0.5;x0[1][0]=1.4;
    int max=20000;double eps=std::pow(0.1,15);
    Matrix ans=Broyden(x0,max,eps,f3,df3);
    std::cout<<ans[0][0]<<std::endl<<ans[1][0]<<std::endl;

}
