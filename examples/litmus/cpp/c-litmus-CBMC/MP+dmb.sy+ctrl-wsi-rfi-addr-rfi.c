/* Copyright (C) 2023 ARM-CBMC
* This benchmark is part of ARM-CBMC */

#include <assert.h>
#include <pthread.h>

// Memory barriers
#define FENCE() asm volatile ("mfence" ::: "memory")

volatile int vars[3]; 
volatile int v_1_X0_1; 
volatile int v_1_X5_2; 
volatile int v_1_X9_1; 

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
  if (v3_W0) goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  vars[2] = 1;
  vars[2] = 2;
  int v6_W5 = vars[2];
  int v7_W6 = v6_W5 ^ v6_W5;
  vars[0+v7_W6] = 1;
  int v10_W9 = vars[0];
  int v25 = (v3_W0 == 1);
  v_1_X0_1 = v25;
  int v26 = (v6_W5 == 2);
  v_1_X5_2 = v26;
  int v27 = (v10_W9 == 1);
  v_1_X9_1 = v27;
  return NULL;
}

int main(int argc, char *argv[]){
  pthread_t thr0; 
  pthread_t thr1; 

  vars[2] = 0;
  vars[1] = 0;
  vars[0] = 0;
  v_1_X0_1 = 0;
  v_1_X5_2 = 0;
  v_1_X9_1 = 0;

  pthread_create(&thr0, NULL, t0, NULL);
  pthread_create(&thr1, NULL, t1, NULL);

  pthread_join(thr0, NULL);
  pthread_join(thr1, NULL);

  int v11 = vars[0];
  int v12 = (v11 == 2);
  int v13 = vars[1];
  int v14 = (v13 == 1);
  int v15 = vars[2];
  int v16 = (v15 == 2);
  int v17 = v_1_X0_1;
  int v18 = v_1_X5_2;
  int v19 = v_1_X9_1;
  int v20_conj = v18 & v19;
  int v21_conj = v17 & v20_conj;
  int v22_conj = v16 & v21_conj;
  int v23_conj = v14 & v22_conj;
  int v24_conj = v12 & v23_conj;
  if (v24_conj == 1) assert(0);
  return 0;
}
