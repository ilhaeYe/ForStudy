#pragma once
#include <assert.h>
#include <algorithm>

namespace RD
{
    template <class T, size_t TSize>
    class Array
    {
    public:
        Array() = default;
        ~Array() = default;

        T& operator[](const size_t index);
        const T& operator[](const size_t index) const;
        void Fill(const T& value);
        void Swap(Array<T, TSize>& rhs);

        size_t Size() const;

    private:
        T _data[TSize];

    };

    template <class T, size_t TSize>
    void Array<T, TSize>::Swap(Array<T, TSize>& rhs)
    {
        std::swap(_data, rhs._data);
    }

    template <class T, size_t TSize>
    size_t Array<T, TSize>::Size() const
    {
        return TSize;
    }

    template <class T, size_t TSize>
    void Array<T, TSize>::Fill(const T& value)
    {
        for (size_t i = 0; i < TSize; ++i)
        {
            _data[i] = value;
        }
    }

    template <class T, size_t TSize>
    T& Array<T, TSize>::operator[](const size_t index)
    {
        assert(index >= 0 && index < TSize);
        return _data[index];
    }

    template <class T, size_t TSize>
    const T& Array<T, TSize>::operator[](const size_t index) const
    {
        assert(index >= 0 && index < TSize);
        return _data[index];
    }
}
