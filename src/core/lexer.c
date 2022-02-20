#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


static void token_smart_push(Tokens *tokens, Token *tok)
{
    if (tok->length > 0)
    {
        char *tmp = calloc(tok->length + 1, 1);
        if (tmp == NULL)
        {
            perror("");
            exit(1);
        }

        memcpy(tmp, tok->data, tok->length);
        vec_push(tokens, tmp);
        vec_clear(tok);
    }
}

void token_free(Tokens *toks)
{
    char *tok;
    size_t i;

    vec_foreach(toks, tok, i)
    {
        free(tok);
    }

    vec_deinit(toks);
}

Tokens myelisp_lexer(FileContent code)
{
    size_t index;
    Token tok;
    Tokens tokens;
    bool isstr = false;
    bool iscomment = false;

    vec_init(&tok);
    vec_init(&tokens);

    for (index = 0; index < strlen(code); index++)
    {
        if (iscomment && code[index] != '\n' && 
            code[index] != EOF && code[index] != '\0')
        {
            continue;
        }

        iscomment = false;

        switch (code[index])
        {
            case '\n':
            case '\r':
            case '\f':
            case '\v':
            {
                token_smart_push(&tokens, &tok);
                break;
            }

            case '\t':
            case ' ':
            {
                if (isstr)
                {
                    vec_push(&tok, ' ');
                }
                else  
                {
                    token_smart_push(&tokens, &tok);
                }

                break;
            }

            case '#':
            {
                if (isstr)
                {
                    vec_push(&tok, '#');
                }
                else  
                {
                    if (tok.length > 0)
                    {
                        fprintf(stderr, "lexing error");
                        exit(1);
                    }

                    if (code[index + 1] == 't' || code[index + 1] == '\\' ||
                        code[index + 1] == '(')
                    {
                        vec_push(&tok, '#');
                        vec_push(&tok, code[index + 1]);
                        token_smart_push(&tokens, &tok);
                    }
                }

                break;
            }

            case '`':
            case '\'':
            case '(':
            case ')':
            {
                if (!isstr)
                {
                    token_smart_push(&tokens, &tok);
                    vec_push(&tok, code[index]);
                    token_smart_push(&tokens, &tok);
                }
                else  
                {
                    vec_push(&tok, code[index]);
                }

                break;
            }

            case '"':
            {
                if (tok.length > 0 && !isstr)
                {
                    fprintf(stderr, "lexing error\n");
                    exit(1);
                }

                vec_push(&tok, '"');

                if (isstr)
                {
                    token_smart_push(&tokens, &tok);
                }

                isstr = true;
                break;
            }

            case ';':
            {
                token_smart_push(&tokens, &tok);
                iscomment = true;
                break;
            }

            default:
            {
                vec_push(&tok, code[index]);
            }

        }
    }

    token_smart_push(&tokens, &tok);
    vec_deinit(&tok);
    return tokens;
}
