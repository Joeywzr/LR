#include <iostream>
#include "LR_grammer.h"

int main()
{
    LR_grammer lr;
    DEDUCTION dd;

    lr.init(dd);
    lr.augmentating_grammer();
    lr.follow_set();

    string text;
    cout << "ÇëÊäÈë´ýÔ¤²â×Ö·û´®£º" << endl;
    cin >> text;

    text = lr.text_process(text);
    lr.analyze_program(text);

    return 0;
}