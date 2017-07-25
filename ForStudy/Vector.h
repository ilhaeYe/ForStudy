#pragma once
#include <stdlib.h>
#include <xmemory0>

namespace RD
{
template<class T>
class Vector
{
public:
    class Iterator
    {
    public:
        Iterator(const Vector<T>* ptr, size_t pos)
            : _ptr(ptr)
            , _pos(pos)
        {}

        // Range based for loop use below methods
        bool operator!=(const Iterator& other) const
        {
            return _pos != other._pos;
        }

        int operator*() const
        {
            return _ptr->At(_pos);
        }

        const Iterator operator++()
        {
            ++_pos;
            return *this;
        }

    private:
        const Vector<T>* _ptr;
        size_t _pos;

    };

    class Allocator
    {
    public:
        Allocator() {};
        ~Allocator() {};

        T* Allocate(size_t size)
        {
            return static_cast<T*> (::operator new(sizeof(T) * size));
        }
        template<class... ARGS>
        void Construct(T* ptr, ARGS&&... args)
        {
            new(ptr) T(std::forward<ARGS>(args)...);
        }
        void Deallocate(T* ptr, size_t size)
        {
            ::operator delete(ptr);
        }
        void Destroy(T* ptr)
        {
            ptr->~T();
        }

    private:

    };

public:
    Vector();
    ~Vector();

    size_t Size() const;
    size_t Capacity() const;

    void Resize(const size_t size);
    void Reserve(const size_t size);

    void Erase(const size_t index);
    void Erase(const size_t startIndex, const size_t endIndex);
    void Insert(const size_t index, const T& value);
    void Insert(const size_t index, const size_t count, const T& value);
    void PushBack(const T& value);
    T At(const size_t index) const;

    void ShrinkToFit();

    void Clear();

    Iterator begin() const { return Iterator(this, 0); }
    Iterator end() const { return Iterator(this, _size); }

    T& operator[](const size_t index);
    const T& operator[](const size_t index) const;

private:
    void Reallocate();
    bool IsFull() const;
    bool IsOutOfRange(const size_t index) const;

private:
    T* _data;
    size_t _size;
    size_t _capacity;
    Allocator _alloc;

};

template<class T>
T RD::Vector<T>::At(const size_t index) const
{
    assert(!IsOutOfRange(index));
    return _data[index];
}

template<class T>
void RD::Vector<T>::Clear()
{
    if (_data == nullptr)
    {
        delete[] _data;
        _data = nullptr;
    }

    _size = 0;
    _capacity = 0;
}

template<class T>
void RD::Vector<T>::ShrinkToFit()
{
    T* pTemp = _alloc.Allocate(_size);
    for (size_t i = 0; i < _size; ++i)
        _alloc.Construct(&pTemp[i], _data[i]);

    for (size_t i = 0; i < _size; ++i)
        _alloc.Destroy(&_data[i]);

    _alloc.Deallocate(_data, _capacity);
    _data = pTemp;
    _capacity = _size;
}

template<class T>
T& RD::Vector<T>::operator[](const size_t index)
{
    assert(!IsOutOfRange(index));
    return _data[index];
}

template<class T>
const T& RD::Vector<T>::operator[](const size_t index) const
{
    assert(!IsOutOfRange(index));
    return _data[index];
}

template<class T>
void RD::Vector<T>::Insert(const size_t index, const size_t count, const T& value)
{
    assert(index == _size || !IsOutOfRange(index));
    assert(count > 0);

    size_t startIndex = index;
    for (size_t i = 0; i < count; ++i)
    {
        Insert(startIndex++, value);
    }
}

template<class T>
void RD::Vector<T>::Erase(const size_t startIndex, const size_t endIndex)
{
    assert(!IsOutOfRange(startIndex));
    assert(!IsOutOfRange(endIndex));

    for (size_t i = endIndex; i >= startIndex; --i)
    {
        Erase(i);
    }
}

template<class T>
bool RD::Vector<T>::IsOutOfRange(const size_t index) const
{
    return !(index >= 0 && index < _size);
}

template<class T>
void RD::Vector<T>::Erase(const size_t index)
{
    assert(!IsOutOfRange(index));

    // move
    for (size_t i = index; i < _size - 1; ++i)
    {
        _data[i] = _data[i + 1];
    }

    _alloc.Destroy(&_data[_size--]);
}

template<class T>
void RD::Vector<T>::Insert(const size_t index, const T& value)
{
    assert(index == _size || !IsOutOfRange(index));

    if (IsFull())
        Reallocate();

    // move
    for (size_t i = _size; i > index; --i)
    {
        _data[i] = _data[i - 1];
    }

    // insert
    _alloc.Construct(&_data[index], value);
    ++_size;
}

template<class T>
bool RD::Vector<T>::IsFull() const
{
    return _size == _capacity;
}

template<class T>
void RD::Vector<T>::Reallocate()
{
    const size_t newCapacity = (_capacity == 0) ? 1 : _capacity * 2;

    T* pTemp = _alloc.Allocate(newCapacity);
    for (size_t i = 0; i < _size; ++i)
        _alloc.Construct(&pTemp[i], _data[i]);

    for (size_t i = 0; i < _size; ++i)
        _alloc.Destroy(&_data[i]);

    _alloc.Deallocate(_data, _capacity);

    _data = pTemp;
    _capacity = newCapacity;
}

template<class T>
void RD::Vector<T>::PushBack(const T& value)
{
    if (IsFull())
        Reallocate();

    _alloc.Construct(&_data[_size++], value);
}

template<class T>
void RD::Vector<T>::Reserve(const size_t size)
{
    if (_capacity >= size)
        return;

    T* pTemp = _alloc.Allocate(size);
    for (size_t i = 0; i < _size; ++i)
        _alloc.Construct(&pTemp[i], _data[i]);

    for (size_t i = 0; i < _size; ++i)
        _alloc.Destroy(&_data[i]);

    _alloc.Deallocate(_data, _capacity);

    _data = pTemp;
    _capacity = size;
}

template<class T>
void RD::Vector<T>::Resize(const size_t size)
{
    if (_size < size)
    {
        //size_t newCount = size - _size;
        T* pTemp = _alloc.Allocate(size);
        for (size_t i = 0; i < _size; ++i)
            pTemp[i] = _data[i];

        for (size_t i = _size; i < size; ++i)
            _alloc.Construct(&pTemp[i]);

        for (size_t i = 0; i < _size; ++i)
            _alloc.Destroy(&_data[i]);

        _alloc.Deallocate(_data, _capacity);

        _data = pTemp;
        _capacity = size;
        _size = size;
    }
    else if (_size > size)
    {
        Erase(size, _size - 1);
    }
}

template<class T>
size_t RD::Vector<T>::Capacity() const
{
    return _capacity;
}

template<class T>
size_t RD::Vector<T>::Size() const
{
    return _size;
}

template<class T>
RD::Vector<T>::~Vector()
{
    // TODO
    // if (_alloc.address() != nullptr) XXXXX
    // if (_alloc.max_size() > 0)
    if (_size > 0) // enough?
    {
        for (size_t i = 0; i < _size; ++i)
        {
            _alloc.Destroy(&_data[i]);
        }
        _alloc.Deallocate(_data, _capacity);

        // have to?
        _size = 0;
        _capacity = 0;
        _data = nullptr;
    }
}

template<class T>
RD::Vector<T>::Vector()
    : _data(nullptr), _size(0), _capacity(0), _alloc(Allocator())
{

}

}
