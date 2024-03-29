源代码仓库：[CompilePrincipleLearning/experiment_4 · yusixian/CompilePrincipleLearning (github.com)](https://github.com/yusixian/CompilePrincipleLearning/tree/master/experiment_4)

源代码在demo文件夹中~

# 一.	实验目的
1. 掌握LR(1)分析法的基本原理
2. 掌握LR(1)分析表的构造方法
3. 掌握LR(1)驱动程序的构造方法

# 二.	实验内容及要求
构造LR(1)分析程序，利用它进行语法分析，判断给出的符号串是否为该文法识别的句子，了解LR（K）分析方法是严格的从左向右扫描，和自底向上的语法分析方法。

根据某一文法编制调试LR（1）分析程序，以便对任意输入的符号串进行分析。本次实验的目的主要是加深对LR（1）分析法的理解。

**对下列文法，用LR（1）分析法对任意输入的符号串进行分析**：
```txt
（0）S’->E

（1）E->E+T

（2）E->T

（3）T->T*F

（4）T->F

（5）F->(E)

（6）F->i
```

输出的格式如下：

(1)LR（1）分析程序，编制人：姓名，学号，班级

(2)输入一以#结束的符号串(包括+-*/（）i#)：在此位置输入符号串

(3)输出过程如下：

| **步骤** | **状态栈** | **符号栈****** | **剩余输入串** | **动作** |
| ------ | ------- | ----------- | --------- | ------ |
| 1      | 0       | #          | i+i*i#   | 移进     |

(4)输入符号串为非法符号串或合法符号串

注意：

1.表达式中允许使用运算符（+|*）、分割符（括号）、字符i，结束符#；

2.如果遇到错误的表达式，应输出错误提示信息（该信息越详细越好）；

3.对学有余力的同学，测试用的表达式事先放在文本文件中，一行存放一个表达式，同时以分号分割。同时将预期的输出结果写在另一个文本文件中，以便和输出进行对照；

4．可采用的其它的文法，但是必须是LR1分析方法。

# 三.	实验过程

## 1、构造识别LR（1）文法活前缀的DFA
如图：新标签页打开，不糊的。

![LR1_DFA.drawio.png](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/3b812acc3e4e4ea9929eef56cebea020~tplv-k3u1fbpfcp-watermark.image?)

action表和goto表如下：

![image.png](https://p9-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/5dbe68ae771f4a89a6dca82976915452~tplv-k3u1fbpfcp-watermark.image?)

## 2、采用的数据结构

```cpp
// ACTION表
// + * ( ) i #
string action[12][6];
// goto表
// a b #
int _goto[12][3];
string vt = "+*()i#";      // 终结符表
string vn = "ETF";        // 非终结符表
string LR[6] = { "E->E+T", "E->T", "T->T*F", "T->F", "F->(E)", "F->i" };   // 存放产生式
stack<char> chars;  // 符号栈
stack<int> state;   // 状态栈
```
## 3、头文件声明和全局变量定义
如下。
```cpp
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>
using namespace std;
const string ExpFileName = "./exp.txt";
const string GotoFileName = "./goto.txt";
const string ActionFileName = "./action.txt";
const int Null = -1;
// ACTION表
// + * ( ) i #
string action[12][6];
// goto表
// a b #
int _goto[12][3];
string vt = "+*()i#";      // 终结符表
string vn = "ETF";        // 非终结符表
string LR[6] = { "E->E+T", "E->T", "T->T*F", "T->F", "F->(E)", "F->i" };   // 存放产生式
```
## 4、函数汇总

### （1）函数汇总表
| 函数名称                      | 功能简述                           |
| ------------------------- | ------------------------------ |
| `readFile`                  | 读取文件函数，返回一个string动态数组，以行数分割    |
| `init`                      | 初始化函数，在该函数中进行goto表和action表的初始化 |
| `printActions / printGotos` | 输出goto表与action表                |
| `isTerminator`              | 判断当前字符c是否是终结符                  |
| `findTerminator`            | 返回终结符所处下标                      |
| `findNonTerminator`         | 返回非终结符所处下标                     |
| `s2string`                  | 将栈转换为字符串返回，方便输出步骤              |
| `analyzeLR1`                | 利用LR1分析法分析字符串exp，输出其分析步骤       |
| `main `                     | 主程序入口，调用读取文件函数开始分析            |


### （2）函数的调用关系

![function4.drawio.png](https://p1-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/3b99924fde594015aac1b75d324243c7~tplv-k3u1fbpfcp-watermark.image?)
### （3）流程图

![main.drawio.png](https://p6-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/fbd377b4720c450894253ad587ca8c3f~tplv-k3u1fbpfcp-watermark.image?)

## 5、实验结果
### 输入
action.txt文件
```txt
N	N	s4	N	s5	N
s6	N	N	N	N	acc
r2	s7	N	r2	N	r2
r4	r4	N	r4	N	r4
N	N	s4	N	s5	N
r6	r6	N	r6	N	r6
N	N	s4	N	s5	N
N	N	s4	N	s5	N
s6	N	N	s11	N	N
r1	s7	N	r1	N	r1
r3	r3	N	r3	N	r3
r5	r5	N	r5	N	r5
```

goto.txt文件
```txt
1	2	3
N	N	N
N	N	N
N	N	N
8	2	3
N	N	N
N	9	3
N	N	10
N	N	N
N	N	N
N	N	N
N	N	N
```

exp.txt文件
```txt
i+(i*i)*(i+i)#
i*i+i*i#
i+i*i+i*(i+i*i)#
i+*(i)+i(i+i*i)#
i+i(i)#
```
### 输出

![image1.png](https://p9-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/00706fefb691427592dcf885bd5729a7~tplv-k3u1fbpfcp-watermark.image?)

![image2.png](https://p9-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/ca94078bbded4bf5802757568e8221b4~tplv-k3u1fbpfcp-watermark.image?)

![image3.png](https://p1-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/26196777c3a241799dcd13ea1a30debc~tplv-k3u1fbpfcp-watermark.image?)

# 完整代码

```cpp
/*
 * @Author: cos
 * @Date: 2022-04-30 14:20:51
 * @LastEditTime: 2022-05-01 02:34:12
 * @LastEditors: cos
 * @Description: 实验4 LR(1) 分析法
 * @FilePath: \CompileTheory\experiment_4\demo\main.cpp
 */
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>
using namespace std;
const string ExpFileName = "./exp.txt";
const string GotoFileName = "./goto.txt";
const string ActionFileName = "./action.txt";
const int Null = -1;
// ACTION表
// + * ( ) i #
string action[12][6];
// goto表
// a b #
int _goto[12][3];
string vt = "+*()i#";      // 终结符表
string vn = "ETF";        // 非终结符表
string LR[6] = { "E->E+T", "E->T", "T->T*F", "T->F", "F->(E)", "F->i" };   // 存放产生式
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
    }
    catch (const exception& e) {
        cerr << e.what() << '\n';
        return res;
    }
}
void printActions() {
    cout << "-----------------ACTION表------------------" << endl;
    cout << "+\t*\t(\t)\ti\t$" << endl;
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 6; ++j)
            cout << action[i][j] << "\t";
        cout << endl;
    }
}
void printGotos() {
    cout << "-----------------GOTO表------------------" << endl;
    cout << "E\tT\tF" << endl;
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 3; ++j)
            cout << _goto[i][j] << "\t";
        cout << endl;
    }
}
void init() {
    vector<string> actions = readFile(ActionFileName);
    for (int i = 0; i < 12; ++i) {
        int cnt = 0;
        string row = actions[i];
        int len = actions[i].length();
        for (int j = 0; j < len; ++j) {
            string temp = "";
            while (j < len && row[j] != ' ' && row[j] != '\t') {
                temp += row[j];
                ++j;
            }
            while (j < len && (row[j] == ' ' || row[j] == '\t'))
                ++j;
            --j;
            action[i][cnt++] = temp;
        }

    }
    printActions();
    vector<string> gotos = readFile(GotoFileName);
    for (int i = 0; i < 12; ++i) {
        int cnt = 0;
        string row = gotos[i];
        int len = row.length();
        for (int j = 0; j < len; ++j) {
            string temp = "";
            while (j < len && row[j] != ' ' && row[j] != '\t') {
                temp += row[j];
                ++j;
            }
            while (j < len && (row[j] == ' ' || row[j] == '\t'))
                ++j;
            --j;
            _goto[i][cnt++] = (temp == "N") ? Null : stoi(temp);
        }
    }
    printGotos();
}
bool isTerminator(char c) {
    return vt.find(c) != string::npos;
}
int findTerminator(char c) { // 返回终结符所处下标
    return vt.find(c);
}
int findNonTerminator(char c) { // 返回非终结符的下标
    return vn.find(c);
}
// 将栈转换为字符串返回
string s2string(stack<int> s) {
    string str = "";
    while(!s.empty()) {
        str += to_string(s.top()) + " ";
        s.pop();
    }
    return str;
}
// 输出剩余输入串
void printRestInput(string exp, int start, int len) {
    for(int i = start; i < len; ++i) 
        cout << exp[i];
    cout << '\t';
}
void analyzeLR1(string exp) {  // 分析一个表达式
    int len = exp.length();
    stack<char> chars;  // 符号栈
    stack<int> state;   // 状态栈
    state.push(0);  // 初始状态为0
    chars.push('#');  // 初始符号为#
    string charsStr = "#";
    stack<int> copyState;
    copyState.push(0);
    int cnt = 0;    // 序号
    int idx = 0;  // 当前输入指针
    cout << "序号\t\t状态栈\t\t符号栈\t\t输入串\t\t描述" << endl;
    cout << cnt++ << '\t' << s2string(copyState) << '\t' << charsStr << '\t' << exp << '\t' << " 初始状态 " << endl;
    while(1) {
        int nowState = state.top();
        char nowChar = exp[idx];    // 当前输入字符
        int isT = findTerminator(nowChar);
        if(isT == Null) {   // 非终结符
            cout << "Error!" << "出现非法字符，程序错误退出" <<endl;
            return;
        }
        string actionStr = action[nowState][isT];
        if(actionStr == "acc") {
            cout << cnt++ << '\t' << s2string(copyState) << '\t' << charsStr << '\t' << exp << '\t' << " accept 接受！ " << endl;
            return;
        } else if(actionStr == "N") {
            cout << cnt++ << '\t' << s2string(copyState) << '\t' << charsStr << '\t' << exp << '\t' << "Error! 程序异常退出" << endl;
            return;
        } else if(actionStr[0] == 'r') {   // 归约
            int num = stoi(actionStr.substr(1));    // 选用第几个产生式归约
            int len = LR[num-1].length()-3;
            while(len--) {
                chars.pop();        // 出栈，归约
                state.pop();
                charsStr = charsStr.substr(0, charsStr.length()-1);
                copyState.pop();   // 便于输出
            }
            chars.push(LR[num-1][0]);   // 产生式左部入符号栈
            charsStr += LR[num-1][0];

            int nowState = state.top();
            int gidx = findNonTerminator(LR[num-1][0]);
            int newState = _goto[nowState][gidx];
            state.push(newState);
            copyState.push(newState);

            cout << cnt++ << '\t' << s2string(copyState) << '\t' << charsStr  << '\t';
            printRestInput(exp, idx, len);
            cout << '\t' << " 归约 " << LR[num-1] << endl;
        } else if(actionStr[0] == 's') {    // 移进
            int newState =  stoi(actionStr.substr(1));
            state.push(newState);
            copyState.push(newState);

            chars.push(nowChar);
            charsStr += nowChar;
            ++idx;  // 输入指针后移

            cout << cnt++ << '\t' << s2string(copyState) << '\t' << charsStr << '\t';
            printRestInput(exp, idx, len);
            cout << '\t' << actionStr << " 移进 " << endl;
        } else {
            cout << "Error!" << "程序异常退出" <<endl;
            return;
        }
    }
}
int main() {
    cout << "LR（1）分析程序，编制人：xxx xxxxxxxx xxxx班" << endl;
    cout << "提示:本程序只能对由'i','+','*','/','(',')'构成的以'#'结束的表达式进行分析，每行读入一个表达式" << endl;
    cout << "读取的文件名为：" << ExpFileName << endl; 
    init();
    vector<string> exps = readFile(ExpFileName);
    int len = exps.size();
    for (int i = 0; i < len; i++) {
        string exp = exps[i];
        cout << "\n------------------待分析表达式" << i+1 << "："<< exp << "--------------------" << endl;
        bool flag = true;
        for (int j = 0; j < exp.length(); j++) {
            if (!isTerminator(exp[j])) {
                cout << "第 "<<   i+1 << "行输入的字符串不合法，请重新输入" << endl;
                flag = false;
                break;
            }
        }
        if (flag) {
            cout << "表达式"  << i+1 << "：" << exp << "分析开始" << endl;
            analyzeLR1(exp);
        }
    }
    return 0;
}
```
