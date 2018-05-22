
#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

// call a single argument R function from the C API
SEXP call_r_interface(SEXP f, SEXP x, SEXP rho);

