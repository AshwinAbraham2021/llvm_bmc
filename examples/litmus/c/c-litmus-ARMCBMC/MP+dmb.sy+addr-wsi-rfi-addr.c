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

long vars[3]; 
long atom_1_X0_1; 
long atom_1_X6_2; 
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
  int v4_W2 = v3_W0 ^ v3_W0;
  atomic_store_explicit(&vars[2+v4_W2], 1, memory_order_relaxed);
  atomic_store_explicit(&vars[2], 2, memory_order_relaxed);
  int v7_W6 = atomic_load_explicit(&vars[2], memory_order_relaxed);
  int v8_W7 = v7_W6 ^ v7_W6;
  int v11_W8 = atomic_load_explicit(&vars[0+v8_W7], memory_order_relaxed);
  int v26 = (v3_W0 == 1);
  atomic_store_explicit(&atom_1_X0_1, v26, memory_order_seq_cst);
  int v27 = (v7_W6 == 2);
  atomic_store_explicit(&atom_1_X6_2, v27, memory_order_seq_cst);
  int v28 = (v11_W8 == 0);
  atomic_store_explicit(&atom_1_X8_0, v28, memory_order_seq_cst);
  return NULL;
}

int main(int argc, char *argv[]){
  pthread_t thr0; 
  pthread_t thr1; 

  atomic_init(&vars[2], 0);
  atomic_init(&vars[1], 0);
  atomic_init(&vars[0], 0);
  atomic_init(&atom_1_X0_1, 0); 
  atomic_init(&atom_1_X6_2, 0); 
  atomic_init(&atom_1_X8_0, 0); 

  pthread_create(&thr0, NULL, t0, NULL);
  pthread_create(&thr1, NULL, t1, NULL);

  pthread_join(thr0, NULL);
  pthread_join(thr1, NULL);

  int v12 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v13 = (v12 == 1);
  int v14 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v15 = (v14 == 1);
  int v16 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v17 = (v16 == 2);
  int v18 = atomic_load_explicit(&atom_1_X0_1, memory_order_seq_cst);
  int v19 = atomic_load_explicit(&atom_1_X6_2, memory_order_seq_cst);
  int v20 = atomic_load_explicit(&atom_1_X8_0, memory_order_seq_cst);
  int v21_conj = v19 & v20;
  int v22_conj = v18 & v21_conj;
  int v23_conj = v17 & v22_conj;
  int v24_conj = v15 & v23_conj;
  int v25_conj = v13 & v24_conj;
  if (v25_conj == 1) assert(0);
  return 0;
}
