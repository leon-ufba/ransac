#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// RANSAC parameters
#define MIN_POINTS 2        // - The minimum number of data points required to estimate the model parameters.
//#define C 0.00              // - The percent of close data points (inliers) required to assert that the model fits well to the data.
#define C 0.50
#define E 8.0                 // - A threshold value to determine data points that are fit well by the model (inlier).
#define T 100
#define N 20                // - Number of iterations required
#define MIN_DIST_POINTS 10  // - The minimum points distance required to select the sample

#define POINT_SIZE sizeof(Point)*2
#define MAX_POINTS 500

#define SIZEOF_MEM ((MAX_POINTS * 2) + MIN_POINTS) * POINT_SIZE

typedef struct {
  int x;
  int y;
  int* r;
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


typedef struct {
    float distance;
    int x;
    int y;
} Outlier;

volatile int indexOutliers[MAX_POINTS];
RansacResult rs;
Line leastSquare(Point* data, int size) {
    float sx = 0;
    float sy = 0;
    float sxy = 0;
    float sx2 = 0;
    if (size == 0) {
        Line line = {INFINITY, 0};
        return line;
    }
    for (int i = 0; i < size; i++) {
        sx += data[i].x;
        sy += data[i].y;
        sxy += data[i].x * data[i].y;
        sx2 += data[i].x * data[i].x;
    }
    float avg_y = sy / size;
    float den = (size * sx2 - sx * sx);
    if (den == 0) {
        Line line = {INFINITY, avg_y};
        return line;
    }
    float a = (size * sxy - sx * sy) / den;
    float b = (sy / size) - a * (sx / size);
    Line line = {a, b};
    return line;
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

float coefficientOfDetermination(Point* data, Line model, float avg_y, int data_size) {
    float ss_res = 0;
    float ss_tot = 0;
    for (int i = 0; i < data_size; i++) {
        float f = model.a * data[i].x + model.b;
        float y_f = (data[i].y - f);
        float y_y = (data[i].y - avg_y);
        ss_res += y_f * y_f;
        ss_tot += y_y * y_y;
    }
    float r = (ss_res / ss_tot);
    return r;
}

int compareOutliers(const void* a, const void* b) {
    float distanceA = ((Outlier*)a)->distance;
    float distanceB = ((Outlier*)b)->distance;
      if ((int)distanceA < (int)distanceB) {
        return -1;
    } else if ((int)distanceA > (int)distanceB) {
        return 1;
    }
    return 0;
}
void nearestOutliers(Point* data,  Line model, Point* outliers, int numData) {
    Outlier tempOutliers[numData];

    for (int i = 0; i < numData; i++) {
        float distance = fabs(model.a * data[i].x - data[i].y + model.b);
        tempOutliers[i].distance = distance;
        tempOutliers[i].x = data[i].x;
        tempOutliers[i].y = data[i].y;
    }

    qsort(tempOutliers, numData, sizeof(Outlier), compareOutliers);

    for (int i = 0; i < numData; i++) {
        outliers[i].x = tempOutliers[i].x;
        outliers[i].y = tempOutliers[i].y;
    }


}
/*
void nearestOutliers(Point* data, Line model, Point* nearest_outliers, int view_range) {
  for (int i = 0; i < view_range; i++) {
    nearest_outliers[i].x = fabs(model.a * (data[i].x - data[i].y + model.b));
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
*/
void checkModel(Point* data, Point* temp, int data_size, int temp_size) {

  Point inliers[data_size];
  Point outliers[data_size];
  int inlinersSize = 0;
  int outlierSize = 0;
  Line model = leastSquare(temp, temp_size);

  inliersOutliers(data, model, inliers, outliers, data_size, &inlinersSize, &outlierSize);

  if(inlinersSize >= rs.bestQty && inlinersSize >= (int)(data_size * C)){
    Line inliersModel = leastSquare(inliers, inlinersSize);
    float inliersAvg_y = 0;
    for (int i = 0; i < inlinersSize; i++) {
        inliersAvg_y += inliers[i].y;
    }
    inliersAvg_y /= inlinersSize;
    float  inliersFit = coefficientOfDetermination(data, inliersModel, inliersAvg_y, data_size);
    if (inliersFit < rs.bestFit) {
      rs.bestModel = inliersModel;
      rs.bestFit = inliersFit;
      rs.bestQty = inlinersSize;
    }
 }

}


float squareDistanceBetweenPoints (Point* a, Point* b){
  int dx = a->x - b->x;
  int dy = a->y - b->y;
  return (dx * dx) + (dy * dy);
}

RansacResult RANSAC(Point* data, int data_size, int view_range) {
  rs.bestModel.a = 0.0;
  rs.bestModel.b = view_range;
  rs.bestFit = INFINITY;
  rs.bestQty = 0;

  int temp_size = MIN_POINTS;
  Point inliers[data_size];
  Point outliers[data_size];
  int loopCounter= 0;
  int inlinersSize = 0;
  int outlierSize = 0;

  inliersOutliers(data, rs.bestModel, inliers, outliers, data_size, &inlinersSize, &outlierSize);

  if (outlierSize == 0) {
    return rs;
  }

  Point nearest_outliers[outlierSize];

  nearestOutliers(outliers, rs.bestModel, nearest_outliers, outlierSize);
  for (int i = 0; i < outlierSize; i++) {
      for (int j = outlierSize - 1; j > 0; j--) {
        checkModel(outliers, (Point[]){ nearest_outliers[i], nearest_outliers[j] }, outlierSize, temp_size);
        loopCounter++;
        if (loopCounter >= T)  break;
      }
      if (loopCounter >= T) break;
  }
  return rs;
}
