#include "MainFunction.h"

#include <iostream>
#include <vector>
#include <ctime>

#include "Array.h"
#include "Vector.h"

void MainArrayFunction::Run()
{
    /* My array */
    RD::Array<int, 10> myArr;
    RD::Array<int, 10> tempArr;
    //MyArray<int, 1> swapArr; // compile error
    //MyArray<float, 10> swapArr; // compile error

    size_t maxSize = myArr.Size();
    myArr.Fill(10);
    myArr[4] = 72;
    tempArr.Fill(45);
    //myArr[12] = 150; // runtime error

    myArr.Swap(tempArr);

    for (int i = 0; i < myArr.Size(); ++i)
    {
        std::cout << myArr[i] << ",";
    }

    std::cout << std::endl;

    for (int i = 0; i < tempArr.Size(); ++i)
    {
        std::cout << tempArr[i] << ",";
    }

}

void MainVectorFunction::Run()
{
    {
    /* My vector */
    RD::Vector<int> vec;
    vec.PushBack(1);
    vec.PushBack(2);
    vec.PushBack(3);
    vec.PushBack(4);
    vec.PushBack(5);

    for (size_t i = 0; i < vec.Size(); ++i)
    {
        const int val = vec[i];
        std::cout << val << ",";
    }
    std::cout << std::endl;

    std::cout << "size : " << vec.Size() << " capacity : " << vec.Capacity() << std::endl;

    vec.Resize(10);
    std::cout << "size : " << vec.Size() << " capacity : " << vec.Capacity() << std::endl;
    vec.Resize(3);
    std::cout << "size : " << vec.Size() << " capacity : " << vec.Capacity() << std::endl;
    vec.Reserve(10);
    std::cout << "size : " << vec.Size() << " capacity : " << vec.Capacity() << std::endl;

    vec.ShrinkToFit();
    std::cout << "size : " << vec.Size() << " capacity : " << vec.Capacity() << std::endl;
    }

    {
    // performance test compare with std data structure
    std::vector<int> stdVec;
    RD::Vector<int> myVec;
    std::clock_t begin = clock();
    std::clock_t end = clock();
    double elapsed_secs = 0.0f;

    begin = clock();
    for (int j = 0; j < 100; ++j)
    {
        stdVec.clear();
        for (int i = 0; i < 10000; ++i)
        {
            stdVec.push_back(i);
        }
    }
    end = clock();

    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "time : " << elapsed_secs << std::endl;

    begin = clock();
    for (int j = 0; j < 100; ++j)
    {
        myVec.Clear();
        for (int i = 0; i < 10000; ++i)
        {
            myVec.PushBack(i);
        }
    }
    end = clock();

    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "time : " << elapsed_secs << std::endl;
    /*
    // release
    time : 0.005
    time : 0.006
    */

    /*
    // size : 100.000
    // release
    time : 0.004
    time : 0.009

    // debug
    time : 0.26 (!?) >> std data-structure has debugging function.
    time : 0.009
    */
    }

}
