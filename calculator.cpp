#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;
int Test(string my_print){
    auto len=my_print.size();
    int i=0;
    //记录括号输入正不正确
    int k=0;
    //while循环验证输入的值
while(i<len){
        if(!((my_print[i] >= '0' && my_print[i] <= '9')
             || my_print[i] == '+' || my_print[i] == '-' || my_print[i] == '*'
             || my_print[i] == '/'
             || my_print[i] == '.' || my_print[i] == '(' || my_print[i] == ')'))
        {
            cout<<"请输入0-9并且计算方式是+-*/！"<<endl;
            return false;
        }
        if(my_print[i] == '(')
            k++;
        else if(my_print[i] == ')'){
            k--;
            if(k<0)return 0;
        }
        i++;
}
if(k!=0){
        cout<<"括号输入错误！"<<endl;
        return 0;
}
    return 1;
}
string stringtoarr(const string str){
    int i=0,z=0,s,temp;
    float rate=10.0,itemp=0.0;
    float valueStr=0.0;
    float a[40];
    char b[20];
    for(i=0;i<40;i++)
        a[i]=0.0;                       
    for(i=0;i<20;i++)
        b[i]=' ';
        i=0;
    for(i=0;i<str[i];i++){
        if(str[i]>='0'&& str[i]<='9')
        {
            if(rate==10.0)
                itemp=itemp*rate+(str[i]-'0');
            else
            {
                itemp=itemp+rate*(str[i]-'0');
                rate=rate/10;
            }
        }
        else if(str[i]=='.')    rate=0.1;
        else if(str[i]=='+'){
            a[z]=itemp;itemp=0;
            z++;
            b[z]='+';
            z++;
            rate=10.0;
        }
        else if(str[i]=='-')
        {
            a[z]=itemp;itemp=0;
            z++;
            b[z]='-';
            z++;
            rate=10.0;
        }
        else if(str[i]=='*')
        {
            a[z]=itemp;itemp=0;
            b[z]='*';
            z++;
            rate=10.0;
        }
        else if(str[i]=='/')
        {
            a[z]=itemp;itemp=0;
            z++;
            b[z]='/';
            z++;
            rate=10.0;
        }
    }
    a[z]=itemp;
    s=z;
    for(i=0;i<=s;i++)
    {
        if(b[i]=='/')
        {
            a[i+1]=1/a[i+1];
            b[i]='*';
        }
    }
    for(i=0;i<=s;i++)
    {
        while(b[i]=='*')
        {
            a[i-1]=a[i-1]*a[i+1];
            for(temp=i+1;temp+2<40;temp++)
                a[temp]=a[temp+2];
            for(temp=i;temp+2<20;temp++)
                b[temp]=b[temp+2];
        }
    }
    valueStr=a[0];
    for(i=0;i<s;i++)
    {
        if(b[i]=='+')
            valueStr+=a[i+1];
        else if(b[i]=='-')
            valueStr-=a[i+1];
    }
    char svalue[16];
    sprintf(svalue,"%f" , valueStr);
    string ssavalue(svalue);
    return ssavalue;
}
string trims(const string &sub){
    string s1,s2,s3,sp,ss;
    int i;
    int counter=0;
    int left,right;
    if(auto pos1=sub.find(")")==string::npos)
        return sub;
    for(i=0;sub[i];i++)
        if(sub[i]=='(')
        {
            left=i;
            counter++;
            break;
        }
    for(i=left+1;sub[i];i++)
    {
        if(sub[i]=='(')
            counter++;
        else if(sub[i]==')')
            counter--;
        if(counter==0)
        {
            right=i;
            break;
        }
    }
    s1=sub.substr(0,left);
    sp=sub.substr(left+1,right-left-1);
    s2=stringtoarr(trims(sub.substr(left+1,right-left-1)));
    s3=trims(sub.substr(right+1));
    ss=s1+s2+s3;
    return ss;
}
void calcation(string &str1){
    int stTe;
    if((stTe=Test(str1))<=0){
        cout<<"输入字符串有误，请重新输入！！！"<<endl;
        return;
    }
    string sk=trims(str1);
    string ssk=stringtoarr(sk);
    cout<<ssk<<endl;
    cout<<"--------------------"<<endl;
}
int main()
{
    string input_str;
    int tsTest;
    while(1)
    {
        cout<<"请输入表达式(退出请输入小写exit):"<<endl;
        cin>>input_str;
        cout<<endl;
        if(input_str.compare("exit")==0)
            break;
        if((tsTest=Test(input_str))==1)
        {
            calcation(input_str);
        }
    }
    cout<<"Close this calculation！"<<endl;
    return 0;
}