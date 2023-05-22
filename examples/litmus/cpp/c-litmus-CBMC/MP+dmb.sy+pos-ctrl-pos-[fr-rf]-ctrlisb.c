/* Copyright (C) 2023 ARM-CBMC
* This benchmark is part of ARM-CBMC */

#include <assert.h>
#include <pthread.h>

// Memory barriers
#define FENCE() asm volatile ("mfence" ::: "memory")

volatile int vars[3]; 
volatile int v_1_X0_1; 
volatile int v_1_X2_1; 
volatile int v_1_X3_0; 
volatile int v_1_X5_0; 
volatile int v_1_X6_1; 
volatile int v_1_X7_0; 

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
  int v6_W2 = vars[1];
  if (v6_W2) goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  int v9_W3 = vars[2];
  int v12_W5 = vars[2];
  int v15_W6 = vars[2];
  if (v15_W6) goto lbl_LC01; else goto lbl_LC01;
lbl_LC01:;
  FENCE();
  int v18_W7 = vars[0];
  int v39 = (v3_W0 == 1);
  v_1_X0_1 = v39;
  int v40 = (v6_W2 == 1);
  v_1_X2_1 = v40;
  int v41 = (v9_W3 == 0);
  v_1_X3_0 = v41;
  int v42 = (v12_W5 == 0);
  v_1_X5_0 = v42;
  int v43 = (v15_W6 == 1);
  v_1_X6_1 = v43;
  int v44 = (v18_W7 == 0);
  v_1_X7_0 = v44;
  return NULL;
}

void *t2(void *arg){
label_3:;
  vars[2] = 1;
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
  v_1_X2_1 = 0;
  v_1_X3_0 = 0;
  v_1_X5_0 = 0;
  v_1_X6_1 = 0;
  v_1_X7_0 = 0;

  pthread_create(&thr0, NULL, t0, NULL);
  pthread_create(&thr1, NULL, t1, NULL);
  pthread_create(&thr2, NULL, t2, NULL);

  pthread_join(thr0, NULL);
  pthread_join(thr1, NULL);
  pthread_join(thr2, NULL);

  int v19 = vars[0];
  int v20 = (v19 == 1);
  int v21 = vars[1];
  int v22 = (v21 == 1);
  int v23 = vars[2];
  int v24 = (v23 == 1);
  int v25 = v_1_X0_1;
  int v26 = v_1_X2_1;
  int v27 = v_1_X3_0;
  int v28 = v_1_X5_0;
  int v29 = v_1_X6_1;
  int v30 = v_1_X7_0;
  int v31_conj = v29 & v30;
  int v32_conj = v28 & v31_conj;
  int v33_conj = v27 & v32_conj;
  int v34_conj = v26 & v33_conj;
  int v35_conj = v25 & v34_conj;
  int v36_conj = v24 & v35_conj;
  int v37_conj = v22 & v36_conj;
  int v38_conj = v20 & v37_conj;
  if (v38_conj == 1) assert(0);
  return 0;
}
