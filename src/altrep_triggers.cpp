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
int altrep_trigger_length(SEXP x)
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
SEXP altrep_trigger_duplicate_ex(SEXP x, int deep)
{
  SEXP res = ALTREP_DUPLICATE_EX(x, (Rboolean) deep);

  return sexp_or_null(res);
}


// [[Rcpp::export]]
SEXP altrep_trigger_serialized_state(SEXP x)
{
  SEXP res = ALTREP_SERIALIZED_STATE(x);

  return sexp_or_null(res);
}


// [[Rcpp::export]]
SEXP altrep_trigger_unserialize_ex(SEXP info, SEXP state, SEXP attr, int objf, int levs)
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
void altrep_trigger_inspect(SEXP x, int pre, int deep, int pvec)
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
SEXP altrep_trigger_coerce(SEXP x, int type)
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
int altrep_trigger_integer_Elt(SEXP x, int i)
{
  return INTEGER_ELT(x, i);
}


// [[Rcpp::export]]
int altrep_trigger_integer_is_sorted(SEXP x)
{
  return INTEGER_IS_SORTED(x);
}


// [[Rcpp::export]]
int altrep_trigger_integer_no_na(SEXP x)
{
  return INTEGER_NO_NA(x);
}


// [[Rcpp::export]]
SEXP altrep_trigger_integer_sum(SEXP x, int na_rm)
{
  return ALTINTEGER_SUM(x, (Rboolean) na_rm);
}


// [[Rcpp::export]]
SEXP altrep_trigger_integer_min(SEXP x, int na_rm)
{
  return ALTINTEGER_MIN(x, (Rboolean) na_rm);
}


// [[Rcpp::export]]
SEXP altrep_trigger_integer_max(SEXP x, int na_rm)
{
  return ALTINTEGER_MAX(x, (Rboolean) na_rm);
}
