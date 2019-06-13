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


void test_altrep(SEXP x)
{
  if (!is_altrep_vector(x))
  {
    Rf_error("Object is not an ALTREP vector");
  }
}


// [[Rcpp::export]]
int trigger_length(SEXP x)
{
  test_altrep(x);

  return (int)(ALTREP_LENGTH(x));
}


// [[Rcpp::export]]
SEXP trigger_duplicate_ex(SEXP x, int deep)
{
  test_altrep(x);
  
  SEXP res = ALTREP_DUPLICATE_EX_PROXY(x, (Rboolean) deep);

  return sexp_or_null(res);
}


// [[Rcpp::export]]
SEXP trigger_serialized_state(SEXP x)
{
  test_altrep(x);
  
  SEXP res = ALTREP_SERIALIZED_STATE_PROXY(x);

  return sexp_or_null(res);
}


// [[Rcpp::export]]
SEXP trigger_dataptr_or_null(SEXP x)
{
  test_altrep(x);
  
  const void* dataptr = DATAPTR_OR_NULL(x);

  if (dataptr == NULL)
  {
    return R_NilValue;
  }

  uint64_t ptr_address = (uint64_t) dataptr;

  SEXP pointer = PROTECT(Rf_allocVector(INTSXP, 2));
  int* pointer_values = INTEGER(pointer);

  pointer_values[0] = (int32_t) ((ptr_address >> 32) & ((1LL << 32) - 1));
  pointer_values[1] = (int32_t) (ptr_address & ((1LL << 32) - 1));

  UNPROTECT(1);

  return pointer;
}


// [[Rcpp::export]]
SEXP trigger_dataptr(SEXP x)
{
  test_altrep(x);
  
  const void* dataptr = DATAPTR(x);
  
  if (dataptr == NULL)
  {
    return R_NilValue;
  }
  
  uint64_t ptr_address = (uint64_t) dataptr;
  
  SEXP pointer = PROTECT(Rf_allocVector(INTSXP, 2));
  int* pointer_values = INTEGER(pointer);
  
  pointer_values[0] = (int32_t) ((ptr_address >> 32) & ((1LL << 32) - 1));
  pointer_values[1] = (int32_t) (ptr_address & ((1LL << 32) - 1));
  
  UNPROTECT(1);
  
  return pointer;
}


// [[Rcpp::export]]
SEXP trigger_get_region(SEXP x, SEXP pos, SEXP size)
{
  test_altrep(x);
  
  R_xlen_t vec_length = Rf_length(x);
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
  R_xlen_t res_length;
  
  int type = TYPEOF(x);

  switch (type)
  {
    case INTSXP:
      res = PROTECT(Rf_allocVector(INTSXP, vec_size));
      res_length = INTEGER_GET_REGION(x, vec_pos, vec_size, INTEGER(res));
      break;
    case LGLSXP:
      res = PROTECT(Rf_allocVector(LGLSXP, vec_size)); 
      res_length = LOGICAL_GET_REGION(x, vec_pos, vec_size, LOGICAL(res));
      break;
    case REALSXP:
      res = PROTECT(Rf_allocVector(REALSXP, vec_size)); 
      res_length = REAL_GET_REGION(x, vec_pos, vec_size, REAL(res));
      break;
    case RAWSXP:
      res = PROTECT(Rf_allocVector(RAWSXP, vec_size)); 
      res_length = RAW_GET_REGION(x, vec_pos, vec_size, RAW(res));
      break;
    default:
        Rf_error("Method get_region cannot be called on a ALTREP vector of this type");
        break;
  }

  UNPROTECT(1);

  if (res_length == 0)
  {
    return R_NilValue;
  }
  
  return res;
}


// [[Rcpp::export]]
SEXP trigger_extract_subset(SEXP x, SEXP indx)
{
  test_altrep(x);

  int type = TYPEOF(indx);
  
  if (type != INTSXP && type != REALSXP)
  {
    Rf_error("Please use a numeric index");
  }
    
  return sexp_or_null(ALTVEC_EXTRACT_SUBSET_PROXY(x, indx, R_NilValue));
}


// [[Rcpp::export]]
SEXP trigger_element(SEXP x, int pos)
{
  test_altrep(x);
  
  R_xlen_t vec_length = Rf_length(x);
  
  if (pos < 0 || pos >= vec_length)
  {
    Rf_error("Position is outside vector boundaries");
  }
  
  int type = TYPEOF(x);
  
  if (type == INTSXP)
  {
    return Rf_ScalarInteger(INTEGER_ELT(x, pos));
  }
  else if (type == LGLSXP)
  {
    return Rf_ScalarLogical(LOGICAL_ELT(x, pos));
  }
  else if (type == REALSXP)
  {
    return Rf_ScalarReal(REAL_ELT(x, pos));
  }
  else if (type == RAWSXP)
  {
    return Rf_ScalarRaw(RAW_ELT(x, pos));
  }
  else if (type == STRSXP)
  {
    return Rf_ScalarString(STRING_ELT(x, pos));
  }

  Rf_error("Method element cannot be called on a ALTREP vector of this type");

  return R_NilValue;
}


// [[Rcpp::export]]
int trigger_is_sorted(SEXP x)
{
  test_altrep(x);
  
  int type = TYPEOF(x);
  
  if (type == INTSXP)
  {
    return INTEGER_IS_SORTED(x);
  }
  else if (type == LGLSXP)
  {
    return LOGICAL_IS_SORTED(x);
  }
  else if (type == REALSXP)
  {
    return REAL_IS_SORTED(x);
  }
  else if (type == STRSXP)
  {
    return STRING_IS_SORTED(x);
  }

  Rf_error("Method is_sorted cannot be called on a ALTREP vector of this type");

  return 0;
}


// [[Rcpp::export]]
int trigger_no_na(SEXP x)
{
  test_altrep(x);
  
  int type = TYPEOF(x);

  if (type == INTSXP)
  {
    return INTEGER_NO_NA(x);
  }
  else if (type == LGLSXP)
  {
    return LOGICAL_NO_NA(x);
  }
  else if (type == REALSXP)
  {
    return REAL_NO_NA(x);
  }
  else if (type == STRSXP)
  {
    return STRING_NO_NA(x);
  }

  Rf_error("Method no_na cannot be called on a ALTREP vector of this type");
  
  return 0;
}


// [[Rcpp::export]]
SEXP trigger_sum(SEXP x, SEXP na_rm)
{
  test_altrep(x);
  
  if (TYPEOF(na_rm) != LGLSXP || Rf_length(na_rm) < 1)
  {
    Rf_error("Please set na_rm using a logical value");
  }

  Rboolean na_remove = (Rboolean) LOGICAL(na_rm)[0];
  
  int type = TYPEOF(x);
  
  if (type == INTSXP)
  {
    SEXP res = ALTINTEGER_SUM(x, na_remove);
    return sexp_or_null(res);
  }
  else if (type == LGLSXP)
  {
    SEXP res = ALTLOGICAL_SUM(x, na_remove);
    return sexp_or_null(res);
  }
  else if (type == REALSXP)
  {
    SEXP res = ALTREAL_SUM(x, na_remove);
    return sexp_or_null(res);
  }

  Rf_error("Method sum cannot be called on a ALTREP vector of this type");
  
  return 0;
}


// [[Rcpp::export]]
SEXP trigger_min(SEXP x, SEXP na_rm)
{
  test_altrep(x);
  
  if (TYPEOF(na_rm) != LGLSXP || Rf_length(na_rm) < 1)
  {
    Rf_error("Please set na_rm using a logical value");
  }
  
  Rboolean na_remove = (Rboolean) LOGICAL(na_rm)[0];
  
  int type = TYPEOF(x);
  
  if (type == INTSXP)
  {
    SEXP res = ALTINTEGER_MIN(x, na_remove);
    return sexp_or_null(res);
  }
  else if (type == REALSXP)
  {
    SEXP res = ALTREAL_MIN(x, na_remove);
    return sexp_or_null(res);
  }

  Rf_error("Method min cannot be called on a ALTREP vector of this type");
  
  return 0;
}


// [[Rcpp::export]]
SEXP trigger_max(SEXP x, SEXP na_rm)
{
  test_altrep(x);
  
  if (TYPEOF(na_rm) != LGLSXP || Rf_length(na_rm) < 1)
  {
    Rf_error("Please set na_rm using a logical value");
  }
  
  Rboolean na_remove = (Rboolean) LOGICAL(na_rm)[0];
  
  int type = TYPEOF(x);
  
  if (type == INTSXP)
  {
    SEXP res = ALTINTEGER_MAX(x, na_remove);
    return sexp_or_null(res);
  }
  else if (type == REALSXP)
  {
    SEXP res = ALTREAL_MAX(x, na_remove);
    return sexp_or_null(res);
  }
  
  Rf_error("Method max cannot be called on a ALTREP vector of this type");
  
  return 0;
}


// [[Rcpp::export]]
SEXP trigger_unserialize_ex(SEXP class_info, SEXP state, SEXP attr, int objf, int levs)
{
  SEXP res = ALTREP_UNSERIALIZE_EX_PROXY(class_info, state, attr, objf, levs);
  
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
int trigger_inspect(SEXP x, int pre, int deep, int pvec)
{
  test_altrep(x);

  if (deep < -1)
  {
    Rf_error("deep specifies the recursion behavior: 0 = no recursion, -1 = [sort of] unlimited"
      " recursion, positive numbers define the maximum recursion depth");
  }

  // if (pvec < 0)
  // {
  //   Rf_error("use a positive int for pVec");
  // }

  return ALTREP_INSPECT_PROXY(x, pre, deep, pvec, inspect_subtree_helper);
}


// [[Rcpp::export]]
SEXP trigger_coerce(SEXP x, int type)
{
  test_altrep(x);
  
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
  
  SEXP res = ALTREP_COERCE_PROXY(x, type);

  return sexp_or_null(res);
}
