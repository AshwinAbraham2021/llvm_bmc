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
long atom_1_X2_1; 
long atom_1_X5_0; 
long atom_1_X7_1; 
long atom_1_X8_0; 

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
  int v6_W2 = atomic_load_explicit(&vars[1], memory_order_relaxed);
  if (v6_W2) goto lbl_LC00; else goto lbl_LC00;
lbl_LC00:;
  int v9_W3 = atomic_load_explicit(&vars[2], memory_order_relaxed);
  if (v9_W3) goto lbl_LC01; else goto lbl_LC01;
lbl_LC01:;
  isb();
  int v12_W5 = atomic_load_explicit(&vars[3], memory_order_relaxed);
  int v15_W7 = atomic_load_explicit(&vars[3], memory_order_relaxed);
  if (v15_W7) goto lbl_LC02; else goto lbl_LC02;
lbl_LC02:;
  isb();
  int v18_W8 = atomic_load_explicit(&vars[0], memory_order_relaxed);
  int v37 = (v3_W0 == 1);
  atomic_store_explicit(&atom_1_X0_1, v37, memory_order_seq_cst);
  int v38 = (v6_W2 == 1);
  atomic_store_explicit(&atom_1_X2_1, v38, memory_order_seq_cst);
  int v39 = (v12_W5 == 0);
  atomic_store_explicit(&atom_1_X5_0, v39, memory_order_seq_cst);
  int v40 = (v15_W7 == 1);
  atomic_store_explicit(&atom_1_X7_1, v40, memory_order_seq_cst);
  int v41 = (v18_W8 == 0);
  atomic_store_explicit(&atom_1_X8_0, v41, memory_order_seq_cst);
  return NULL;
}

void *t2(void *arg){
label_3:;
  atomic_store_explicit(&vars[3], 1, memory_order_relaxed);
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
  atomic_init(&atom_1_X2_1, 0); 
  atomic_init(&atom_1_X5_0, 0); 
  atomic_init(&atom_1_X7_1, 0); 
  atomic_init(&atom_1_X8_0, 0); 

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
  int v25 = atomic_load_explicit(&atom_1_X0_1, memory_order_seq_cst);
  int v26 = atomic_load_explicit(&atom_1_X2_1, memory_order_seq_cst);
  int v27 = atomic_load_explicit(&atom_1_X5_0, memory_order_seq_cst);
  int v28 = atomic_load_explicit(&atom_1_X7_1, memory_order_seq_cst);
  int v29 = atomic_load_explicit(&atom_1_X8_0, memory_order_seq_cst);
  int v30_conj = v28 & v29;
  int v31_conj = v27 & v30_conj;
  int v32_conj = v26 & v31_conj;
  int v33_conj = v25 & v32_conj;
  int v34_conj = v24 & v33_conj;
  int v35_conj = v22 & v34_conj;
  int v36_conj = v20 & v35_conj;
  if (v36_conj == 1) assert(0);
  return 0;
}
