//
// Created by Memo on 2018/12/8.
//

#include "LR_grammer.h"

void LR_grammer::init(DEDUCTION &dd)
{
    start = "E";
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

    dd.left = "E";
    dd.right = "E+T";
    deduction.push_back(dd);
    dd.right = "E-T";
    deduction.push_back(dd);
    dd.right = "T";
    deduction.push_back(dd);

    dd.left = "T";
    dd.right = "T*F";
    deduction.push_back(dd);
    dd.right = "T/F";
    deduction.push_back(dd);
    dd.right = "F";
    deduction.push_back(dd);

    dd.left = "F";
    dd.right = "(E)";
    deduction.push_back(dd);
    dd.right = "n";
    deduction.push_back(dd);
}

void LR_grammer::augmentating_grammer(DEDUCTION &dd)
{
    nonterminal.emplace_back("S");
    start = "S";
    dd.left = "S";
    dd.right = "E";
    deduction.push_back(dd);
}

vector<string> LR_grammer::get_first_set(string to_get_first)//构建first集
{
    vector<string> mid;
    for (auto i:deduction) {
        if (i.left == to_get_first) {
            auto iter = first.find(to_get_first);
            if (iter != first.end())
                mid = first[to_get_first];
            string head = i.right.substr(0, 1);
            for (auto nt:nonterminal) {
                if (head[0] == nt[0]) {
                    return get_first_set(head);
                }
            }
            for (auto t:terminal) {
                if (head[0] == t[0]) {
                    if (find(mid.begin(), mid.end(), t) == mid.end())//若没有该终结符，则加入first集
                        mid.push_back(t);
                    break;
                }
            }
        }
    }
    return mid;
}

void LR_grammer::first_set()
{
    for (auto i:nonterminal)
        first[i] = get_first_set(i);
}

void LR_grammer::follow_set()
{
    for (auto i:nonterminal)
        follow[i] = get_follow_set(i);
}

vector<string> LR_grammer::get_follow_set(string to_get_follow)//构建follow集
{
    if (!follow[to_get_follow].empty())
        return follow[to_get_follow];
    vector<string> mid;
    vector<string>::iterator it;
    if (to_get_follow == "S")
    {
        mid.emplace_back("$");
        return mid;
    }
    for (auto i:deduction)
    {
        int pos = i.right.find(to_get_follow);
        if(pos >= 0 && pos != i.right.size() - 1)
        {
            string after = i.right.substr(pos+1, 1);
            for(it = terminal.begin();it != terminal.end();it++)
            {
                if(*it == after)
                {
                    if(find(mid.begin(), mid.end(), *it) == mid.end())
                        mid.push_back(after);
                    break;
                }
            }
            for(it = nonterminal.begin();it != nonterminal.end();it++)
            {
                if(*it == after)
                {
                    vector<string> temp = get_follow_set(after);
                    for(it = temp.begin();it != temp.end();it++)
                    {
                        if(find(mid.begin(), mid.end(), *it) == mid.end())
                            mid.push_back(*it);
                    }
                    break;
                }
            }
        }
        else if(pos >= 0 && pos == i.right.size() - 1)
        {
            vector<string> temp = get_follow_set(i.left);
            for(it = temp.begin();it != temp.end();it++)
            {
                if(find(mid.begin(), mid.end(), *it) == mid.end())
                    mid.push_back(*it);
            }
        }
    }
    return mid;
}

void LR_grammer::print_test()
{

    cout << "---------------------------" << endl;
    cout << "follow集:" << endl;
    for (auto i:follow) {
        cout << i.first << " : ";
        for (int j = 0; j < i.second.size(); j++)
            if (j == i.second.size() - 1)
                cout << i.second[j];
            else
                cout << i.second[j] << " , ";
        cout << endl;
    }
}