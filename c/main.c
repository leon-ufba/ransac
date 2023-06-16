#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ransac.c"

#define PI 3.14
#define file_path "..\\python\\coords\\dataset_test_2.txt"

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

int main() {
    srand(time(NULL));
    Line model1 = { 0.0, 0.0 };
    Line model2 = { 0.0, 0.0 };
    Point shape[1];
    Point data[MAX_POINTS];
    Point data2[MAX_POINTS];

    readPoints(data, shape);

    int data_size = (int)shape[0].x; // number of data points

    if(data_size > MAX_POINTS) data_size = MAX_POINTS;
    
    model1 = RANSAC(data, data_size);

    int inliers_size = bestInlinersQty;
    int outliers_size = (int)(data_size-bestInlinersQty);

    for (int k=0; k<outliers_size; k++) {
        data2[k] = data[indexOutliers[k]];
    }

    if (outliers_size>10) model2 = RANSAC(data2, outliers_size);

    Point intersection = { 0.0, 0.0 };
    float distance = 0.0;
    float angle = 0.0;
    Point begin = data[data_size-2];
    if (model2.a != 0 & model2.b != 0) { 
        intersection = calculateIntersection(&model1, &model2);
        distance = squareDistanceBetweenPoints(&intersection, &begin);
        angle = getAngleFromModel(model2.a);
    }
    
    
    saveResult(&model1, &model2, &begin, &intersection, distance, angle);
    
    printf("data_size: \t%d\n", data_size);
    printf("initial position:\t%d\t%d\n", begin.x, begin.y);
    printf("\n--------Step 1----------\n");
    printf("inliers_size: \t%d\n", inliers_size);
    printf("outliers_size:\t%d\n", outliers_size);
    printf("\n--------Ransac Result----------\n");
    printf("bestModel 1:\t%f\t%f\n", model1.a, model1.b);
    printf("bestModel 2:\t%f\t%f\n", model2.a, model2.b);
    printf("\n--------Result----------\n");
    printf("intersection point:\t%d\t%d\n", intersection.x, intersection.y);
    printf("square distance:\t%f\n", distance);
    printf("angle: \t%f\n", angle);
    printf("\n");

    return 0;
}