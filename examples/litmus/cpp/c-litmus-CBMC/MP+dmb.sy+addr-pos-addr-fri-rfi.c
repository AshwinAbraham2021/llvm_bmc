/* Copyright (C) 2023 ARM-CBMC
* This benchmark is part of ARM-CBMC */

#include <assert.h>
#include <pthread.h>

// Memory barriers
#define FENCE() asm volatile ("mfence" ::: "memory")

volatile int vars[3]; 
volatile int v_1_X0_1; 
volatile int v_1_X7_0; 
volatile int v_1_X10_1; 

void *t0(void *arg){
label_1:;
  vars[0] = 2;
  FENCE();
  vars[1] = 1;
  return NULL;
}

void *t1(void *arg){
label_2:;
  int v3_W0 = vars[1];
  int v4_W2 = v3_W0 ^ v3_W0;
  int v7_W3 = vars[2+v4_W2];
  int v10_W5 = vars[2];
  int v11_W6 = v10_W5 ^ v10_W5;
  int v14_W7 = vars[0+v11_W6];
  vars[0] = 1;
  int v17_W10 = vars[0];
  int v29 = (v3_W0 == 1);
  v_1_X0_1 = v29;
  int v30 = (v14_W7 == 0);
  v_1_X7_0 = v30;
  int v31 = (v17_W10 == 1);
  v_1_X10_1 = v31;
  return NULL;
}

int main(int argc, char *argv[]){
  pthread_t thr0; 
  pthread_t thr1; 

  vars[2] = 0;
  vars[1] = 0;
  vars[0] = 0;
  v_1_X0_1 = 0;
  v_1_X7_0 = 0;
  v_1_X10_1 = 0;

  pthread_create(&thr0, NULL, t0, NULL);
  pthread_create(&thr1, NULL, t1, NULL);

  pthread_join(thr0, NULL);
  pthread_join(thr1, NULL);

  int v18 = vars[0];
  int v19 = (v18 == 2);
  int v20 = vars[1];
  int v21 = (v20 == 1);
  int v22 = v_1_X0_1;
  int v23 = v_1_X7_0;
  int v24 = v_1_X10_1;
  int v25_conj = v23 & v24;
  int v26_conj = v22 & v25_conj;
  int v27_conj = v21 & v26_conj;
  int v28_conj = v19 & v27_conj;
  if (v28_conj == 1) assert(0);
  return 0;
}
