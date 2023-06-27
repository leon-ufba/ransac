#include "types.h"
#include <stdint.h>
// RANSAC parameters
#define MIN_POINTS 2        // - The minimum number of data points required to estimate the model parameters.
//#define C 0.00              // - The percent of close data points (inliers) required to assert that the model fits well to the data.
#define C 0.50
#define E 8.0                 // - A threshold value to determine data points that are fit well by the model (inlier).
#define T 100
#define N 20                // - Number of iterations required
#define MIN_DIST_POINTS 10  // - The minimum points distance required to select the sample
#define MEMORY_DATA (Point *) 0x40000
#define POINT_SIZE sizeof(Point)*2
#define MAX_POINTS 500

#define SIZEOF_MEM ((MAX_POINTS * 2) + MIN_POINTS) * POINT_SIZE

#define MEDIDOR_LEITURA (int *) 0x5100c
#define MEDIDOR_ESCRITA (int *) 0x51008

//*MEDIDOR_ESCRITA = 0; // para resetar a contagem
//*MEDIDOR_ESCRITA = 1; // para iniciar/retomar a contagem
//*MEDIDOR_ESCRITA = 2; // para pausar a contagem

RansacResult RANSAC(int data_size, int view_range);

void readStructFromMemory(Point* structPtr, uint32_t address);
