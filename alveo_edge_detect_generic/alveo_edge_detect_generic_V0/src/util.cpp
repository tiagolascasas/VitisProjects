#include <cstdio>
#include "config.h"

int checksum(int buf[H * W])
{
    int n = 0;
    for (int i = 0; i < H * W; i++)
    {
    	n += buf[i];
    }
    printf("Checksum %s", n == CHECKSUM ? "SUCCESS" : "FAILURE");
    printf(" (actual: %d, expected: %d)\n", n, CHECKSUM);
    return n;
}

void output_dsp(int *buf, char *name, int width, int height)
{
    FILE *file = fopen(name, "w");

    for (int i = 0; i < height * width - 1; i++)
    {
        fprintf(file, "%d,", buf[i]);
    }
    fprintf(file, "%d", buf[height * width - 1]);
    fclose(file);
}

void output_dsp_rgb(int buf[H * W * 3], char *name)
{
    FILE *file = fopen(name, "w");

    for (int i = 0; i < H * W * 3 - 1; i++)
    {
        fprintf(file, "%d,", buf[i]);
    }
    fprintf(file, "%d", buf[H * W * 3 - 1]);
    fclose(file);
}
