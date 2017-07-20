#pragma once
#include <stdlib.h>

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
    T* _data;
    size_t _size;
    size_t _capacity;

private:
    void Reallocate();
    bool IsFull() const;
    bool IsOutOfRange(const size_t index) const;

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
    T* pTemp = new T[_size];
    for (size_t i = 0; i < _size; ++i)
    {
        pTemp[i] = _data[i];
    }

    delete[] _data;
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

    --_size;
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

    // end
    _data[index] = value;
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
    _capacity = (_capacity == 0) ? 1 : _capacity * 2;

    T* pTemp = new T[_capacity];
    for (size_t i = 0; i < _size; ++i)
    {
        pTemp[i] = _data[i];
    }

    delete[] _data;
    _data = &pTemp[0];
}

template<class T>
void RD::Vector<T>::PushBack(const T& value)
{
    if (IsFull())
        Reallocate();

    _data[_size++] = value;
}

template<class T>
void RD::Vector<T>::Reserve(const size_t size)
{
    if (_capacity >= size)
        return;

    _capacity = size;
    T* pTemp = new T[_capacity];
    for (size_t i = 0; i < _size; ++i)
    {
        pTemp[i] = _data[i];
    }

    delete[] _data;
    _data = pTemp;
}

template<class T>
void RD::Vector<T>::Resize(const size_t size)
{
    if (_size < size)
    {
        size_t insertCnt = size - _size;
        Insert(_size, insertCnt, T());
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
    if (_data != nullptr)
    {
        delete[] _data;
        _data = nullptr;
    }
}

template<class T>
RD::Vector<T>::Vector() : _data(nullptr), _size(0), _capacity(0)
{

}

}
