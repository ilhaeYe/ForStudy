#include "MainFunction.h"
#define _CRTDBG_MAP_ALLOC #include <stdlib.h> #include <crtdbg.h>

int main()
{
    MainFunction* pFunc;
    //pFunc = new MainArrayFunction();
    pFunc = new MainVectorFunction();
    //pFunc = new MainUnionFunction();
    //pFunc = new MainAllocatorFunction();

    pFunc->Run();

    delete pFunc;
    _CrtDumpMemoryLeaks();
    return 0;
}