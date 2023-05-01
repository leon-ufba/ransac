#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MIN_POINTS 2        // - The minimum number of data points required to estimate the model parameters.
#define MAX_ITERATIONS 100  // - The maximum number of iterations allowed in the algorithm.
#define C 0.00              // - The percent of close data points (inliers) required to assert that the model fits well to the data.
#define E 0.05              // - A threshold value to determine data points that are fit well by the model (inlier).

typedef struct {
  float x;
  float y;
} Point;

#define POINT_SIZE sizeof(Point)*2
#define MAX_POINTS 69

#define SIZEOF_MEM ((MAX_POINTS * 2) + MIN_POINTS) * POINT_SIZE

volatile float bestModel[2] = {0, 0};
volatile float bestFit = INFINITY;
volatile int verbose = 0;
volatile float totalDistToPointTime = 0;
volatile float totalLeastSquareTime = 0;
volatile float totalFitTime = 0;

float coefficientOfDetermination(Point* data, int n, float model[2], float* avg_y) {
  float ss_res = 0;
  float ss_tot = 0;
  for (int i = 0; i < n; i++) {
    float f = model[0] * data[i].x + model[1];
    float y_f = (data[i].y - f);
    float y_y = (data[i].y - (*avg_y));
    ss_res += y_f * y_f;
    ss_tot += y_y * y_y;
  }
  // float r = 1 - (ss_res / ss_tot); // original coefficient
  float r = (ss_res / ss_tot);	 // modified coefficient (lower is better)
  return r;
}

void leastSquare(Point* data, int n, float model[2], float* avg_y) {
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
  *avg_y = sy / n;
  model[0] = a;
  model[1] = b;
}

void checkModel(Point* data, Point* temp, int data_size, int temp_size) {
  clock_t t;
  float model[2];
  float avg_y;
  leastSquare(temp, temp_size, model, &avg_y);
  

  Point inliers[MAX_POINTS];
  int inlinersQty = 0;
  float square = E * sqrt(model[0] * model[0] + 1.0);
  t = clock();
  for (int k = 0; k < data_size; k++) {
    float dist = (model[0] * data[k].x - data[k].y + model[1]);
    if (dist <= square) {
      inliers[inlinersQty] = data[k];
      inlinersQty++;
    }
  }
  t = clock() - t;
  totalDistToPointTime += ((float)t);

  if (inlinersQty >= 2 && inlinersQty >= (int)(data_size * C)) {
    float inliersModel[2];
    float fit;

    t = clock();
    leastSquare(inliers, inlinersQty, inliersModel, &avg_y);
    t = clock() - t;
    totalLeastSquareTime += ((float)t);
    
    t = clock();
    fit = coefficientOfDetermination(data, data_size, inliersModel, &avg_y);
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

  float dataX[] = {
    -0.848,-0.800,-0.704,-0.632,-0.488,
    -0.472,-0.368,-0.336,-0.280,-0.200,
    -0.00800,-0.0840,0.0240,0.100,0.124,
    0.148,0.232,0.236,0.324,0.356,0.368,
    0.440,0.512,0.548,0.660,0.640,0.712,
    0.752,0.776,0.880,0.920,0.944,-0.108,
    -0.168,-0.720,-0.784,-0.224,-0.604,
    -0.740,-0.0440,0.388,-0.0200,0.752,
    0.416,-0.0800,-0.348,0.988,0.776,
    0.680,0.880,-0.816,-0.424,-0.932,
    0.272,-0.556,-0.568,-0.600,-0.716,
    -0.796,-0.880,-0.972,-0.916,0.816,
    0.892,0.956,0.980,0.988,0.992,
    0.004
  };

  float dataY[] = {
    -0.917,-0.833,-0.801,-0.665,-0.605,
    -0.545,-0.509,-0.433,-0.397,-0.281,
    -0.205,-0.169,-0.0531,-0.0651,0.0349,
    0.0829,0.0589,0.175,0.179,0.191,0.259,
    0.287,0.359,0.395,0.483,0.539,0.543,
    0.603,0.667,0.679,0.751,0.803,-0.265,
    -0.341,0.111,-0.113,0.547,0.791,0.551,
    0.347,0.975,0.943,-0.249,-0.769,-0.625,
    -0.861,-0.749,-0.945,-0.493,0.163,
    -0.469,0.0669,0.891,0.623,-0.609,
    -0.677,-0.721,-0.745,-0.885,-0.897,
    -0.969,-0.949,0.707,0.783,0.859,
    0.979,0.811,0.891,-0.137
  };


  unsigned int seed = 42;
  srand(seed); /* Intializes random number generator */
  Point data[MAX_POINTS];
  Point newPoint;
  for (int i = 0; i < MAX_POINTS; i++) {
    newPoint.x = dataX[i];
    newPoint.y = dataY[i];
    // newPoint.x = rand() / ((float)RAND_MAX);
    // newPoint.y = rand() / ((float)RAND_MAX);
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