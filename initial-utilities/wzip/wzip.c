#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("wzip: file1 [file2 ...]\n");
        return 1;
    }

    int cur_char;
    int count = 0;

    for (int i = 1; i < argc; i++)
    {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL)
        {
            printf("wzip: cannot open file\n");
            return 1;
        }

        int ch;
        while ((ch = getc(file)) != EOF)
        {
            if (count == 0)
            {
                cur_char = (char)ch;
                count++;
            }
            else if (cur_char == ch)
            {
                count++;
            }
            else
            {
                ungetc(ch, file);
                char ch_out = (char)cur_char;
                fwrite(&count, sizeof(count), 1, stdout);
                fwrite(&ch_out, sizeof(ch_out), 1, stdout);
                count = 0;
            }
        }
    }

    if (count > 0)
    {
        char ch_out = (char)cur_char;
        fwrite(&count, sizeof(count), 1, stdout);
        fwrite(&ch_out, sizeof(ch_out), 1, stdout);
    }
}