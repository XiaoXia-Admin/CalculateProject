#include<MyMath.h> 
void menu()//菜单 
{
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    printf ("\t\t\t\t\t%s", asctime(timeinfo) );//显示当前时间
	printf ("\t\t\t*******************数据结构课程设计*********************\n");
	printf ("\t\t\t*------------------------------------------------------*\n");
    printf ("\t\t\t*******************计算机193夏金宇**********************\n");
    printf ("\t\t\t--------------Welcome to My Calculator---------------\n");
    printf ("\t\t\t*                                                      *\n");
	printf ("\t\t\t*                   0.退出管理系统                     *\n");
    printf ("\t\t\t*                   1.计算算数表达式		       *\n");
	printf ("\t\t\t*------------------------------------------------------*\n");
	printf ("\t\t\t*    使用说明(该计算可以计算+,-,*,/,取余,tan,sin,cos   *\n");
	printf ("\t\t\t*             √(这里的根号用@代替)^(幂运算)，负数)    *\n");
    printf ("\t\t\t*------------------------------------------------------*\n");
    printf ("\t\t\t*  ---------Press key(0/1) to run program----------    *\n\n");
}
void IniteStack(Stack &s)//初始化栈 
{
	s.data=(char*)malloc(sizeof(char)*N);//动态申请空间 
	s.top=-1;
}
int StackFull(Stack s)//栈是否满 
{
	if(s.top==N-1)
		return 1;
	else
		return 0;
} 
int StackEmpty(Stack s)//栈是否为空 
{
	if(s.top<0)
		return 1;
	else
		return 0;	
}
void InStack(Stack &s,char e)//入栈 
{
	if(StackFull(s))
	{
		printf("栈已经满了无法入栈\n");
		return ; 
	}
	else
	{
		s.top++;
		s.data[s.top]=e;
	}
} 
char PushStack(Stack &s)//弹栈 
{
	char x;
	if(StackEmpty(s))
	{
		printf("栈为空无法弹栈\n");
		return NULL;
	}
	else
	{
		x=s.data[s.top];
		s.top--;
		return x;	
	}
}
void Destroy(Stack &s)//销毁栈
{
	free(s.data);//释放data空间
	s.data=NULL; //赋值为空放置是野指针 
	s.top=0;
	printf("\n\t\t\t栈已经被销毁!!");
}
int Calculate(char *hou)//计算中缀表达式，返回结果 
{
	int i,j,k,top=-1,flag,trans1,trans2,flag1=0,flag2=0;//top为栈顶,trans1,trans2用来取余是转换用，flag1用来记special是否存字母,flag2记开头是否为负
	int len;//len表示数字小数点之前的长度
	double temp;//temp为临时变量，在存入Node结构体中
	char ch[N];//先把数字的表达式放进ch[N]中，在转化为数字存入结构体中
	char special[N];//特殊字符的辅助数组(像cos,tan,sin)
	pNode data=(pNode)calloc(N,sizeof(Node));//创建结构体数组放数,用calloc直接初始化
	for(i=0,k=0;hou[i]!='\0';i++)
	{	
		if((('0'<hou[i+1]&&hou[i+1]<'9')&&(hou[i]=='-')))//为负数标记为1
		{
			flag2=1;
			continue;
		}
		if(97<=hou[i]&&hou[i]<=122)//当前是英文字母
		{
			special[k]=hou[i];
			k++;
			flag1=1;
			continue;
		}
		special[k]='\0';
		k=0;//记录完英文之后，k=0,就代表special里什么也没有了，方便下次记录 
		if('0'<=hou[i]&&hou[i]<='9')//当前位数字
		{
			flag=0; 
			j=0;//记录字符串长度
			while(hou[i]!=' ')
			{
				if(hou[i]=='.')//判断是否为小数，分开讨论
					flag=1;//有小数
				ch[j]=hou[i];//将数字存入data[N]中
				i++;
				j++;
			}
			ch[j]='\0';//表示字符串尾部
			if(flag)
			{
				for(j=0;ch[j]!='.';j++)//找小数点之前的长度
					len=j;
				for(j=0,temp=0;ch[j]!='.';j++)//计算小数点之前的和
					temp+=(ch[j]-'0')*Pow(10,len-j);
				for(j=len+2;ch[j]!='\0';j++)//计算小数点之后的和
					temp+=(ch[j]-'0')*Pow(10,len-j+1);
				top++;
				data[top].data=temp;//将辅助变量里的数放入结构体之中 
				data[top].flag=1;//并标记1，该数为浮点型 
			}
			else//没有小数点
			{
				for(j=0;ch[j]!='\0';j++)//找小数点之前的长度
					len=j;
				for(j=0,temp=0;ch[j]!='\0';j++)//计算小数点之前的和
					temp+=(ch[j]-'0')*Pow(10,len-j);
				top++;
				data[top].data=temp;
				data[top].flag=0; //并标记，该数为整型 
			}
			if(flag2==1)//flag2为1说明这个数为负数
				data[top].data*=-1;//将结构体中存入的乘负一 
			if(My_Strcmp(special,"cos")==0)//如果 special里是cos,sin,tan将执行相应的计算并且flag1标记为0方便下次special的判断 
			{
				data[top].data=Cos(data[top].data*PI/180);
				flag1=0;
			}
			else if(My_Strcmp(special,"sin")==0)
			{
				data[top].data=Sin(data[top].data*PI/180);
				flag1=0;
			}
			else if(My_Strcmp(special,"tan")==0)
			{
				data[top].data=Tan(data[top].data*PI/180);
				flag1=0;
			}
			else if(flag1)
			{
				printf("\n\t\t\t表达式错误!!!!\n\n\t\t\t错误原因:tan,sin,cos不合法!\n");			
				return 0;
			}
			flag2=0;//在算完一个数之后，负数标记刷新 
		}
		else//如果为运算符，栈顶两个数出栈，并把这两个数的运算结果入栈,，33/@4-(41.23+(tan(45)+cos(60)+son(30))^1)*(52%7)
		{
			switch(hou[i])//根据不同的运算符进行相应的运算,	

			{
				case '+'://下列的计算都是那结构体里的栈顶之前的数和栈顶的数进行相应的运算符计算，并且存入top--中 
					temp=data[top-1].data;
					temp+=data[top].data;
					top--;
					data[top].data=temp;
					break;
				case '-':
					temp=data[top-1].data;
					temp-=data[top].data;
					top--;
					data[top].data=temp;
					break;
				case '*':
					temp=data[top-1].data;
					temp*=data[top].data;
					top--;
					data[top].data=temp;
					break;
				case '/':
					if(data[top].data==0)
					{
						printf("\n\t\t\t表达式错误!!!!\n\n\t\t\t错误原因:除数不能为0!\n");			
						return 0; 
					}
					temp=data[top-1].data;
					temp/=data[top].data;
					top--;
					data[top].data=temp;
					break;
				case '%':
					if(!data[top-1].flag&&!data[top].flag)//看%符号前后的数flag标记是否为0，不是零说明为浮点型的数则报错 
					{
						trans1=(int)data[top-1].data;
						trans2=(int)data[top].data;
					}
					else
					{
						printf("\n\t\t\t表达式错误!!!!\n\n\t\t\t错误原因:只有整数可以取余!\n");			
						return 0;
					}
					trans1%=trans2;
					top--;
					data[top].data=(double)trans1;
					break;
				case '^':
					temp=data[top-1].data;
					temp=Pow(temp,data[top].data);
					top--;
					data[top].data=temp;
					break;
				case '@':
					if(data[top].data<0)//如果栈顶的数小于零则不能开根号 
					{
						printf("\n\t\t\t表达式错误!!!!\n\n\t\t\t错误原因:负数不能开根号!\n");			
						return 0;
					}
					data[top].data=Sqrt(data[top].data);
					break;
				default:
					printf("\n\t\t\t表达式错误!!!!\n\n\t\t\t错误原因:有非法字符，无法识别该字符!\n");			
					return 0;
			}
		}
	}
	printf("\n\t\t\t结果为:%lf",data[top].data);
	return 0;
}
int Transfer(char *zhong)//在里面讲中缀表达式转换为后缀表达式 ，最后返回结果 
{
	Stack s;
	char hou[N];//存放后缀表达式 
	int i,j,flag=0,length=0,length1=strlen(zhong);//用flag=1来标记现在栈顶是数，用来判断是否出现两个连续的元素算符来保持代码的健壮性
	int spot;//用来记录小数点的个数
	int right=0,left=0;//用来记录左右括号是否匹配
	IniteStack(s);
	for(i=0,j=0;i<length1;i++)
	{
		if(97<=zhong[i]&&zhong[i]<=122)//如果为a到z之间直接存入后缀表达式中，到时候先算 
		{
			hou[j]=zhong[i];
			j++;
			continue;
		}
		if(i==0&&zhong[i]=='-')//如果开头为负号，直接存入 
		{
			hou[j]=zhong[i];
			j++;
			continue;
		}
		if((('0'<zhong[i+1]&&zhong[i+1]<'9')&&zhong[i]=='-'&&zhong[i-1]=='(')||(('0'<zhong[i+1]&&zhong[i+1]<'9')&&zhong[i]=='-'&&zhong[i-1]=='@'))//如果i为负号i-1为(,i+1为数字也直接存入后缀表达式中，根号也是一样的。 
		{
			hou[j]=zhong[i];
			j++;
			continue;
		}
		switch(zhong[i])
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				for(spot=0;(zhong[i]<='9'&&'0'<=zhong[i])||zhong[i]=='.';i++,j++)//如果为数字或小数点放进后缀表达式数组中，并且统计小数点个数
				{
					hou[j]=zhong[i];
					if(zhong[i]=='.')
						spot++;
				}
				i--;
				if(spot>1)//两个小数点报错
				{
					printf("\n\t\t\t表示是错误!!!\n\n\t\t\t错误原因:表达式中数字有两个小数点\n");
					return 0;
				}
				hou[j]=' ';//用空格分开两个数
				j++;
				flag=1;//目前是数字
				break;
			case '(':
				if(flag)
				{
					printf("\n\t\t\t表示是错误!!!\n\n\t\t\t错误原因:数字后面直接跟括号\n");
					return 0;
				}
				InStack(s,zhong[i]);
				left++;//左括号加一
				break;
			case ')':
				right++;//有括号加一
				while(s.data[s.top]!='(')//有括号为最高优先级，所以弹出左括号之上的所有运算符 
				{
					hou[j]=PushStack(s);
					j++;
				}
				PushStack(s);
				break;
			case '+':
			case '-':
				if(!flag&&i!=0&&zhong[i-1]!='('&&zhong[i-1]!='@')
				{
					printf("\n\t\t\t表示是错误!!!\n\n\t\t\t错误原因:hh存在两个连续的运算符之间没有数字\n");
					return 0;
				}
				while(!StackEmpty(s)&&s.data[s.top]!='(')//因为+-只比(高所以只要不为左括号，都可以直接进入后缀表达式中 ，最后此符号在入栈
				{

					hou[j]=PushStack(s);
					j++;
				}
				InStack(s,zhong[i]);
				flag=0;//此时后缀表达式最顶部已经不是数了刷新标记
				break;
			case '*':
			case '/':
			case '%':
				if(!flag&&i!=0)
				{
					printf("\n\t\t\t表示是错误!!!\n\n\t\t\t错误原因:存在两个连续的运算符之间没有数字\n");
					return 0;
				}
				while(!StackEmpty(s)&&(s.data[s.top]=='*'||s.data[s.top]=='/'||s.data[s.top]=='%'||s.data[s.top]=='@'||s.data[s.top]=='^'))//*，/,%只比+-优先级高，所以只有比他们高的和本身可以弹栈，除此之外入栈
				{
					hou[j]=PushStack(s);
					j++;
				}
				InStack(s,zhong[i]);
				flag=0;
				break;
			case '^':
			case '@':
				if(!flag&&i!=0&&zhong[i]!='@')//数字后面是根号没事
				{
					printf("\n\t\t\t表示是错误!!!\n\n\t\t\t错误原因:存在两个连续的运算符之间没有数字\n");
					return 0;
				}
				while(!StackEmpty(s)&&(s.data[s.top]=='^'||s.data[s.top]=='@'))//没有比@,^优先级还高的，所以只有遇到@,^才弹栈，除此之外入栈
				{
					hou[j]=PushStack(s);
					j++;
				}
				InStack(s,zhong[i]);
				flag=0;
				break;
			default:
				printf("\n\t\t\t表达式错误!!!!\n\n\t\t\t错误原因:有非法字符，无法识别该字符!\n");			
				return 0;
		}
	}
	if(left!=right)//左右括号不相等报错
	{
		printf("\n\t\t\t表达式错误!!!!\n\n\t\t\t错误原因:左右括号不匹配!\n");			
		return 0;
	}
	while(!StackEmpty(s))//最后将栈中的元素全部弹出
	{
		hou[j]=PushStack(s);
		j++;
	}
	hou[j]='\0';//给后缀表达式以\0结尾
	Calculate(hou);
	Destroy(s); 
	return 0;
}
void main()
{
    char zhong[N]; //zhong为中缀表达式
    char ch[N];//用于接收输的选项 
    while(1)
    {
		system("color 0B");//字体颜色 
    	menu();
    	printf("\t\t\t请输入你要的功能:");
    	scanf("%s",ch);
		if(My_Strcmp(ch,"1")==0)//1为进行计算 
		{
			printf("\n\t\t\t请输入要计算的算数表达式:");
			scanf("%s",zhong); 
			Transfer(zhong);
		}
		else if(My_Strcmp(ch,"0")==0)//0退出 
		{
			printf("\n\t\t\t欢迎下次使用");
			return;
		}
		else//不是0或1就报错 
			printf("\n\t\t\t选项输入错误请重新输入\n");
		system("pause");
		system("cls");
	}
}
