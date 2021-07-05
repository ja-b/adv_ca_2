#include<stdio.h>
#include<stdlib.h>
#include<papi.h>
#include<string.h>

#define FACTOR 10

double simple_accum(const double *data, size_t sz) {
  double s = 0;
  for (size_t i = 0; i < sz; i++) {
    s += data[i];
  }
  return s;
}

int main(int argc, char **argv) {

  size_t n;
  if (argc != 3) {
    printf("usage: ./hi_flop n\n");
    abort();
  }

  n = atoi(argv[1]);

  double *data = (double *) malloc(n * sizeof(double));

  for (size_t i = 0; i < n; ++i) {
    data[i] = 1;
  }

  double res;
  int ret;
  ret = PAPI_hl_region_begin("hi_flop");

  res = simple_accum(data, n);

  ret = PAPI_hl_region_end("hi_flop");

  printf("Total val: %f", res);

  return 0;
}

