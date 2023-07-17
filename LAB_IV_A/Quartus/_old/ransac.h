/*
 * ransac.h
 *
 *  Created on: 2 de jul de 2023
 *      Author: Caroline
 */

#ifndef RANSAC_H_
#define RANSAC_H_

#define X j
#define Y j+1
#define MAX_POINTS 300

typedef struct {
  int x;
  int y;
} Point;

typedef struct {
  float a;
  float b;
} Line;

typedef struct {
    Line bestModel;
    float bestFit;
    int bestQty;
} RansacResult;


int square_root(int number);
Point calculateIntersection(Line* k, Line* l);
float getAngleFromModel(float a);
Line leastSquare(Point* data, int size);
float coefficientOfDetermination(Point* data, Line model, float avg_y, int data_size);
void inliersOutliersMemory(int* data, Line model, Point* inliers, Point* outliers, int dataSize, int* inlierSize, int* outlierSize);
void inliersOutliers(Point* data, Line model, Point* inliers, Point* outliers, int dataSize, int* inlierSize, int* outlierSize);
void checkModel(Point* data, Point* temp, RansacResult* rs, int data_size, int temp_size);
float squareDistanceBetweenPoints (Point* a, Point* b);
RansacResult RANSAC(int* data, Point* botPos, Point* outliers, int data_size);




#endif /* RANSAC_H_ */
