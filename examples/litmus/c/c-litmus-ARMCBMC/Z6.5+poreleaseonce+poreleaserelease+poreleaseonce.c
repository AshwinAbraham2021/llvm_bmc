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
long atom_2_X1_0; 

void *t0(void *arg){
label_1:;
  atomic_store_explicit(&vars[1], 1, memory_order_release);
  atomic_store_explicit(&vars[0], 1, memory_order_relaxed);
  return NULL;
}

void *t1(void *arg){
label_2:;
  atomic_store_explicit(&vars[0], 2, memory_order_release);
  atomic_store_explicit(&vars[2], 1, memory_order_release);
  return NULL;
}

void *t2(void *arg){
label_3:;
  atomic_store_explicit(&vars[2], 2, memory_order_release);
  int v3_W1 = atomic_load_explicit(&vars[1], memory_order_relaxed);
  int v11 = (v3_W1 == 0);
  atomic_store_explicit(&atom_2_X1_0, v11, memory_order_seq_cst);
  return NULL;
}

int main(int argc, char *argv[]){
  pthread_t thr0; 
  pthread_t thr1; 
  pthread_t thr2; 

  atomic_init(&vars[2], 0);
  atomic_init(&vars[1], 0);
  atomic_init(&vars[0], 0);
  atomic_init(&atom_2_X1_0, 0); 

  pthread_create(&thr0, NULL, t0, NULL);
  pthread_create(&thr1, NULL, t1, NULL);
  pthread_create(&thr2, NULL, t2, NULL);

  pthread_join(thr0, NULL);
  pthread_join(thr1, NULL);
  pthread_join(thr2, NULL);

  int v4 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v5 = (v4 == 2);
  int v6 = atomic_load_explicit(&vars[2], memory_order_seq_cst);
  int v7 = (v6 == 2);
  int v8 = atomic_load_explicit(&atom_2_X1_0, memory_order_seq_cst);
  int v9_conj = v7 & v8;
  int v10_conj = v5 & v9_conj;
  if (v10_conj == 1) assert(0);
  return 0;
}
