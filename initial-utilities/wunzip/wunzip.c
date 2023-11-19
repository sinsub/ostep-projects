#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("wunzip: file1 [file2 ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL)
        {
            printf("wzip: cannot open file\n");
            return 1;
        }

        int count;
        char ch;

        while (fread(&count, sizeof(count), 1, file))
        {
            fread(&ch, sizeof(ch), 1, file);
            while (count-- > 0)
                putchar(ch);
        }
    }
}