#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024
char buffer[BUFSIZE];

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL)
        {
            printf("wcat: cannot open file\n");
            return 1;
        }

        while ((fgets(buffer, BUFSIZE, file)))
            printf("%s", buffer);
    }
}