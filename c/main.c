#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "ransac.c"

#define PI 3.14
#define file_path "dataset_test_2"

int readPoints(Point* data, Point* shape, int index) {
    char* fileName;
    if(index == 0 ){
        fileName="data0.txt";
    }else if(index == 1 ){
       fileName="data1.txt";
    }else if(index == 2 ){
       fileName="data2.txt";
    }else if(index == 3 ){
       fileName="data3.txt";
    }else if(index == 4 ){
       fileName="data4.txt";
    }

    FILE* file = fopen(fileName, "r");

    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo\n");
        return 1;
    }

    if (fscanf(file, "%d %d", &shape[0].x, &shape[0].y) == 1) {

    }
    int i = 0;
    while (fscanf(file, "%d %d", &data[i].x, &data[i].y) != EOF) {
        //printf("%d %d - %d\n", data[i].x, data[i].y, i);
        i++;
    }
    fclose(file);

    return i;
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
    Point shape[1];

    Point data2[MAX_POINTS];
    RansacResult ransacResult;


     // number of data points


    for(int i = 0; i < 5; i++){
        Point data[20*MAX_POINTS];
        int points =readPoints(data, shape,i);
        int data_size = (int)shape[0].x;
        if(data_size > MAX_POINTS) data_size = MAX_POINTS;
        ransacResult = RANSAC(data, points,data_size);
        printf("\n----------------------\n");
        printf("bestFit: %f\n", ransacResult.bestFit);
        printf("bestQty: %d\n", ransacResult.bestQty);
        printf("bestModel: %f\t%f\n", ransacResult.bestModel.a,ransacResult.bestModel.b );
        printf("\n----------------------\n");
    }
/*
    model1 = ransacResult.bestModel;
    int inliers_size = ransacResult.bestQty;
    int outliers_size = (int)(data_size-ransacResult.bestQty);

    for (int k=0; k<outliers_size; k++) {
        data2[k] = data[indexOutliers[k]];
    }

    if (outliers_size>10) {
        ransacResult = RANSAC(data2, outliers_size);
        model2 = ransacResult.bestModel;
    }

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
    printf("\n------------------------\n");
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
*/
    return 0;
}
