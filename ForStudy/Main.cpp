#include "MainFunction.h"

int main()
{
    MainFunction* pFunc;
    //pFunc = new MainArrayFunction();
    pFunc = new MainVectorFunction();

    pFunc->Run();

    return 0;
}