#include "myelisp.h"
#include "utils/istype.h"

#include <stdio.h>
#include <string.h>

static Type readform(TokenReader *r);

static Type readlist(TokenReader *r)
{
    Type token;
    Type tmp;

    token.type = MYELISP_LIST;
    vec_init(&token.as_list);
    (void) reader_next(r);

    while (strcmp(reader_current(r), ")"))
    {
        if (reader_eof(r))
        {
            free(r->buf);
            vec_deinit(&token.as_list);
            fprintf(stderr, "unexpected EOF\n");
            exit(1);
        }

        tmp = readform(r);
        (void) vec_push(&token.as_list, tmp);
    }

    (void) reader_next(r);
    return token;
}

static Type readatom(TokenReader *r)
{
    Type token;
    char *s = reader_next(r);

    if (isnumber(s))
    {
        token.type = MYELISP_INT;
        token.as_int = atoll(s);
    }
    else if (isfloat(s))
    {
        token.type = MYELISP_FLOAT;
        token.as_float = strtod(s, NULL);
    }
    else if (*s == '\"' && isstr(s))
    {
        s[strlen(s) - 1] = '\0';
        s++;

        token.type = MYELISP_STRING;
        token.as_str = s;
    }
    else if (strcmp("#t", s) == 0)
    {
        token.type = MYELISP_TRUE;
    }
    else if(strcmp("nil", s) == 0)
    {
        token.type = MYELISP_NIL;
    }
    else  
    {
        token.type = MYELISP_SYMBOL;
        token.as_str = s;
    }

    return token;
}

static Type readform(TokenReader *r)
{
    char *tok = reader_current(r);

    switch (*tok)
    {
        case '(':
        {
            return readlist(r);
        }

        case ')':
        {
            fprintf(stderr, "unexpected )\n");
            free(r->buf);
            exit(1);
        }

        default:
        {
            return readatom(r);
        }
    }
}

void ast_free(Type *ast)
{
    Type tok;
    int i;

    if (ast->type != MYELISP_LIST)
    {
        return;
    }

    vec_foreach(&ast->as_list, tok, i)
    {
        if (tok.type == MYELISP_LIST)
        {
            ast_free(&tok);
        }
    }

    vec_deinit(&ast->as_list);
}

Type myelisp_parser(Tokens toks)
{
    TokenReader r;
    Type ast;

    ast.type = MYELISP_LIST;
    vec_init(&ast.as_list);
    
    reader_init(&r, toks.data, toks.length);

    while (!reader_eof(&r))
    {
        (void) vec_push(&ast.as_list, readform(&r));
    }

    return ast; 
}
