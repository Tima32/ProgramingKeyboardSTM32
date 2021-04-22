#pragma once
#include "FixedString.hpp"

template <size_t capasity>
FixedString<capasity>::FixedString()
{
    str[0] = '\0';
    size = 0;
}

template <size_t capasity>
char* FixedString<capasity>::toCStr()
{
    return str;
}
template<size_t capasity>
const char* FixedString<capasity>::toCStr() const
{
    return str;
}

template<size_t capasity>
size_t FixedString<capasity>::getCapasity() const
{
    return capasity;
}

template<size_t capasity>
size_t FixedString<capasity>::getSize() const
{
    return size;
}

template<size_t capasity>
size_t FixedString<capasity>::readSerial()
{
    for (size_t i = 0; i < capasity; ++i)
    {
        int read_char = cserial.read();
        str[i] = read_char;

        if(str[i] == '\0')
        {
            size = i;
            break;
        }

        if (read_char == -1)
        {
            size = i;
            str[i] = 0;
            break;
        }
    }
    return size;
}

template<size_t capasity>
char& FixedString<capasity>::operator[](size_t i)
{
    return str[i];
}
template<size_t capasity>
const char& FixedString<capasity>::operator[](size_t i) const
{
    return str[i];
}