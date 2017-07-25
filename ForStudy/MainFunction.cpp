#include "MainFunction.h"

#include <iostream>
#include <vector>
#include <ctime>

#include "Array.h"
#include "Vector.h"
#include <xmemory0>

// Array -----------------------------------------------------------
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
// ~Array -----------------------------------------------------------

// Vector -----------------------------------------------------------
void MainVectorFunction::Run()
{
    //{
    ///* My vector */
    //RD::Vector<int> vec;
    //vec.PushBack(1);
    //vec.PushBack(2);
    //vec.PushBack(3);
    //vec.PushBack(4);
    //vec.PushBack(5);

    //for (size_t i = 0; i < vec.Size(); ++i)
    //{
    //    const int val = vec[i];
    //    std::cout << val << ",";
    //}
    //std::cout << std::endl;

    //std::cout << "size : " << vec.Size() << " capacity : " << vec.Capacity() << std::endl;

    //vec.Resize(10);
    //std::cout << "size : " << vec.Size() << " capacity : " << vec.Capacity() << std::endl;
    //vec.Resize(3);
    //std::cout << "size : " << vec.Size() << " capacity : " << vec.Capacity() << std::endl;
    //vec.Reserve(10);
    //std::cout << "size : " << vec.Size() << " capacity : " << vec.Capacity() << std::endl;

    //vec.ShrinkToFit();
    //std::cout << "size : " << vec.Size() << " capacity : " << vec.Capacity() << std::endl;
    //}

    //{
    //// performance test compare with std data structure
    //std::vector<int> stdVec;
    //RD::Vector<int> myVec;
    //std::clock_t begin = clock();
    //std::clock_t end = clock();
    //double elapsed_secs = 0.0f;

    //begin = clock();
    //for (int j = 0; j < 100; ++j)
    //{
    //    stdVec.clear();
    //    for (int i = 0; i < 10000; ++i)
    //    {
    //        stdVec.push_back(i);
    //    }
    //}
    //end = clock();

    //elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    //std::cout << "time : " << elapsed_secs << std::endl;

    //begin = clock();
    //for (int j = 0; j < 100; ++j)
    //{
    //    myVec.Clear();
    //    for (int i = 0; i < 10000; ++i)
    //    {
    //        myVec.PushBack(i);
    //    }
    //}
    //end = clock();

    //elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    //std::cout << "time : " << elapsed_secs << std::endl;
    ///*
    //// release
    //time : 0.005
    //time : 0.006
    //*/

    ///*
    //// size : 100.000
    //// release
    //time : 0.004
    //time : 0.009

    //// debug
    //time : 0.26 (!?) >> std data-structure has debugging function.
    //time : 0.009
    //*/
    //}

    //// Iterator
    //{
    //    int size = 5;
    //    RD::Vector<int> vec;
    //    vec.Reserve(size);
    //    for (int i = 0; i < size; ++i)
    //    {
    //        vec.PushBack(i);
    //    }

    //    for (auto it = vec.begin(); it != vec.end(); ++it)
    //    {
    //        std::cout << (*it) << std::endl;
    //    }
    //    std::cout << std::endl;

    //    for (auto num : vec)
    //    {
    //        std::cout << num << std::endl;
    //    }
    //}

    {
        //std::vector<Integer> vec;
        //vec.reserve(10);
        //vec.emplace_back(Integer::Create(1));
        //vec.resize(10);

        //RD::Vector<Integer> vec;
        //vec.Reserve(10);
        //vec.PushBack(Integer::Create(1));
        //vec.PushBack(Integer::Create(2));
        //vec.PushBack(Integer::Create(3));
        //vec.PushBack(Integer::Create(4));
        //vec.Erase(0);

        RD::Vector<int> vec;
        vec.Reserve(10);
        vec.PushBack(1);
        vec.PushBack(2);
        vec.PushBack(3);
        vec.PushBack(4);
        vec.Erase(0);
        vec.Resize(2);
        vec.ShrinkToFit();

        for (size_t i = 0; i < vec.Size(); ++i)
        {
            std::cout << vec[i] << std::endl;
        }
    }
}
// ~Vector -----------------------------------------------------------

// Union -----------------------------------------------------------
void MainUnionFunction::Run()
{
    // Characteristic of Union
    using byte = unsigned char;
    using u32 = unsigned int;

    struct size_byte_t
    {
        byte b1;
        byte b2;
        byte b3;
        byte b4;
    };

    union size_data_t
    {
        u32 size;
        size_byte_t bytes;
    };

    size_data_t s_data;
    s_data.size = 0x12345678;

    printf("b1=%2x b2=%2x b3=%2x b4=%2x",
        s_data.bytes.b1, s_data.bytes.b2, s_data.bytes.b3, s_data.bytes.b3);

    // why do we need union?
    Initialize();
    while (!_inputs.empty())
    {
        Input i = _inputs.front();
        switch (i.type)
        {
        case WeatherType::Temperature:
            processTemperature(i.temperData);
            break;
        case WeatherType::Wind:
            processWind(i.windData);
            break;
        }
        _inputs.pop();
    }
}

void MainUnionFunction::Initialize()
{
    Input first, second;

    first.type = WeatherType::Temperature;
    first.temperData = { 101, 19890806.0, 91.8, 108.5, 67.2 };
    _inputs.push(first);

    second.type = WeatherType::Wind;
    second.windData = { 204, 19890101.0, 14.0, 27.5 };
    _inputs.push(second);
}
// ~Union -----------------------------------------------------------

// ~Allocator -----------------------------------------------------------
void MainAllocatorFunction::Run()
{
    class Dummy
    {
    public:
        Dummy(int i) : _i(i) { std::cout << "ctor" << std::endl; };
        ~Dummy() { std::cout << "dtor" << std::endl; };

        int GetI() const { return _i; }

    private:
        int _i;

    };

    std::allocator<Dummy> alloc;
    Dummy* pDummy = alloc.allocate(5);
    alloc.construct(pDummy, Dummy(5));
    alloc.construct(&pDummy[1], Dummy(3));

    std::cout << pDummy[0].GetI() << std::endl;
    std::cout << pDummy[1].GetI() << std::endl;
    std::cout << pDummy[10].GetI() << std::endl;

    //alloc.destroy(pDummy);
    alloc.deallocate(pDummy, 5);

    std::cout << pDummy[0].GetI() << std::endl;
    std::cout << pDummy[1].GetI() << std::endl;
    std::cout << pDummy[10].GetI() << std::endl;

    // output
    /*
    5
    3
    -823578275

    -823578275
    -823578275
    -823578275
    */

}
