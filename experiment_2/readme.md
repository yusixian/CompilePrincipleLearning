<!--
 * @Author: cos
 * @Date: 2022-04-13 01:05:53
 * @LastEditTime: 2022-04-13 01:35:32
 * @LastEditors: cos
 * @Description: 
 * @FilePath: \CS\experiment_2\LL(1)分析法设计.md
-->

# 一.	实验目的

1. 掌握LL(1)分析法的基本原理
2. 掌握LL(1)分析表的构造方法
3. 掌握LL(1)驱动程序的构造方

# 二.	实验内容及要求

编写识别单词的词法分析程序。

根据某一文法编制调试LL（1）分析程序，以便对任意输入的符号串进行分析。本次实验的目的主要是加深对预测分析LL（1）分析法的理解。

例：对下列文法，用LL（1）分析法对任意输入的符号串进行分析：

（1）E->TG

（2）G->+TG|—TG

（3）G->ε

（4）T->FS

（5）S->*FS|/FS

（6）S->ε

（7）F->(E)

（8）F->i

输出的格式如下：

(1) `LL（1）分析程序，编制人：姓名，学号，班级`

(2) 输入一以#结束的符号串(包括 `+*（）i#`)：i*(i+i)+(i*i)#

(3) 输出过程步骤如下：

| **步骤** | **分析栈** | **剩余输入串** | **所用产生式** |
| -------------- | ---------------- | -------------------- | -------------------- |
| 1              | E                | i+i*i#               | E->TG                |

(4)输入符号串为非法符号串(或者为合法符号串)

备注：

(1) 在“ **所用产生式** ”一列中如果对应有推导则写出所用产生式；如果为匹配终结符则写明匹配的终结符；如分析异常出错则写为“分析出错”；若成功结束则写为“分析成功”。

(2)在此位置输入符号串为用户自行输入的符号串。

(3)上述描述的输出过程只是其中一部分的。

注意：1．表达式中允许使用运算符（+-*/）、分割符（括号）、字符i，结束符#；

2．如果遇到错误的表达式，应输出错误提示信息（该信息越详细越好）；

3．对学有余力的同学，测试用的表达式事先放在文本文件中，一行存放一个表达式，同时以分号分割。同时将预期的输出结果写在另一个文本文件中，以便和输出进行对照；

4．可采用的其它的文法

# 三.	实验过程

## 1、采用的数据结构

产生式类型定义为type，左侧为origin，大写字符，右侧产生的字符

```cpp

struct type { /*产生式类型定义      */
    char origin;   /*产生式左侧字符 大写字符  */
    string array; /*产生式右边字符 */
    int length;    /*字符个数      */
    type():origin('N'), array(""), length(0) {}
    void init(char a, string b) {
        origin = a;
        array = b;
        length = array.length();
    }
};
```

初始化数据结构如下：

```cpp
e.init('E', "TG"), t.init('T', "FS");
g.init('G', "+TG"), g1.init('G', "^");
s.init('S', "*FS"), s1.init('S', "^");
f.init('F', "(E)"), f1.init('F', "i");
```

## 2、头文件声明和全局变量定义

如下

```cpp
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;
const string ExpFileName = "./exp.txt";
char analyeStack[20];                           /*分析栈*/
char restStack[20];                             /*剩余栈*/
const string v1 = "i+*()#"; /*终结符 */
const string v2 = "EGTSF";      /*非终结符   */
const string acceptStr = "i+*()#";   // 接受的字符串
int top, ridx, len; /*len为输入串长度 */
struct type { /*产生式类型定义      */
    char origin;   /*产生式左侧字符 大写字符  */
    string array; /*产生式右边字符 */
    int length;    /*字符个数      */
    type():origin('N'), array(""), length(0) {}
    void init(char a, string b) {
        origin = a;
        array = b;
        length = array.length();
    }
};
type e, t, g, g1, s, s1, f, f1; /* 产生式结构体变量 */
type C[10][10];                 /* 预测分析表 */
```

## 4、函数汇总

### （1）函数汇总表

函数名称         | 功能简述                                   |
| ------------ | -------------------------------------- |
| `readFile`     | 读取文件函数，返回一个string动态数组，以行数分割            |
| `init`         | 初始化函数，在该函数中进行分析栈、剩余栈的初始化               |
| `print`        | 输出当前分析栈和剩余栈                            |
| `isTerminator` | 判断当前字符c是否是终结符                          |
| `analyze`      | 分析字符串s，输出其分析步骤                         |
| `main`         | 主程序入口，从此进入，填充初始分析表及产生式初始化，调用读取文件函数开始分析
### （2）函数的调用关系
![function](https://img-blog.csdnimg.cn/abc7e8b3a3284171aa084634eb198772.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5L2ZY29z,size_12,color_FFFFFF,t_70,g_se,x_16)

## 5、实验结果

### 输入

code.txt

```
int main() {
    char ch = 'ss';
    string str = "Hello, World!"
    char ch2 = 's';
    init();
    double x = 10.31;/* some comment */
    int m = 0;
    int y = 310, m = 0.31;
    while(pos < len) {
        int flag = read_next();
        if(flag == _EOF_) break;
        if(flag != _ERROR_) {
            Token t(flag, tempToken);
            tokenList.push_back(t);
            cout << t << endl;
        } else cout << "Error!" << endl;
    }
    return 0;
}
```

### 输出

![0I3RK{8 N%JNPNA</code></code>(WB_R.png](https://p1-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/a2c8cbe0d32a4149a4d8ec9525d9b39a~tplv-k3u1fbpfcp-watermark.image?)

# 四、实验总结

此次实验还是很有意思的，最终跑通的时候也是非常有成就感，个人感觉不用拘泥于用什么算法，只需要捋清楚自己的思路，如何设计才能使这个程序能正确识别？主要有一个优先级的思路，空格和换行符会被跳过，然后先判断是否为数字或者字母，在进行相应处理，然后进行一些特殊界符的判断，如字符串、注释等。我认为代码就足以很好的说清楚这个流程。这个程序暂时只使用常用符号（.）来支持小数，如果需要更多，可以在judge中的isdigit()后进行修改，改起来并不困难。显然，judge函数中的函数还可以拆成更细致的几个函数，但这就等以后再补全了。

# 五、思考题回答

## 程序设计中哪些环节影响词法分析的效率？如何提高效率？

答：有待优化的部分还有不少，例如在判断是否为关键字时，目前的方法是把可能为标识符或者关键字的字符串读取完后存放在一个字符数组后再逐个与关键字表进行匹配，可改为在读取的同时判断，这样会提高效率。还有就是界符匹配也是同理。

# 完整代码

```cpp
/*
 * @Author: cos
 * @Date: 2022-04-05 00:10:59
 * @LastEditTime: 2022-04-08 02:37:49
 * @LastEditors: cos
 * @Description: 词法分析器设计实现
 * @FilePath: \CS\experiment_1\demo\main.cpp
 */
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
using namespace std;
const string CategoryFileName = "./categoryCode.txt";
const string CodeFileName = "./code.txt";
string keywords[22];  // 关键字表 种别码1-22
string operate[28];  // 运算符表 种别码23-50
string delimiter[15];  // 界符表 种别码51-65
map<string, int> categoryCode;  // 种别码表
const string op = "+-*/%=!&|<>";
const int _EOF_ = -2;
const int _ERROR_ = -1;
enum { 
    _ID_, _INT_, _DOUBLE_, _OPERATOR_, _DELIMITER_, _KEYWORD_, _CHAR_, _STRING_, _COMMENT_, _SPACE_
};  // 类型
string cat[10] = { "id", "int", "double", "operator", "delimiter", "keyword", "char", "string", "comment", "space" };
struct Token {
    int type;   // 种别码
    string value;       // 值 关键字/变量名/数字/运算符/界符
    string category;    // 种别码对应的类型名称
    Token(int type, string value, string category) : type(type), value(value), category(category) {}
    friend ostream& operator<<(ostream& os, const Token& t) {
        os << t.category << ", type: " << t.type << ", value: " << t.value;
        return os;
    }
};
int pos, len;  // 当前字符位置和长度
string code, tempToken;  // 当前识别的字符串
vector<Token> tokenList;  // 存储识别出的token
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
void init() {
    vector<string> res = readFile(CategoryFileName); 
    // cout << "len:" << len << endl;
    for(int i = 0; i < 22; ++i) {
        keywords[i] = res[i];
        categoryCode[res[i]] = i+1;
        // cout << "keyword:" << res[i] << endl;
    }
    for(int i = 0; i < 28; ++i) {
        operate[i] = res[i + 22];
        categoryCode[res[i+22]] = i+23;
        // cout << "operate:" << res[i + 22] << endl;
    }
    for(int i = 0; i < 15; ++i) {
        delimiter[i] = res[i + 50];
        categoryCode[res[i+50]] = i+51;
        // cout << "delimiter:" << res[i + 50] << endl;
    }
    res = readFile(CodeFileName);
    for(int i = 0; i < res.size(); ++i)
        code += res[i]+'\n';
    len = code.size();
}
char peek() {
    if (pos+1 < len) return code[pos+1];
    else return '\0';
}
inline bool isDigit(char c) {
    return c >= '0' && c <= '9';
}
// 是否为字母或下划线
inline bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}
bool isKeyword(string s) {
    for(int i = 0; i < 22; ++i)
        if (s == keywords[i]) 
            return true;
    return false;
}
bool isOP(char ch) {
    return op.find(ch) != string::npos;
}
bool isOperator(string s) {
    for(int i = 0; i < 28; ++i)
        if (s == operate[i]) return true;
    return false;
}
bool isDelimiter(char ch) {
    for(int i = 0; i < 15; ++i)
        if (ch == delimiter[i][0]) return true;
    return false;
}
int judge(char ch) {
    if(ch == '\n' || ch == ' ') return _SPACE_;
    if(isDigit(ch)) {
        char nextChar = peek();
        if(ch == '0' && nextChar == '.') { // 0.多少
            ++pos;
            if(!isDigit(peek()))   // .后面不是数字
                return _ERROR_;
            tempToken = "0.";
            while(isDigit(peek())) {
                tempToken += peek();
                ++pos;
            }
            return _DOUBLE_;    // 8
        } else if(ch == '0' && !isDigit(nextChar)) { // 不是数字也不是.，说明是单纯的一个0
            tempToken = "0";
            return _INT_;   // 5
        } else if(ch != '0') {  // digit1
            tempToken = ch;
            while(isDigit(peek())) {
                tempToken += peek();
                ++pos;
            }
            char nextChar = peek();
            if(nextChar == '.') {
                tempToken += nextChar;
                ++pos;
                nextChar = peek();
                if(isDigit(nextChar)) {
                    tempToken += peek();
                    ++pos;
                    while(isDigit(peek())) {
                        tempToken += peek();
                        ++pos;
                    }
                    return _DOUBLE_;    // 8
                } else return _ERROR_;
            } else return _INT_;    // 6
        } else {    // 0+数字
            ++pos;
            return _ERROR_;         // ERROR
        }
    }
    if(isLetter(ch)) {
        tempToken = ch;
        char nextChar = peek();
        while( isLetter(nextChar) || isDigit(nextChar) ) { // 标识符~
            tempToken += nextChar;
            ++pos;
            nextChar = peek();
        }
        return isKeyword(tempToken) ? _KEYWORD_ : _ID_;
    } 
    if(ch == '\"') {
        tokenList.push_back(Token(54, "\"", cat[_DELIMITER_]));
        tempToken = "";
        char nextChar = peek();
        while(nextChar != '\"') {
            tempToken += nextChar;
            ++pos;
            nextChar = peek();
        }
        tokenList.push_back(Token(69, tempToken, cat[_STRING_]));
        tokenList.push_back(Token(54, "\"", cat[_DELIMITER_]));
        pos += 2;
        return _STRING_;
    }
    if(ch == '\'') {
        tempToken = "";
        ++pos;
        char nextChar = peek();
        if(nextChar == '\'') {
            tokenList.push_back(Token(53, "\'", cat[_DELIMITER_]));
            tempToken += code[pos];
            tokenList.push_back(Token(68, tempToken, cat[_CHAR_]));
            tokenList.push_back(Token(53, "\'", cat[_DELIMITER_]));
            ++pos;
            return _CHAR_;
        } else if(code[pos] == '\'') {
            tokenList.push_back(Token(53, "\'", cat[_DELIMITER_]));
            tokenList.push_back(Token(68, tempToken, cat[_CHAR_]));  // 空字符串
            tokenList.push_back(Token(53, "\'", cat[_DELIMITER_]));
            return _CHAR_;
        } else {
            while(pos < len && nextChar != '\'') {
                ++pos;
                nextChar = peek();
            }
            ++pos;
            return _ERROR_;
        }
    }
    if(ch == '/') {
        if(peek() == '*') {
            ++pos;
            char nextChar = peek();
            ++pos;
            tempToken = "";
            while(pos < len) {
                if(nextChar == '*' && peek() == '/') {
                    tokenList.push_back(Token(55, "/*", cat[_DELIMITER_]));
                    tokenList.push_back(Token(71, tempToken, cat[_COMMENT_]));
                    tokenList.push_back(Token(56, "*/", cat[_DELIMITER_]));
                    ++pos;
                    ++pos;
                    return _COMMENT_;
                } else {
                    tempToken += nextChar;
                    nextChar = peek();
                    ++pos;
                }
            }
            return _ERROR_;
        }
    }

    if(isOP(ch)) {   // op运算符
        tempToken = "";
        tempToken += ch;
        char nextChar = peek();
        if(isOP(nextChar)) {
            if(isOperator(tempToken + nextChar)) {
                tempToken += nextChar;
                ++pos;
                return _OPERATOR_;      // 15
            } else return _OPERATOR_;   // 14
        } else return _OPERATOR_;       // 14
    }
    if(isDelimiter(ch)) {
        tempToken = "";
        tempToken += ch;
        return _DELIMITER_;
    }
    return _ERROR_;  
}
int read_next() {
    int type = judge(code[pos]);
    while(pos < len && type == _SPACE_) {
        ++pos;
        type = judge(code[pos]);
    }
    if(pos >= len) return _EOF_; 
    ++pos;
    if(type == _ERROR_) return _ERROR_;
    if(type == _DOUBLE_) {
        // cout << "double: " << tempToken << endl;
        tokenList.push_back(Token(67, tempToken, cat[_DOUBLE_]));
        return _DOUBLE_;
    }
    if(type == _INT_) {
        // cout << "int: " << tempToken << endl;
        tokenList.push_back(Token(66, tempToken, cat[_INT_]));
        return _INT_;
    }
    if(type == _ID_) {  // 标识符
        // cout << "id: " << tempToken << endl;
        tokenList.push_back(Token(70, tempToken, cat[_ID_]));
        return _ID_;
    }
    if(type == _OPERATOR_ || type == _KEYWORD_ || type == _DELIMITER_) {
        tokenList.push_back(Token(categoryCode[tempToken], tempToken, cat[type]));
        return type;
    }
    return _ERROR_;
}
int main() {
    init();
    while(pos < len) {
        int flag = read_next();
        if(flag == _EOF_) break;
        else if(flag == _ERROR_) tokenList.push_back(Token(_ERROR_, "ERROR!", "ERROR"));
    }
    for(auto t : tokenList)
        cout << t << endl;
    return 0;
}
```
