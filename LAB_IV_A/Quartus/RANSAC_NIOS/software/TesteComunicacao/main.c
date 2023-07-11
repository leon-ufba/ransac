#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "data.h"

#define STEP coords
#define SIZE size


int main() {

    int data_size = 0;
    int temp_data_size = 0;
    int temp_x = 0;
    int temp_y = 0;

    //read data_size
	data_size = SIZE;
	temp_data_size = (2*data_size);

    int j = 0;
    for (int i = 0; i<temp_data_size; i+=1) {
    	data[i] = (STEP[X]&0xFFFF)|(STEP[Y]<<16);
    	controle[0] = i;
    	j+=2;
    }
    printf("size: %d\n", data_size);

    for (int i = 0; i<data_size; i+=1) {
    	temp_x = data[i]&0xFFFF;
    	temp_y = (data[i]>>16)&0xFFFF;
    	printf("%d, %d\n", temp_x, temp_y);
    }
    return 0;
}
