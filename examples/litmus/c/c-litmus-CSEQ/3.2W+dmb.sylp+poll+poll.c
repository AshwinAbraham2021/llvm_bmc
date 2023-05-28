/* Copyright (C) 2023 ARM-CBMC
* This benchmark is part of ARM-CBMC */

#include <assert.h>
#include <pthread.h>

// Memory barriers
#define FENCE()

volatile int vars[3]; 

void *t0(void *arg){
label_1:;
  FENCE();
  vars[0] = 2;
  FENCE();
  vars[1] = 1;
  return NULL;
}

void *t1(void *arg){
label_2:;
  FENCE();
  vars[1] = 2;
  FENCE();
  vars[2] = 1;
  return NULL;
}

void *t2(void *arg){
label_3:;
  FENCE();
  vars[2] = 2;
  FENCE();
  vars[0] = 1;
  return NULL;
}

int main(int argc, char *argv[]){
  pthread_t thr0; 
  pthread_t thr1; 
  pthread_t thr2; 

  vars[2] = 0;
  vars[1] = 0;
  vars[0] = 0;

  pthread_create(&thr0, NULL, t0, NULL);
  pthread_create(&thr1, NULL, t1, NULL);
  pthread_create(&thr2, NULL, t2, NULL);

  pthread_join(thr0, NULL);
  pthread_join(thr1, NULL);
  pthread_join(thr2, NULL);

  int v1 = vars[0];
  int v2 = (v1 == 2);
  int v3 = vars[1];
  int v4 = (v3 == 2);
  int v5 = vars[2];
  int v6 = (v5 == 2);
  int v7_conj = v4 & v6;
  int v8_conj = v2 & v7_conj;
  if (v8_conj == 1) assert(0);
  return 0;
}
