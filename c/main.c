#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ransac.c"

//#define file_path "..\\..\\python\\coords\\dataset_test_2.txt"
#define file_path "testes\\step1.txt"

int readPoints(int* step, Point* StepXY, int* data_size, Point* data) {
    FILE* file = fopen(file_path, "r");
    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo\n");
        return 1;
    }
    
    if (fscanf(file, "%d", step) != 1) {
        fprintf(stderr, "Erro ao ler o valor de step\n");
        fclose(file);
        return 1;
    }
    
    if (fscanf(file, "%f %f", &StepXY->x, &StepXY->y) != 2) {
        fprintf(stderr, "Erro ao ler o valor de StepXY\n");
        fclose(file);
        return 1;
    }
    
    if (fscanf(file, "%d", data_size) != 1) {
        fprintf(stderr, "Erro ao ler o valor de data_size\n");
        fclose(file);
        return 1;
    }
     for (int i = 0; i < *data_size; i++) {
        if (fscanf(file, "%f %f", &(data)[i].x, &(data)[i].y) != 2) {
            fprintf(stderr, "Erro ao ler os valores de data\n");
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    
    return 0;
}

int saveResult(int step, RansacResult rs, float distance, float angle) {
    FILE *file = fopen("FPGAout1.txt", "w");
    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo\n");
        return 1;
    }

    // Escreve os resultados no arquivo
    fprintf(file, "%d\n", step);
    fprintf(file, "[%.6f, %.6f]\n", rs.bestModel.a, rs.bestModel.b );
    fprintf(file, "%.6f\n", rs.bestFit);
    fprintf(file, "%d\n", rs.bestQty);
    fprintf(file, "%.6f\n", angle);
    fprintf(file, "%.6f", distance);

    fclose(file);

    return 0;
}

Point calculateIntersection(Line* k, Line* l) {
    Point intersection;
    intersection.x = (l->b - k->b) / (k->a - l->a);
    intersection.y = k->a * intersection.x + k->b;
    return intersection;
}

float getAngleFromModel(float a) {
    float radian = atan(a);
    //float degree = radianToDegree(radian);
    return radian;
}

int main() {
    Point start;
    Point StepXY;
    Point data[MAX_POINTS]= { 0.0, 0.0 };
    Point outliers[MAX_POINTS] = { 0.0, 0.0 };
    RansacResult model = { 0.0, 0.0 };
    int data_size;
    int step;

    if (readPoints(&step, &StepXY, &data_size, data) != 0) {
        fprintf(stderr, "Erro ao ler os pontos do arquivo\n");
        return 1;
    }

    if(data_size > MAX_POINTS) data_size = MAX_POINTS;

    // ------------ Calcula primeiro modelo de linha ------------//
    //Posicao inical do robo
    start.x = 0;
    start.y = 25;
    model = RANSAC(&start, data, outliers, data_size);
    int inliers_size = model.bestQty;
    int outliers_size = (int)(data_size-inliers_size);

    // ------------ Variaveis para resultado final -------------//
    Point intersection = { 0.0, 0.0 };
    float distance = 0.0;
    float angle = 0.0;
    Line reference;
    reference.a = 0;
    reference.b = 25;

	if  (model.bestModel.a == 0.0){
		distance = data[data_size-1].x;
	}
	else
	{
		intersection = calculateIntersection(&model.bestModel,  &reference);
		distance = squareDistanceBetweenPoints(&intersection, &start);
        distance = sqrt(distance);
		angle = getAngleFromModel (model.bestModel.a);
	}
    
    saveResult(step, model, distance, angle);
    printf("data_size: \t%d\n", data_size);
    printf("initial position:\t%f\t%f\n", start.x, start.y);
    printf("\n--------Step 1----------\n");
    printf("inliers_size: \t%d\n", inliers_size);
    printf("outliers_size:\t%d\n", outliers_size);
    printf("\n--------Result----------\n");
    printf("intersection point:\t%f\t%f\n", intersection.x, intersection.y);
    printf("square distance:\t%f\n", distance);
    printf("angle: \t%f\n", angle);
    printf("\n");

    printf("\n-------------------------------------------------------------\n");
    printf("bestFit: %f\n", model.bestFit);
    printf("bestQty: %d\n", model.bestQty);
    printf("bestModel: %f\t%f\n", model.bestModel.a, model.bestModel.b );

    return 0;
}