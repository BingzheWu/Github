#include<iostream>
#include<cmath>
#include"extract_root.h"
double f(double x)
{
    return double(std::pow(x,6)-x-1);
}
double df(double x)
{
    return double(6*std::pow(x,5)-1);
}
Matrix f3(Matrix x){
    Matrix ans(2,1);
    ans[0][0]=(x[0][0]+3)*(std::pow(x[1][0],3)-7)+18;
    ans[1][0]=std::sin(x[1][0]*std::exp(x[0][0])-1);
    return ans;
}
Matrix df3(Matrix x){
    Matrix ans(2,2);
    ans[0][0]=std::pow(x[1][0],3)-7;
    ans[0][1]=3*(x[0][0]+3)*x[1][0]*x[1][0];
    ans[1][0]=std::cos(x[1][0]*std::exp(x[0][0])-1)*x[1][0]*std::exp(x[0][0]);
    ans[1][1]=std::cos(x[1][0]*std::exp(x[0][0])-1)*std::exp(x[0][0]);
    return ans;
}
void output1(Matrix x0,int max,double eps,Matrix cur){
    Matrix ans(2,1);
    std::cout<<"/hline"<<std::endl;
    std::cout<<"迭代次数& "<<"误差& "<<"\\\\"<<std::endl<<"/hline"<<std::endl;
    for (int i=1;i<=max;i++){
        ans=Broyden(x0,i,eps,f3,df3);
        std::cout<<i<<"& "<<Norm_Matrix(ans-cur)<<"& "<<"\\\\"<<std::endl<<"/hline"<<std::endl;
    }
    std::cout<<"迭代次数& "<<"误差& "<<"\\\\"<<std::endl<<"/hline"<<std::endl;
    for (int i=1;i<=max;i++){
        ans=Newton_solve(x0,i,eps,f3,df3);
        std::cout<<i<<"& "<<Norm_Matrix(ans-cur)<<"& "<<"\\\\"<<std::endl<<"/hline"<<std::endl;
    }
}
int main()
{
    Matrix x0(2,1);Matrix cur(2,1);
    cur[0][0]=0;cur[1][0]=1.0;
    x0[0][0]=-0.5;
    x0[1][0]=1.4;
    int max=10;double eps=std::pow(0.1,15);
    output1(x0,max,eps,cur);
}
