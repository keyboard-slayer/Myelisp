#include "istype.h"

#include <stddef.h>
#include <string.h>
#include <ctype.h>

bool isnumber(char const *s)
{
    bool ret = true;

    for (size_t i = (s[0] == '-' ? 1 : 0); i < strlen(s); i++)
    {
        if (isdigit(s[i]) == 0)
        {
            ret = false;
        }
    }

    return (s[0] == '-' && strlen(s) == 1) ? false : ret;
}

bool isfloat(char const *s)
{
    bool has_digit = false;
    bool found_dot = false;
    bool ret = true;

    for (size_t i = (s[0] == '-' ? 1 : 0); i < strlen(s); i++)
    {
        if (found_dot && s[i] == '.' && !isdigit(s[i]))
        {
            ret = false;
        }

        if (isdigit(s[i]))
        {
            has_digit = true;
        }

        if (s[i] == '.')
        {
            found_dot = true;
        }
    }

    return found_dot && has_digit && ret;
}

bool isstr(char const *s)
{
    if (s[0] != '\"')
    {
        return 0;
    }

    size_t i;

    for (i = 1; i < strlen(s); i++)
    {
        if (s[i] == '\\')
        {
            i++;
        }

        if (s[i] == '\"' && s[i + 1] != 0)
        {
            return false;
        }
    }

    if (s[i - 1] != '\"')
    {
        return false;
    }

    return true;
}
