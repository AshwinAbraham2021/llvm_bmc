/* Copyright (C) 2023 ARM-CBMC
* This benchmark is part of ARM-CBMC */

#include <assert.h>
#include <pthread.h>
#include <stdatomic.h>

// Memory barriers
void dmbld();
void dmbst();
void dmbsy();
void isb();

long vars[4]; 
long atom_1_X0_1; 
long atom_1_X3_0; 
long atom_1_X5_1; 
long atom_1_X8_1; 
long atom_1_X9_0; 

void *t0(void *arg){
label_1:;
  atomic_store_explicit(&vars[0], 1, memory_order_relaxed);
  dmbsy();
  atomic_store_explicit(&vars[1], 1, memory_order_relaxed);
  return NULL;
}

void *t1(void *arg){
label_2:;
  int v3_W0 = atomic_load_explicit(&vars[1], memory_order_relaxed);
  int v4_W2 = v3_W0 ^ v3_W0;
  int v7_W3 = atomic_load_explicit(&vars[2+v4_W2], memory_order_relaxed);
  int v10_W5 = atomic_load_explicit(&vars[2], memory_order_relaxed);
  int v11_W6 = v10_W5 ^ v10_W5;
  int v12_W6 = v11_W6 + 1;
  atomic_store_explicit(&vars[3], v12_W6, memory_order_relaxed);
  int v15_W8 = atomic_load_explicit(&vars[3], memory_order_relaxed);
  if (v15_W8) goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  isb();
  int v18_W9 = atomic_load_explicit(&vars[0], memory_order_relaxed);
  int v40 = (v3_W0 == 1);
  atomic_store_explicit(&atom_1_X0_1, v40, memory_order_seq_cst);
  int v41 = (v7_W3 == 0);
  atomic_store_explicit(&atom_1_X3_0, v41, memory_order_seq_cst);
  int v42 = (v10_W5 == 1);
  atomic_store_explicit(&atom_1_X5_1, v42, memory_order_seq_cst);
  int v43 = (v15_W8 == 1);
  atomic_store_explicit(&atom_1_X8_1, v43, memory_order_seq_cst);
  int v44 = (v18_W9 == 0);
  atomic_store_explicit(&atom_1_X9_0, v44, memory_order_seq_cst);
  return NULL;
}

void *t2(void *arg){
label_3:;
  atomic_store_explicit(&vars[2], 1, memory_order_relaxed);
  return NULL;
}

int main(int argc, char *argv[]){
  pthread_t thr0; 
  pthread_t thr1; 
  pthread_t thr2; 

  atomic_init(&vars[3], 0);
  atomic_init(&vars[2], 0);
  atomic_init(&vars[1], 0);
  atomic_init(&vars[0], 0);
  atomic_init(&atom_1_X0_1, 0); 
  atomic_init(&atom_1_X3_0, 0); 
  atomic_init(&atom_1_X5_1, 0); 
  atomic_init(&atom_1_X8_1, 0); 
  atomic_init(&atom_1_X9_0, 0); 

  pthread_create(&thr0, NULL, t0, NULL);
  pthread_create(&thr1, NULL, t1, NULL);
  pthread_create(&thr2, NULL, t2, NULL);

  pthread_join(thr0, NULL);
  pthread_join(thr1, NULL);
  pthread_join(thr2, NULL);

  int v19 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v20 = (v19 == 1);
  int v21 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v22 = (v21 == 1);
  int v23 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v24 = (v23 == 1);
  int v25 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v26 = (v25 == 1);
  int v27 = atomic_load_explicit(&atom_1_X0_1, memory_order_seq_cst);
  int v28 = atomic_load_explicit(&atom_1_X3_0, memory_order_seq_cst);
  int v29 = atomic_load_explicit(&atom_1_X5_1, memory_order_seq_cst);
  int v30 = atomic_load_explicit(&atom_1_X8_1, memory_order_seq_cst);
  int v31 = atomic_load_explicit(&atom_1_X9_0, memory_order_seq_cst);
  int v32_conj = v30 & v31;
  int v33_conj = v29 & v32_conj;
  int v34_conj = v28 & v33_conj;
  int v35_conj = v27 & v34_conj;
  int v36_conj = v26 & v35_conj;
  int v37_conj = v24 & v36_conj;
  int v38_conj = v22 & v37_conj;
  int v39_conj = v20 & v38_conj;
  if (v39_conj == 1) assert(0);
  return 0;
}
