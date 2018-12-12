//
// Created by Memo on 2018/12/8.
//

#ifndef LR_LR_GRAMMER_H
#define LR_LR_GRAMMER_H
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <map>
#include <string>
#include <iomanip>
#include <stack>
using namespace std;

typedef struct DEDUCTION
{
    string left;
    string right;
    int pos;
} DEDUCTION;
class LR_grammer
{
    //产生式
    vector<DEDUCTION> deductions,item;

    vector<vector<DEDUCTION>> dfa;
    //终结符集、非终结符集
    vector<string> nonterminal, terminal;
    //first集、follow集
    map<string, vector<string>> first, follow;
    //分析表的列坐标
    map<char, int> table_coordinate;
    //分析表
    vector<vector<string>> analyze_table;

public:
    //初始化
    void init(DEDUCTION &dd);
    //增广文法
    void augmentating_grammer();
    //生成各非终结符的follow集
    void follow_set();
    //获取follow集
    vector<string> get_follow_set(string to_get_follow);
    //打印follow集
    void print_test();
    //LR分析程序
    void analyze_program(string text);
    //处理输入文本
    string text_process(string text);


};


#endif //LR_LR_GRAMMER_H
