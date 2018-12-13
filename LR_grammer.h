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
    string left;//�����ʽ
    string right;//�Ҳ���ʽ
} DEDUCTION;

class LR_grammer
{
    //����ʽ
    vector<DEDUCTION> deductions;
    //�ս���������ս����
    vector<string> nonterminal, terminal;
    //�������������
    map<char, int> table_coordinate;
    //������
    vector<vector<string>> analyze_table;

public:
    //��ʼ��
    void init(DEDUCTION &dd);

    //�����ķ�
    void augmentating_grammer();

    //LR��������
    void analyze_program(string text, vector<double> number);

    //���������ı�
    string text_process(string text, vector<double> &number);
};

#endif //LR_LR_GRAMMER_H