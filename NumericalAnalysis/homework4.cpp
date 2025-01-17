#include<iostream>
#include<cmath>
#include"extract_root.h"
using namespace std;
double f(double x)
{
    return double(std::pow(x,6)-x-1);
}
double df(double x)
{
    return double(6*std::pow(x,5)-1);
}
//第二题条件
double f2(double x){
	return std::cos(x)+1.0/(1+std::exp(-2*x));
}
double df2(double x){
	return -1*std::sin(x)+(2*std::exp(-2*x))/std::pow((1+std::exp(-2*x)),2);
}
double scheme1(double x0){
	double x1;
	x1=std::acos(std::cos(x0)-f2(x0));
	return x1;
}
double scheme2(double x0){
	double x1=0.5*std::log((-1.0)/(1+1/(std::cos(x0))));
	return x1;
}

//第三题条件
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
//第四题条件
Matrix f4 (Matrix x){
    Matrix ans(3,1);
    ans[0][0]=-cos(x[0][0])/81.0+x[1][0]*x[1][0]/9.0+sin(x[2][0])/3.0-x[0][0];
    ans[1][0]=sin(x[0][0])/3.0+cos(x[2][0])/3.0-x[1][0];
    ans[2][0]=-cos(x[0][0])/9.0+x[1][0]/3.0+sin(x[2][0])/6.0-x[2][0];
    return ans;
}
Matrix df4(Matrix x){
    Matrix ans(3,3);
    ans[0][0]=sin(x[0][0])/81.0-1;ans[0][1]=2.0/9.0*x[1][0];ans[0][2]=cos(x[2][0])/3.0;
    ans[1][0]=cos(x[0][0])/3.0;ans[1][1]=-1;ans[1][2]=-sin(x[2][0])/3.0;
    ans[2][0]=sin(x[0][0])/9.0;ans[2][1]=1.0/3.0;ans[2][2]=cos(x[2][0])/6.0-1;
    return ans;
}
Matrix scheme4(Matrix x0){
    Matrix x1(3,1);
    x1[0][0]=f4(x0)[0][0]+x0[0][0];
    x1[1][0]=f4(x0)[1][0]+x0[1][0];
    x1[2][0]=f4(x0)[2][0]+x0[2][0];
    return x1;
}
Matrix Scheme4(Matrix x0,int max,double eps){
    Matrix x1(3,1);
    for(int i=1;i<max;i++){
        x1=scheme4(x0);
        if( Norm_Matrix(x1-x0)<eps){
            break;
        }
        x0=x1;
    }
    return x1; 

}
void output1(double x0,int max, double eps,double cur ){
	double x1;
    cout<<"格式1"<<endl;
    cout<<"迭代次数& "<<"相对误差"<<"\\\\"<<endl<<"\\hline"<<endl;
	for ( int i =1;i<max;i++){
		x1=scheme1(x0);
        cout<<i<<"& "<<abs(x1-cur)<<"\\\\"<<endl<<"\\hline"<<endl;
		if(std::abs(x0-x1)<eps){
			break;
		}
		x0=x1;
	}
    cout<<"格式2"<<endl;
    cout<<"迭代次数& "<<"相对误差"<<"\\\\"<<endl<<"\\hline"<<endl;
	for ( int i =1;i<max;i++){
		x1=scheme2(x0);
        cout<<i<<"& "<<abs(x1-cur)<<"\\\\"<<endl<<"\\hline"<<endl;
		if(std::abs(x0-x1)<eps){
			break;
		}
		x0=x1;
	}
    cout<<"牛顿法 "<<endl;
    cout<<"迭代次数& "<<"相对误差"<<"\\\\"<<endl<<"\\hline"<<endl;
	for(int i=1;i<max;i++){
		x1=newton_solve(x0,i,eps,f2,df2);
        cout<<i<<"& "<<abs(x1-cur)<<"\\\\"<<endl<<"\\hline"<<endl;
    }
}
void output2(Matrix x0,int max,double eps,Matrix cur){
    Matrix ans(2,1);
    cout<<"Broyden"<<endl;
    std::cout<<"\\hline"<<std::endl;
    std::cout<<"迭代次数& "<<"误差& "<<"\\\\"<<std::endl<<"\\hline"<<std::endl;
    for (int i=1;i<=max;i++){
        ans=Broyden(x0,i,eps,f3,df3);
        std::cout<<i<<"& "<<Norm_Matrix(ans-cur)<<"& "<<"\\\\"<<std::endl<<"\\hline"<<std::endl;
    }
    cout<<"牛顿法"<<endl;
    std::cout<<"迭代次数& "<<"误差& "<<"\\\\"<<std::endl<<"\\hline"<<std::endl;
    for (int i=1;i<=max;i++){
        ans=Newton_solve(x0,i,eps,f3,df3);
        std::cout<<i<<"& "<<Norm_Matrix(ans-cur)<<"& "<<"\\\\"<<std::endl<<"\\hline"<<std::endl;
    }
}
void output3(Matrix x0,int max,double eps){
    Matrix ans0(3,1);
    Matrix ans1(3,1);
    Matrix cur(3,1);
    cur[0][0]=0;cur[1][0]=1/3.0;cur[2][0]=0;
    ans0=Newton_solve(x0,1,eps,f4,df4);
    cout<<"迭代次数k& "<<"二范数误差\\\\ "<<endl;
    cout<<"\\hline"<<endl;
    for (int i = 1;i<max-1;i++){
        ans1=Newton_solve(x0,i,eps,f4,df4);
        cout<<i<<"& "<<Norm_Matrix(ans0-cur)<<"\\\\"<<endl<<"\\hline"<<endl;
        ans0=ans1;
    }
    cout<<"迭代次数k& "<<"二范数误差& "<<"$\\dfrac{\\|x_{k+1}-x_*}{x_k-x_*}$\\\\"<<endl;
    cout<<"\\hline"<<endl;
    ans0=Scheme4(x0,1,eps);
    for (int i = 1;i<max-1;i++){
        ans1=Scheme4(x0,i,eps);
        cout<<i<<"& "<<Norm_Matrix(ans0-cur)<<"& "<<(Norm_Matrix(ans1-cur))/Norm_Matrix(ans0-cur)<<"\\\\"<<endl<<"\\hline"<<endl;
        ans0=ans1;
    }
        
}

int main()
{
    Matrix x0(2,1);Matrix cur(2,1);
    cur[0][0]=0;cur[1][0]=1.0;
    x0[0][0]=-0.5;
    x0[1][0]=1.4;
    int max=10;double eps=std::pow(0.1,15);
    output2(x0,max,eps,cur);
    double cur1=3.07642116379;
	output1(3,7,eps,cur1);
    Matrix x0_1(3,1);
    x0_1[0][0]=x0_1[1][0]=x0_1[2][0]=1.0;
    output3(x0_1,50,eps);
}
