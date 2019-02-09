
#include "api_helpers.h"

// call a single argument R function from the C API
SEXP call_r_interface(SEXP f, SEXP x, SEXP rho) {

  SEXP call = PROTECT(LCONS(f, LCONS(x, R_NilValue)));
  SEXP val = R_forceAndCall(call, 1, rho);
  UNPROTECT(1);
  return val;
}

// [[Rcpp::export]]
int is_altrep_vector(SEXP vec) {
  return ALTREP(vec);
}
