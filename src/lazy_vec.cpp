
#include <Rcpp.h>

#include <Rinternals.h>

#include "altrep_interface.h"

#define lcons Rf_lcons

SEXP lazy_vec_construct(SEXP lazyvec_interface) {

  return construct_lazy_vec(lazyvec_interface);
}


SEXP call_r_method(SEXP f, SEXP x, SEXP rho) {

  SEXP call = PROTECT(LCONS(f, LCONS(x, R_NilValue)));
  SEXP val = R_forceAndCall(call, 1, rho);
  UNPROTECT(1);
  return val;
}
