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
