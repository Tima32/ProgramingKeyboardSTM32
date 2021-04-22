#pragma once
#include "main.hpp"
#include "FixedString.hpp"

//-------------------[DbgPrint]-----------------//
template <typename T, typename ...Args>
void DebugPrint(T&& arg, Args&&... args)
{
    cserial.print(arg);
    DebugPrint(args ...);
}
template <typename T>
void DebugPrint(T&& arg)
{
    cserial.print(arg);
}

template <typename T>
void DebugPrintLn(T&& arg)
{
    cserial.println(arg);
}
template <typename T, typename ...Args>
void DebugPrintLn(T&& arg, Args&&... args)
{
    cserial.print(arg);
    DebugPrintLn(args ...);
}

//in out in/out
bool ParsParam(const FixedString<256>& str, char const** params, uint8_t& count);

namespace Parameter
{
    //compare parameter
    bool Cmp(const char* param, const char* name);
    uint16_t ahextoi16(const char* str);
}