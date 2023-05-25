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
long atom_1_X0_1; 

void *t0(void *arg){
label_1:;
  atomic_store_explicit(&vars[1], 2, memory_order_relaxed);
  atomic_store_explicit(&vars[0], 1, memory_order_release);
  return NULL;
}

void *t1(void *arg){
label_2:;
  int v3_W0 = atomic_load_explicit(&vars[0], memory_order_relaxed);
  int v4_cmpeq = (v3_W0 == 0);
  if (v4_cmpeq)  goto lbl_label230; else goto lbl_label230;
lbl_label230:;
  atomic_store_explicit(&vars[1], 1, memory_order_relaxed);
  int v9 = (v3_W0 == 1);
  atomic_store_explicit(&atom_1_X0_1, v9, memory_order_seq_cst);
  return NULL;
}

int main(int argc, char *argv[]){
  pthread_t thr0; 
  pthread_t thr1; 

  atomic_init(&vars[1], 0);
  atomic_init(&vars[0], 0);
  atomic_init(&atom_1_X0_1, 0); 

  pthread_create(&thr0, NULL, t0, NULL);
  pthread_create(&thr1, NULL, t1, NULL);

  pthread_join(thr0, NULL);
  pthread_join(thr1, NULL);

  int v5 = atomic_load_explicit(&vars[1], memory_order_seq_cst);
  int v6 = (v5 == 2);
  int v7 = atomic_load_explicit(&atom_1_X0_1, memory_order_seq_cst);
  int v8_conj = v6 & v7;
  if (v8_conj == 1) assert(0);
  return 0;
}
