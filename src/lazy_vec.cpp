
#include <Rcpp.h>

#include "altrep_interface.h"

SEXP lazy_vec_construct(SEXP lazyvec_interface) {

  return Rf_ScalarLogical(1);
}

