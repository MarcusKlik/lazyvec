//  lazyvec - R package for creating, testing and deploying custom ALTREP vectors
//
//  Copyright (C) 2019-present, Mark AJ Klik
//
//  This file is part of the lazyvec R package.
//
//  The lazyvec R package is free software: you can redistribute it and/or modify it
//  under the terms of the GNU Affero General Public License version 3 as
//  published by the Free Software Foundation.
//
//  The lazyvec R package is distributed in the hope that it will be useful, but
//  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License
//  for more details.
//
//  You should have received a copy of the GNU Affero General Public License along
//  with the lazyvec R package. If not, see <http://www.gnu.org/licenses/>.
//
//  You can contact the author at:
//  - lazyvec R package source repository : https://github.com/fstpackage/lazyvec


#include "api_helpers.h"

// Convert nullptr to R_NilValue
SEXP sexp_or_null(SEXP res)
{
  if (!res)
  {
    return R_NilValue;
  }

  return res;
}


int is_altrep_vector(SEXP vec) {
  return ALTREP(vec);
}


// throw error if x is not an ALTREP vector
void test_altrep(SEXP x)
{
  if (!is_altrep_vector(x))
  {
    Rf_error("Object is not an ALTREP vector");
  }
}


// internal lazyvec version
int lazyvec_internal_version()
{
  return LAZYVEC_VERSION;
}


// Call a single argument R function from the C API and evaluate in environment rho
SEXP call_r_interface(SEXP f, SEXP x, SEXP rho) {

  SEXP call = PROTECT(LCONS(f, LCONS(x, R_NilValue)));
  SEXP val = R_forceAndCall(call, 1, rho);
  UNPROTECT(1);

  return val;
}


// Call a dual argument R function from the C API and evaluate in environment rho
SEXP call_dual_r_interface(SEXP f, SEXP x1, SEXP x2, SEXP rho) {
  
  SEXP call = PROTECT(LCONS(f, LCONS(x1, LCONS(x2, R_NilValue))));
  SEXP val = R_forceAndCall(call, 2, rho);
  UNPROTECT(1);

  return val;
}


// Call a tripple argument R function from the C API and evaluate in environment rho
SEXP call_tripple_r_interface(SEXP f, SEXP x1, SEXP x2, SEXP x3, SEXP rho) {
  
  SEXP call = PROTECT(LCONS(f, LCONS(x1, LCONS(x2, LCONS(x3, R_NilValue)))));
  SEXP val = R_forceAndCall(call, 3, rho);
  UNPROTECT(1);

  return val;
}
