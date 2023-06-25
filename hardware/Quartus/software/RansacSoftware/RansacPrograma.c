#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "ransac.h"


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
        i++;
    }
    fclose(file);

    return i;
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
	fprintf(stderr,"Init");
    //srand(time(NULL));
    Line model1 = { 0.0, 0.0 };
    Point shape;
    Point myStruct;

    RansacResult ransacResult;
    //for(int i = 0; i < 5; i++){
        readStructFromMemory(&shape,MEMORY_DATA);
        fprintf(stdout,"Shape X: %d\n", shape.x);
        fprintf(stdout,"Shape Y: %d\n", shape.y);
        Point * data = MEMORY_DATA;
        int* points = MEMORY_DATA+1 ;//readPoints(data, shape,i);
        int* data_size = MEMORY_DATA;
        if(data_size > MAX_POINTS) data_size = MAX_POINTS;
        ransacResult = RANSAC(data, *points, *data_size);
        printf("\n----------------------\n");
        printf("bestFit: %f\n", ransacResult.bestFit);
        printf("bestQty: %d\n", ransacResult.bestQty);
        printf("bestModel: %f\t%f\n", ransacResult.bestModel.a,ransacResult.bestModel.b );
        printf("\n----------------------\n");
    //}

    return 0;
}
