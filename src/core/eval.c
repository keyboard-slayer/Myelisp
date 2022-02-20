#include "myelisp.h"
#include "types.h"
#include "builtin.h"

#include <assert.h>
#include <stdio.h>

bool is_init = false;
static size_t level = 0;
static MapFunc builtin;

static Type execute_subast(Type subast)
{
    Builtin *func;

    if (subast.as_list.data[0].type != MYELISP_SYMBOL)
    {
        myelisp_print(subast);
        fprintf(stderr, "can't evaluate: a symbol was expected\n");
        exit(1);
    }

    func = map_get(&builtin, subast.as_list.data[0].as_str);
    if (func == NULL)
    {
        fprintf(stderr, "%s is undefined\n", subast.as_list.data[0].as_str);
        exit(1);
    }

    vec_splice(&subast.as_list, 0, 1);
    return (*func)(subast);
}

Type myelisp_eval(Type ast)
{
    Type context;
    Type node;
    Type return_value = NIL;
    int i;

    if (!is_init)
    {
        builtin_init(&builtin);
        is_init = true;
    }

    context.type = MYELISP_LIST;
    vec_init(&context.as_list);

    vec_foreach(&ast.as_list, node, i)
    {
        if (node.type == MYELISP_LIST)
        {
            level++;
            (void) vec_push(&context.as_list, myelisp_eval(node));
            level--;
        }
        else  
        {
            (void) vec_push(&context.as_list, node);
        }
    }

    if (context.as_list.length > 0 && level)
    {
        return_value = execute_subast(context);
    }

    vec_deinit(&context.as_list);
    return return_value;
}

