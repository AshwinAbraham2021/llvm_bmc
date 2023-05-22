/* Copyright (C) 2023 ARM-CBMC
* This benchmark is part of ARM-CBMC */

#include <assert.h>
#include <pthread.h>

// Memory barriers
#define FENCE() asm volatile ("mfence" ::: "memory")

volatile int vars[2]; 
volatile int v_0_X0_1; 
volatile int v_1_X0_1; 

void *t0(void *arg){
label_1:;
  int v3_W0 = vars[1];
  int v4_cmpeq = (v3_W0 == 0);
  if (v4_cmpeq)  goto lbl_label100; else goto lbl_label100;
lbl_label100:;
  vars[0] = 1;
  int v11 = (v3_W0 == 1);
  v_0_X0_1 = v11;
  return NULL;
}

void *t1(void *arg){
label_2:;
  FENCE();
  int v7_W0 = vars[0];
  vars[1] = 1;
  int v12 = (v7_W0 == 1);
  v_1_X0_1 = v12;
  return NULL;
}

int main(int argc, char *argv[]){
  pthread_t thr0; 
  pthread_t thr1; 

  vars[1] = 0;
  vars[0] = 0;
  v_0_X0_1 = 0;
  v_1_X0_1 = 0;

  pthread_create(&thr0, NULL, t0, NULL);
  pthread_create(&thr1, NULL, t1, NULL);

  pthread_join(thr0, NULL);
  pthread_join(thr1, NULL);

  int v8 = v_0_X0_1;
  int v9 = v_1_X0_1;
  int v10_conj = v8 & v9;
  if (v10_conj == 1) assert(0);
  return 0;
}
