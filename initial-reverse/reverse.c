#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "stack.h"

char *next_line(FILE *stream)
{
    size_t bufsize = 1;
    char *buf = (char *)mmalloc(1);

    int len = getline(&buf, &bufsize, stream);
    if (len == -1)
    {
        free(buf);
        return NULL;
    }
    return buf;
}

void reverse(FILE *in, FILE *out)
{
    Stack *stack = NULL;
    char *line;
    while ((line = next_line(in)))
        push(&stack, line);
    while (stack != NULL)
    {
        char *buf = pop(&stack);
        fprintf(out, "%s", buf);
        free(buf);
    }
}

int main(int argc, char *argv[])
{
    if (argc > 3)
    {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        return 1;
    }

    FILE *in = argc < 2 ? stdin : fopen(argv[1], "r");
    FILE *out = argc < 3 ? stdout : fopen(argv[2], "w");

    if (!in || !out)
    {
        fprintf(stderr, "reverse: cannot open file '%s'\n", !in ? argv[1] : argv[2]);
        return 1;
    }

    // check if the two files are the same
    struct stat in_stat, out_stat;
    fstat(fileno(in), &in_stat);
    fstat(fileno(out), &out_stat);
    if (in_stat.st_ino == out_stat.st_ino)
    {
        fprintf(stderr, "reverse: input and output file must differ\n");
        return 1;
    }

    reverse(in, out);
}
