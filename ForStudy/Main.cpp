#include "MainFunction.h"

int main()
{
    MainFunction* pFunc;
    //pFunc = new MainArrayFunction();
    //pFunc = new MainVectorFunction();
    //pFunc = new MainUnionFunction();
    pFunc = new MainAllocatorFunction();

    pFunc->Run();

    return 0;
}