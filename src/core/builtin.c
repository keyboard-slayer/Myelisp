#include "builtin.h"
#include "types.h"

#include "utils/map.h"

#include <stdio.h>

Type myelisp_print(Type ast)
{
    Type tmp;
    int i;

    vec_foreach(&ast.as_list, tmp, i)
    {
        switch (tmp.type)
        {
            case MYELISP_STRING:
            {
                printf("\"%s\"", tmp.as_str);
                break;
            }

            case MYELISP_FLOAT:
            {
                printf("%lf", tmp.as_float);
                break;
            }

            case MYELISP_CHAR:
            {
                printf("%c", tmp.as_chr);
                break;
            }

            case MYELISP_INT:
            {
                printf("%ld", tmp.as_int);
                break;
            }

            case MYELISP_LIST:
            {
                myelisp_print(tmp);
                break;
            }

            case MYELISP_SYMBOL:
            {
                printf("%s", tmp.as_str);
                break;
            }

            case MYELISP_NIL:
            {
                printf("nil");
                break;
            }

            case MYELISP_TRUE:
            {
                printf("#t");
                break;
            }

            default:
            {
                printf("???\n");
                exit(1);
                break;
            }
        }
    }

    printf("\n");

    return NIL;
}

Type myelisp_plus(Type ast)
{
    Type tmp;
    int i;
    double sum = 0;
    bool is_float = false;

    vec_foreach(&ast.as_list, tmp, i)
    {
        switch (tmp.type)
        {
            case MYELISP_INT:
            {
                sum += tmp.as_int;
                break;
            }
            
            case MYELISP_FLOAT:
            {
                is_float = true;
                sum += tmp.as_float;
                break;
            }

            default:
            {
                fprintf(stderr, "sum: invalid type\n");
                exit(1);
            }
        }
    }

    if (is_float)
    {
        tmp.type = MYELISP_FLOAT;
        tmp.as_float = sum;
    }
    else  
    {
        tmp.type = MYELISP_INT;
        tmp.as_int = sum;
    }

    return tmp;
}

Type myelisp_minus(Type ast)
{
    bool has_value = false;
    bool is_float = false;

    Type tmp;
    int i;
    double sum = 0;

    vec_foreach(&ast.as_list, tmp, i)
    {
        switch (tmp.type)
        {
            case MYELISP_INT:
            {
                if (!has_value)
                {
                    sum = tmp.as_int;
                }
                else  
                {
                    sum -= tmp.as_int;
                }

                break;
            }

            case MYELISP_FLOAT:
            {
                is_float = true;

                if (!has_value)
                {
                    sum = tmp.as_float;
                }
                else  
                {
                    sum -= tmp.as_float;
                }

                break;
            }

            default:
            {
                fprintf(stderr, "substraction: invalid type\n");
                exit(1);
            }
        }
    }

    if (is_float)
    {
        tmp.type = MYELISP_FLOAT;
        tmp.as_float = sum;
    }
    else  
    {
        tmp.type = MYELISP_INT;
        tmp.as_int = sum;
    }

    return tmp;
}

void builtin_init(MapFunc *func)
{
    map_init(func);

    map_set(func, "+", myelisp_plus);
    map_set(func, "-", myelisp_minus);
    map_set(func, "print", myelisp_print);
}
