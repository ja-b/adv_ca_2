#include<stdio.h>
#include<stdlib.h>
#include<papi.h>
#include<string.h>

#define CONST_1 20.0f
#define CONST_2 60.0f
#define CONST_3 60.0f
#define CONST_4 30.0f
#define CONST_5 10.0f
#define CONST_6 15.0f
#define CONST_7 110.0f
#define CONST_8 111.0f
#define CONST_9 12.0f
#define CONST_10 2.0f
#define CONST_11 3.0f
#define CONST_12 4.0f
#define PADDING 64
#define REPS 1000

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
    register float t = 0.0f;
    for (int c = 0; c < REPS; c++) {
      for (size_t j = 0; j < PADDING; j++) {
        t += data[i - j] * data[i] + data[i + j] * CONST_1 + CONST_2 + CONST_3 * CONST_4 + CONST_5 * CONST_6 + CONST_6 * CONST_7 +CONST_8 + CONST_9 * CONST_10 + CONST_11 * CONST_12;
      }
      s += t + CONST_1 * CONST_2 + CONST_3 + CONST_4 * CONST_5 + CONST_6;
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

