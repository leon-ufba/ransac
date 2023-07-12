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
#define STEP coords_2
#define SIZE size_2

int main() {
	int *data = END_BASE_DATA;
    Point outliers[MAX_POINTS];
    int temp_data_size = 0;
    int data_size = 0;

    //read data_size
    data_size = (int)(SIZE&0xFF);
    temp_data_size = (2*data_size);

    int j = 0;
    for (int i = 0; i<=temp_data_size; i+=1) {
    	data[i] = (STEP[X]&0xFF)|(STEP[Y]<<8);
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
	reference.b = 25;

    model = RANSAC(data, &start, outliers, data_size);


    // ------------ Variaveis para resultado final -------------//
    Point intersection = { 0.0, 0.0 };
    int distance = 0.0;
    float angle = 0.0;

	if  (model.bestModel.a == 0.0){
		distance = data[data_size-1]&0xFF;
	}
	else
	{
		intersection = calculateIntersection(&model.bestModel,  &reference);
		distance = (int)squareDistanceBetweenPoints(&intersection, &start);
		angle = getAngleFromModel (model.bestModel.a);
	}

	printf("-----LOG-----\n");
    printf("%d %d\n", intersection.x, intersection.y);
    printf("-----RESULTADO-----\n");
    printf("%f %f\n", model.bestModel.a, model.bestModel.b );
    printf("%f\n", model.bestFit);
    printf("%d\n", model.bestQty);
    printf("%f\n", angle);
    printf("%d\n", distance);

    return 0;
}
