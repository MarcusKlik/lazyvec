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


#include <Rcpp.h>
#include "api_helpers.h"

// general ALTREP methods
  

// [[Rcpp::export]]
int trigger_length(SEXP x)
{
  return (int)(ALTREP_LENGTH(x));
}


SEXP sexp_or_null(SEXP res)
{
  if (!res)
  {
    return R_NilValue;
  }
  
  return res;
}


// [[Rcpp::export]]
SEXP trigger_duplicate_ex(SEXP x, int deep)
{
  SEXP res = ALTREP_DUPLICATE_EX(x, (Rboolean) deep);

  return sexp_or_null(res);
}


// [[Rcpp::export]]
SEXP trigger_serialized_state(SEXP x)
{
  SEXP res = ALTREP_SERIALIZED_STATE(x);

  return sexp_or_null(res);
}


// [[Rcpp::export]]
SEXP trigger_dataptr_or_null(SEXP x)
{
  const void* dataptr = DATAPTR_OR_NULL(x);

  if (dataptr == NULL)
  {
    return R_NilValue;
  }

  uint64_t ptr_address = (uint64_t) dataptr;

  SEXP pointer = PROTECT(Rf_allocVector(INTSXP, 2));
  int* pointer_values = INTEGER(pointer);
  
  pointer_values[0] = (int32_t) (ptr_address >> 32);
  pointer_values[1] = ptr_address & ((1LL << 32) - 1);
  
  UNPROTECT(1);
  
  return pointer;
}


// [[Rcpp::export]]
SEXP trigger_get_region(SEXP x, SEXP pos, SEXP size)
{
  int type = TYPEOF(x);

  // expect pos and size arguments of the correct type at this point

  R_xlen_t vec_length = R_xlen_t(x);
  R_xlen_t vec_pos = INTEGER(Rf_coerceVector(pos, INTSXP))[0];
  R_xlen_t vec_size = INTEGER(Rf_coerceVector(size, INTSXP))[0];

  if (vec_pos < 0 || vec_pos > (vec_length - 1))
  {
    Rf_error("Position is outside vector boundaries");
  }

  R_xlen_t end_pos = vec_pos + vec_size - 1;
  
  if (end_pos < 0 || end_pos > (vec_length - 1))
  {
    Rf_error("Size too large, resulting range is outside vector boundaries");
  }
  
  SEXP res;

  switch (type)
  {
    case INTSXP:
      res = PROTECT(Rf_allocVector(INTSXP, vec_size)); 
      INTEGER_GET_REGION(x, vec_pos, vec_size, INTEGER(res));
      break;
    case LGLSXP:
      res = PROTECT(Rf_allocVector(LGLSXP, vec_size)); 
      LOGICAL_GET_REGION(x, vec_pos, vec_size, LOGICAL(res));
      break;
    case REALSXP:
      res = PROTECT(Rf_allocVector(REALSXP, vec_size)); 
      REAL_GET_REGION(x, vec_pos, vec_size, REAL(res));
      break;
    case RAWSXP:
      res = PROTECT(Rf_allocVector(RAWSXP, vec_size)); 
      RAW_GET_REGION(x, vec_pos, vec_size, RAW(res));
      break;
    default:
        Rf_error("Method get_region cannot be called on a ALTREP vector of this type");
        break;
  }

  return res;
}


// [[Rcpp::export]]
SEXP trigger_unserialize_ex(SEXP info, SEXP state, SEXP attr, int objf, int levs)
{
  SEXP res = ALTREP_UNSERIALIZE_EX(info, state, attr, objf, levs);
  
  return sexp_or_null(res);
}


// used as a proxy for the inspect_subtree method normally supplied by R
void inspect_subtree_helper(SEXP, int, int, int)
{
}
  

// Trigger ALTREP_INSPECT method
// 
// x is the object to inspect
// pre is the prefix
// deep specifies the recursion behavior (0 = no recursion, -1 = [sort of] unlimited
//   recursion, positive numbers define the maximum recursion depth)
// pvec is the maximum number of vector elements to show
// [[Rcpp::export]]
void trigger_inspect(SEXP x, int pre, int deep, int pvec)
{
  if (!is_altrep_vector(x))
  {
    Rf_error("x is not an ALTREP vector");
  }

  if (deep < -1)
  {
    Rf_error("deep specifies the recursion behavior: 0 = no recursion, -1 = [sort of] unlimited"
      " recursion, positive numbers define the maximum recursion depth");
  }

  // if (pvec < 0)
  // {
  //   Rf_error("use a positive int for pVec");
  // }

  ALTREP_INSPECT(x, pre, deep, pvec, inspect_subtree_helper);
}


// Valid SEXP types:
// 10  |  LGLSXP
// 13  |  INTSXP
// 14  |  REALSXP
// 15  |  CPLXSXP
// 16  |  STRSXP
// 19  |  VECSXP
// 24  |  RAWSXP
// 20  |  EXPRSXP

// [[Rcpp::export]]
SEXP trigger_coerce(SEXP x, int type)
{
  if (!is_altrep_vector(x))
  {
    Rf_error("x is not an ALTREP vector");
  }
  
  if ((type != LGLSXP) &&
      (type != INTSXP) &&
      (type != REALSXP) &&
      (type != CPLXSXP) &&
      (type != STRSXP) &&
      (type != VECSXP) &&
      (type != RAWSXP) &&
      (type != EXPRSXP))
  {
    Rf_error("Undefined type, valid types are 10 (LGLSXP), 13 (INTSXP), 14 (REALSXP)"
      "15 (CPLXSXP), 16 (STRSXP), 19 (VECSXP), 24 (RAWSXP) and 20 (EXPRSXP)");
  }
  
  SEXP res = ALTREP_COERCE(x, type);

  return sexp_or_null(res);
}


// integer methods

// [[Rcpp::export]]
int trigger_integer_Elt(SEXP x, int i)
{
  return INTEGER_ELT(x, i);
}


// [[Rcpp::export]]
int trigger_integer_is_sorted(SEXP x)
{
  return INTEGER_IS_SORTED(x);
}


// [[Rcpp::export]]
int trigger_integer_no_na(SEXP x)
{
  return INTEGER_NO_NA(x);
}


// [[Rcpp::export]]
SEXP trigger_integer_sum(SEXP x, int na_rm)
{
  return ALTINTEGER_SUM(x, (Rboolean) na_rm);
}


// [[Rcpp::export]]
SEXP trigger_integer_min(SEXP x, int na_rm)
{
  return ALTINTEGER_MIN(x, (Rboolean) na_rm);
}


// [[Rcpp::export]]
SEXP trigger_integer_max(SEXP x, int na_rm)
{
  return ALTINTEGER_MAX(x, (Rboolean) na_rm);
}
