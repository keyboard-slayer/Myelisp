#include <stdio.h>
#include <stdlib.h>

#include "utils/loader.h"
#include "core/myelisp.h"
#include "core/builtin.h"

int main(int argc, char const **argv)
{
    FileContent source;
    Tokens tokens;
    Type ast;

    if (argc == 1)
    {
        fprintf(stderr, "no files specified\n");
        return 1;
    }

    source = get_file_content(argv[1]);
    tokens = myelisp_lexer(source);

    ast = myelisp_parser(tokens);
    myelisp_eval(ast);    

    token_free(&tokens);
    ast_free(&ast);
    free(source);
    return 0;
}
