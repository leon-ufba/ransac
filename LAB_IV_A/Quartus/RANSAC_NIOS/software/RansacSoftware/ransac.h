/*
 * ransac.h
 *
 *  Created on: 2 de jul de 2023
 *      Author: Caroline
 */

#ifndef RANSAC_H_
#define RANSAC_H_

#define PACKING_COORD(x, y) (((x) & 0xFF) << 0) | (((y) & 0xFF) << 8)
#define GET_X(packing) ((int)(packing) & 0xFF)
#define GET_Y(packing) ((int)(packing) >> 8)
#define MAX_POINTS 300

#define END_BASE_DATA (int *) 0x0000
// enderecos do medidor de desempenho
#define MEDIDOR_LEITURA (int *) 0x11008
#define MEDIDOR_ESCRITA (int *) 0x1100c

//variaveis profiling
volatile int square_root_counter;
volatile int calculateIntersection_counter;
volatile int getAngleFromModel_counter;
volatile int leastSquare_counter;
volatile int coefficientOfDetermination_counter;
volatile int inliersOutliersMemory_counter;
volatile int inliersOutliers_counter;
volatile int squareDistanceBetweenPoints_counter;


typedef struct {
  float a;
  float b;
} Line;

typedef struct {
    Line bestModel;
    float bestFit;
    int bestQty;
} RansacResult;


float square_root(float number);
int calculateIntersection(Line* k, Line* l);
float getAngleFromModel(float a);
Line leastSquare(int* data, int size);
float coefficientOfDetermination(int* data, Line model, int avg_y, int data_size);
void inliersOutliersMemory(int* data, Line model, int* inliers, int* outliers, int dataSize, int* inlierSize, int* outlierSize);
void inliersOutliers(int* data, Line model, int* inliers, int* outliers, int dataSize, int* inlierSize, int* outlierSize);
void checkModel(int* data, int* temp, RansacResult* rs, int data_size, int temp_size);
int squareDistanceBetweenPoints (int a, int b);
RansacResult RANSAC(int* data, int botPos, int* outliers, int data_size);




#endif /* RANSAC_H_ */
