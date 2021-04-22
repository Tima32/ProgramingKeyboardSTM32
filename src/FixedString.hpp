#pragma once
#include "main.hpp"

template <size_t capasity>
class FixedString
{
public:
    FixedString();

    char* toCStr();
    const char* toCStr()const;
    size_t getCapasity() const;
    size_t getSize() const;

    size_t readSerial();

    char& operator[](size_t i);
    const char& operator[](size_t i) const;
private:
    char str[capasity];
    size_t size;
};

#include "FixedString.inl"