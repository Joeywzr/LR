//
// Created by Memo on 2018/12/8.
//

#include "LR_grammer.h"

void LR_grammer::init(DEDUCTION &dd)//初始化
{
    nonterminal.emplace_back(" ");
    nonterminal.emplace_back("E");
    nonterminal.emplace_back("T");
    nonterminal.emplace_back("F");
    terminal.emplace_back("+");
    terminal.emplace_back("-");
    terminal.emplace_back("*");
    terminal.emplace_back("/");
    terminal.emplace_back("(");
    terminal.emplace_back(")");
    terminal.emplace_back("n");//代表数字

    deductions.push_back(dd);
    dd.left = "E";
    dd.right = "E+T";
    deductions.push_back(dd);
    dd.right = "E-T";
    deductions.push_back(dd);
    dd.right = "T";
    deductions.push_back(dd);

    dd.left = "T";
    dd.right = "T*F";
    deductions.push_back(dd);
    dd.right = "T/F";
    deductions.push_back(dd);
    dd.right = "F";
    deductions.push_back(dd);

    dd.left = "F";
    dd.right = "(E)";
    deductions.push_back(dd);
    dd.right = "n";
    deductions.push_back(dd);

    analyze_table = {
            {"ERR", "ERR", "ERR", "ERR", "S4",  "ERR", "S5",  "ERR", "1",   "2",   "3"},
            {"S6",  "S7",  "ERR", "ERR", "ERR", "ERR", "ERR", "ACC", "ERR", "ERR", "ERR"},
            {"R3",  "R3",  "S8",  "S9",  "ERR", "R3",  "ERR", "R3",  "ERR", "ERR", "ERR"},
            {"R6",  "R6",  "R6",  "R6",  "ERR", "R6",  "ERR", "R6",  "ERR", "ERR", "ERR"},
            {"ERR", "ERR", "ERR", "ERR", "S4",  "ERR", "S5",  "ERR", "10",  "2",   "3"},
            {"R8",  "R8",  "R8",  "R8",  "ERR", "R8",  "ERR", "R8",  "ERR", "ERR", "ERR"},
            {"ERR", "ERR", "ERR", "ERR", "S4",  "ERR", "S5",  "ERR", "ERR", "11",  "3"},
            {"ERR", "ERR", "ERR", "ERR", "S4",  "ERR", "S5",  "ERR", "ERR", "12",  "3"},
            {"ERR", "ERR", "ERR", "ERR", "S4",  "ERR", "S5",  "ERR", "ERR", "ERR", "13"},
            {"ERR", "ERR", "ERR", "ERR", "S4",  "ERR", "S5",  "ERR", "ERR", "ERR", "14"},
            {"S6",  "S7",  "ERR", "ERR", "ERR", "S15", "ERR", "ERR", "ERR", "ERR", "ERR"},
            {"R1",  "R1",  "S8",  "S9",  "ERR", "R1",  "ERR", "R1",  "ERR", "ERR", "ERR"},
            {"R2",  "R2",  "S8",  "S9",  "ERR", "R2",  "ERR", "R2",  "ERR", "ERR", "ERR"},
            {"R4",  "R4",  "R4",  "R4",  "ERR", "R4",  "ERR", "R4",  "ERR", "ERR", "ERR"},
            {"R5",  "R5",  "R5",  "R5",  "ERR", "R5",  "ERR", "R5",  "ERR", "ERR", "ERR"},
            {"R7",  "R7",  "R7",  "R7",  "ERR", "R7",  "ERR", "R7",  "ERR", "ERR", "ERR"}
    };
    table_coordinate = {{'+', 0},
                        {'-', 1},
                        {'*', 2},
                        {'/', 3},
                        {'(', 4},
                        {')', 5},
                        {'n', 6},
                        {'$', 7},
                        {'E', 8},
                        {'T', 9},
                        {'F', 10}};
}

void LR_grammer::augmentating_grammer()//增广文法
{
    nonterminal[0] = "S";
    deductions[0].left = "S";
    deductions[0].right = "E";
}

void LR_grammer::analyze_program(string text)//LR分析程序
{
    if (text == "DIGITAL FORMAT ERROR!")//如果字符串中有非法字符或者数字格式不正确，则报错退出分析程序
    {
        cout << text;
        return;
    }
    text.append("$");
    stack<char> symble;//符号栈
    stack<int> state;//状态栈
    state.push(0);//开始时把0状态压入状态栈顶
    symble.push('-');//开始时把‘-’压入符号栈顶
    int cur = 0;//当前字符在字符串中的位置
    int s;//当前状态
    char a;//当前字符
//------------输出格式初始化------------------------------------
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << setiosflags(ios::left) << setw(40) << "栈" << setw(20) << "输入" << setw(22) << resetiosflags(ios::left)
         << "分析动作" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    string state_print = "State:  0  ";
    string symble_print = "Symble: -  ";
    string input_print = text;
//---------------------------------------------------------
    do
    {
        s = state.top();//令s为栈顶状态
        a = text[cur];//a为当前字符
        if (analyze_table[s][table_coordinate[a]][0] == 'S')//如果动作为移进
        {
            //把a和s分别压入状态栈和符号栈顶
            symble.push(a);
            string temp_str = analyze_table[s][table_coordinate[a]].substr(1,
                                                                           analyze_table[s][table_coordinate[a]].size() -
                                                                           1);
            int temp_int = atoi(temp_str.c_str());
            state.push(temp_int);
            cur++;//指向下一输入符号
            //输出格式制定
            cout << setiosflags(ios::left) << setw(40) << state_print << setw(20) << input_print << setw(20)
                 << resetiosflags(ios::left) << "Shift " << state.top() << endl;
            cout << setiosflags(ios::left) << setw(40) << symble_print << resetiosflags(ios::left) << endl << endl;
            if (state.top() >= 10)
                state_print += to_string(state.top()) + " ";
            else
                state_print += to_string(state.top()) + "  ";
            symble_print += a;
            symble_print.append("  ");
            input_print = input_print.substr(1, input_print.size() - 1);
        }
        else if (analyze_table[s][table_coordinate[a]][0] == 'R')//如果动作为归约
        {
            DEDUCTION temp_dec = deductions[analyze_table[s][table_coordinate[a]][1] - '0'];
            //输出格式制定
            cout << setiosflags(ios::left) << setw(40) << state_print << setw(20) << input_print << setw(20)
                 << resetiosflags(ios::left) << "reduce by " << temp_dec.left << " -> " << temp_dec.right << endl;
            cout << setiosflags(ios::left) << setw(40) << symble_print << resetiosflags(ios::left) << endl << endl;
            int length = temp_dec.right.size();
            //栈顶弹出归约产生式右部长度个符号
            while (length--)
            {
                symble.pop();
                state.pop();
                symble_print = symble_print.substr(0, symble_print.size() - 3);
                state_print = state_print.substr(0, state_print.size() - 3);
            }
            int top = state.top();
            //将归约产生式左部符号压入符号栈，goto[S',A]压入状态栈顶
            symble.push(temp_dec.left[0]);
            string temp_str = analyze_table[top][table_coordinate[symble.top()]];
            int temp_int = atoi(temp_str.c_str());
            state.push(temp_int);
            //输出格式制定
            if (temp_int >= 10)
                state_print += to_string(temp_int) + " ";
            else
                state_print += to_string(temp_int) + "  ";
            symble_print += temp_dec.left;
            symble_print.append("  ");
        }
        else if (analyze_table[s][table_coordinate[a]] == "ACC")//如果动作为接受
        {
            cout << setiosflags(ios::left) << setw(40) << state_print << setw(20) << input_print << setw(21)
                 << resetiosflags(ios::left) << "SUCCESS!" << endl;
            cout << setiosflags(ios::left) << setw(40) << symble_print << resetiosflags(ios::left) << endl;
            cout << "-----------------------------------------------------------------------------------------" << endl;
            return;
        }
        else
        {
            cout << "ERROR!" << endl;
            cout << "-----------------------------------------------------------------------------------------" << endl;
            return;
        }
    } while (true);
}

string LR_grammer::text_process(string text, vector<int> &number)//处理输入文本
{
    int cur = 0;
    int length = text.size();
    int state = 0;
    string after;
    while (length--)
    {
        if (text[cur] > '0' && text[cur] < '9')//如果当前字符为数字
        {
            if (state == 0)
            {
                after += 'n';
                state = 1;
            }
            else if (state == 3 || state == 4)
                state = 5;
            cur++;
        }
        else if (text[cur] == '.')//如果当前字符为‘.’
        {
            if (state == 1)
                state = 2;
            else
                return "DIGITAL FORMAT ERROR!";//返回数字格式错误
            cur++;
        }
        else if (text[cur] == 'e' || text[cur] == 'E')//如果当前字符为e或E
        {
            if (state == 1 || state == 2)
                state = 3;
            else
                return "DIGITAL FORMAT ERROR!";//返回数字格式错误
            cur++;
        }
        else if (text[cur] == '+' || text[cur] == '-')//如果当前字符为+或-
        {
            if (state == 3)
                state = 4;
            else
            {
                after += text[cur];
                state = 0;
            }
            cur++;
        }
        else if (text[cur] == '*' || text[cur] == '/' || text[cur] == '(' || text[cur] == ')')//如果当前字符为*、(或)
        {
            after += text[cur];
            state = 0;
            cur++;
        }
        else
            return "DIGITAL FORMAT ERROR!";//返回数字格式错误
    }
    return after;
}

string LR_grammer::text_process1(string text, vector<double> &number)//处理输入文本
{
    int cur = 0;
    int length = text.size();
    int state = 0;
    string after;
    string to_num;
    double temp;
    while (length--)
    {
        if (text[cur] >= '0' && text[cur] <= '9')//如果当前字符为数字
        {
            to_num += text[cur];
            if (state == 0)
            {
                after += 'n';
                state = 1;
            }
            else if (state == 3 || state == 4)
                state = 5;
            cur++;
        }
        else if (text[cur] == '.')//如果当前字符为‘.’
        {
            to_num += text[cur];
            if (state == 1)
                state = 2;
            else
                return "DIGITAL FORMAT ERROR!";//返回数字格式错误
            cur++;
        }
        else if (text[cur] == 'e' || text[cur] == 'E')//如果当前字符为e或E
        {
            to_num += text[cur];
            if (state == 1 || state == 2)
                state = 3;
            else
                return "DIGITAL FORMAT ERROR!";//返回数字格式错误
            cur++;
        }
        else if (text[cur] == '+' || text[cur] == '-')//如果当前字符为+或-
        {
            if (state == 3)
            {
                state = 4;
                to_num += text[cur];
            }
            else
            {
                after += text[cur];
                temp = atof(to_num.c_str());
                number.push_back(temp);
                to_num = "";
                state = 0;
            }
            cur++;
        }
        else if (text[cur] == '*' || text[cur] == '/' || text[cur] == '(' || text[cur] == ')')//如果当前字符为*、(或)
        {
            after += text[cur];
            if(text[cur] == '*' || text[cur] == '/')
            {
                temp = atof(to_num.c_str());
                number.push_back(temp);
                to_num = "";
            }
            state = 0;
            cur++;
        }
        else
            return "DIGITAL FORMAT ERROR!";//返回数字格式错误
    }
    temp = atof(to_num.c_str());
    number.push_back(temp);
    to_num = "";
    return after;
}

void LR_grammer::analyze_program1(string text, vector<double> number)//LR分析程序
{
    if (text == "DIGITAL FORMAT ERROR!")//如果字符串中有非法字符或者数字格式不正确，则报错退出分析程序
    {
        cout << text;
        return;
    }
    int cur_number = 0;
    pair<char,double> p;
    text.append("$");
    stack<pair<char, double>> symble;//符号栈
    stack<int> state;//状态栈
    state.push(0);//开始时把0状态压入状态栈顶
    p.first = '-';
    p.second = 0;
    symble.push(p);//开始时把<‘-’,0>压入符号栈顶
    int cur = 0;//当前字符在字符串中的位置
    int s;//当前状态
    char a;//当前字符
//------------输出格式初始化------------------------------------
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << setiosflags(ios::left) << setw(40) << "栈" << setw(20) << "输入" << setw(22) << resetiosflags(ios::left)
         << "分析动作" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    string state_print = "State:  0  ";
    string symble_print = "Symble: -  ";
    string input_print = text;
//---------------------------------------------------------
    do
    {
        s = state.top();//令s为栈顶状态
        a = text[cur];//a为当前字符
        if (analyze_table[s][table_coordinate[a]][0] == 'S')//如果动作为移进
        {
            //把a和s分别压入状态栈和符号栈顶
            p.first = a;
            if(a == 'n')
                p.second = number[cur_number++];
            else
                p.second = 0;
            symble.push(p);
            string temp_str = analyze_table[s][table_coordinate[a]].substr(1,
                                                                           analyze_table[s][table_coordinate[a]].size() -
                                                                           1);
            int temp_int = atoi(temp_str.c_str());
            state.push(temp_int);
            cur++;//指向下一输入符号
            //输出格式制定
            cout << setiosflags(ios::left) << setw(40) << state_print << setw(20) << input_print << setw(20)
                 << resetiosflags(ios::left) << "Shift " << state.top() << endl;
            cout << setiosflags(ios::left) << setw(40) << symble_print << resetiosflags(ios::left) << endl << endl;
            if (state.top() >= 10)
                state_print += to_string(state.top()) + " ";
            else
                state_print += to_string(state.top()) + "  ";
            symble_print += a;
            symble_print.append("  ");
            input_print = input_print.substr(1, input_print.size() - 1);
        }
        else if (analyze_table[s][table_coordinate[a]][0] == 'R')//如果动作为归约
        {
            DEDUCTION temp_dec = deductions[analyze_table[s][table_coordinate[a]][1] - '0'];
            //输出格式制定
            cout << setiosflags(ios::left) << setw(40) << state_print << setw(20) << input_print << setw(20)
                 << resetiosflags(ios::left) << "reduce by " << temp_dec.left << " -> " << temp_dec.right << endl;
            cout << setiosflags(ios::left) << setw(40) << symble_print << resetiosflags(ios::left) << endl << endl;
            int length = temp_dec.right.size();
            //栈顶弹出归约产生式右部长度个符号
            double num_temp = 0;
            int flag = 0;
            if(length == 1)
            {
                while (length--)
                {
                    num_temp = symble.top().second;
                    symble.pop();
                    state.pop();
                    symble_print = symble_print.substr(0, symble_print.size() - 3);
                    state_print = state_print.substr(0, state_print.size() - 3);
                }
            }
            else
            {
                while (length--)
                {
                    if(symble.top().first == '+')
                        flag = 1;
                    else if(symble.top().first == '-')
                        flag = 2;
                    else if(symble.top().first == '*')
                        flag = 3;
                    else if(symble.top().first == '/')
                        flag = 4;
                    else if(symble.top().first == ')')
                        flag = 5;

                    if(symble.top().first != '+' &&
                            symble.top().first != '-' &&
                            symble.top().first != '*' &&
                            symble.top().first != '/' &&
                            symble.top().first != ')')
                    {
                        if(flag == 0)
                            num_temp = symble.top().second;
                        else if(flag == 1)
                            num_temp += symble.top().second;
                        else if(flag == 2)
                            num_temp = symble.top().second - num_temp;
                        else if(flag == 3)
                            num_temp *= symble.top().second;
                        else if(flag == 4)
                            num_temp = symble.top().second / num_temp;
                        else if(flag == 5)
                        {
                            num_temp = symble.top().second;
                            flag = 6;
                        }
                    }
                    symble.pop();
                    state.pop();
                    symble_print = symble_print.substr(0, symble_print.size() - 3);
                    state_print = state_print.substr(0, state_print.size() - 3);
                }
            }
            int top = state.top();
            //将归约产生式左部符号压入符号栈，goto[S',A]压入状态栈顶
            p.first = temp_dec.left[0];
            p.second = num_temp;
            symble.push(p);
            cout << "当前栈顶值为:" << symble.top().second << endl;
            string temp_str = analyze_table[top][table_coordinate[symble.top().first]];
            int temp_int = atoi(temp_str.c_str());
            state.push(temp_int);
            //输出格式制定
            if (temp_int >= 10)
                state_print += to_string(temp_int) + " ";
            else
                state_print += to_string(temp_int) + "  ";
            symble_print += temp_dec.left;
            symble_print.append("  ");
        }
        else if (analyze_table[s][table_coordinate[a]] == "ACC")//如果动作为接受
        {
            cout << setiosflags(ios::left) << setw(40) << state_print << setw(20) << input_print << setw(21)
                 << resetiosflags(ios::left) << "SUCCESS!" << endl;
            cout << setiosflags(ios::left) << setw(40) << symble_print << resetiosflags(ios::left) << endl;
            cout << "-----------------------------------------------------------------------------------------" << endl;
            cout << "计算值为:" << symble.top().second << endl;
            return;
        }
        else
        {
            cout << "ERROR!" << endl;
            cout << "-----------------------------------------------------------------------------------------" << endl;
            return;
        }
    } while (true);
}