//
// Created by Memo on 2018/12/8.
//

#include "LR_grammer.h"

void LR_grammer::init(DEDUCTION &dd)
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
            {"ERR","ERR", "ERR", "ERR", "S4",  "ERR", "S5" , "ERR", "1",   "2",   "3"},
            {"S6", "S7",  "ERR", "ERR", "ERR", "ERR", "ERR" ,"ACC", "ERR", "ERR", "ERR"},
            {"R3", "R3",  "S8",  "S9",  "ERR", "R3",  "ERR", "R3",  "ERR", "ERR", "ERR"},
            {"R6", "R6",  "R6",  "R6",  "ERR", "R6",  "ERR", "R6",  "ERR", "ERR", "ERR"},
            {"ERR","ERR", "ERR", "ERR", "S4",  "ERR", "S5",  "ERR", "10",   "2",  "3"},
            {"R8", "R8",  "R8",  "R8",  "ERR", "R8",  "ERR", "R8",  "ERR", "ERR", "ERR"},
            {"ERR","ERR", "ERR", "ERR", "S4",  "ERR", "S5",  "ERR", "ERR", "11",  "3"},
            {"ERR","ERR", "ERR", "ERR", "S4",  "ERR", "S5",  "ERR", "ERR", "12",  "3"},
            {"ERR","ERR", "ERR", "ERR", "S4",  "ERR", "S5",  "ERR", "ERR", "ERR", "13"},
            {"ERR","ERR", "ERR", "ERR", "S4",  "ERR", "S5",  "ERR", "ERR", "ERR", "14"},
            {"S6", "S7",  "ERR", "ERR", "ERR", "S15", "ERR", "ERR", "ERR", "ERR", "ERR"},
            {"R1", "R1",  "S8",  "S9",  "ERR", "R1",  "ERR", "R1",  "ERR", "ERR", "ERR"},
            {"R2", "R2",  "S8",  "S9",  "ERR", "R2",  "ERR", "R2",  "ERR", "ERR", "ERR"},
            {"R4", "R4",  "R4",  "R4",  "ERR", "R4",  "ERR", "R4",  "ERR", "ERR", "ERR"},
            {"R5", "R5",  "R5",  "R5",  "ERR", "R5",  "ERR", "R5",  "ERR", "ERR", "ERR"},
            {"R7", "R7",  "R7",  "R7",  "ERR", "R7",  "ERR", "R7",  "ERR", "ERR", "ERR"}
    };
    table_coordinate = {{'+',0},{'-',1},{'*',2},{'/',3},{'(',4},{')',5},{'n',6},{'$',7},{'E',8},{'T',9},{'F',10} };
}

void LR_grammer::augmentating_grammer()
{
    nonterminal[0] = "S";
    deductions[0].left = "S";
    deductions[0].right = "E";
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
    for (auto i:deductions)
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

void LR_grammer::analyze_program(string text)
{
    text.append("$");
    stack<char> symble;
    stack<int> state;
    state.push(0);
    symble.push('-');
    int cur = 0;
    int s;
    char a;

    do{
        s = state.top();
        a = text[cur];
        if(analyze_table[s][table_coordinate[a]][0] == 'S')
        {
            symble.push(a);
            string temp_str = analyze_table[s][table_coordinate[a]].substr(1,analyze_table[s][table_coordinate[a]].size() - 1);
            int temp_int = atoi(temp_str.c_str());
            state.push(temp_int);
            cur++;
            cout << "Shift " << state.top() << endl;
        }
        else if(analyze_table[s][table_coordinate[a]][0] == 'R')
        {
            DEDUCTION temp_dec = deductions[analyze_table[s][table_coordinate[a]][1] - '0'];
            int length = temp_dec.right.size();
            while(length--)
            {
                symble.pop();
                state.pop();
            }
            int top = state.top();
            symble.push(temp_dec.left[0]);
            string temp_str = analyze_table[top][table_coordinate[symble.top()]];
            int temp_int = atoi(temp_str.c_str());
            state.push(temp_int);
            cout << "reduce by " << temp_dec.left << " -> " << temp_dec.right << endl;
        }
        else if(analyze_table[s][table_coordinate[a]] == "ACC")
        {
            cout << "SUCCESS!" << endl;
            return;
        }

        else
        {
            cout << "ERROR!" << endl;
            return;
        }
    }while(1);
}

string LR_grammer::text_process(string text)
{
    int cur = 0;
    int length = text.size();
    int state = 0;
    string after;
    while(length--)
    {
        if(text[cur] > '0' && text[cur] < '9')
        {
            if(state == 0)
            {
                after += 'n';
                state = 1;
            }
            else if(state == 3 || state == 4)
                state = 5;
            cur++;
        }
        else if(text[cur] == '.')
        {
            if(state == 1)
                state = 2;
            else
                return "NUMBER ERROR";
            cur++;
        }
        else if(text[cur] == 'e' || text[cur] == 'E')
        {
            if(state == 1 || state == 2)
                state = 3;
            else
                return "NUMBER ERROR";
            cur++;
        }
        else if(text[cur] == '+' || text[cur] == '-')
        {
            if(state == 3)
                state = 4;
            else
            {
                after += text[cur];
                state = 0;
            }
            cur++;
        }
        else if(text[cur] == '*' || text[cur] == '/' || text[cur] == '(' || text[cur] == ')')
        {
            after += text[cur];
            state = 0;
            cur++;
        }
        else
            return "NUMBER ERROR";
    }
    return after;
}