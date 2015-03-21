#include<iostream>
#include<cmath>
void Forward(float& i0,float& i1,int n)
{
    i1=-5*i0+1.0/double(n);
    i0=i1;
}
int main()
{
    float i0=std::log(1.2);float i1;
    for(int k=0;k!=20;k++)
    {
        Forward(i0,i1,k+1);
        std::cout<<"I= "<<i1<<std::endl;
    }

}
