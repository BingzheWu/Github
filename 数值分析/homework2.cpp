/*add a */
#include<iostream>
#include<cmath>
#include"differential.h"
double f(double x)
{
    return std::exp(-x/4.0);
}
double df(double x)
{
    return -0.25*f(x);
}
int main()
{
   //3.1
   int k1=10;
   std::cout.precision(5);
   double ans=1.0/0.7;
   for(k1=1;k1<11;k1++){
   double h1=1.0/(std::pow(10,k1));
  /* std::cout<<1.0/0.7<<" "<<Foward_dy(0.7,h1,std::log)<<" "<<Center_dy(0.7,h1,std::log)<<
       " "<<tri_dy(0.7,h1,std::log)<<std::endl;*/
/*方便将数据在Latex中制表，作格式化输出*/
   double out1=Foward_dy(0.7,h1,std::log);double out2=Center_dy(0.7,h1,std::log);double out3=tri_dy(0.7,h1,std::log);
   double e1=std::abs(ans-out1),e2=std::abs(ans-out2),e3=std::abs(ans-out3);
   std::cout<<ans<<'&'<<" $1/10^"<<k1<<"$&"<<" "<<out1<<'&'<<" "<<e1<<"& "<<out2<<"& "<<e2<<"& "<<out3<<"& "<<e3<<"\\\\"<<std::endl;
   }
   //3.2
   int n=11;double h=1.0/(n-1);
   std::cout<<"3.2结果"<<std::endl;
   std::vector<double> test(n),X(n),ans1(n),ans2(n);
   for(int i=0;i!=n;i++)
   {
       X[i]=i*h;
       test[i]=df(X[i]);
   }
   ans1=Center_2_dy(X,n,f,test[0],test[n-1],h);
   ans2=implicit(X,n,f,test[0],test[n-1],h);
   for(int i=0;i!=n;i++)
   {
       std::cout<<"i="<<X[i]<<" "<<test[i]<<" "<<ans1[i]<<" "<<ans2[i]<<std::endl;
   }


}
