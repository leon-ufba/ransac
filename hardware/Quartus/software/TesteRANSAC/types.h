typedef struct {
  int x;
  int y;
} Point;

typedef struct {
  float a;
  float b;
} Line;

typedef struct {
    Line bestModel;
    float bestFit;
    int bestQty;
} RansacResult;


typedef struct {
    float distance;
    int x;
    int y;
} Outlier;
