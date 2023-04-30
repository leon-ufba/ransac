#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include <time.h>

#define MIN_POINTS 2    // - The minimum number of data points required to estimate the model parameters.
#define MAX_ITERATIONS 100  // - The maximum number of iterations allowed in the algorithm.
#define C 0.10 // - The percent of close data points (inliers) required to assert that the model fits well to the data.
#define E 0.10 // - A threshold value to determine data points that are fit well by the model (inlier).

typedef struct {
  float x;
  float y;
} Point;

#define POINT_SIZE sizeof(Point)*2
#define MAX_POINTS 100


#define SIZEOF_MEM ((MAX_POINTS * 2) + MIN_POINTS) * POINT_SIZE



volatile float bestModel[2] = {0, 0};
volatile float bestFit = INFINITY;
volatile int verbose = 0;
// volatile float totalTime = 0;

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


  Point inliers[MAX_POINTS];
  int inlinersQty = 0;
  float square = sqrt(model[0] * model[0] + 1.0);
  for (int k = 0; k < data_size; k++) {

    float dist = distToLine(data[k], model, square);
    if (dist <= E) {
      inliers[inlinersQty] = data[k];
      inlinersQty++;
    }
  }

  if (inlinersQty >= 2 && inlinersQty >= (int)(data_size * C)) {
    float inliersModel[2];
    float fit;
    leastSquare(inliers, inlinersQty, inliersModel);
    fit = coefficientOfDetermination(data, data_size, inliersModel);
    if (verbose) {
      for (int o = 0; o < temp_size; o++) printf("{%lf, %lf}  ", temp[o].x, temp[o].y);
      printf("\n");
      printf("%d\n", inlinersQty);
      printf("%lf\n", fit);
      printf("%lf  %lf\n", model[0], model[1]);
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
  /*Point data[MAX_POINTS];
  Point temp;
  for (int i = 0; i < MAX_POINTS; i++) {
    temp.x = rand()/((float) RAND_MAX);
    temp.y = rand()/((float) RAND_MAX);
    data[i] = temp;
  }*/
//  clock_t t;
//  t = clock();
  Point data[] = { 
    {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5}, {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5},
    {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5}, {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5},
    {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5}, {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5},
    {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5}, {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5},
    {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5}, {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5},
    {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5}, {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5},
  };
  // float data[][2] = {{95,90}, {85,80}, {80,70}, {70,65}, {60,60}};
  int data_size = sizeof(data) / sizeof(Point);	 // number of data points

  RANSAC(data, data_size);
  // t = clock() - t;
  // totalTime += ((float)t);
  // printf("\n------------------------\n");
  // printf("totalTime - %lf\n", totalTime/CLOCKS_PER_SEC);
  printf("\n------------------------\n");
  printf("\n");
  printf("bestFit:  \t%lf\n", bestFit);
  printf("bestModel:\t%lf\t%lf\n", bestModel[0], bestModel[1]);
  printf("\n");

  return 0;
}