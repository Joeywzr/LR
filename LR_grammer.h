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
    //����ʽ
    vector<DEDUCTION> deduction;
    //�ս���������ս����
    vector<string> nonterminal, terminal;
    //first����follow��
    map<string, vector<string>> first, follow;
    //��ʼ��
    string start;

public:
    //��ʼ��
    void init(DEDUCTION &dd);
    //�����ķ�
    void augmentating_grammer(DEDUCTION &dd);
    //���ɸ����ս����first��
    void first_set();
    //���ɸ����ս����follow��
    void follow_set();
    //��ȡfirst��
    vector<string> get_first_set(string to_get_first);
    //��ȡfollow��
    vector<string> get_follow_set(string to_get_follow);

    void print_test();
};


#endif //LR_LR_GRAMMER_H
