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
long atom_1_X9_1; 
long atom_1_X11_0; 

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
  int v7_W3 = v6_W2 ^ v6_W2;
  int v10_W4 = atomic_load_explicit(&vars[2+v7_W3], memory_order_relaxed);
  int v11_W6 = v10_W4 ^ v10_W4;
  atomic_store_explicit(&vars[3+v11_W6], 1, memory_order_relaxed);
  int v14_W9 = atomic_load_explicit(&vars[3], memory_order_relaxed);
  int v15_W10 = v14_W9 ^ v14_W9;
  int v18_W11 = atomic_load_explicit(&vars[0+v15_W10], memory_order_relaxed);
  int v35 = (v3_W0 == 1);
  atomic_store_explicit(&atom_1_X0_1, v35, memory_order_seq_cst);
  int v36 = (v6_W2 == 1);
  atomic_store_explicit(&atom_1_X2_1, v36, memory_order_seq_cst);
  int v37 = (v14_W9 == 1);
  atomic_store_explicit(&atom_1_X9_1, v37, memory_order_seq_cst);
  int v38 = (v18_W11 == 0);
  atomic_store_explicit(&atom_1_X11_0, v38, memory_order_seq_cst);
  return NULL;
}

int main(int argc, char *argv[]){
  pthread_t thr0; 
  pthread_t thr1; 

  atomic_init(&vars[3], 0);
  atomic_init(&vars[2], 0);
  atomic_init(&vars[1], 0);
  atomic_init(&vars[0], 0);
  atomic_init(&atom_1_X0_1, 0); 
  atomic_init(&atom_1_X2_1, 0); 
  atomic_init(&atom_1_X9_1, 0); 
  atomic_init(&atom_1_X11_0, 0); 

  pthread_create(&thr0, NULL, t0, NULL);
  pthread_create(&thr1, NULL, t1, NULL);

  pthread_join(thr0, NULL);
  pthread_join(thr1, NULL);

  int v19 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v20 = (v19 == 1);
  int v21 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v22 = (v21 == 1);
  int v23 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v24 = (v23 == 1);
  int v25 = atomic_load_explicit(&atom_1_X0_1, memory_order_seq_cst);
  int v26 = atomic_load_explicit(&atom_1_X2_1, memory_order_seq_cst);
  int v27 = atomic_load_explicit(&atom_1_X9_1, memory_order_seq_cst);
  int v28 = atomic_load_explicit(&atom_1_X11_0, memory_order_seq_cst);
  int v29_conj = v27 & v28;
  int v30_conj = v26 & v29_conj;
  int v31_conj = v25 & v30_conj;
  int v32_conj = v24 & v31_conj;
  int v33_conj = v22 & v32_conj;
  int v34_conj = v20 & v33_conj;
  if (v34_conj == 1) assert(0);
  return 0;
}
