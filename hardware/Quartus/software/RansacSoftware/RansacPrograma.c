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
#define PI 3.14
#define file_git status
path "..\\python\\coords\\dataset_test_2.txt"


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


void printPointArray(Point arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("Point %d: x = %d, y = %d\n", i, arr[i].x, arr[i].y);
  }
}

int readPoints(Point* data, Point* shape) {
    FILE* file = fopen(file_path, "r");
    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo\n");
        return 1;
    }

    if (fscanf(file, "%d %d", &shape[0].x, &shape[0].y) == 1) {

    }
    int i = 0;
    while (fscanf(file, "%d %d", &data[i].x, &data[i].y) != EOF) {
        i++;
    }

    fclose(file);

    return 0;
}

int saveResult(Line* f, Line* s, Point* begin, Point* intersection, float distance, float angle) {
    FILE *file = fopen("resultados.csv", "w");
    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo\n");
        return 1;
    }

    // Escreve os resultados no arquivo
    fprintf(file, "%.6f, %.6f\n", f->a, f->b);
    fprintf(file, "%.6f, %.6f\n", s->a, s->b);
    fprintf(file, "%d, %d\n", begin->x, begin->y);
    fprintf(file, "%d, %d\n", intersection->x, intersection->y);
    fprintf(file, "%.6f, %.6f\n", distance, angle);


    fclose(file);

    return 0;
}

Point calculateIntersection(Line* k, Line* l) {
    Point intersection;
    intersection.x = (l->b - k->b) / (k->a - l->a);
    intersection.y = k->a * intersection.x + k->b;
    return intersection;
}

float radianToDegree(float radian) {
    return radian * 180.0 / PI;
}

float getAngleFromModel(float a) {
    float radian = atan(a);
    float degree = radianToDegree(radian);
    return degree;
}






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
    if (inlinersSize > rs.bestFit) {
      rs.bestModel = model;
      rs.bestQty = inlinersSize;
      rs.bestFit = inlinersSize;
    }
 }


 /*/ for (int k = 0; k < data_size; k++) {
    //calcula dist�ncia entre o modelo e os pontos
    float dist = (model.a * data[k].x - data[k].y + model.b);
    if (dist * dist <= square2) {
      inliers[inlinersSize] = data[k];
      inlinersSize++;
    } else {
      // salva o index dos outliers
      indexOutliers[outlierSize] = k;
      outlierSize++;
    }
  }*/

}


float squareDistanceBetweenPoints (Point* a, Point* b){
  int dx = a->x - b->x;
  int dy = a->y - b->y;
  return (dx * dx) + (dy * dy);
}

RansacResult RANSAC(Point* data, int data_size) {
  rs.bestModel.a = 0.0;
  rs.bestModel.b = data_size;

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

  nearestOutliers(outliers, rs.bestModel, nearest_outliers, data_size);
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

int main() {
    srand(time(NULL));
    Line model1 = { 0.0, 0.0 };
    Line model2 = { 0.0, 0.0 };

    return 0;
}

(int **) 0x7ffffac98
(int **) 0x7ffffac98