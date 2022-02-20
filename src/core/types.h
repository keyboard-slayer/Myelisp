#pragma once 

#include <stdint.h>
#include "utils/vec.h"

enum MYELISP_TYPES
{
    MYELISP_NIL,
    MYELISP_TRUE,
    MYELISP_INT,
    MYELISP_FLOAT,
    MYELISP_SYMBOL,
    MYELISP_STRING,
    MYELISP_LIST,
    MYELISP_CHAR
};

typedef struct myelisp_type Type;
typedef vec_t(Type) MyelispVec;

struct myelisp_type
{
    enum MYELISP_TYPES type;

    union
    {
        int64_t as_int;
        double as_float;
        char *as_str;
        char as_chr;
        MyelispVec as_list;
    };
};

#define NIL (Type) {.type = MYELISP_NIL}
