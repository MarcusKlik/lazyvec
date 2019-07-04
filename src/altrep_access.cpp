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


// [[Rcpp::export]]
SEXP altrep_class(SEXP vec) {
  test_altrep(vec);

  return ALTREP_CLASS(vec);
}


// Get the exact ALTREP class descriptor
// [[Rcpp::export]]
SEXP altrep_full_class(SEXP altrep_vec) {
  test_altrep(altrep_vec);

  return ATTRIB(ALTREP_CLASS(altrep_vec));
}


// [[Rcpp::export]]
SEXP altrep_data1(SEXP altrep_vec) {
  test_altrep(altrep_vec);

  return sexp_or_null(R_altrep_data1(altrep_vec));
}


// [[Rcpp::export]]
SEXP altrep_data2(SEXP altrep_vec) {
  test_altrep(altrep_vec);

  return sexp_or_null(R_altrep_data2(altrep_vec));
}
