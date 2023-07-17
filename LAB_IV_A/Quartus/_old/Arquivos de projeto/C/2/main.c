#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ransac.h"
#include "coords.h"

#define END_BASE_MEMO (int *) 0x0000
#define END_BASE_CONTROLE (int *) 0x0004
#define END_BASE_DISTANCE (int *) 0x0008
#define END_BASE_ANGLE (int *) 0x00010
#define END_BASE_DATA (int *) 0x0018

int main() {
	int *data = END_BASE_DATA;
    Point outliers[MAX_POINTS];
    int temp_data_size = 2*size;
    int data_size = size;

    int j = 0;
    for (int i = 0; i<=temp_data_size; i+=1) {
    	data[i] = (coords[X]&0xFF)|(coords[Y]<<8);
    	j+=2;
    }

    if(data_size > MAX_POINTS) data_size = MAX_POINTS;

    // ------------ Calcula primeiro modelo de linha ------------//
    //Posicao inical do robo
    Point start;
    start.x = 0;
    start.y = 25;
    RansacResult model;
    Line reference;
	reference.a = 0;
	reference.a = 25;

    model = RANSAC(data, &start, outliers, data_size);

    // ------------ Variaveis para resultado final -------------//
    Point intersection = { 0.0, 0.0 };
    int distance = 0;
    float angle = 0.0;

	if  (model.bestModel.a == 0.0){
		distance = data[data_size]&0xFF;
	}
	else
	{
		intersection = calculateIntersection(&model.bestModel,  &reference);
		distance = (int)squareDistanceBetweenPoints(&intersection, &start);
		angle = getAngleFromModel (model.bestModel.a);
	}

    printf("%d %d\n", intersection.x, intersection.y);
    printf("%d\n", distance);
    printf("%f\n", angle);
    printf("%f\n", model.bestFit);
    printf("%d\n", model.bestQty);
    printf("%f %f\n", model.bestModel.a, model.bestModel.b );

    return 0;
}
