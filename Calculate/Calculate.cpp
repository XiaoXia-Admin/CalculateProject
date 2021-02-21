#include<MyMath.h> 
void menu()//�˵� 
{
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    printf ("\t\t\t\t\t%s", asctime(timeinfo) );//��ʾ��ǰʱ��
	printf ("\t\t\t*******************���ݽṹ�γ����*********************\n");
	printf ("\t\t\t*------------------------------------------------------*\n");
    printf ("\t\t\t*******************�����193�Ľ���**********************\n");
    printf ("\t\t\t--------------Welcome to My Calculator---------------\n");
    printf ("\t\t\t*                                                      *\n");
	printf ("\t\t\t*                   0.�˳�����ϵͳ                     *\n");
    printf ("\t\t\t*                   1.�����������ʽ		       *\n");
	printf ("\t\t\t*------------------------------------------------------*\n");
	printf ("\t\t\t*    ʹ��˵��(�ü�����Լ���+,-,*,/,ȡ��,tan,sin,cos   *\n");
	printf ("\t\t\t*             ��(����ĸ�����@����)^(������)������)    *\n");
    printf ("\t\t\t*------------------------------------------------------*\n");
    printf ("\t\t\t*  ---------Press key(0/1) to run program----------    *\n\n");
}
void IniteStack(Stack &s)//��ʼ��ջ 
{
	s.data=(char*)malloc(sizeof(char)*N);//��̬����ռ� 
	s.top=-1;
}
int StackFull(Stack s)//ջ�Ƿ��� 
{
	if(s.top==N-1)
		return 1;
	else
		return 0;
} 
int StackEmpty(Stack s)//ջ�Ƿ�Ϊ�� 
{
	if(s.top<0)
		return 1;
	else
		return 0;	
}
void InStack(Stack &s,char e)//��ջ 
{
	if(StackFull(s))
	{
		printf("ջ�Ѿ������޷���ջ\n");
		return ; 
	}
	else
	{
		s.top++;
		s.data[s.top]=e;
	}
} 
char PushStack(Stack &s)//��ջ 
{
	char x;
	if(StackEmpty(s))
	{
		printf("ջΪ���޷���ջ\n");
		return NULL;
	}
	else
	{
		x=s.data[s.top];
		s.top--;
		return x;	
	}
}
void Destroy(Stack &s)//����ջ
{
	free(s.data);//�ͷ�data�ռ�
	s.data=NULL; //��ֵΪ�շ�����Ұָ�� 
	s.top=0;
	printf("\n\t\t\tջ�Ѿ�������!!");
}
int Calculate(char *hou)//������׺���ʽ�����ؽ�� 
{
	int i,j,k,top=-1,flag,trans1,trans2,flag1=0,flag2=0;//topΪջ��,trans1,trans2����ȡ����ת���ã�flag1������special�Ƿ����ĸ,flag2�ǿ�ͷ�Ƿ�Ϊ��
	int len;//len��ʾ����С����֮ǰ�ĳ���
	double temp;//tempΪ��ʱ�������ڴ���Node�ṹ����
	char ch[N];//�Ȱ����ֵı��ʽ�Ž�ch[N]�У���ת��Ϊ���ִ���ṹ����
	char special[N];//�����ַ��ĸ�������(��cos,tan,sin)
	pNode data=(pNode)calloc(N,sizeof(Node));//�����ṹ���������,��callocֱ�ӳ�ʼ��
	for(i=0,k=0;hou[i]!='\0';i++)
	{	
		if((('0'<hou[i+1]&&hou[i+1]<'9')&&(hou[i]=='-')))//Ϊ�������Ϊ1
		{
			flag2=1;
			continue;
		}
		if(97<=hou[i]&&hou[i]<=122)//��ǰ��Ӣ����ĸ
		{
			special[k]=hou[i];
			k++;
			flag1=1;
			continue;
		}
		special[k]='\0';
		k=0;//��¼��Ӣ��֮��k=0,�ʹ���special��ʲôҲû���ˣ������´μ�¼ 
		if('0'<=hou[i]&&hou[i]<='9')//��ǰλ����
		{
			flag=0; 
			j=0;//��¼�ַ�������
			while(hou[i]!=' ')
			{
				if(hou[i]=='.')//�ж��Ƿ�ΪС�����ֿ�����
					flag=1;//��С��
				ch[j]=hou[i];//�����ִ���data[N]��
				i++;
				j++;
			}
			ch[j]='\0';//��ʾ�ַ���β��
			if(flag)
			{
				for(j=0;ch[j]!='.';j++)//��С����֮ǰ�ĳ���
					len=j;
				for(j=0,temp=0;ch[j]!='.';j++)//����С����֮ǰ�ĺ�
					temp+=(ch[j]-'0')*Pow(10,len-j);
				for(j=len+2;ch[j]!='\0';j++)//����С����֮��ĺ�
					temp+=(ch[j]-'0')*Pow(10,len-j+1);
				top++;
				data[top].data=temp;//�������������������ṹ��֮�� 
				data[top].flag=1;//�����1������Ϊ������ 
			}
			else//û��С����
			{
				for(j=0;ch[j]!='\0';j++)//��С����֮ǰ�ĳ���
					len=j;
				for(j=0,temp=0;ch[j]!='\0';j++)//����С����֮ǰ�ĺ�
					temp+=(ch[j]-'0')*Pow(10,len-j);
				top++;
				data[top].data=temp;
				data[top].flag=0; //����ǣ�����Ϊ���� 
			}
			if(flag2==1)//flag2Ϊ1˵�������Ϊ����
				data[top].data*=-1;//���ṹ���д���ĳ˸�һ 
			if(My_Strcmp(special,"cos")==0)//��� special����cos,sin,tan��ִ����Ӧ�ļ��㲢��flag1���Ϊ0�����´�special���ж� 
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
				printf("\n\t\t\t���ʽ����!!!!\n\n\t\t\t����ԭ��:tan,sin,cos���Ϸ�!\n");			
				return 0;
			}
			flag2=0;//������һ����֮�󣬸������ˢ�� 
		}
		else//���Ϊ�������ջ����������ջ������������������������ջ,��33/@4-(41.23+(tan(45)+cos(60)+son(30))^1)*(52%7)
		{
			switch(hou[i])//���ݲ�ͬ�������������Ӧ������,	

			{
				case '+'://���еļ��㶼���ǽṹ�����ջ��֮ǰ������ջ������������Ӧ����������㣬���Ҵ���top--�� 
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
						printf("\n\t\t\t���ʽ����!!!!\n\n\t\t\t����ԭ��:��������Ϊ0!\n");			
						return 0; 
					}
					temp=data[top-1].data;
					temp/=data[top].data;
					top--;
					data[top].data=temp;
					break;
				case '%':
					if(!data[top-1].flag&&!data[top].flag)//��%����ǰ�����flag����Ƿ�Ϊ0��������˵��Ϊ�����͵����򱨴� 
					{
						trans1=(int)data[top-1].data;
						trans2=(int)data[top].data;
					}
					else
					{
						printf("\n\t\t\t���ʽ����!!!!\n\n\t\t\t����ԭ��:ֻ����������ȡ��!\n");			
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
					if(data[top].data<0)//���ջ������С�������ܿ����� 
					{
						printf("\n\t\t\t���ʽ����!!!!\n\n\t\t\t����ԭ��:�������ܿ�����!\n");			
						return 0;
					}
					data[top].data=Sqrt(data[top].data);
					break;
				default:
					printf("\n\t\t\t���ʽ����!!!!\n\n\t\t\t����ԭ��:�зǷ��ַ����޷�ʶ����ַ�!\n");			
					return 0;
			}
		}
	}
	printf("\n\t\t\t���Ϊ:%lf",data[top].data);
	return 0;
}
int Transfer(char *zhong)//�����潲��׺���ʽת��Ϊ��׺���ʽ ����󷵻ؽ�� 
{
	Stack s;
	char hou[N];//��ź�׺���ʽ 
	int i,j,flag=0,length=0,length1=strlen(zhong);//��flag=1���������ջ�������������ж��Ƿ��������������Ԫ����������ִ���Ľ�׳��
	int spot;//������¼С����ĸ���
	int right=0,left=0;//������¼���������Ƿ�ƥ��
	IniteStack(s);
	for(i=0,j=0;i<length1;i++)
	{
		if(97<=zhong[i]&&zhong[i]<=122)//���Ϊa��z֮��ֱ�Ӵ����׺���ʽ�У���ʱ������ 
		{
			hou[j]=zhong[i];
			j++;
			continue;
		}
		if(i==0&&zhong[i]=='-')//�����ͷΪ���ţ�ֱ�Ӵ��� 
		{
			hou[j]=zhong[i];
			j++;
			continue;
		}
		if((('0'<zhong[i+1]&&zhong[i+1]<'9')&&zhong[i]=='-'&&zhong[i-1]=='(')||(('0'<zhong[i+1]&&zhong[i+1]<'9')&&zhong[i]=='-'&&zhong[i-1]=='@'))//���iΪ����i-1Ϊ(,i+1Ϊ����Ҳֱ�Ӵ����׺���ʽ�У�����Ҳ��һ���ġ� 
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
				for(spot=0;(zhong[i]<='9'&&'0'<=zhong[i])||zhong[i]=='.';i++,j++)//���Ϊ���ֻ�С����Ž���׺���ʽ�����У�����ͳ��С�������
				{
					hou[j]=zhong[i];
					if(zhong[i]=='.')
						spot++;
				}
				i--;
				if(spot>1)//����С���㱨��
				{
					printf("\n\t\t\t��ʾ�Ǵ���!!!\n\n\t\t\t����ԭ��:���ʽ������������С����\n");
					return 0;
				}
				hou[j]=' ';//�ÿո�ֿ�������
				j++;
				flag=1;//Ŀǰ������
				break;
			case '(':
				if(flag)
				{
					printf("\n\t\t\t��ʾ�Ǵ���!!!\n\n\t\t\t����ԭ��:���ֺ���ֱ�Ӹ�����\n");
					return 0;
				}
				InStack(s,zhong[i]);
				left++;//�����ż�һ
				break;
			case ')':
				right++;//�����ż�һ
				while(s.data[s.top]!='(')//������Ϊ������ȼ������Ե���������֮�ϵ���������� 
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
					printf("\n\t\t\t��ʾ�Ǵ���!!!\n\n\t\t\t����ԭ��:hh�������������������֮��û������\n");
					return 0;
				}
				while(!StackEmpty(s)&&s.data[s.top]!='(')//��Ϊ+-ֻ��(������ֻҪ��Ϊ�����ţ�������ֱ�ӽ����׺���ʽ�� �����˷�������ջ
				{

					hou[j]=PushStack(s);
					j++;
				}
				InStack(s,zhong[i]);
				flag=0;//��ʱ��׺���ʽ����Ѿ���������ˢ�±��
				break;
			case '*':
			case '/':
			case '%':
				if(!flag&&i!=0)
				{
					printf("\n\t\t\t��ʾ�Ǵ���!!!\n\n\t\t\t����ԭ��:�������������������֮��û������\n");
					return 0;
				}
				while(!StackEmpty(s)&&(s.data[s.top]=='*'||s.data[s.top]=='/'||s.data[s.top]=='%'||s.data[s.top]=='@'||s.data[s.top]=='^'))//*��/,%ֻ��+-���ȼ��ߣ�����ֻ�б����Ǹߵĺͱ�����Ե�ջ������֮����ջ
				{
					hou[j]=PushStack(s);
					j++;
				}
				InStack(s,zhong[i]);
				flag=0;
				break;
			case '^':
			case '@':
				if(!flag&&i!=0&&zhong[i]!='@')//���ֺ����Ǹ���û��
				{
					printf("\n\t\t\t��ʾ�Ǵ���!!!\n\n\t\t\t����ԭ��:�������������������֮��û������\n");
					return 0;
				}
				while(!StackEmpty(s)&&(s.data[s.top]=='^'||s.data[s.top]=='@'))//û�б�@,^���ȼ����ߵģ�����ֻ������@,^�ŵ�ջ������֮����ջ
				{
					hou[j]=PushStack(s);
					j++;
				}
				InStack(s,zhong[i]);
				flag=0;
				break;
			default:
				printf("\n\t\t\t���ʽ����!!!!\n\n\t\t\t����ԭ��:�зǷ��ַ����޷�ʶ����ַ�!\n");			
				return 0;
		}
	}
	if(left!=right)//�������Ų���ȱ���
	{
		printf("\n\t\t\t���ʽ����!!!!\n\n\t\t\t����ԭ��:�������Ų�ƥ��!\n");			
		return 0;
	}
	while(!StackEmpty(s))//���ջ�е�Ԫ��ȫ������
	{
		hou[j]=PushStack(s);
		j++;
	}
	hou[j]='\0';//����׺���ʽ��\0��β
	Calculate(hou);
	Destroy(s); 
	return 0;
}
void main()
{
    char zhong[N]; //zhongΪ��׺���ʽ
    char ch[N];//���ڽ������ѡ�� 
    while(1)
    {
		system("color 0B");//������ɫ 
    	menu();
    	printf("\t\t\t��������Ҫ�Ĺ���:");
    	scanf("%s",ch);
		if(My_Strcmp(ch,"1")==0)//1Ϊ���м��� 
		{
			printf("\n\t\t\t������Ҫ������������ʽ:");
			scanf("%s",zhong); 
			Transfer(zhong);
		}
		else if(My_Strcmp(ch,"0")==0)//0�˳� 
		{
			printf("\n\t\t\t��ӭ�´�ʹ��");
			return;
		}
		else//����0��1�ͱ��� 
			printf("\n\t\t\tѡ�������������������\n");
		system("pause");
		system("cls");
	}
}
