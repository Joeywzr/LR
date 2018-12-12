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
        text = lr.text_process(text);//�����ַ���
        lr.analyze_program(text);//LR��������
        cout << "\n\n�������Ԥ���ַ���(����#�˳�����)��" << endl;
        cin >> text;
    }

    return 0;
}