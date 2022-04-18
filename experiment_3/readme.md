源代码在demo文件夹中~
# 一.	实验目的
将非后缀式用来表示的算术表达式转换为用逆波兰式来表示的算术表达式，并计算用逆波兰式来表示的算术表达式的值。

# 二.	实验内容及要求
将非后缀式用来表示的算术表达式转换为用逆波兰式来表示的算术表达式，并计算用逆波兰式来表示的算术表达式的值。
程序输入/输出示例：
输出的格式如下：
(1)逆波兰式的生成及计算程序，编制人：姓名，学号，班级
(2)输入一以#结束的中缀表达式(包括+—*/（）数字#)：在此位置输入符号串如(28+68)*2#
(3)逆波兰式为：28&68+2*
(4)逆波兰式28&68+2*计算结果为192
> 备注：\
（1） 在生成的逆波兰式中如果两个数相连则用&分隔，如28和68，中间用&分隔\
（2）在此位置输入符号串为用户自行输入的符号串。

## 注意
1. 表达式中允许使用运算符（+-*/）、分割符（括号）、数字，结束符#
2. 如果遇到错误的表达式，应输出错误提示信息（该信息越详细越好）
3. 对学有余力的同学，测试用的表达式事先放在文本文件中，一行存放一个表达式，同时以分号分割。同时将预期的输出结果写在另一个文本文件中，以便和输出进行对照

# 三.	实验过程

## 1、功能描述
读取文件exp.txt中每一行表达式，输出其逆波兰表达式以及根据逆波兰表达式求值。
## 2、采用的数据结构

```cpp
class ReversePolishExp {
    private:
        int len;
        string exp;
        vector<string> postfixExp;
        stack<string> s;
    public:
        ReversePolishExp(string exp) {
            this->exp = exp;
            this->len = exp.length();
            this->postfixExp = getPostfixExp(exp);
        }
        // 判断是否为数字
        bool isDigit(char c) {
            return c >= '0' && c <= '9';
        }
        // 判断是否为+-*/
        bool isOperate(char c) {
            return op.find(c) != string::npos;
        }
        // 将字符串转换为整数
        int s2i(string s) {
            int res = 0;
            for (auto i : s)
                res = res * 10 + (i - '0');
            return res;
        }
        // 读入一个完整的整数。
        string readNum(string exp, int& idx) {
            string res = "";
            while(idx < len && isDigit(exp[idx])) {
                res += exp[idx];
                idx++;
            }
            --idx;
            return res;
        }
        // 根据中缀计算后缀表达式
        vector<string> getPostfixExp(string exp) {
            vector<string> res;
            for(int i = 0; i < len; ++i) {
                char nowChar = exp[i];
                if(isDigit(nowChar)) { 
                    res.push_back(readNum(exp, i));
                } else if(isOperate(nowChar)) { 
                    string temp = string(1, nowChar);
                    if(opMap[temp] == 1) {  // + -
                        while(!s.empty() && s.top() != "(") {
                            res.push_back(s.top());
                            s.pop();
                        }
                    } else {    // * /
                        while(!s.empty() && (s.top() == "*" || s.top() == "/")) {
                            res.push_back(s.top());
                            s.pop();
                        }
                    }
                    s.push(temp);
                } else if(nowChar == '(') {  
                    s.push("(");
                } else if(nowChar == ')') {  
                    while(!s.empty() && s.top() != "(") {
                        res.push_back(s.top());
                        s.pop();
                    }
                    s.pop();    
                }
            }
            while(!s.empty()) { 
                res.push_back(s.top());
                s.pop();
            }
            return res;
        }
        // 计算后缀表达式的值
        double compute() {
            stack<double> s2;
            for(auto item: postfixExp) {
                if(isDigit(item[0])) {  // 是数字的话 直接入栈
                    s2.push(s2i(item)*1.0);
                } else {
                    double b = s2.top();
                    s2.pop();
                    double a = s2.top();
                    s2.pop();
                    switch(item[0]) {
                        case '+': s2.push(a + b); break;
                        case '-': s2.push(a - b); break;
                        case '*': s2.push(a * b); break;
                        case '/': 
                            if(b == 0) {
                                cout << "Error: denominator is 0!" << endl;
                                return Error;
                            }
                            s2.push(a / b); 
                            break;
                    }
                }
            }
            return s2.top();
        }
        void printPostfixExp() {
            if(this->postfixExp.empty()) {
                cout << "postfixExp is empty" << endl;
                return;
            }
            cout << "输出的逆波兰表达式为: ";
            for (auto i : this->postfixExp)
                cout << i << " ";
            cout << endl;
        }
        void printExp() {
            if(this->exp.empty()) {
                cout << "exp is empty" << endl;
                return;
            }
            cout << "输入的中缀表达式为: " << this->exp << endl;
        }
};
```
## 3、头文件声明和全局变量定义
如下。
```cpp
/*
 * @Author: cos
 * @Date: 2022-04-18 00:46:57
 * @LastEditTime: 2022-04-18 20:40:38
 * @LastEditors: cos
 * @Description: 编译原理实验三 逆波兰表达式计算及求值
 * @FilePath: \CompileTheory\experiment_3\demo\main.cpp
 */
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <fstream>
using namespace std;
const int Error = -1;
const string ExpFileName = "./exp.txt";
const string existChars = "+-*/()0123456789";
const string op = "+-*/"; 
map <string, int> opMap = {
    {"+", 1},
    {"-", 1},
    {"*", 2},
    {"/", 2},
};
```
## 4、函数汇总

### （1）函数汇总表

| 函数名称            | 功能简述                        |
| --------------- | --------------------------- |
| `readFile`        | 读取文件函数，返回一个string动态数组，以行数分割 |
| `isValid`         | 判断表达式是否有效（只能包含`+-* /()数字`）    |
| `isDigit`         | 判断字符是否为数字                   |
| `isOperate`       | 判断是否为 + - * /                  |
| `s2i`             | 字符串转数字                      |
| `readNum`         | 读取连续的数字构成整数返回               |
| `getPostfixExp`   | 中缀表达式转逆波兰表达式                |
| `compute`         | 计算逆波兰表达式的值                  |
| `printExp`        | 输出中缀表达式                     |
| `printPostfixExp` | 输出逆波兰表达式

### （2）函数的调用关系
![function3.drawio.png](https://p1-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/e6c67d4e323742a9b2c0c5a9569d01b4~tplv-k3u1fbpfcp-watermark.image?)
### （3）流程图
![main.drawio.png](https://p9-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/772d9329232c42eab2ae9f3ec1760db8~tplv-k3u1fbpfcp-watermark.image?)
## 5、实验结果
### 输入
exp.txt
```txt
(28+68)*2
(12-10+10*2)/2
32+12/(42-4*10)
12/0+12
(1+1)+1)
hauihd1@!
```
### 输出
```
读取的文件名为：./exp.txt

------------------样例1: (28+68)*2--------------------
第1行输入的表达式合法，开始计算
输入的中缀表达式为: (28+68)*2
第2行输入的表达式合法，开始计算
输入的中缀表达式为: (12-10+10*2)/2
输出的逆波兰表达式为: 12 10 - 10 2 * + 2 /
./../x86_64-w64-mingw32/lib/../lib/libmingw32.a(lib64_libmingw32_a-crt0_c.o):crt0_c.c:(.text+0x46): undefined reference to `WinMain'
collect2.exe: error: ld returned 1 exit status
PS C:\Users\34504\OneDrive - nahcox\Programming\CS\CompileTheory\experiment_3\demo> cd "c:\Users\34504\OneDrive - nahcox\Programming\CS\CompileTheory\experiment_3\demo\" ; if ($?) { g++ main.cpp -o main } ; if ($?) { .\main }
逆波兰式的生成及计算程序，编制人： 201916010728 余思娴 计科F1901班
读取的文件名为：./exp.txt

------------------样例1: (28+68)*2--------------------
第1行输入的表达式合法，开始计算
输入的中缀表达式为: (28+68)*2
输出的逆波兰表达式为: 28 68 + 2 * 
该逆波兰表达式的计算值为：192

------------------样例2: (12-10+10*2)/2--------------------
第2行输入的表达式合法，开始计算
输入的中缀表达式为: (12-10+10*2)/2
输出的逆波兰表达式为: 12 10 - 10 2 * + 2 / 
该逆波兰表达式的计算值为：11

------------------样例3: 32+12/(42-4*10)--------------------
第3行输入的表达式合法，开始计算
输入的中缀表达式为: 32+12/(42-4*10)
输出的逆波兰表达式为: 32 12 42 4 10 * - / + 
该逆波兰表达式的计算值为：38

------------------样例4: 12/0+12--------------------
第4行输入的表达式合法，开始计算
输入的中缀表达式为: 12/0+12
输出的逆波兰表达式为: 12 0 / 12 +
该逆波兰表达式的计算值为：Error: denominator is 0!
-1

------------------样例5: (1+1)+1)--------------------
Error: ) without (!

------------------样例6: hauihd1@!--------------------
Error:输入的表达式不合法（只能包含+—*/()数字）!
```

# 完整代码
```cpp
/*
 * @Author: cos
 * @Date: 2022-04-18 00:46:57
 * @LastEditTime: 2022-04-18 20:40:38
 * @LastEditors: cos
 * @Description: 编译原理实验三 逆波兰表达式计算及求值
 * @FilePath: \CompileTheory\experiment_3\demo\main.cpp
 */
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <fstream>
using namespace std;
const int Error = -1;
const string ExpFileName = "./exp.txt";
const string existChars = "+-*/()0123456789";
const string op = "+-*/"; 
map <string, int> opMap = {
    {"+", 1},
    {"-", 1},
    {"*", 2},
    {"/", 2},
};
// 读文件
vector<string> readFile(string fileName) {
    vector<string> res;
    try {
        ifstream fin;
        fin.open(fileName);
        string temp;
        while (getline(fin, temp))
            res.push_back(temp);
        return res;
    } catch(const exception& e) {
        cerr << e.what() << '\n';
        return res;
    }
}

bool isValid(string exp) {
    if(exp.find_first_not_of(existChars) != string::npos){
        cout << "Error:输入的表达式不合法（只能包含+—*/()数字）!" << endl;
        return false;
    }
    stack<char> s;  // ()???
    for (auto i : exp) {
        if(i == '(')
            s.push(i);
        else if(i == ')') {
            if(s.empty()){
                cout << "Error: ) without (!\n";
                return false;
            }
            s.pop();
        }
    }
    return true;
}
class ReversePolishExp {
    private:
        int len;
        string exp;
        vector<string> postfixExp;
        stack<string> s;
    public:
        ReversePolishExp(string exp) {
            this->exp = exp;
            this->len = exp.length();
            this->postfixExp = getPostfixExp(exp);
        }
        // 判断是否为数字
        bool isDigit(char c) {
            return c >= '0' && c <= '9';
        }
        // 判断是否为+-*/
        bool isOperate(char c) {
            return op.find(c) != string::npos;
        }
        // 将字符串转换为整数
        int s2i(string s) {
            int res = 0;
            for (auto i : s)
                res = res * 10 + (i - '0');
            return res;
        }
        // 读入一个完整的整数。
        string readNum(string exp, int& idx) {
            string res = "";
            while(idx < len && isDigit(exp[idx])) {
                res += exp[idx];
                idx++;
            }
            --idx;
            return res;
        }
        // 根据中缀计算后缀表达式
        vector<string> getPostfixExp(string exp) {
            vector<string> res;
            for(int i = 0; i < len; ++i) {
                char nowChar = exp[i];
                if(isDigit(nowChar)) { 
                    res.push_back(readNum(exp, i));
                } else if(isOperate(nowChar)) { 
                    string temp = string(1, nowChar);
                    if(opMap[temp] == 1) {  // + -
                        while(!s.empty() && s.top() != "(") {
                            res.push_back(s.top());
                            s.pop();
                        }
                    } else {    // * /
                        while(!s.empty() && (s.top() == "*" || s.top() == "/")) {
                            res.push_back(s.top());
                            s.pop();
                        }
                    }
                    s.push(temp);
                } else if(nowChar == '(') {  
                    s.push("(");
                } else if(nowChar == ')') {  
                    while(!s.empty() && s.top() != "(") {
                        res.push_back(s.top());
                        s.pop();
                    }
                    s.pop();    
                }
            }
            while(!s.empty()) { 
                res.push_back(s.top());
                s.pop();
            }
            return res;
        }
        // 计算后缀表达式的值
        double compute() {
            stack<double> s2;
            for(auto item: postfixExp) {
                if(isDigit(item[0])) {  // 是数字的话 直接入栈
                    s2.push(s2i(item)*1.0);
                } else {
                    double b = s2.top();
                    s2.pop();
                    double a = s2.top();
                    s2.pop();
                    switch(item[0]) {
                        case '+': s2.push(a + b); break;
                        case '-': s2.push(a - b); break;
                        case '*': s2.push(a * b); break;
                        case '/': 
                            if(b == 0) {
                                cout << "Error: denominator is 0!" << endl;
                                return Error;
                            }
                            s2.push(a / b); 
                            break;
                    }
                }
            }
            return s2.top();
        }
        void printPostfixExp() {
            if(this->postfixExp.empty()) {
                cout << "postfixExp is empty" << endl;
                return;
            }
            cout << "输出的逆波兰表达式为: ";
            for (auto i : this->postfixExp)
                cout << i << " ";
            cout << endl;
        }
        void printExp() {
            if(this->exp.empty()) {
                cout << "exp is empty" << endl;
                return;
            }
            cout << "输入的中缀表达式为: " << this->exp << endl;
        }
};
int main(){
    cout << "读取的文件名为：" << ExpFileName << endl; 
    vector<string> exps = readFile(ExpFileName);
    int len = exps.size();
    for(int i = 0; i < len; i++) {
        string exp = exps[i];
        cout << "\n------------------样例" << i+1 << ": "<< exp << "--------------------" << endl;
        if(!isValid(exp)) continue;
        cout << "第"<< i+1 << "行输入的表达式合法，开始计算" << endl;
        ReversePolishExp res(exp);
        res.printExp();
        res.printPostfixExp();
        cout << "该逆波兰表达式的计算值为：" << res.compute() << endl;
    }
    return 0;
}

```
