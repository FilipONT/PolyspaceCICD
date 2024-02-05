#include "functions.h"

int main(void)
{
    func(1);
    func_IDP_test();
    func_NTL();
    func_SLR();
    int x = func_RNI(rand());
    func_DBZ(rand());

    return 0;
}
