#pragma once

// Image size
#ifndef SIZE
#define SIZE FHD
#endif

#define DEFAULT 0
#define CGA 1
#define VGA 2
#define WVGA 3
#define SVGA 4
#define HD 5

// extra
#define FHD 30
#define QHD 40
#define _4K 50

#if SIZE == DEFAULT
#define W 512
#define H 512
#define T 40 // 127
#define IMAGE "img_512_512.dat"
#define CHECKSUM 3618195

#elif SIZE == CGA
#define W 320
#define H 200
#define T 40 // 127
#define IMAGE "img_320_200.dat"
#define CHECKSUM 1104915
#elif SIZE == VGA
#define W 640
#define H 480
#define T 40 // 127
#define IMAGE "img_640_480.dat"
#define CHECKSUM 1608540
#elif SIZE == WVGA
#define W 800
#define H 480
#define T 40 // 127
#define IMAGE "img_800_480.dat"
#define CHECKSUM 1411425
#elif SIZE == SVGA
#define W 800
#define H 600
#define T 40 // 127
#define IMAGE "img_800_600.dat"
#define CHECKSUM 2590290
#elif SIZE == HD
#define W 1280
#define H 720
#define T 40 // 127
#define IMAGE "img_1280_720.dat"
#define CHECKSUM 3408585

// extra
#elif SIZE == FHD
#define W 1920
#define H 1080
#define T 40 // 127
#define IMAGE "img_1920_1080.dat"
#define CHECKSUM 2478090
#elif SIZE == QHD
#define W 2560
#define H 1440
#define T 40 // 127
#define IMAGE "img_2560_1440.dat"
#define CHECKSUM 5467200
#elif SIZE == _4K
#define W 3840
#define H 2160
#define T 40 // 127
#define IMAGE "img_3840_2160.dat"
#define CHECKSUM 49698735
#endif

// Universal params
#define ITER 0 // 1000

#define K 3
#define MAXBUF 3840 * 2160

#define CONV_SMOOTH 0
#define CONV_VERT 1
#define CONV_HORIZ 2

// Version-specific params
#ifndef SCENARIO
#define SCENARIO V0
#endif

#define V0 1
#define V0C 2
#define V0CE 3
#define V0E 4
#define V1 5
#define V1C 6
#define V1CE 7
#define V1E 8
#define V2 9
#define V2C 10
#define V2CE 11
#define V2E 12

#if SCENARIO == V0
#define MAIN_ALL
#define SET_FILTER
#endif

#if SCENARIO == V0C
#define MAIN_ALL
#endif

#if SCENARIO == V0CE
#endif

#if SCENARIO == V0E
#define SET_FILTER
#endif
