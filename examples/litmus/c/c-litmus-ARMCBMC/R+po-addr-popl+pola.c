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
long atom_0_X9_2; 
long atom_1_X2_0; 

void *t0(void *arg){
label_1:;
  atomic_store_explicit(&vars[0], 1, memory_order_relaxed);
  int v3_W2 = atomic_load_explicit(&vars[1], memory_order_relaxed);
  int v4_W4 = v3_W2 ^ v3_W2;
  int v7_W5 = atomic_load_explicit(&vars[2+v4_W4], memory_order_relaxed);
  atomic_store_explicit(&vars[3], 1, memory_order_release);
  int v10_W9 = atomic_load_explicit(&vars[3], memory_order_relaxed);
  int v23 = (v10_W9 == 2);
  atomic_store_explicit(&atom_0_X9_2, v23, memory_order_seq_cst);
  return NULL;
}

void *t1(void *arg){
label_2:;
  atomic_store_explicit(&vars[3], 2, memory_order_release);
  int v13_W2 = atomic_load_explicit(&vars[0], memory_order_acquire);
  int v24 = (v13_W2 == 0);
  atomic_store_explicit(&atom_1_X2_0, v24, memory_order_seq_cst);
  return NULL;
}

int main(int argc, char *argv[]){
  pthread_t thr0; 
  pthread_t thr1; 

  atomic_init(&vars[3], 0);
  atomic_init(&vars[2], 0);
  atomic_init(&vars[1], 0);
  atomic_init(&vars[0], 0);
  atomic_init(&atom_0_X9_2, 0); 
  atomic_init(&atom_1_X2_0, 0); 

  pthread_create(&thr0, NULL, t0, NULL);
  pthread_create(&thr1, NULL, t1, NULL);

  pthread_join(thr0, NULL);
  pthread_join(thr1, NULL);

  int v14 = atomic_load_explicit(&vars[3], memory_order_seq_cst);
  int v15 = (v14 == 2);
  int v16 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v17 = (v16 == 1);
  int v18 = atomic_load_explicit(&atom_0_X9_2, memory_order_seq_cst);
  int v19 = atomic_load_explicit(&atom_1_X2_0, memory_order_seq_cst);
  int v20_conj = v18 & v19;
  int v21_conj = v17 & v20_conj;
  int v22_conj = v15 & v21_conj;
  if (v22_conj == 1) assert(0);
  return 0;
}
