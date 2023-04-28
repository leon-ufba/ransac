#include <stdio.h>
#include <math.h>

#define p 2   // - The minimum number of data points required to estimate the model parameters.
#define t 100 // - The maximum number of iterations allowed in the algorithm.
#define c 10  // - The number of close data points (inliers) required to assert that the model fits well to the data.
#define e 0.1 // - A threshold value to determine data points that are fit well by the model (inlier).

double dimSum(double data[][2], int n, int dim) {
  double sum = 0.0;
  for (int i = 0; i < n; i++) {
    sum += data[i][dim];
  }
  return sum;
}

double dimsProdSum(double data[][2], int n, int dim1, int dim2) {
  double sum = 0.0;
  for (int i = 0; i < n; i++) {
    sum += data[i][dim1] * data[i][dim2];
  }
  return sum;
}

void leastSquare(double data[][2], int n, double result[2]) {
  double sx = dimSum(data, n, 0);
  double sy = dimSum(data, n, 1);
  double sxy = dimsProdSum(data, n, 0, 1);
  double sx2 = dimsProdSum(data, n, 0, 0);
  double a = (n * sxy - sx * sy) / (n * sx2 - sx * sx);
  double b = (sy / n) - a * (sx / n);
  result[0] = a;
  result[1] = b;
}

double coefficientOfDetermination(double data[][2], int n, double regLin[2]) {
  double ss_res = 0;
  for (int i = 0; i < n; i++) {
    double f = regLin[0] * data[i][0] + regLin[1];
    double y_f = (data[i][1] - f);
    ss_res += y_f * y_f;
  }
  double y_avg = dimSum(data, n, 1) / n;
  double ss_tot = 0;
  for (int i = 0; i < n; i++) {
    double y_y = (data[i][1] - y_avg);
    ss_tot += y_y * y_y;
  }
  double r = 1 - (ss_res / ss_tot);
  return r;
}

double RANSAC(double data[][2], int n) {
  double bestFit = 0.0;
  // double bestErr = 1.0 / 0.0;
  
  // for (int i = 0; i < n; i++) {
  //   printf("%lf, %lf\n", data[i][0], data[i][1]);
  // }

  double regLin[2];
  leastSquare(data, n, regLin);
  
  printf("%lf  %lf\n", regLin[0], regLin[1]);

  double r = coefficientOfDetermination(data, n, regLin);

  printf("%lf\n", r);

  // for (int i = 0; i < t; i++) {
  //   int maybeInliers[p][2]; //p randomly selected values from data
  //   int maybeModel[3]; //model parameters fitted to maybeInliers
  // }
  
  
  // maybeInliers := p randomly selected values from data
  // maybeModel := model parameters fitted to maybeInliers
  // confirmedInliers := empty set
  // for every point in data do
  //     if point fits maybeModel with an error smaller than t then
  //         add point to confirmedInliers
  //     end if
  // end for
  // if the number of elements in confirmedInliers is > d then
  //     // This implies that we may have found a good model.
  //     // Now test how good it is.
  //     betterModel := model parameters fitted to all the points in confirmedInliers
  //     thisErr := a measure of how well betterModel fits these points
  //     if thisErr < bestErr then
  //         bestFit := betterModel
  //         bestErr := thisErr
  //     end if
  // end if

  return bestFit;
}

int main () {
  printf("Hello World1\n");
  double data[][2] = {{0,1}, {1,2}, {2,4}, {3,4}, {4,5}};
  // double data[][2] = {{95,90}, {85,80}, {80,70}, {70,65}, {60,60}};
  int n = sizeof(data) / sizeof(double) / 2; // number of n

  RANSAC(data, n);
  printf("Hello World2\n");
  return 0;
}