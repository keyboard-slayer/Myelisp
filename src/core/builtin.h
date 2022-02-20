#pragma once 

#include "myelisp.h"
#include "utils/map.h"

typedef Type (*Builtin)(Type);
typedef map_t(Builtin) MapFunc;

Type myelisp_print(Type ast);
Type myelisp_plus(Type ast);
Type myelisp_minus(Type ast);

void builtin_init(MapFunc *func);
