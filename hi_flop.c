#include<stdio.h>
#include<stdlib.h>
#include<papi.h>
#include<string.h>

#define PADDING 2

float simple_accum(const float *data, size_t sz) {
  float s = 0;
  for (size_t i = 0; i < sz; i++) {
    s += data[i];
  }
  return s;
}

float simple_accum_f(float *dst, const float *data, size_t sz) {
  for (size_t i = 0; i < sz; i++) {
    dst[i] = data[i] + data[i-1] + data[i-2];
  }
}

int main(int argc, char **argv) {

  size_t n;
  if (argc != 2) {
    printf("usage: ./hi_flop n\n");
    abort();
  }

  n = atoi(argv[1]);

  float *data = (float *) malloc(n * sizeof(float));
  float *dst = (float *) malloc(n * sizeof(float));

  for (size_t i = 0; i < n; ++i) {
    data[i] = 1;
  }

  float res;
  int ret;
  ret = PAPI_hl_region_begin("hi_flop");

  res = simple_accum_f(dst + PADDING, data + PADDING, n - PADDING);

  ret = PAPI_hl_region_end("hi_flop");

  printf("Total val: %f", res);

  free(data);
  free(dst);

  return 0;
}

