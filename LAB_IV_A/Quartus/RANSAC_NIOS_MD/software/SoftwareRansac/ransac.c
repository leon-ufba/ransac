#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdint.h>
#include "ransac.h"

// RANSAC parameters
#define MIN_POINTS 2        // - The minimum number of data points required to estimate the model parameters.
#define C 0.5              // - The percent of close data points (inliers) required to assert that the model fits well to the data.
#define E 5               // - A threshold value to determine data points that are fit well by the model (inlier).
#define N 10                // - Number of iterations required
#define MIN_DIST_POINTS 25  // - The minimum points distance required to select the sample


float square_root(float number) {
	//*MEDIDOR_ESCRITA = 0; // para resetar a contagem
	//*MEDIDOR_ESCRITA = 1; // para iniciar a contagem
	float x = number;
	float y = 1;
    float precision = 0.1;
    while (x - y > precision) {
        x = (x + y) / 2;
        y = number / x;
    }

    //*MEDIDOR_ESCRITA = 2; // para pausar a contagem
    //fprintf('square_root = %d', MEDIDOR_LEITURA);
    return x;
}

Point calculateIntersection(Line* k, Line* l) {
	//*MEDIDOR_ESCRITA = 0; // para resetar a contagem
	//*MEDIDOR_ESCRITA = 1; // para iniciar a contagem
	Point intersection;
    intersection.x = (l->b - k->b) / (k->a - l->a);
    intersection.y = (k->a * intersection.x + k->b);
    //*MEDIDOR_ESCRITA = 2; // para pausar a contagem
    return intersection;
}

float getAngleFromModel(float a) {
	//*MEDIDOR_ESCRITA = 0; // para resetar a contagem
	//*MEDIDOR_ESCRITA = 1; // para iniciar a contagem
	float radian = -atan(a);
	//*MEDIDOR_ESCRITA = 2; // para pausar a contagem
    return radian;
}

Line leastSquare(Point* data, int size) {
	//*MEDIDOR_ESCRITA = 0; // para resetar a contagem
	//*MEDIDOR_ESCRITA = 1; // para iniciar a contagem
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
    //*MEDIDOR_ESCRITA = 2; // para pausar a contagem
    return line;
}

float coefficientOfDetermination(Point* data, Line model, float avg_y, int data_size) {
	//*MEDIDOR_ESCRITA = 0; // para resetar a contagem
	//*MEDIDOR_ESCRITA = 1; // para iniciar a contagem
	float ss_res = 0;
    float ss_tot = 0;
    for (int i = 0; i < data_size; i++) {
    	*MEDIDOR_ESCRITA = 0; // para resetar a contagem
    	*MEDIDOR_ESCRITA = 1; // para iniciar a contagem
        float f = model.a * data[i].x + model.b;
        float y_f = (data[i].y - f);
        float y_y = (data[i].y - avg_y);
        ss_res += y_f * y_f;
        ss_tot += y_y * y_y;
        *MEDIDOR_ESCRITA = 2; // para pausar a contagem
    }
    float r = (ss_res / ss_tot);
    //*MEDIDOR_ESCRITA = 2; // para pausar a contagem
    return r;
}

void inliersOutliersMemory(int* data, Line model, Point* inliers, Point* outliers, int dataSize, int* inlierSize, int* outlierSize) {

	*MEDIDOR_ESCRITA = 0; // para resetar a contagem
	*MEDIDOR_ESCRITA = 1; // para iniciar a contagem
    float square2 = E * E * (model.a * model.a + 1.0);
    *MEDIDOR_ESCRITA = 2; // para pausar a contagem

    for (int k = 0; k < dataSize; k++) {
    	int tempX = data[k]&0xFF;
    	int tempY = (data[k]>>8)&0xFF ;

    	*MEDIDOR_ESCRITA = 0; // para resetar a contagem
    	*MEDIDOR_ESCRITA = 1; // para iniciar a contagem
        float dist = (model.a * tempX - tempY + model.b);
        *MEDIDOR_ESCRITA = 2; // para pausar a contagem

        if (dist * dist <= square2) {
        	inliers[*inlierSize].x = data[k]&0xFF;
        	inliers[*inlierSize].y = (data[k]>>8)&0xFF;
            (*inlierSize)++;
        } else {
        	outliers[*outlierSize].x = data[k]&0xFF;
        	outliers[*outlierSize].y = (data[k]>>8)&0xFF;
            (*outlierSize)++;
        }
    }
    //*MEDIDOR_ESCRITA = 2; // para pausar a contagem
    //*MEDIDOR_ESCRITA = 2; // para pausar a contagem

}

void inliersOutliers(Point* data, Line model, Point* inliers, Point* outliers, int dataSize, int* inlierSize, int* outlierSize) {
	//*MEDIDOR_ESCRITA = 0; // para resetar a contagem
	//*MEDIDOR_ESCRITA = 1; // para iniciar a contagem
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
    //*MEDIDOR_ESCRITA = 2; // para pausar a contagem
    //*MEDIDOR_ESCRITA = 2; // para pausar a contagem

}

void checkModel(Point* data, Point* temp, RansacResult* rs, int data_size, int temp_size) {
	//*MEDIDOR_ESCRITA = 0; // para resetar a contagem
	//*MEDIDOR_ESCRITA = 1; // para iniciar a contagem
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
    //*MEDIDOR_ESCRITA = 2; // para pausar a contagem
    //*MEDIDOR_ESCRITA = 2;
}

float squareDistanceBetweenPoints (Point* a, Point* b){
	//*MEDIDOR_ESCRITA = 0; // para resetar a contagem
	//*MEDIDOR_ESCRITA = 1; // para iniciar a contagem
	int dx = a->x - b->x;
    int dy = a->y - b->y;
    float resultado = (dx * dx) + (dy * dy);
    //*MEDIDOR_ESCRITA = 2; // para pausar a contagem
    return resultado;
}

RansacResult RANSAC(int* data, Point* botPos, Point* outliers, int data_size) {
    RansacResult rs;
    //srand(32);
    rs.bestModel.a = 0.0;
    rs.bestModel.b = (float)botPos->y;
    rs.bestFit = INFINITY;
    rs.bestQty = 0;

    Point inliers[MAX_POINTS];

    int temp_dist_points = 0;
    int temp_index = 0;

    int loopCounter = 0;
    int inlinersSize = 0;
    int outlierSize = 0;

    inliersOutliersMemory(data, rs.bestModel, inliers, outliers, data_size, &inlinersSize, &outlierSize);

    if (outlierSize <= 25) {
        rs.bestFit = INFINITY;
        rs.bestQty = data_size;
        return rs;
    }

    int temp_size = MIN_POINTS;
    Point temp[temp_size]; // alocacao tamanho P

    //Posicao inicial do robo
    temp[0] = outliers[0];
    //Execute for N iterations
    while(loopCounter < N) {
		//Sorteia 2 coordenadas que tenham uma distancia minima entre si
		if(temp_dist_points < MIN_DIST_POINTS) {
		for (int j = 1; j < temp_size; j++) {
			temp_index = rand() % outlierSize;
			temp[j].x = outliers[temp_index].x;
			temp[j].y = outliers[temp_index].y;
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
