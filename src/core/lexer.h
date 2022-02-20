#pragma once 

#include "utils/loader.h"
#include "utils/vec.h"

#include <stddef.h>

#define DEFAULT_TOKENS_CAPACITY (10)

typedef Vec(char *) Tokens;
typedef Vec(char) Token;

Tokens myelisp_lexer(FileContent code);
void token_free(Tokens *toks);
