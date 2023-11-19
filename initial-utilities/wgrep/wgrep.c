#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *buffer;
size_t size;

void grep(FILE *file, char *term, int term_len)
{
    int read = 0;
    while ((read = getline(&buffer, &size, file)) != -1)
    {
        for (int i = 0; i < read; i++)
        {
            if (!strncmp(term, buffer + i, term_len))
            {
                printf("%s", buffer);
                break;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }

    buffer = (char *)malloc(size);
    int term_len = strlen(argv[1]);

    if (argc == 2)
    {
        grep(stdin, argv[1], term_len);
        return 0;
    }

    for (int i = 2; i < argc; i++)
    {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL)
        {
            printf("wgrep: cannot open file\n");
            return 1;
        }
        grep(file, argv[1], term_len);
    }
}