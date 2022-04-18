/*
 * @Author: cos
 * @Date: 2022-04-18 00:46:57
 * @LastEditTime: 2022-04-18 20:52:52
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
    
    cout << "逆波兰式的生成及计算程序，编制人： 201916010728 余思娴 计科F1901班" << endl;
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
