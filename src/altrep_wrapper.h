
#ifndef LAZYVEC_WRAPPER_H
#define LAZYVEC_WRAPPER_H

extern "C" {

  void register_altwrap_integer_class(DllInfo *dll);

  SEXP construct_altrep_wrapper(SEXP data);

}

#endif  // LAZYVEC_WRAPPER_H
