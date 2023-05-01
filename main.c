#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MIN_POINTS 2        // - The minimum number of data points required to estimate the model parameters.
#define MAX_ITERATIONS 100  // - The maximum number of iterations allowed in the algorithm.
#define C 0.00              // - The percent of close data points (inliers) required to assert that the model fits well to the data.
#define E 0.10              // - A threshold value to determine data points that are fit well by the model (inlier).

typedef struct {
  float x;
  float y;
} Point;

#define POINT_SIZE sizeof(Point)*2
#define MAX_POINTS 500

#define SIZEOF_MEM ((MAX_POINTS * 2) + MIN_POINTS) * POINT_SIZE

volatile float bestModel[2] = {0, 0};
volatile float bestFit = INFINITY;
volatile int verbose = 0;
volatile float totalDistToPointTime = 0;
volatile float totalLeastSquareTime = 0;
volatile float totalFitTime = 0;

float coefficientOfDetermination(Point* data, int n, float model[2]) {
  float y_avg = 0;
  float ss_res = 0;
  float ss_tot = 0;
  for (int i = 0; i < n; i++) {
    y_avg += data[i].y;
  }
  y_avg /= n;
  for (int i = 0; i < n; i++) {
    float f = model[0] * data[i].x + model[1];
    float y_f = (data[i].y - f);
    float y_y = (data[i].y - y_avg);
    ss_res += y_f * y_f;
    ss_tot += y_y * y_y;
  }
  // float r = 1 - (ss_res / ss_tot); // original coefficient
  float r = (ss_res / ss_tot);	 // modified coefficient (lower is better)
  return r;
}

void leastSquare(Point* data, int n, float model[2]) {
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
  float a = (n * sxy - sx * sy) / (n * sx2 - sx * sx);
  float b = (sy / n) - a * (sx / n);
  model[0] = a;
  model[1] = b;
}

float distToLine(Point point, float model[2], float square) {
  return fabs(model[0] * point.x - point.y + model[1]) / square;
}

void checkModel(Point* data, Point* temp, int data_size, int temp_size) {
  float model[2];
  leastSquare(temp, temp_size, model);
  
  clock_t t;

  Point inliers[MAX_POINTS];
  int inlinersQty = 0;
  float square = E * sqrt(model[0] * model[0] + 1.0);
  for (int k = 0; k < data_size; k++) {
    t = clock();
    float dist = (model[0] * data[k].x - data[k].y + model[1]);
    t = clock() - t;
    totalDistToPointTime += ((float)t);
    if (dist <= square) {
      inliers[inlinersQty] = data[k];
      inlinersQty++;
    }
  }

  if (inlinersQty >= 2 && inlinersQty >= (int)(data_size * C)) {
    float inliersModel[2];
    float fit;
    t = clock();
    leastSquare(inliers, inlinersQty, inliersModel);
    t = clock() - t;
    totalLeastSquareTime += ((float)t);
    
    t = clock();
    fit = coefficientOfDetermination(data, data_size, inliersModel);
    t = clock() - t;
    totalFitTime += ((float)t);

    if (verbose) {
      for (int o = 0; o < temp_size; o++) printf("{%f, %f}  ", temp[o].x, temp[o].y);
      printf("\n");
      printf("%d\n", inlinersQty);
      printf("%f\n", fit);
      printf("%f  %f\n", model[0], model[1]);
      printf("\n");
    }
    if (fit < bestFit) {
      bestFit = fit;
      bestModel[0] = inliersModel[0];
      bestModel[1] = inliersModel[1];
    }
  }

}

void RANSAC(Point* data, int data_size) {
  int temp_size = MIN_POINTS;
  Point temp[2]; // alocação tamanho P
  for (int i = 0; i < data_size; i++) {
    temp[0] = data[i];
    for (int j = i + 1; j < data_size; j++) {
      temp[1] = data[j];
      checkModel(data, temp, data_size, temp_size);
    }
  }
}

int main() {
  unsigned int seed = 42;
  srand(seed); /* Intializes random number generator */
  Point data[MAX_POINTS];
  Point newPoint;
  for (int i = 0; i < MAX_POINTS; i++) {
    newPoint.x = rand() / ((float)RAND_MAX);
    newPoint.y = rand() / ((float)RAND_MAX);
    data[i] = newPoint;
  }

  // Point data[] = { 
  //   {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5}, {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5},
  //   {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5}, {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5},
  //   {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5}, {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5},
  //   {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5}, {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5},
  //   {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5}, {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5},
  //   {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5}, {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5},
  // };

  int data_size = sizeof(data) / sizeof(Point);	 // number of data points


  clock_t t;
  t = clock();
  RANSAC(data, data_size);
  t = clock() - t;
  float totalTime = ((float)t);


  printf("\n------------------------\n");
  printf("totalDistToPointTime - %f\t%f\n", totalDistToPointTime / CLOCKS_PER_SEC, totalDistToPointTime / totalTime);
  printf("totalLeastSquareTime - %f\t%f\n", totalLeastSquareTime / CLOCKS_PER_SEC, totalLeastSquareTime / totalTime);
  printf("totalFitTime         - %f\t%f\n", totalFitTime         / CLOCKS_PER_SEC, totalFitTime         / totalTime);
  printf("totalTime            - %f\t%f\n", totalTime            / CLOCKS_PER_SEC, totalTime            / totalTime);
  printf("\n------------------------\n");
  printf("\n");
  printf("bestFit:  \t%f\n", bestFit);
  printf("bestModel:\t%f\t%f\n", bestModel[0], bestModel[1]);
  printf("\n");

  return 0;
}