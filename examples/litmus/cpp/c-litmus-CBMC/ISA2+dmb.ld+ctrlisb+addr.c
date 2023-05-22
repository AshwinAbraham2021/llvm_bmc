/* Copyright (C) 2023 ARM-CBMC
* This benchmark is part of ARM-CBMC */

#include <assert.h>
#include <pthread.h>

// Memory barriers
#define FENCE() asm volatile ("mfence" ::: "memory")

volatile int vars[3]; 
volatile int v_1_X0_1; 
volatile int v_2_X0_1; 
volatile int v_2_X3_0; 

void *t0(void *arg){
label_1:;
  vars[0] = 1;
  FENCE();
  vars[1] = 1;
  return NULL;
}

void *t1(void *arg){
label_2:;
  int v3_W0 = vars[1];
  if (v3_W0) goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  FENCE();
  vars[2] = 1;
  int v16 = (v3_W0 == 1);
  v_1_X0_1 = v16;
  return NULL;
}

void *t2(void *arg){
label_3:;
  int v6_W0 = vars[2];
  int v7_W2 = v6_W0 ^ v6_W0;
  int v10_W3 = vars[0+v7_W2];
  int v17 = (v6_W0 == 1);
  v_2_X0_1 = v17;
  int v18 = (v10_W3 == 0);
  v_2_X3_0 = v18;
  return NULL;
}

int main(int argc, char *argv[]){
  pthread_t thr0; 
  pthread_t thr1; 
  pthread_t thr2; 

  vars[2] = 0;
  vars[1] = 0;
  vars[0] = 0;
  v_1_X0_1 = 0;
  v_2_X0_1 = 0;
  v_2_X3_0 = 0;

  pthread_create(&thr0, NULL, t0, NULL);
  pthread_create(&thr1, NULL, t1, NULL);
  pthread_create(&thr2, NULL, t2, NULL);

  pthread_join(thr0, NULL);
  pthread_join(thr1, NULL);
  pthread_join(thr2, NULL);

  int v11 = v_1_X0_1;
  int v12 = v_2_X0_1;
  int v13 = v_2_X3_0;
  int v14_conj = v12 & v13;
  int v15_conj = v11 & v14_conj;
  if (v15_conj == 1) assert(0);
  return 0;
}
