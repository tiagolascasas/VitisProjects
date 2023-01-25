#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include "config.h"

void rgbToGrayscale(int *image_rgb, int *image_gray, int width, int height)
{
//#pragma HLS inline
    int size = width * height;

    for (int i = 0, j = 0; i < size; i++, j += 3)
    {
#pragma HLS pipeline
            int r = image_rgb[j];
            int g = image_rgb[j + 1];
            int b = image_rgb[j + 2];

            float gray = 0.299 * r + 0.587 * g + 0.114 * b;
            image_gray[i] = (int)floor(gray);
    }
}

void convolve2d_smooth(int *input_image, int *output_image, int width, int height)
{
//#pragma HLS inline
    int i;
    int j;
    int c;
    int r;
    int normal_factor;
    int sum;
    int dead_rows;
    int dead_cols;

    int filter[K * K];
	filter[0] = 1;
	filter[1] = 2;
	filter[2] = 1;
	filter[3] = 2;
	filter[4] = 4;
	filter[5] = 2;
	filter[6] = 1;
	filter[7] = 2;
	filter[8] = 1;

    dead_rows = K / 2;
    dead_cols = K / 2;

    normal_factor = 0;
    for (r = 0; r < K; r++)
    {
#pragma HLS unroll
        for (c = 0; c < K; c++)
        {
            normal_factor += abs(filter[r * K + c]);
        }
    }

    if (normal_factor == 0)
        normal_factor = 1;

    for (r = 0; r < height - K + 1; r++)
    {
        for (c = 0; c < width - K + 1; c++)
        {
#pragma HLS pipeline
            sum = 0;
            for (i = 0; i < K; i++)
            {
#pragma HLS unroll
                for (j = 0; j < K; j++)
                {
                    sum += input_image[(r + i) * width + (c + j)] * filter[i * K + j];
                }
            }
            output_image[(r + dead_rows) * width + (c + dead_cols)] = (sum / normal_factor);
        }
    }
}

void convolve2d_vertical(int *input_image, int *output_image, int width, int height)
{
//#pragma HLS inline
    int i;
    int j;
    int c;
    int r;
    int normal_factor;
    int sum;
    int dead_rows;
    int dead_cols;

    int filter[K * K];
	filter[0] = 1;
	filter[1] = 0;
	filter[2] = -1;
	filter[3] = 2;
	filter[4] = 0;
	filter[5] = -2;
	filter[6] = 1;
	filter[7] = 0;
	filter[8] = -1;

    dead_rows = K / 2;
    dead_cols = K / 2;

    normal_factor = 0;
    for (r = 0; r < K; r++)
    {
#pragma HLS unroll
        for (c = 0; c < K; c++)
        {
            normal_factor += abs(filter[r * K + c]);
        }
    }

    if (normal_factor == 0)
        normal_factor = 1;

    for (r = 0; r < height - K + 1; r++)
    {
        for (c = 0; c < width - K + 1; c++)
        {
#pragma HLS pipeline
            sum = 0;
            for (i = 0; i < K; i++)
            {
#pragma HLS unroll
                for (j = 0; j < K; j++)
                {
                    sum += input_image[(r + i) * width + (c + j)] * filter[i * K + j];
                }
            }
            output_image[(r + dead_rows) * width + (c + dead_cols)] = (sum / normal_factor);
        }
    }
}

void convolve2d_horizontal(
    int *input_image,
    int *output_image,
    int width,
    int height)
{
//#pragma HLS inline
    int i;
    int j;
    int c;
    int r;
    int normal_factor;
    int sum;
    int dead_rows;
    int dead_cols;

    int filter[K * K];
	filter[0] = 1;
	filter[1] = 2;
	filter[2] = 1;
	filter[3] = 0;
	filter[4] = 0;
	filter[5] = 0;
	filter[6] = -1;
	filter[7] = -2;
	filter[8] = -1;
    dead_rows = K / 2;
    dead_cols = K / 2;

    normal_factor = 0;
    for (r = 0; r < K; r++)
    {
#pragma HLS unroll
        for (c = 0; c < K; c++)
        {
            normal_factor += abs(filter[r * K + c]);
        }
    }

    if (normal_factor == 0)
        normal_factor = 1;

    for (r = 0; r < height - K + 1; r++)
    {
        for (c = 0; c < width - K + 1; c++)
        {
#pragma HLS pipeline
            sum = 0;
            for (i = 0; i < K; i++)
            {
#pragma HLS unroll
                for (j = 0; j < K; j++)
                {
                    sum += input_image[(r + i) * width + (c + j)] * filter[i * K + j];
                }
            }
            output_image[(r + dead_rows) * width + (c + dead_cols)] = (sum / normal_factor);
        }
    }
}

void combthreshold(int *image_gray, int *temp_buf, int *output, int width, int height)
{
//#pragma HLS inline
    int i, j;
    int temp1;
    int temp2;
    int temp3;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; ++j)
        {
#pragma HLS pipeline
            temp1 = abs(image_gray[i * width + j]);
            temp2 = abs(temp_buf[i * width + j]);
            temp3 = (temp1 > temp2) ? temp1 : temp2;
            output[i * width + j] = (temp3 > T) ? 255 : 0;
        }
    }
}

//https://support.xilinx.com/s/question/0D52E00006jpexfSAA/custom-clock-frequency-to-the-kernel-does-not-work?language=en_US
extern "C" {
void edge_detect(int *image_rgb, int *output, int width, int height)
{
    int temp_buf[MAXBUF] = {0};

    rgbToGrayscale(image_rgb, image_rgb, width, height);

    convolve2d_smooth(image_rgb, output, width, height);

    convolve2d_vertical(output, image_rgb, width, height);

    convolve2d_horizontal(output, temp_buf, width, height);

    combthreshold(image_rgb, temp_buf, output, width, height);
}
}


