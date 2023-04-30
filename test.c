
#include <stdio.h>
#include <stdlib.h>

#define MAX_POINTS 5

typedef struct {
  float x;
  float y;
} Point;

int main() {
  unsigned int seed = 42;
  srand(seed); /* Intializes random number generator */
  Point data[MAX_POINTS];
  Point newPoint;
  for (int i = 0; i < MAX_POINTS; i++) {
    newPoint.x = rand() / ((float)RAND_MAX);
    newPoint.y = rand() / ((float)RAND_MAX);
    data[i] = newPoint;
  }

  /* Print random numbers from 0 to 50 */
  for (int i = 0; i < MAX_POINTS; i++) {
    printf("%f\t%f\n", data[i].x, data[i].y);
  }

  return (0);
}