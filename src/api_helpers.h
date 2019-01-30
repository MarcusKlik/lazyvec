
#ifndef API_HELPERS_H
#define API_HELPERS_H

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include "R_ext/Altrep.h"

// call a single argument R function from the C API
SEXP call_r_interface(SEXP f, SEXP x, SEXP rho);

#endif // API_HELPERS_H
