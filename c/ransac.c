#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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


// RANSAC parameters
#define MIN_POINTS 2        // - The minimum number of data points required to estimate the model parameters.
//#define C 0.00              // - The percent of close data points (inliers) required to assert that the model fits well to the data.
#define T 100
#define E 8.0                 // - A threshold value to determine data points that are fit well by the model (inlier).
#define N 20                // - Number of iterations required
#define MIN_DIST_POINTS 10  // - The minimum points distance required to select the sample

#define POINT_SIZE sizeof(Point)*2
#define MAX_POINTS 500

#define SIZEOF_MEM ((MAX_POINTS * 2) + MIN_POINTS) * POINT_SIZE

volatile int indexOutliers[MAX_POINTS];
volatile int bestInlinersQty;
RansacResult rs;
void leastSquare(Point* data, int n, Line* model) {
  float sx = 0;
  float sy = 0;
  float sxy = 0;
  float sx2 = 0;
  for (int i = 0; i < n; i++) {
    sx += data[i].x;
    sy += data[i].y;
    sxy += data[i].x * data[i].y;
    sx2 += data[i].x * data[i].x;
  }
  (*model).a = (n * sxy - sx * sy) / (n * sx2 - sx * sx);
  (*model).b = (sy / n) - (*model).a * (sx / n);
}


void inliersOutliers(Point* data, Line model, Point* inliers, Point* outliers, int dataSize, int* inlierSize, int* outlierSize) {
    float square2 = E * E * (model.a * model.a + 1.0);
    for (int k = 0; k < dataSize; k++) {
        float dist = (model.a * data[k].x - data[k].y + model.b);
        if (dist * dist <= square2) {
            inliers[*inlierSize].x = data[k].x;
            inliers[*inlierSize].y = data[k].y;
            (*inlierSize)++;
        } else {
            outliers[*outlierSize].x = data[k].x;
            outliers[*outlierSize].y = data[k].y;
            (*outlierSize)++;
        }
    }
}


void nearestOutliers(Point* data, Line model, Point* nearest_outliers, int view_range) {
  for (int i = 0; i < view_range; i++) {
    nearest_outliers[i].x = fabs(model.a * (data[i].x - data[i].y + model.b);
    nearest_outliers[i].y = data[i].x;
  }
  for (int i = 0; i < view_range - 1; i++) {
    int minIndex = i;
    for (int j = i + 1; j < view_range; j++) {
      if (nearest_outliers[j].x < nearest_outliers[minIndex].x) {
        minIndex = j;
      }
    }
    Point temp = nearest_outliers[i];
    nearest_outliers[i] = nearest_outliers[minIndex];
    nearest_outliers[minIndex] = temp;
  }
}

void checkModel(Point* data, Point* temp, int data_size) {
  Line model;

  leastSquare(temp, temp_size, &model);

  Point inliers[MAX_POINTS];
  int inlinersQty = 0;
  int outliersQty = 0;
  float square2 = E * E * (model.a * model.a + 1.0);

  for (int k = 0; k < data_size; k++) {
    //calcula distância entre o modelo e os pontos
    float dist = (model.a * data[k].x - data[k].y + model.b);
    if (dist * dist <= square2) {
      inliers[inlinersQty] = data[k];
      inlinersQty++;
    } else {
      // salva o index dos outliers
      indexOutliers[outliersQty] = k;
      outliersQty++;
    }
  }
    if (inlinersQty > bestInlinersQty) {
      bestInlinersQty = inlinersQty;
      *bestModel = model;
    }
}


float squareDistanceBetweenPoints (Point* a, Point* b){
  int dx = a->x - b->x;
  int dy = a->y - b->y;
  return (dx * dx) + (dy * dy);
}

RansacResult RANSAC(Point* data, int view_range) {
  rs.bestModel.a = 0.0;
  rs.bestModel.b = view_range;

  int temp_size = MIN_POINTS;
  Point inliers[view_range];
  Point outliers[view_range];

  int inlinersSize = 0;
  int outlierSize = 0;

  inliersOutliers(data, rs.bestModel, &inliers, &outliers, view_range, &inlinersSize, &outlierSize);

  if (outlierSize == 0) {
    return rs;
  }

  Point nearest_outliers[outlierSize];

  nearestOutliers(&outliers, rs.bestModel, &nearest_outliers, view_range);
  for (int i = 0; i < outlierSize; i++) {
      for (int j = outlierSize - 1; j > 0; j--) {
        checkModel(outliers, (Point[]){ nearest_outliers[i], nearest_outliers[j] }, outlierSize);
      
        loopCounter++;
        if (loopCounter >= T) {
          break;
        }
      }
      if (loopCounter >= T) {
        break;
      }
  }

/*
  //Posição inicial do robô
  temp[0] = data[view_range-2];

  //Execute for N iterations
  while(count_iter < N) {
    //Sampling randomly 2 data points
    if(temp_dist_points < MIN_DIST_POINTS) {
      for (int j = 1; j < temp_size; j++) {
        temp_index = rand() % view_range;
        temp[j] = data[temp_index];
        temp_dist_points = squareDistanceBetweenPoints(&temp[0], &temp[1]);
      }
    }
    else {
      checkModel(data, temp, &bestModel, data_size, temp_size);
      temp_dist_points = 0;
      count_iter++;
    }
  
  }
  */
  return bestModel;
}