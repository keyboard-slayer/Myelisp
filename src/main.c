#include <stdio.h>
#include <stdlib.h>

#include "utils/loader.h"
#include "core/lexer.h"
#include "core/parser.h"

int main(int argc, char const **argv)
{
    FileContent source;
    Tokens tokens;

    if (argc == 1)
    {
        fprintf(stderr, "no files specified\n");
        return 1;
    }

    source = get_file_content(argv[1]);
    tokens = myelisp_lexer(source);
    myelisp_parser(tokens);

    token_free(&tokens);
    free(source);
    return 0;
}
