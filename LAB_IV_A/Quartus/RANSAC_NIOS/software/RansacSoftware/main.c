/*
 * main.c
 *
 *  Created on: 14 de jul de 2023
 *      Author: Caroline
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ransac.h"

#define END_BASE_MEMO (int *) 0x0000
#define END_BASE_CONTROLE (int *) 0x0004
#define END_BASE_DATA (int *) 0x0018


int main() {

	int *data = END_BASE_DATA;
	FILE *entrada;
	FILE *saida;
	char next_line;
	int step;
	int data_size, x, y;
	Point outliers[MAX_POINTS];


	entrada = fopen("/mnt/host/FPGAin.txt", "r");
	saida = fopen("/mnt/host/FPGAout.txt", "w");

	while (!(feof(entrada))) {
		fscanf(entrada, "%d", &step);
		fscanf(entrada, "%d", &data_size);
		for (int i = 0; i < data_size; i++) {
			fscanf(entrada, "%d %d", &x, &y);
			data[i] = (x&0xFF)|(y<<8);
		}
		fscanf(entrada, "%c", &next_line);


	if(data_size > MAX_POINTS) data_size = MAX_POINTS;

// ------------ Variaveis para modelo de linha ------------//
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
	float distance = 0;
	float angle = 0.0;

	if  ((model.bestModel.a < 0.1)&&(model.bestModel.a > -0.1)){
		distance = 50;
	}
	else
	{
		intersection = calculateIntersection(&model.bestModel,  &reference);
		distance = square_root(squareDistanceBetweenPoints(&intersection, &start));
		angle = getAngleFromModel (model.bestModel.a);
	}


	fprintf(saida, "%d\n", step);
	fprintf(saida, "[%.2f, %.2f]\n", model.bestModel.a, model.bestModel.b );
	fprintf(saida, "%.2f\n", model.bestFit);
	fprintf(saida, "%d\n", model.bestQty);
	fprintf(saida, "%.2f\n", angle);
	fprintf(saida, "%.2f", distance);
	fprintf(saida, "%c", '\n');
	fprintf(saida, "%c", '\n');
	}

	fclose(entrada);
	fclose(saida);

	return 0;

}
