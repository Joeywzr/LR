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
    string left;//左产生式
    string right;//右产生式
} DEDUCTION;

class LR_grammer
{
    //产生式
    vector<DEDUCTION> deductions;
    //终结符集、非终结符集
    vector<string> nonterminal, terminal;
    //分析表的列坐标
    map<char, int> table_coordinate;
    //分析表
    vector<vector<string>> analyze_table;

public:
    //初始化
    void init(DEDUCTION &dd);

    //增广文法
    void augmentating_grammer();

    //LR分析程序
    void analyze_program(string text, vector<double> number);

    //处理输入文本
    string text_process(string text, vector<double> &number);
};

#endif //LR_LR_GRAMMER_H