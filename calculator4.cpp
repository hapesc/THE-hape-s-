#include<iostream>
#include<string>
#include<vector>
using namespace std;
#define MAXN 10000

class calculator
{
    public:
    calculator(){}
    calculator(const string&obj){
        expression=obj;
        len=obj.size();//修改的地方
        std::cout<<"calculator is ready"<<std::endl;
        int pos;
        for(int i=0;i<expression.size();i++)
        {
            if(expression[i]=='(')
            {
               parenthesesL[i]=i;
               pos=i;//记录左括号角标
            }else if(expression[i]==')')
            {
               parenthesesR[pos]=i;//记录pos位置左括号对应的右括号位置
            }
        }
    }
    void input(const string&obj)
    {
        expression=obj;
        len=obj.size();//修改的地方
        int pos=0;
        for(int i=0;i<expression.size();i++)
        {
            if(expression[i]=='(')
            {
               parenthesesL[++pos]=i;
               
            }else if(expression[i]==')')
            {
               parenthesesR[parenthesesL[pos]]=i;
               pos--;//记录pos位置左括号对应的右括号位置
            }
        }
    }
    double solve(int begin,int end);
    
    ~calculator(){}
    int len;
    private:
    
    string expression;
    int read(int s);//s是string的角标
    int read_pos=0;//记录每次读完数字后的角标
    int parenthesesL[MAXN];
    int parenthesesR[MAXN];
};
int calculator::read(int s)
{
    int num=0,f=1;
    if(expression[s]=='(')
    {
        num=this->solve(s+1,parenthesesR[s]-1);
        read_pos=parenthesesR[s]+1;
        return num;
    }else if(expression[s]=='-')
    {
        f=-1;
        s++;
    }
    for(;expression[s]>='0'&&expression[s]<='9';s++)
    {
        num=num*10+expression[s]-'0';
    }
    read_pos=s;//读完数字的角标+1
    return num*f;
}
double calculator::solve(int begin,int end)
{
    int top=-1;//记录栈顶位置
    double stack[2][MAXN];
    if(expression[begin]!='-')
        {
            top++;
            stack[0][top]=read(begin);
            stack[1][top]=1;//1代表+号
        }else if(expression[begin]=='-'){
            top++;
            stack[0][top]=read(begin+1);
            stack[1][top]=-1;//-1代表-号
            
        }
        begin=read_pos;
    
    while(begin<end){
        if(expression[begin]=='+')
        {
            top++;
            stack[0][top]=read(begin+1);
            stack[1][top]=1;//1代表+号
        }else if(expression[begin]=='-')
        {
            top++;
            stack[0][top]=read(begin+1);
            stack[1][top]=-1;//-1代表-号
            
        }else if(expression[begin]=='*')//遇到乘除号不入栈，直接与栈顶元素进行乘除
        {
            stack[0][top]*=read(begin+1);
        }else if(expression[begin]=='/')
        {
            stack[0][top]/=read(begin+1);
        }
        begin=read_pos;
    }//表达式读入栈
    double ans=0;
    for(int i=0;i<=top;i++){
        ans+=stack[0][i]*stack[1][i];
    }//计算结果
    return ans;
}

int main()
{
    string text;
    cin>>text;
    calculator c1;
    c1.input(text);
    cout<<c1.solve(0,c1.len-1)<<endl;
    return 0;
}