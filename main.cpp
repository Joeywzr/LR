#include <iostream>
#include "LR_grammer.h"

int main()
{
    LR_grammer lr;
    DEDUCTION dd;

    lr.init(dd);//��ʼ��
    lr.augmentating_grammer();//�����ķ�

    string text;
    cout << "�������Ԥ���ַ���(����#�˳�����)��" << endl;
    cin >> text;
    while (text != "#")
    {
        vector<double> number;
        text = lr.text_process1(text, number);//�����ַ���
        lr.analyze_program1(text, number);//LR��������
        cout << "\n\n�������Ԥ���ַ���(����#�˳�����)��" << endl;
        cin >> text;
    }

    return 0;
}