#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define PI 3.14159265358979
#define N 100
typedef struct{
    char *data;
    int top;
}Stack;//栈，用来中缀表达式转换后缀表达式
typedef struct p{
	double data;//用double精度高
	int flag;//标记是否有小数点
}Node,*pNode;//用来存放在ch中转化的数
int My_Strcmp(char *p,char *j)//字符串比较 
{
	int i;
	if(p[0]=='\0')
		return -1; 
	for(i=0;p[i]!='\0'&&j[i]!='\0';i++)
	{
		if(p[i]>j[i])
			return 1;
		if(p[i]<j[i])
			return -1;
	}
	return 0;
}
double Pow(double j,double n) //幂的运算 
{
	double result=1,result1=0.1;
	double i,temp;
	if(n==0||j==1)
		return 1;
	else if(j==0)
		return 0;
	if(n>0)//指数大于零用乘 
	{
		for(i=0;i<n;i++) 
			result*=j;
	}
	else//小于零用处除 
	{
		temp=(-1)*n;
		for(i=0;i<temp;i++)
			result/=j;
	}
	return result;
}
double fabs(double x)//取绝对值 
{
	if(x<0)
		return -x;
	return x;
}
double K_sqrt(double x,double i)//开根号 
{
	double x1,y;
	x1=(i+x/i)/2.0;//利用牛顿迭代公式 
	if(fabs(x1-i)>=10e-15)
		y=K_sqrt(x,x1);
	else
		y=x1;
	return y; 
}
double Sqrt(double x)//开根号 
{
	return K_sqrt(x,1);
} 
double fac(int n)//阶乘 
{
	if(n>1)
		return n*fac(n-1);
	else
		return 1;	
}

double Sin(double x)//sin 
{
	double result=0,temp=0;
	int n=1,s=1;
	do{
		temp=Pow(x,n)/fac(n);//利用泰勒公式 
		result+=s*temp;
		n+=2;
		s*=-1;
	}while(1e-7<temp);
	return result;
}
double Cos(double x)//cos sinx=cos(pi/2-x)
{
	return Sin(PI/2-x);
}
double Tan(double x)//tan tanx=sinx/cosx
{
	double i,y;
	i=Sin(x);
	y=Cos(x);
	return i/y;
}
