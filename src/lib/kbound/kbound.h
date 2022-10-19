#ifndef BMC_KBOUND_H
#define BMC_KBOUND_H

#include <fstream>

#include "include/options.h"

class kbound{

private:
  options& o;
  std::unique_ptr<llvm::Module>& module;
  std::ofstream ofcpp;
  unsigned current_indent;

  // dump to kbound
  void dump_newline();
  void dump_indent();
  void dump_define(std::string name, std::string val);
  void dump_decl_scalar(std::string name, std::string type);
  void dump_decl_array(std::string name, std::string type, std::string size);
  void dump_macors(std::string name, std::string val);

public:
  kbound( std::unique_ptr<llvm::Module>& m_, options& o_ );
  ~kbound();
  void run();
 
  // bool verify_prop();


 
};

#endif // BMC_KBOUND_H
