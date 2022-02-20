#pragma once 

#include "lexer.h"
#include "utils/reader.h"

void myelisp_parser(Tokens toks);

typedef Reader(char **) TokenReader;
