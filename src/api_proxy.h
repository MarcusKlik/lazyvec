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


#ifndef API_PROXY_H
#define API_PROXY_H

#include "R_ext/Altrep.h"

#define ALTREP_METHODS						\
  R_altrep_UnserializeEX_method_t UnserializeEX;		     \
  R_altrep_Unserialize_method_t Unserialize;			        \
  R_altrep_Serialized_state_method_t Serialized_state;	\
  R_altrep_DuplicateEX_method_t DuplicateEX;			        \
  R_altrep_Duplicate_method_t Duplicate;			            \
  R_altrep_Coerce_method_t Coerce;				                 \
  R_altrep_Inspect_method_t Inspect;				               \
  R_altrep_Length_method_t Length

#define ALTVEC_METHODS					                        \
  ALTREP_METHODS;					                               \
  R_altvec_Dataptr_method_t Dataptr;			              \
  R_altvec_Dataptr_or_null_method_t Dataptr_or_null;	\
  R_altvec_Extract_subset_method_t Extract_subset

typedef struct { ALTREP_METHODS; } altrep_methods_t;
typedef struct { ALTVEC_METHODS; } altvec_methods_t;

#define CLASS_METHODS_TABLE(type_class) STDVEC_DATAPTR(type_class)
#define GENERIC_METHODS_TABLE(x, type_class) \
  ((type_class##_methods_t *) CLASS_METHODS_TABLE(ALTREP_CLASS(x)))
#define ALTREP_METHODS_TABLE(x) GENERIC_METHODS_TABLE(x, altrep)
#define ALTVEC_METHODS_TABLE(x) GENERIC_METHODS_TABLE(x, altvec)

#define DISPATCH_TARGET_HELPER(x, ...) x
#define DISPATCH_TARGET(...) DISPATCH_TARGET_HELPER(__VA_ARGS__, dummy)

#define DO_DISPATCH(type, fun, ...)					\
  type##_METHODS_TABLE(DISPATCH_TARGET(__VA_ARGS__))->fun(__VA_ARGS__)

#define ALTREP_DISPATCH(fun, ...) DO_DISPATCH(ALTREP, fun, __VA_ARGS__)
#define ALTVEC_DISPATCH(fun, ...) DO_DISPATCH(ALTVEC, fun, __VA_ARGS__)

SEXP ALTVEC_EXTRACT_SUBSET_PROXY(SEXP x, SEXP indx, SEXP call);
SEXP ALTREP_SERIALIZED_STATE_PROXY(SEXP x);
SEXP ALTREP_COERCE_PROXY(SEXP x, int type);
Rboolean ALTREP_INSPECT_PROXY(SEXP x, int pre, int deep, int pvec,
  void (*inspect_subtree)(SEXP, int, int, int));
SEXP ALTREP_DUPLICATE_EX_PROXY(SEXP x, Rboolean deep);

#endif  // API_PROXY_H