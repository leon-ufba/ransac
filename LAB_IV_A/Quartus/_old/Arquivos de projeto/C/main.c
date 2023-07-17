#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ransac.c"
#include "ransac.h"



Point calculateIntersection(Line* k, Line* l) {
    Point intersection;
    controle[0] = 11;
    intersection.x = (l->b - k->b) / (k->a - l->a);
    intersection.y = k->a * intersection.x + k->b;
    return intersection;
}

float getAngleFromModel(float a) {
    float radian = atan(a);
    return radian;
}

int main() {

    Point outliers[MAX_POINTS];
    int temp_data_size = 2*size;
    int data_size = size;

    int j = 0;
    for (int i = 0; i<=temp_data_size; i+=1) {
    	data[i] = (coords[X]&0xFF)|(coords[Y]<<8);
    	controle[0] = i;
    	j+=2;
    }

    controle[0] = 1;
    if(data_size > MAX_POINTS) data_size = MAX_POINTS;

    // ------------ Calcula primeiro modelo de linha ------------//
    //Posicao inical do robo
    Point start;
    start.x = 0;
    start.y = 25;
    controle[0] = 2;
    RansacResult model;
    Line reference;
	reference.a = 0;
	reference.a = 25;

    model = RANSAC(&start, outliers, data_size);

    // ------------ Variaveis para resultado final -------------//
    Point intersection = { 0.0, 0.0 };
    int distance = 0;
    float angle = 0.0;

	if  (model.bestModel.a == 0.0){
		controle[0] = 9;
		distance = data[data_size]&0xFF;
	}
	else
	{
		controle[0] = 10;
		intersection = calculateIntersection(&model.bestModel,  &reference);
		distance = (int)squareDistanceBetweenPoints(&intersection, &start);
		angle = getAngleFromModel (model.bestModel.a);
	}

	controle[0] = 12;
	store_distance[0] = distance;
	store_angle[0] = angle;
	controle[0] = 13;

    printf("%f %f\n", intersection.x, intersection.y);
    printf("%d\n", distance);
    printf("%f\n", angle);
    printf("%f\n", model.bestFit);
    printf("%d\n", model.bestQty);
    printf("%f %f\n", model.bestModel.a, model.bestModel.b );
    controle[0] = 14;

    return 0;
}
