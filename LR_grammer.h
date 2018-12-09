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
} DEDUCTION;
class LR_grammer
{
    //产生式
    vector<DEDUCTION> deduction;
    //终结符集、非终结符集
    vector<string> nonterminal, terminal;
    //first集、follow集
    map<string, vector<string>> first, follow;
    //起始符
    string start;

public:
    //初始化
    void init(DEDUCTION &dd);
    //增广文法
    void augmentating_grammer(DEDUCTION &dd);
    //生成各非终结符的first集
    void first_set();
    //生成各非终结符的follow集
    void follow_set();
    //获取first集
    vector<string> get_first_set(string to_get_first);
    //获取follow集
    vector<string> get_follow_set(string to_get_follow);

    void print_test();
};


#endif //LR_LR_GRAMMER_H
