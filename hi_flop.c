#include<stdio.h>
#include<stdlib.h>
#include<papi.h>
#include<string.h>

#define PADDING 64
#define REPS 1000

float constants[] = {
  20.0f,
  40.0f,
  8.0f,
  12.0f,
  16.0f,
  22.0f,
  24.0f,
  32.0f,
  13.0f,
  0.501f,
  0.601f,
  11.0f,
  12.0f,
  10.0f,
  21.0f,
  23.0f
};

float simple_accum(const float *data, size_t sz) {
  float s = 0;
  for (size_t i = 0; i < sz; i++) {
    s += data[i];
  }
  return s;
}

float simple_accum_f(const float *data, size_t sz) {
  register float s = 0.0f;
  for (size_t i = 0; i < sz; i++) {
    for (size_t k = 0; k < REPS; k++) {
      for (size_t j = 0; j < 16; j++) {
        s += data[i] * constants[j];
      }
    }
  }
  return s;
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

  res = simple_accum_f(data + PADDING, n - PADDING);

  ret = PAPI_hl_region_end("hi_flop");

//  float sum = 0.0f;
//  for (size_t i = 0; i < n; i++) {
//    sum += dst[i];
//  }
  printf("Total val: %f", res);

  free(data);
  free(dst);

  return 0;
}

