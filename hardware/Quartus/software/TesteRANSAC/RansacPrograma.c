#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "ransac.h"


#define PI 3.14

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
	//fprintf(stderr,"Init\n");
    //srand(time(NULL));
    Point shape;

    RansacResult ransacResult;
    //for(int i = 0; i < 5; i++){
	readStructFromMemory(&shape,0);
	//fprintf(stdout,"Shape X: %d\n", shape.x);
	//fprintf(stdout,"Shape Y: %d\n", shape.y);
	//readStructFromMemory(&shape,2);

	int points = shape.x ;//readPoints(data, shape,i);
	int data_size = shape.x;
	if(data_size > MAX_POINTS) data_size = MAX_POINTS;
	ransacResult = RANSAC( points, data_size);
	printf("\n----------------------\n");
	printf("bestFit: %f\n", ransacResult.bestFit);
	printf("bestQty: %d\n", ransacResult.bestQty);
	printf("bestModel: %f\t%f\n", ransacResult.bestModel.a,ransacResult.bestModel.b );
	printf("\n----------------------\n");
    //}

    return 0;
}
