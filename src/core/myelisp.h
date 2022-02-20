#pragma once 

#include "types.h"

#include "utils/reader.h"
#include "utils/loader.h"
#include "utils/vec.h"

#include <stddef.h>

#define DEFAULT_TOKENS_CAPACITY (10)

typedef vec_t(char *) Tokens;
typedef vec_t(char) Token;
typedef Reader(char **) TokenReader;

Type myelisp_parser(Tokens toks);
Tokens myelisp_lexer(FileContent code);
Type myelisp_eval(Type ast);
void token_free(Tokens *toks);
void ast_free(Type *ast);
