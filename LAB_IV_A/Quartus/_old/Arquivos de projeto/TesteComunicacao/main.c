#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ransac.h"



int main() {

    int data_size = 0;
    int temp_data_size = 0;
    int temp_x = 0;
    int temp_y = 0;

    //read data_size
	data_size = (int)(size&0xFF);
	temp_data_size = (2*data_size);

    int j = 0;
    for (int i = 0; i<temp_data_size; i+=1) {
    	data[i] = (coords[X]&0xFF)|(coords[Y]<<8);
    	controle[0] = i;
    	j+=2;
    }
    printf("size: %d\n", data_size);

    for (int i = 0; i<data_size; i+=1) {
    	temp_x = data[i]&0xFF;
    	temp_y = (data[i]>>8)&0xFF;
    	printf("%d, %d\n", temp_x, temp_y);
    }
    return 0;
}
