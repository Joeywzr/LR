#include <iostream>
#include "LR_grammer.h"

int main()
{
    LR_grammer lr;
    DEDUCTION dd;
    lr.init(dd);
    cout << "ga";
    lr.augmentating_grammer(dd);
    lr.follow_set();

    lr.print_test();
    return 0;
}