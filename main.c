#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define P 2    // - The minimum number of data points required to estimate the model parameters.
#define T 100  // - The maximum number of iterations allowed in the algorithm.
#define C 0.10 // - The percent of close data points (inliers) required to assert that the model fits well to the data.
#define E 0.10 // - A threshold value to determine data points that are fit well by the model (inlier).

volatile double bestModel[2] = {0, 0};
volatile double bestFit = INFINITY;
volatile int verbose = 0;

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

double dimSum(double** data, int n, int dim) {
  double sum = 0.0;
  for (int i = 0; i < n; i++) {
    sum += data[i][dim];
  }
  return sum;
}

double dimsProdSum(double** data, int n, int dim1, int dim2) {
  double sum = 0.0;
  for (int i = 0; i < n; i++) {
    sum += data[i][dim1] * data[i][dim2];
  }
  return sum;
}

double coefficientOfDetermination(double** data, int n, double model[2]) {
  double ss_res = 0;
  for (int i = 0; i < n; i++) {
    double f = model[0] * data[i][0] + model[1];
    double y_f = (data[i][1] - f);
    ss_res += y_f * y_f;
  }
  double y_avg = dimSum(data, n, 1) / n;
  double ss_tot = 0;
  for (int i = 0; i < n; i++) {
    double y_y = (data[i][1] - y_avg);
    ss_tot += y_y * y_y;
  }
  // double r = 1 - (ss_res / ss_tot); // original coefficient
  double r = (ss_res / ss_tot);	 // modified coefficient (lower is better)
  return r;
}

void leastSquare(double** data, int n, double model[2]) {
  double sx = dimSum(data, n, 0);
  double sy = dimSum(data, n, 1);
  double sxy = dimsProdSum(data, n, 0, 1);
  double sx2 = dimsProdSum(data, n, 0, 0);
  double a = (n * sxy - sx * sy) / (n * sx2 - sx * sx);
  double b = (sy / n) - a * (sx / n);
  model[0] = a;
  model[1] = b;
}

double distToLine(double* point, double model[2]) {
  double x = point[0];
  double y = point[1];
  double a = model[0];
  double b = -1;
  double c = model[1];
  return fabs(a * x + b * y + c) / sqrt(a * a + b * b);
}

void checkModel(double** data, double** temp, int data_size, int temp_size) {
  double model[2];
  leastSquare(temp, temp_size, model);


  double** inliers = malloc2d(data_size);
  int inlinersQty = 0;

  for (int k = 0; k < data_size; k++) {
    double dist = distToLine(data[k], model);
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

void combinationUtil(double** data, double** temp, int start, int end, int index, int data_size, int temp_size) {
  if (index == temp_size) {
    checkModel(data, temp, data_size, temp_size);
    return;
  }
  for (int i = start; i <= end && end - i + 1 >= temp_size - index; i++) {
    temp[index][0] = data[i][0];
    temp[index][1] = data[i][1];
    combinationUtil(data, temp, i + 1, end, index + 1, data_size, temp_size);
  }
}

void RANSAC(double** data, int data_size) {
  // FOR MORE THAN P INITIAL POINTS
  // for (int temp_size = P; temp_size <= data_size; temp_size++) {
  //   double** temp = malloc2d(temp_size);
  //   combinationUtil(data, temp, 0, data_size - 1, 0, data_size, temp_size);
  //   free2d(temp, temp_size);
  // }

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

  printf("\n------------------------\n");
  printf("\n");
  printf("bestFit:  \t%lf\n", bestFit);
  printf("bestModel:\t%lf\t%lf\n", bestModel[0], bestModel[1]);
  printf("\n");

  return 0;
}