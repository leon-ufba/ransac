#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
  float x;
  float y;
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
#define C 0.5              // - The percent of close data points (inliers) required to assert that the model fits well to the data.
#define E 2               // - A threshold value to determine data points that are fit well by the model (inlier).
#define N 10                // - Number of iterations required
#define MIN_DIST_POINTS 10  // - The minimum points distance required to select the sample

#define POINT_SIZE sizeof(Point)*2
#define MAX_POINTS 300

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

void checkModel(Point* data, Point* temp, RansacResult* rs, int data_size, int temp_size) {
  
    Point inliers[MAX_POINTS];
    Point outliers[MAX_POINTS];
    int inlinersSize = 0;
    int outlierSize = 0;
    Line model = leastSquare(temp, temp_size);

    inliersOutliers(data, model, inliers, outliers, data_size, &inlinersSize, &outlierSize);
    
    if(inlinersSize >= rs->bestQty && inlinersSize >= (int)(data_size * C)){
        Line inliersModel = leastSquare(inliers, inlinersSize);
        float inliersAvg_y = 0;
        for (int i = 0; i < inlinersSize; i++) {
            inliersAvg_y += inliers[i].y;
        }
        inliersAvg_y /= inlinersSize;
        float  inliersFit = coefficientOfDetermination(inliers, inliersModel, inliersAvg_y, data_size);
        if (inliersFit < rs->bestFit) {
        rs->bestModel = inliersModel;
        rs->bestFit = inliersFit;
        rs->bestQty = inlinersSize;
        }
    } 
}
float squareDistanceBetweenPoints (Point* a, Point* b){
    int dx = a->x - b->x;
    int dy = a->y - b->y;
    return (dx * dx) + (dy * dy);
}

RansacResult RANSAC(Point* botPos, Point* data, Point* outliers, int data_size) {
    RansacResult rs;
    
    rs.bestModel.a = 0.0;
    rs.bestModel.b = botPos->y;
    rs.bestFit = INFINITY;
    rs.bestQty = 0;
    
    Point inliers[MAX_POINTS];
    
    int temp_dist_points = 0;
    int temp_index = 0;

    int loopCounter= 0;
    int inlinersSize = 0;
    int outlierSize = 0;

    inliersOutliers(data, rs.bestModel, inliers, outliers, data_size, &inlinersSize, &outlierSize);

    if (outlierSize == 0) {
        rs.bestFit = INFINITY;
        rs.bestQty = data_size;
        return rs;
    }
    int temp_size = MIN_POINTS;
    Point temp[temp_size]; // alocação tamanho P
    
    /**for (int i=0; i<=outlierSize; i++){
        printf("%f, %f\n", outliers[i].x, outliers[i].y);
    }**/

    //Posição inicial do robô
    temp[0] = outliers[0];

    //Execute for N iterations
    while(loopCounter < N) {
        //Sorteia 2 coordenadas que tenham uma distância minima entre si
        if(temp_dist_points < MIN_DIST_POINTS) {
        for (int j = 1; j < temp_size; j++) {
            temp_index = rand() % outlierSize;
            temp[j] = data[temp_index];

            temp_dist_points = squareDistanceBetweenPoints(&temp[0], &temp[1]);
        }
        }
        else {
            checkModel(outliers, temp, &rs, outlierSize, temp_size);
            temp_dist_points = 0;
            loopCounter++;
        }
    }

    return rs;
}
