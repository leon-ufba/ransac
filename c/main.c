#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ransac.c"

#define PI 3.14
//#define file_path "..\\..\\python\\coords\\dataset_test_2.txt"
#define file_path "step1.txt"

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

int saveResult(Line* f, Line* s, Point* begin, Point* intersection, float distance, float angle) {
    FILE *file = fopen("FPGAout.txt", "w");
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

//float radianToDegree(float radian) {
//   return radian * 180.0 / PI;
//}

float getAngleFromModel(float a) {
    float radian = atan(a);
    //float degree = radianToDegree(radian);
    return radian;
}

int main() {
    Point begin;
    Point StepXY;
    Point data[MAX_POINTS]= { 0.0, 0.0 };
    Point outliers[MAX_POINTS] = { 0.0, 0.0 };
    RansacResult models[2] = { 0.0, 0.0 };
    int data_size;
    int step;

    if (readPoints(&step, &StepXY, &data_size, data) != 0) {
        fprintf(stderr, "Erro ao ler os pontos do arquivo\n");
        return 1;
    }

    if(data_size > MAX_POINTS) data_size = MAX_POINTS;

    // ------------ Calcula primeiro modelo de linha ------------//
    //Posicao inical do robo
    begin.x = 0;
    begin.y = 25;
    models[0] = RANSAC(&begin, data, outliers, data_size);
    int inliers_size = models[0].bestQty;
    int outliers_size = (int)(data_size-inliers_size);

    // -------- Variaveis para segundo modelo de linha ---------//
    Point beginSecond = outliers[0];
    
    // ------------ Variaveis para resultado final -------------//
    Point intersection = { 0.0, 0.0 };
    float distance = 0.0;
    float angle = 0.0;

    // ---- Condicao para conjunto de pontos com modelo unico ----//
    if (outliers_size < 10) distance = data[data_size-1].x - begin.x;
    // ---- Condicao para calcular segundo modelo de linha ----//
    else { 

     models[1] = RANSAC(&beginSecond, outliers, outliers, outliers_size);

        if  (models[1].bestModel.a != 0 & models[1].bestModel.b != 0) { 
            intersection = calculateIntersection(&models[0].bestModel,  &models[1].bestModel);
            distance = squareDistanceBetweenPoints(&intersection, &begin);
            angle = getAngleFromModel (models[1].bestModel.a);
        }

    }
    
    printf("data_size: \t%d\n", data_size);
    printf("initial position:\t%f\t%f\n", begin.x, begin.y);
    printf("initial position 2:\t%f\t%f\n", beginSecond.x, beginSecond.y);
    printf("\n--------Step 1----------\n");
    printf("inliers_size: \t%d\n", inliers_size);
    printf("outliers_size:\t%d\n", outliers_size);
    printf("\n--------Result----------\n");
    printf("intersection point:\t%f\t%f\n", intersection.x, intersection.y);
    printf("square distance:\t%f\n", distance);
    printf("angle: \t%f\n", angle);
    printf("\n");

    printf("\n-------------------------------------------------------------\n");
    printf("bestFit: %f\n", models[0].bestFit);
    printf("bestQty: %d\n", models[0].bestQty);
    printf("bestModel: %f\t%f\n", models[0].bestModel.a, models[0].bestModel.b );
    printf("\n----------------------\n");
    printf("bestFit: %f\n", models[1].bestFit);
    printf("bestQty: %d\n", models[1].bestQty);
    printf("bestModel: %f\t%f\n", models[1].bestModel.a, models[1].bestModel.b );

    return 0;
}