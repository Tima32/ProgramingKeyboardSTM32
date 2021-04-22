#include "Functions.hpp"

bool ParsParam(const FixedString<256>& str, char const** params, uint8_t& count)
{
    uint8_t param_count = 1;
    params[0] = &str[0];

    for (size_t i = 0; str[i] != '\0'; i++)
    {
        if(str[i] == ' ' && str[i+1] != '\0')
        {
            if ( param_count == count)
            {
                count = param_count;
                return false;
            }
            params[param_count] = &str[i+1];
            param_count++;
        }
    }
    count = param_count;
    return true;
}

namespace Parameter
{
    //compare parameter
    bool Cmp(const char* param, const char* name)
    {
        while (true)
        {
           if (*param == *name)
            {
                if (*param == '\0')
                    return true;
                param++;
                name++;
            }
            else if (*param == ' ' || *param == '\0')
            {
                return true;
            }
            else
            {
                return false;
            }
        
        }
    
    }
    uint16_t ahextoi16(const char* str)
    {
        uint16_t num = 0;

        while(true)
        {
            if ('0' <= *str && *str <= '9')
            {
                num *= 16;
                num += *str - '0';
            }
            else if('A' <= *str && *str <= 'F')
            {
                num *= 16;
                num += *str - 'A' + 10;
            }
            else if('a' <= *str && *str <= 'f')
            {
                num *= 16;
                num += *str - 'a' + 10;
            }
            else
            {
                break;
            }
            str++;
        }
        return num;
    }
}