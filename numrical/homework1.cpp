#include"interpolation.h"
double Runge(double x)
{
    return 1.0/(x*x+1);
}
double dRunge(double x)
{
    double temp=(1+x*x)*(1+x*x);
    return -2*x/temp;
}
int main()
{
    //习题2.1
    int n1=11;
    std::vector<double> X1(n1),Y1(n1),dY1(n1);
    for(int i=0;i!=n1;i++)
    {
        X1[i]=-5.0+i;
        Y1[i]=Runge(X1[i]);
        dY1[i]=dRunge(X1[i]);
    }
    
    //习题2.2
    int n=21;
    double pi=3.1415926;
    std::vector<double> X(n),Y(n);
    for(int i=0;i!=n;i++)
    {
        X[i]=5*std::cos(double(2*i+1)/42*pi);
        Y[i]=Runge(X[i]);

    }
    //获取绘图数据
    int number2=101;
    for(int j=0;j!=number2;j++)
    {
        double h=10.0/(number2-1);
        double temp=-5+j*h;
        std:: cout.precision(6);std::cout<<std::fixed;
        std::cout<<temp<<" "<<Runge(temp)<<" "<<lagrange(temp,n,X,Y)<<" "<<newton(temp,n1,X1,Y1)<<
        " "<<piecewise(temp,n1,X1,Y1)<<" "<<piecewise_hermit(temp,n1,X1,Y1,dY1)<<
        " "<<spline(temp,n1,X1,Y1)<<std::endl;
    }
    return 0;


}
