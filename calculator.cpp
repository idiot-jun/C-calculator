#include"iostream"
#include "stack"
#include <cctype>
#include "math.h"
using namespace std;
//判断优先级
bool priority_one(char one_char) {
    if(one_char=='+'||one_char=='-'){
        return true;
    }else{
        return false;
    }
}
bool priority_two(char two_char)
{
    if(two_char=='*'||two_char=='/'){
        return true;
    }else{
        return false;
    }
}
//修改为后缀表达式
void calculator_postfix(string &my_input) {
    stack<char>stack;
    string result;
    for (int i = 0; i < my_input.size(); i++)
    {
        if (isdigit(my_input[i]) || my_input[i] == '.')
        {
            while (isdigit(my_input[i]) || my_input[i] == '.')
            {
                //这里使用i++主要是为了后面计算两位数以上的数字。
                result += my_input[i++];
            }
            //通过i--让i的值回到以前的值。
            i--;
            result += ' ';
        }
        else if (priority_one(my_input[i])) {
            while (stack.size() && (priority_one(stack.top()) || priority_two(stack.top()))) {
                result += stack.top();
                stack.pop();
            }
            stack.push(my_input[i]);
        }
        else if (my_input[i] == ')') {
            while (stack.top() != '(') {
                result += stack.top();
                stack.pop();
            }
            stack.pop();
        }
        else if (priority_two(my_input[i])) {
            //读到二级运算符
            while (stack.size() && priority_two(stack.top()))
            {
                result += stack.top();
                stack.pop();
            }
            stack.push(my_input[i]);//压入二级运算符
        }
        else
            stack.push(my_input[i]);
    }
    while (stack.size())
    {
        result += stack.top();
        stack.pop();
    }
    my_input=result;
}
//实现了大于9以及小数的计算
double double_digit(string s) {
    double result=0;
    double point_num=0;
    int index=0;
    int length=s.size();
    string left_stu;
    string right_stu;
    for(int i=0;i<length;i++){
        if(s[i]!='.'){
            result=result*10+s[i]-'0';
        }else{
            index=i;
            left_stu=s.substr(0,index-1);
            right_stu=s.substr(index+1,length-i-i);
            for(auto i:left_stu){
                result=result*10+i-'0';
            }
            for(auto i:right_stu){
                point_num=point_num*10+i-'0';
            }
            double num=point_num/pow(10,right_stu.size());
            result=result+num;
            return result;
        }
    }
    return result;
}
double Calculate(string my_input) {
    double res ,t;
    //数字的栈
    stack<double>val_num;
    string temp;
    for (int i = 0; i < my_input.size(); i++) {
        temp = "";
        if (isdigit(my_input[i]) || my_input[i] == '.') {
            while (isdigit(my_input[i]) || my_input[i] == '.') {
                temp += my_input[i++];
            }
            val_num.push(double_digit(temp));
        }
        else {
            switch (my_input[i])
            {
                case '+':
                    t = val_num.top();
                    val_num.pop();
                    t += val_num.top();
                    val_num.pop();
                    val_num.push(t);
                    break;
                case '-':
                    t = val_num.top();
                    val_num.pop();
                    t= val_num.top() - t;
                    val_num.pop();
                    val_num.push(t);
                    break;
                case '*':
                    t = val_num.top();
                    val_num.pop();
                    t *= val_num.top();
                    val_num.pop();
                    val_num.push(t);
                    break;
                case '/':
                    t = val_num.top();
                    val_num.pop();
                    t= val_num.top() / t;
                    val_num.pop();
                    val_num.push(t);
                    break;
                default:
                    cerr << "运算错误" << endl;
                    break;
            }
        }
    }
    res = val_num.top();
    return res;
}
int main() {
    string my_input, result;
    while(true) {
        cout << "输入表达式：" << endl;
        cin >> my_input;
        if(my_input=="exit"){
            break;
        }
        calculator_postfix(my_input);
        cout << "运算结果：" << Calculate(my_input) << endl;
    }
    return 0;
}