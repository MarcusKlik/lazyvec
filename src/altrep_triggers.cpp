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


// [[Rcpp::export]]
int altrep_length_method(SEXP x)
{
  return (int)(ALTREP_LENGTH(x));
}


// [[Rcpp::export]]
SEXP altrep_duplicate_ex_method(SEXP x, int deep)
{
  return ALTREP_DUPLICATE_EX(x, (Rboolean) deep);
}


// [[Rcpp::export]]
SEXP altrep_coerce_method(SEXP x, int type)
{
  return ALTREP_COERCE(x, type);
}


// [[Rcpp::export]]
int altrep_integer_Elt_method(SEXP x, int i)
{
  return INTEGER_ELT(x, i);
}


// [[Rcpp::export]]
int altrep_integer_is_sorted_method(SEXP x)
{
  return INTEGER_IS_SORTED(x);
}


// [[Rcpp::export]]
int altrep_integer_no_na_method(SEXP x)
{
  return INTEGER_NO_NA(x);
}


// [[Rcpp::export]]
SEXP altrep_integer_sum_method(SEXP x, int na_rm)
{
  return ALTINTEGER_SUM(x, (Rboolean) na_rm);
}


// [[Rcpp::export]]
SEXP altrep_integer_min_method(SEXP x, int na_rm)
{
  return ALTINTEGER_MIN(x, (Rboolean) na_rm);
}


// [[Rcpp::export]]
SEXP altrep_integer_max_method(SEXP x, int na_rm)
{
  return ALTINTEGER_MAX(x, (Rboolean) na_rm);
}
