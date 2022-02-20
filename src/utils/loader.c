#include "loader.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

FileContent get_file_content(const char *filename)
{
    size_t size;
    FileContent content;
    FILE *fp;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("");
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    content = calloc(size + 1, 1);
    if (content == NULL)
    {
        perror("");
        exit(1);
    }

    fread(content, size, 1, fp);
    fclose(fp);

    return content;
}

