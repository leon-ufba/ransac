/*
 * ransac.h
 *
 *  Created on: 2 de jul de 2023
 *      Author: Caroline
 */

#ifndef RANSAC_H_
#define RANSAC_H_

#define END_BASE_MEMO (int *) 0x0000
#define END_BASE_CONTROLE (int *) 0x0004
#define END_BASE_DISTANCE (int *) 0x0008
#define END_BASE_ANGLE (int *) 0x00010
#define END_BASE_DATA (int *) 0x0018
#define END_BASE_DATA_Y (int *) 0x3ec8
//#define END_BASE_DATA_OUTLIERS_X (int *) 0x348
//#define END_BASE_DATA_OUTLIERS_Y (int *) 0x4b0
//#define END_BASE_DATA_INLIERS_X (int *) 0x5dc
//#define END_BASE_DATA_INLIERS_Y (int *) 0x6ea


#define X j
#define Y j+1
#define MAX_POINTS 300


int *data = END_BASE_DATA;
int *data_Y = END_BASE_DATA_Y;
int *store_distance= END_BASE_DISTANCE;
int *store_angle = END_BASE_ANGLE;
int *cena = END_BASE_MEMO;
//int *inliers_X = END_BASE_DATA_INLIERS_X;
//int *inliers_Y = END_BASE_DATA_INLIERS_Y;
//int *outliers_X = END_BASE_DATA_OUTLIERS_X;
//int *outliers_Y = END_BASE_DATA_OUTLIERS_Y;
int *controle = END_BASE_CONTROLE;


#define TAM (int)153*2

int size = 153;
char coords[TAM] = {
		0, 24, 1, 24, 2, 24, 3, 24, 4, 24, 5, 24, 6, 24, 7, 24, 8, 24, 9, 24, 10, 24,
		11, 24, 12, 24, 13, 24, 14, 24, 15, 24, 16, 24, 17, 24, 18, 24, 19, 24,
		20, 24, 21, 24, 22, 24, 23, 24, 24, 24, 25, 24, 26, 24, 27, 24, 28, 24, 29, 24,
		30, 24, 31, 24, 32, 24, 33, 24, 34, 24, 35, 24, 36, 24, 37, 24, 38, 24, 39, 24,
		40, 24, 41, 24, 42, 24, 43, 24, 44, 24, 45, 24, 46, 24, 47, 24, 48, 24, 49, 24,
		50, 24,  0, 25,  1, 25,  2, 25,  3, 25, 4, 25, 5, 25, 6, 25, 7, 25, 8, 25,
		9, 25, 10, 25, 11, 25, 12, 25, 13, 25, 14, 25, 15, 25, 16, 25, 17, 25, 18, 25,
		19, 25, 20, 25, 21, 25, 22, 25, 23, 25, 24, 25, 25, 25, 26, 25, 27, 25, 28, 25,
		29, 25, 30, 25, 31, 25, 32, 25, 33, 25, 34, 25, 35, 25, 36, 25, 37, 25, 38, 25,
		39, 25, 40, 25, 41, 25, 42, 25, 43, 25, 44, 25, 45, 25, 46, 25, 47, 25, 48, 25,
		49, 25, 50, 25, 0, 26, 1, 26, 2, 26, 3, 26, 4, 26, 5, 26, 6, 26, 7, 26,
		8, 26,  9, 26, 10, 26, 11, 26, 12, 26, 13, 26, 14, 26, 15, 26, 16, 26, 17, 26,
		18, 26, 19, 26, 20, 26, 21, 26, 22, 26, 23, 26, 24, 26, 25, 26, 26, 26, 27, 26,
		28, 26, 29, 26, 30, 26, 31, 26, 32, 26, 33, 26, 34, 26, 35, 26, 36, 26, 37, 26,
		38, 26, 39, 26, 40, 26, 41, 26, 42, 26, 43, 26, 44, 26, 45, 26, 46, 26, 47, 26,
		48, 26, 49, 26, 50, 26};




#endif /* RANSAC_H_ */
