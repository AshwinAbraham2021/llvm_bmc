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

long vars[2]; 
long atom_0_X0_1; 
long atom_0_X2_2; 
long atom_1_X2_2; 

void *t0(void *arg){
label_1:;
  int v3_W0 = atomic_load_explicit(&vars[0], memory_order_relaxed);
  int v4_W2 = v3_W0 + 0;
  atomic_store_explicit(&vars[1], 1, memory_order_relaxed);
  int v20 = (1 == 1);
  atomic_store_explicit(&atom_0_X0_1, v20, memory_order_seq_cst);
  int v21 = (v4_W2 == 2);
  atomic_store_explicit(&atom_0_X2_2, v21, memory_order_seq_cst);
  return NULL;
}

void *t1(void *arg){
label_2:;
  int v7_W0 = atomic_load_explicit(&vars[1], memory_order_relaxed);
  int v8_W2 = v7_W0 + 1;
  atomic_store_explicit(&vars[0], v8_W2, memory_order_relaxed);
  int v22 = (v8_W2 == 2);
  atomic_store_explicit(&atom_1_X2_2, v22, memory_order_seq_cst);
  return NULL;
}

int main(int argc, char *argv[]){
  pthread_t thr0; 
  pthread_t thr1; 

  atomic_init(&vars[1], 0);
  atomic_init(&vars[0], 0);
  atomic_init(&atom_0_X0_1, 0); 
  atomic_init(&atom_0_X2_2, 0); 
  atomic_init(&atom_1_X2_2, 0); 

  pthread_create(&thr0, NULL, t0, NULL);
  pthread_create(&thr1, NULL, t1, NULL);

  pthread_join(thr0, NULL);
  pthread_join(thr1, NULL);

  int v9 = atomic_load_explicit(&atom_0_X0_1, memory_order_seq_cst);
  int v10 = atomic_load_explicit(&atom_0_X2_2, memory_order_seq_cst);
  int v11 = atomic_load_explicit(&atom_1_X2_2, memory_order_seq_cst);
  int v12 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v13 = (v12 == 1);
  int v14 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v15 = (v14 == 2);
  int v16_conj = v13 & v15;
  int v17_conj = v11 & v16_conj;
  int v18_conj = v10 & v17_conj;
  int v19_conj = v9 & v18_conj;
  if (v19_conj == 1) assert(0);
  return 0;
}
