
#ifndef LAZYVEC_INTERFACE_H
#define LAZYVEC_INTERFACE_H

extern "C" {

  void register_integer_class(DllInfo *dll);

  SEXP construct_lazy_vec(SEXP data);

}

#endif  // LAZYVEC_INTERFACE_H
