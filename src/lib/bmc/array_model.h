#ifndef TILER_ARRAY_MODEL_H
#define TILER_ARRAY_MODEL_H

#include "lib/utils/llvm_utils.h"
#include "lib/utils/z3_utils.h"
#include "include/options.h"

// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wunused-parameter"
// // #include "llvm/Pass.h"
// #include "llvm/IR/Value.h"
// #include "llvm/IR/Constants.h"
// // #include "llvm/Support/raw_ostream.h"
// // #include "llvm/IR/Instructions.h"
// // #include "llvm/IR/IntrinsicInst.h"
// #pragma GCC diagnostic pop

class array_state{
public:

  // array_state( unsigned total_partitions ) {
  //   pm_state = new partition_model_state();
  // }
  array_state() {}

  //anything else is needed???
  std::vector<expr>& get_name_vec() { return array_index_names; };
private:
  std::vector<expr> array_index_names;
};


class array_model_full;
class array_model_fixed_len;
class array_model_partition;

class array_model{
public:
  array_model( solver_context& ctx_ ) : solver_ctx(ctx_) {}

  // need to provide copy operator

  // void init_array_state( const bb* );
  expr join_array_state( std::vector<expr>&,
                             std::vector<unsigned>& prevs,
                             unsigned src
                             // std::vector<const bb*>&,
                             // const bb*
                             );
  virtual expr get_fresh_ary_name( unsigned ) = 0;
  // virtual expr array_write( llvm::Instruction* I, expr idx,
  //                               expr val ) = 0;
  // virtual expr array_read( llvm::Instruction* I, expr idx ) = 0;

  // array_state& get_array_state( const bb* b ) { return exit_ary_map.at(b); }
  array_state& get_state( unsigned b ) { return exit_ary_map.at(b); }
  void set_array_state( unsigned b, array_state& s ) {
    exit_ary_map[b] = s;
  }

  expr get_array_state_var( unsigned b, unsigned ith_ary ) {
    return exit_ary_map.at(b).get_name_vec()[ith_ary];
  }

private:
  solver_context& solver_ctx;
  array_model_t model = NONE;
  // std::map< const bb*, array_state > exit_ary_map;
  std::map< unsigned, array_state > exit_ary_map;

  friend array_model_full;
  friend array_model_fixed_len;
  friend array_model_partition;
};


class array_model_full : public array_model {
public:
  array_model_full( solver_context& ctx_ ) : array_model(ctx_) {
    model = FULL;
  }

  inline void set_array_num( unsigned len ) {
    num_arrays = len;
    for( unsigned i = 0; i < num_arrays; i++) {
      ar_sorts.push_back( solver_ctx.array_sort( solver_ctx.int_sort(),
                                             solver_ctx.int_sort() ) );
    }
  }

  inline void set_array_num( std::vector<sort>& sorts ) {
    ar_sorts = sorts;
    num_arrays = ar_sorts.size();
  }

  inline void
  set_access_map( std::map< const llvm::Instruction*, unsigned >& map ) {
    ary_access_to_index = map;
  }

  // void init_state( const bb* );
  void init_state( unsigned );
  void init_state( unsigned eb, array_state& s );
  virtual expr get_fresh_ary_name( unsigned );
  //virtual

  std::pair<expr,expr>
  array_write( unsigned bidx, const llvm::StoreInst* I,
               expr& idx, expr& val );
  //virtual
  expr array_read( unsigned bidx, const llvm::LoadInst* I, expr& idx );

  void update_names( unsigned, std::vector<const llvm::Instruction*>&);
  void update_name( unsigned, unsigned );
  void copy_to_init_state( array_state& );

private:
  unsigned num_arrays;
  std::vector< sort > ar_sorts;
  std::vector< expr > lengths;
  std::map< const llvm::Instruction*, unsigned > ary_access_to_index;
};

class array_model_fixed_len : public array_model {
public:
  array_model_fixed_len( solver_context& ctx_ ) : array_model(ctx_) {
    model = FIXED_LEN;
  }

  // void init_state( const bb* );
  void init_state( unsigned );

  inline void set_partition_len( unsigned len ) { num_partition = len; }
  inline void
  set_access_map( std::map< const llvm::Instruction*, unsigned >& map ) {
    ary_access_to_patition_map = map;
  }
  virtual expr get_fresh_ary_name( unsigned );
  //virtual
  std::pair<expr,expr>
  array_write( unsigned bidx, const llvm::StoreInst* I, expr& idx, expr& val );
  //virtual
  expr array_read( unsigned bidx, const llvm::LoadInst* I, expr& val );

private:
  unsigned num_partition=0;
  std::map< const llvm::Instruction*, unsigned > ary_access_to_patition_map;

};


class array_model_partition : public array_model {
public:
  array_model_partition( solver_context& ctx_ ) : array_model(ctx_) {
    model = PARTITION;
  }
  virtual expr get_fresh_ary_name( unsigned );

};




#endif //TILER_ARRAY_MODEL_H
