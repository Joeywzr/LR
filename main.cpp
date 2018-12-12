#include <iostream>
#include "LR_grammer.h"

int main()
{
    LR_grammer lr;
    DEDUCTION dd;

    lr.init(dd);//初始化
    lr.augmentating_grammer();//增广文法

    string text;
    cout << "请输入待预测字符串(输入#退出程序)：" << endl;
    cin >> text;
    while (text != "#")
    {
        text = lr.text_process(text);//处理字符串
        lr.analyze_program(text);//LR分析程序
        cout << "\n\n请输入待预测字符串(输入#退出程序)：" << endl;
        cin >> text;
    }

    return 0;
}