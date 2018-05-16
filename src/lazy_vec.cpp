
#include <Rcpp.h>

#include "altrep_interface.h"

SEXP lazy_vec_construct(SEXP lazyvec_interface) {

  return construct_lazy_vec(lazyvec_interface);
}

