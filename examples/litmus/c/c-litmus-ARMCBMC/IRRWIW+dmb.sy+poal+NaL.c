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
long atom_1_X0_2; 
long atom_1_X2_0; 
long atom_3_X0_1; 

void *t0(void *arg){
label_1:;
  atomic_store_explicit(&vars[0], 2, memory_order_relaxed);
  return NULL;
}

void *t1(void *arg){
label_2:;
  int v3_W0 = atomic_load_explicit(&vars[0], memory_order_relaxed);
  dmbsy();
  int v6_W2 = atomic_load_explicit(&vars[1], memory_order_relaxed);
  int v18 = (v3_W0 == 2);
  atomic_store_explicit(&atom_1_X0_2, v18, memory_order_seq_cst);
  int v19 = (v6_W2 == 0);
  atomic_store_explicit(&atom_1_X2_0, v19, memory_order_seq_cst);
  return NULL;
}

void *t2(void *arg){
label_3:;
  atomic_store_explicit(&vars[1], 1, memory_order_release);
  return NULL;
}

void *t3(void *arg){
label_4:;
  int v9_W0 = atomic_load_explicit(&vars[1], memory_order_acquire);
  atomic_store_explicit(&vars[0], 1, memory_order_release);
  int v20 = (v9_W0 == 1);
  atomic_store_explicit(&atom_3_X0_1, v20, memory_order_seq_cst);
  return NULL;
}

int main(int argc, char *argv[]){
  pthread_t thr0; 
  pthread_t thr1; 
  pthread_t thr2; 
  pthread_t thr3; 

  atomic_init(&vars[1], 0);
  atomic_init(&vars[0], 0);
  atomic_init(&atom_1_X0_2, 0); 
  atomic_init(&atom_1_X2_0, 0); 
  atomic_init(&atom_3_X0_1, 0); 

  pthread_create(&thr0, NULL, t0, NULL);
  pthread_create(&thr1, NULL, t1, NULL);
  pthread_create(&thr2, NULL, t2, NULL);
  pthread_create(&thr3, NULL, t3, NULL);

  pthread_join(thr0, NULL);
  pthread_join(thr1, NULL);
  pthread_join(thr2, NULL);
  pthread_join(thr3, NULL);

  int v10 = atomic_load_explicit(&vars[0], memory_order_seq_cst);
  int v11 = (v10 == 2);
  int v12 = atomic_load_explicit(&atom_1_X0_2, memory_order_seq_cst);
  int v13 = atomic_load_explicit(&atom_1_X2_0, memory_order_seq_cst);
  int v14 = atomic_load_explicit(&atom_3_X0_1, memory_order_seq_cst);
  int v15_conj = v13 & v14;
  int v16_conj = v12 & v15_conj;
  int v17_conj = v11 & v16_conj;
  if (v17_conj == 1) assert(0);
  return 0;
}
