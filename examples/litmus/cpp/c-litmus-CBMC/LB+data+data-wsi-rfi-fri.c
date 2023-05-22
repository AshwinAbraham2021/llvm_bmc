/* Copyright (C) 2023 ARM-CBMC
* This benchmark is part of ARM-CBMC */

#include <assert.h>
#include <pthread.h>

// Memory barriers
#define FENCE() asm volatile ("mfence" ::: "memory")

volatile int vars[2]; 
volatile int v_0_X0_3; 
volatile int v_1_X0_1; 
volatile int v_1_X5_2; 

void *t0(void *arg){
label_1:;
  int v3_W0 = vars[0];
  int v4_W2 = v3_W0 ^ v3_W0;
  int v5_W2 = v4_W2 + 1;
  vars[1] = v5_W2;
  int v22 = (v3_W0 == 3);
  v_0_X0_3 = v22;
  return NULL;
}

void *t1(void *arg){
label_2:;
  int v8_W0 = vars[1];
  int v9_W2 = v8_W0 ^ v8_W0;
  int v10_W2 = v9_W2 + 1;
  vars[0] = v10_W2;
  vars[0] = 2;
  int v13_W5 = vars[0];
  vars[0] = 3;
  int v23 = (v8_W0 == 1);
  v_1_X0_1 = v23;
  int v24 = (v13_W5 == 2);
  v_1_X5_2 = v24;
  return NULL;
}

int main(int argc, char *argv[]){
  pthread_t thr0; 
  pthread_t thr1; 

  vars[1] = 0;
  vars[0] = 0;
  v_0_X0_3 = 0;
  v_1_X0_1 = 0;
  v_1_X5_2 = 0;

  pthread_create(&thr0, NULL, t0, NULL);
  pthread_create(&thr1, NULL, t1, NULL);

  pthread_join(thr0, NULL);
  pthread_join(thr1, NULL);

  int v14 = vars[0];
  int v15 = (v14 == 3);
  int v16 = v_0_X0_3;
  int v17 = v_1_X0_1;
  int v18 = v_1_X5_2;
  int v19_conj = v17 & v18;
  int v20_conj = v16 & v19_conj;
  int v21_conj = v15 & v20_conj;
  if (v21_conj == 1) assert(0);
  return 0;
}
