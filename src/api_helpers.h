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


#ifndef API_HELPERS_H
#define API_HELPERS_H

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include "R_ext/Altrep.h"

#include "api_proxy.h"

// settings
#define LAZYVEC_VERSION 21  // 0 * 256 + 1 * 16 + 5

// serialization
#define SERIALIZED_PAYLOAD  0
#define SERIALIZED_METADATA 1
#define SERIALIZED_VERSION  2
#define SERIALIZED_STATE    3

// altvec listeners
#define ALTREP_METHOD_LENGTH            0
#define ALTREP_METHOD_DATAPTR_OR_NULL   1
#define ALTREP_METHOD_GET_REGION        2
#define ALTREP_METHOD_ELT               3
#define ALTREP_METHOD_DATAPTR           4
#define ALTREP_METHOD_IS_SORTED         5
#define ALTREP_METHOD_NO_NA             6
#define ALTREP_METHOD_SUM               7
#define ALTREP_METHOD_MIN               8
#define ALTREP_METHOD_MAX               9
#define ALTREP_METHOD_INSPECT          10
#define ALTREP_METHOD_UNSERIALIZE_EX   11
#define ALTREP_METHOD_SERIALIZED_STATE 12
#define ALTREP_METHOD_DUPLICATE_EX     13
#define ALTREP_METHOD_COERCE           14
#define ALTREP_METHOD_EXTRACT_SUBSET   15
#define ALTREP_METHOD_UNSERIALIZE      16
#define ALTREP_METHOD_DUPLICATE        17

// lazyvec user methods
#define LAZYVEC_METHOD_LENGTH            0
#define LAZYVEC_METHOD_DATAPTR_OR_NULL   1
#define LAZYVEC_METHOD_GET_REGION        2
#define LAZYVEC_METHOD_ELT               3
#define LAZYVEC_METHOD_DATAPTR           4
#define LAZYVEC_METHOD_IS_SORTED         5
#define LAZYVEC_METHOD_NO_NA             6
#define LAZYVEC_METHOD_SUM               7
#define LAZYVEC_METHOD_MIN               8
#define LAZYVEC_METHOD_MAX               9
#define LAZYVEC_METHOD_INSPECT          10
#define LAZYVEC_METHOD_UNSERIALIZE_EX   11
#define LAZYVEC_METHOD_SERIALIZED_STATE 12
#define LAZYVEC_METHOD_DUPLICATE_EX     13
#define LAZYVEC_METHOD_COERCE           14
#define LAZYVEC_METHOD_EXTRACT_SUBSET   15
#define LAZYVEC_METHOD_UNSERIALIZE      16
#define LAZYVEC_METHOD_DUPLICATE        17

// conversion helpers
#define SEXP_TO_INT(x) *INTEGER(x)
#define SEXP_TO_DOUBLE(x) *REAL(x)
#define SEXP_TO_RBYTE(x) (Rbyte)(*RAW(x))
#define SEXP_TO_CHARXP(x) STRING_ELT(x, 0)

typedef void (*inspect_subtree_method)(SEXP, int, int, int);


// get meta data components from the ALTREP vector
#define ALTWRAP_PAYLOAD(x) VECTOR_ELT(R_altrep_data1(x), 0)
#define ALTWRAP_LISTENERS(x) VECTOR_ELT(R_altrep_data1(x), 1)
#define ALTWRAP_METADATA(x) VECTOR_ELT(R_altrep_data1(x), 2)
#define ALTWRAP_VERSION(x) VECTOR_ELT(R_altrep_data1(x), 3)
#define ALTWRAP_PARENT_ENV(x) VECTOR_ELT(R_altrep_data1(x), 4)

// override default altrep methods
#define CALL_METHOD_SETTER(CNAME, TNAME, MNAME) \
  R_set_##CNAME##_##MNAME##_method(altwrap_##TNAME##_class, altwrap_##TNAME##_##MNAME##_method)


// get meta data components from the ALTREP vector
#define LAZYVEC_PAYLOAD(x) VECTOR_ELT(R_altrep_data1(x), 0)
#define LAZYVEC_LISTENERS(x) VECTOR_ELT(R_altrep_data1(x), 1)
#define LAZYVEC_METADATA(x) VECTOR_ELT(R_altrep_data1(x), 2)
#define LAZYVEC_PARENT_ENV(x) VECTOR_ELT(R_altrep_data1(x), 3)
#define LAZYVEC_USER_DATA(x) VECTOR_ELT(R_altrep_data1(x), 4)
#define LAZYVEC_FULL_VEC(x) VECTOR_ELT(R_altrep_data1(x), 5)

// setters
#define LAZYVEC_SET_FULL_VEC(x, y) SET_VECTOR_ELT(R_altrep_data1(x), 5, y)


#define CALL_LAZYVEC_SETTER(CNAME, TNAME, MNAME) \
  R_set_##CNAME##_##MNAME##_method(lazyvec_##TNAME##_class, lazyvec_##TNAME##_##MNAME##_method)


// convert nullptr to R_NilValue
SEXP sexp_or_null(SEXP res);

// call R function with a single argument from the C API
SEXP call_r_interface(SEXP f, SEXP x, SEXP rho);

// call R function with two arguments from the C API
SEXP call_dual_r_interface(SEXP f, SEXP x1, SEXP x2, SEXP rho);

// call R function with three arguments from the C API
SEXP call_tripple_r_interface(SEXP f, SEXP x1, SEXP x2, SEXP x3, SEXP rho);

int is_altrep_vector(SEXP vec);

// [[Rcpp::export]]
int lazyvec_internal_version();


#endif // API_HELPERS_H
