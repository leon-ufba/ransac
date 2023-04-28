#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include <time.h>

#define P 2    // - The minimum number of data points required to estimate the model parameters.
#define T 100  // - The maximum number of iterations allowed in the algorithm.
#define C 0.10 // - The percent of close data points (inliers) required to assert that the model fits well to the data.
#define E 0.10 // - A threshold value to determine data points that are fit well by the model (inlier).

volatile double bestModel[2] = {0, 0};
volatile double bestFit = INFINITY;
volatile int verbose = 0;
// volatile double totalTime = 0;

double** malloc2d(int n) {
  double** arr = malloc(n * sizeof(double*));
  for (int i = 0; i < n; i++) {
    arr[i] = malloc(2 * sizeof(double));
  }
  return arr;
}

void free2d(double** arr, int n) {
  for (int i = 0; i < n; i++) {
    free(arr[i]);
  }
  free(arr);
}

double coefficientOfDetermination(double** data, int n, double model[2]) {
  double y_avg = 0;
  double ss_res = 0;
  double ss_tot = 0;
  for (int i = 0; i < n; i++) {
    y_avg += data[i][1];
  }
  y_avg /= n;
  for (int i = 0; i < n; i++) {
    double f = model[0] * data[i][0] + model[1];
    double y_f = (data[i][1] - f);
    double y_y = (data[i][1] - y_avg);
    ss_res += y_f * y_f;
    ss_tot += y_y * y_y;
  }
  // double r = 1 - (ss_res / ss_tot); // original coefficient
  double r = (ss_res / ss_tot);	 // modified coefficient (lower is better)
  return r;
}

void leastSquare(double** data, int n, double model[2]) {
  double sx = 0;
  double sy = 0;
  double sxy = 0;
  double sx2 = 0;
  for (int i = 0; i < n; i++) {
    sx += data[i][0];
    sy += data[i][1];
    sxy += data[i][0] * data[i][1];
    sx2 += data[i][0] * data[i][0];
  }
  double a = (n * sxy - sx * sy) / (n * sx2 - sx * sx);
  double b = (sy / n) - a * (sx / n);
  model[0] = a;
  model[1] = b;
}

double distToLine(double* point, double model[2]) {
  return fabs(model[0] * point[0] - point[1] + model[1]) / sqrt(model[0] * model[0] + 1.0);
}

void checkModel(double** data, double** temp, int data_size, int temp_size) {
  double model[2];
  leastSquare(temp, temp_size, model);


  double** inliers = malloc2d(data_size);
  int inlinersQty = 0;

  for (int k = 0; k < data_size; k++) {
    // clock_t t;
    // t = clock();
    double dist = distToLine(data[k], model);
    // t = clock() - t;
    // totalTime += ((double)t);
    if (dist <= E) {
      inliers[inlinersQty][0] = data[k][0];
      inliers[inlinersQty][1] = data[k][1];
      inlinersQty++;
    }
  }

  if (inlinersQty >= 2 && inlinersQty >= (int)(data_size * C)) {
    double inliersModel[2];
    double fit;
    leastSquare(inliers, inlinersQty, inliersModel);
    fit = coefficientOfDetermination(data, data_size, inliersModel);
    if (verbose) {
      for (int o = 0; o < temp_size; o++) printf("{%lf, %lf}  ", temp[o][0], temp[o][1]);
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

  free2d(inliers, inlinersQty);

}

void RANSAC(double** data, int data_size) {
  int temp_size = P;
  double** temp = malloc2d(temp_size);
  for (int i = 0; i < data_size; i++) {
    temp[0][0] = data[i][0];
    temp[0][1] = data[i][1];
    for (int j = i + 1; j < data_size; j++) {
      temp[1][0] = data[j][0];
      temp[1][1] = data[j][1];
      checkModel(data, temp, data_size, temp_size);
    }
  }
  free2d(temp, temp_size);
}

int main() {
  double data_arr[][2] = { {0, 1}, {1, 2}, {2, 4}, {3, 4}, {4, 5} };
  // double data[][2] = {{95,90}, {85,80}, {80,70}, {70,65}, {60,60}};
  int data_size = sizeof(data_arr) / sizeof(data_arr[0]);	 // number of data points
  double** data = malloc2d(data_size);
  for (int i = 0; i < data_size; i++) {
    data[i][0] = data_arr[i][0];
    data[i][1] = data_arr[i][1];
  }
  RANSAC(data, data_size);
  free2d(data, data_size);

  // printf("\n------------------------\n");
  // printf("totalTime - %lf\n", totalTime/CLOCKS_PER_SEC);
  printf("\n------------------------\n");
  printf("\n");
  printf("bestFit:  \t%lf\n", bestFit);
  printf("bestModel:\t%lf\t%lf\n", bestModel[0], bestModel[1]);
  printf("\n");

  return 0;
}