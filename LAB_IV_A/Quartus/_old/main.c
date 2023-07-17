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
#define PIO_DADOS (char *) 0x11020
#define PIO_SAIDA (char *) 0x11010
#define PIO_CONTROLE (char *) 0x11000


int main() {

	int *data = END_BASE_DATA;
	FILE *entrada;
	//FILE *saida;
	int step;
	int data_size, x, y;
	//char temp_x, temp_y;
	//char str[20];

	Point outliers[MAX_POINTS];


	entrada = fopen("/mnt/host/entrada.txt", "r");

	while (!(feof(entrada))) {
		fscanf(entrada, "%d", &step);
		fscanf(entrada, "%d", &data_size);
		for (int i = 0; i < data_size; i++) {
			fscanf(entrada, "%d %d", &x, &y);
			data[i] = (x&0xFF)|(y<<8);
		}
	}

	fclose(entrada);

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
	int distance = 0;
	float angle = 0.0;

	if  (model.bestModel.a == 0.0){
		distance = square_root(data[data_size-1]&0xFF);
	}
	else
	{
		intersection = calculateIntersection(&model.bestModel,  &reference);
		distance = square_root((int)squareDistanceBetweenPoints(&intersection, &start));
		angle = getAngleFromModel (model.bestModel.a);
	}


	return 0;

}
