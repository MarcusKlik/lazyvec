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
#include <stdint.h>


// altrep integer class definition
static R_altrep_class_t lazyvec_ALTREP_TYPE_class;


// [[Rcpp::export]]
SEXP lazyvec_ALTREP_TYPE_wrapper(SEXP data)
{
  return R_new_altrep(lazyvec_ALTREP_TYPE_class, data, NILSXP);
}


// generator source end: Inspect
// generator source start: Length
R_xlen_t lazyvec_ALTREP_TYPE_Length_method(SEXP x)
{
  // custom payload
  SEXP user_data = PROTECT(LAZYVEC_USER_DATA(x));

  // length listener method
  SEXP length_listener = PROTECT(VECTOR_ELT(LAZYVEC_DIAGNOSTICS(x), LAZYVEC_METHOD_LENGTH));

  SEXP custom_length = PROTECT(call_r_interface(length_listener, user_data, LAZYVEC_PACKAGE_ENV(x)));
  
  // type and length checking is done on R side
  R_xlen_t res_length = (R_xlen_t)(*INTEGER(custom_length));
  
  UNPROTECT(3);  // custom_length, length_listener, user_data
  
  return res_length;
}


// generator source end: Serialized_state
// generator source start: Inspect
Rboolean lazyvec_ALTREP_TYPE_Inspect_method(SEXP x, int pre, int deep, int pvec,
  inspect_subtree_method subtree_method)
{
  return FALSE;
}


// generator source end: Length
// generator source start: Dataptr
void* lazyvec_ALTREP_TYPE_Dataptr_method(SEXP x, Rboolean writeable)
{
  // custom payload
  SEXP user_data = PROTECT(LAZYVEC_USER_DATA(x));

  // calling environment
  SEXP calling_env = PROTECT(LAZYVEC_PACKAGE_ENV(x));

  // length listener method
  SEXP full_vector_listener = PROTECT(VECTOR_ELT(LAZYVEC_DIAGNOSTICS(x), LAZYVEC_METHOD_FULL_VECTOR));

  SEXP stored_full_vec = LAZYVEC_FULL_VEC(x);

  // return dataptr of stored vector
  if (!Rf_isNull(stored_full_vec)) {
    UNPROTECT(3);
    return DATAPTR(stored_full_vec);
  }

  // retrieve full vector
  SEXP full_vector = PROTECT(call_r_interface(full_vector_listener, user_data, calling_env));

  // add vector to user data
  LAZYVEC_SET_FULL_VEC(x, full_vector);

  UNPROTECT(4);

  return DATAPTR(full_vector);
}


// generator source end: Dataptr
// generator source start: Dataptr_or_null
const void *lazyvec_ALTREP_TYPE_Dataptr_or_null_method(SEXP x)
{
  SEXP stored_full_vec = LAZYVEC_FULL_VEC(x);
  
  // return dataptr of stored vector
  if (!Rf_isNull(stored_full_vec)) {
    return DATAPTR(stored_full_vec);
  }
  
  return NULL;
}


// generator source end: Dataptr_or_null
// generator source start: Elt
CPP_TYPE lazyvec_ALTREP_TYPE_Elt_method(SEXP x, R_xlen_t i)
{
  // custom payload
  SEXP user_data = PROTECT(LAZYVEC_USER_DATA(x));
  
  // calling environment
  SEXP calling_env = PROTECT(LAZYVEC_PACKAGE_ENV(x));
  
  // length listener method
  SEXP elt_listener = PROTECT(VECTOR_ELT(LAZYVEC_DIAGNOSTICS(x), LAZYVEC_METHOD_ELT));

  // i argument
  SEXP i_arg = PROTECT(Rf_ScalarInteger((int)(i + 1)));

  // should return a length 1 vector containing the element
  SEXP custom_element = PROTECT(call_dual_r_interface(elt_listener, user_data, i_arg, calling_env));

  // convert to CPP_TYPE
  CPP_TYPE element = SEXP_TO_CPP(custom_element);

  UNPROTECT(5);
  
  return element;
}


// generator source end: Elt
// generator source start: Get_region
R_xlen_t lazyvec_ALTREP_TYPE_Get_region_method(SEXP x, R_xlen_t i, R_xlen_t n, CPP_TYPE *buf)
{
  // test for expanded vector here

  // custom payload
  SEXP user_data = PROTECT(LAZYVEC_USER_DATA(x));

  // calling environment
  SEXP calling_env = PROTECT(LAZYVEC_PACKAGE_ENV(x));

  // length listener method
  SEXP get_region_listener = PROTECT(VECTOR_ELT(LAZYVEC_DIAGNOSTICS(x), LAZYVEC_METHOD_GET_REGION));

  // i, n argument
  SEXP i_arg = PROTECT(Rf_ScalarInteger((int)(i + 1)));
  SEXP n_arg = PROTECT(Rf_ScalarInteger((int)(i)));

  // should return a length n vector containing the elements
  SEXP vec_elems = PROTECT(call_tripple_r_interface(get_region_listener, user_data, i_arg, n_arg, calling_env));

  // convert to C_TYPE
  CPP_TYPE* elements = (CPP_TYPE*)(TYPE_METHOD(vec_elems));

  memcpy(buf, elements, n * sizeof(CPP_TYPE));

  UNPROTECT(6);

  return (R_xlen_t) LENGTH(vec_elems);
}


// generator source end: Get_region
// generator source start: Is_sorted
int lazyvec_ALTREP_TYPE_Is_sorted_method(SEXP x)
{
  // custom payload
  SEXP user_data = PROTECT(LAZYVEC_USER_DATA(x));
  
  // calling environment
  SEXP calling_env = PROTECT(LAZYVEC_PACKAGE_ENV(x));
  
  // length listener method
  SEXP is_sorted_listener = PROTECT(VECTOR_ELT(LAZYVEC_DIAGNOSTICS(x), LAZYVEC_METHOD_IS_SORTED));
  
  // returns int
  SEXP custom_is_sorted = PROTECT(call_r_interface(is_sorted_listener, user_data, calling_env));
  
  // type and length checking is done on R side
  int res_is_sorted = *INTEGER(custom_is_sorted);
  
  UNPROTECT(4);
  
  return res_is_sorted;
}


// generator source end: Is_sorted
// generator source start: No_NA
int lazyvec_ALTREP_TYPE_No_NA_method(SEXP x)
{
  // custom payload
  SEXP user_data = PROTECT(LAZYVEC_USER_DATA(x));
  
  // calling environment
  SEXP calling_env = PROTECT(LAZYVEC_PACKAGE_ENV(x));
  
  // length listener method
  SEXP no_na_listener = PROTECT(VECTOR_ELT(LAZYVEC_DIAGNOSTICS(x), LAZYVEC_METHOD_NO_NA));
  
  // returns int
  SEXP custom_no_na = PROTECT(call_r_interface(no_na_listener, user_data, calling_env));
  
  // type and length checking is done on R side
  int res_no_na = *INTEGER(custom_no_na);
  
  UNPROTECT(4);
  
  return res_no_na;
}


// generator source end: No_NA
// generator source start: Sum
SEXP lazyvec_ALTREP_TYPE_Sum_method(SEXP x, Rboolean na_rm)
{
  // custom payload
  SEXP user_data = PROTECT(LAZYVEC_USER_DATA(x));

  // calling environment
  SEXP calling_env = PROTECT(LAZYVEC_PACKAGE_ENV(x));

  // sum listener method
  SEXP sum_listener = PROTECT(VECTOR_ELT(LAZYVEC_DIAGNOSTICS(x), LAZYVEC_METHOD_SUM));

  // na_rm argument
  SEXP na_rm_arg = PROTECT(Rf_ScalarLogical(na_rm));

  // returns SEXP (integer or double)
  SEXP custom_sum = PROTECT(call_dual_r_interface(sum_listener, user_data, na_rm_arg, calling_env));

  UNPROTECT(5);

  return custom_sum;
}


// generator source end: Sum
// generator source start: Min
SEXP lazyvec_ALTREP_TYPE_Min_method(SEXP x, Rboolean na_rm)
{
  // custom payload
  SEXP user_data = PROTECT(LAZYVEC_USER_DATA(x));
  
  // calling environment
  SEXP calling_env = PROTECT(LAZYVEC_PACKAGE_ENV(x));
  
  // min listener method
  SEXP min_listener = PROTECT(VECTOR_ELT(LAZYVEC_DIAGNOSTICS(x), LAZYVEC_METHOD_MIN));
  
  // na_rm argument
  SEXP na_rm_arg = PROTECT(Rf_ScalarLogical(na_rm));
  
  // returns SEXP (integer or double)
  SEXP custom_min = PROTECT(call_dual_r_interface(min_listener, user_data, na_rm_arg, calling_env));
  
  UNPROTECT(5);
  
  return custom_min;
}


// generator source end: Min
// generator source start: Max
SEXP lazyvec_ALTREP_TYPE_Max_method(SEXP x, Rboolean na_rm)
{
  // custom payload
  SEXP user_data = PROTECT(LAZYVEC_USER_DATA(x));
  
  // calling environment
  SEXP calling_env = PROTECT(LAZYVEC_PACKAGE_ENV(x));
  
  // max listener method
  SEXP max_listener = PROTECT(VECTOR_ELT(LAZYVEC_DIAGNOSTICS(x), LAZYVEC_METHOD_MAX));
  
  // na_rm argument
  SEXP na_rm_arg = PROTECT(Rf_ScalarLogical(na_rm));
  
  // returns SEXP (integer or double)
  SEXP custom_max = PROTECT(call_dual_r_interface(max_listener, user_data, na_rm_arg, calling_env));
  
  UNPROTECT(5);
  
  return custom_max;
}


// generator source end: Max
// generator source start: Duplicate_
SEXP lazyvec_ALTREP_TYPE_Duplicate_method(SEXP x, Rboolean deep)
{
  return lazyvec_ALTREP_TYPE_DuplicateEX_method(SEXP x, deep);
}


// generator source end: Duplicate_
// generator source start: DuplicateEX
SEXP lazyvec_ALTREP_TYPE_DuplicateEX_method(SEXP x, Rboolean deep)
{
  // custom payload
  SEXP user_data = PROTECT(LAZYVEC_USER_DATA(x));
  
  // calling environment
  SEXP calling_env = PROTECT(LAZYVEC_PACKAGE_ENV(x));
  
  // length listener method
  SEXP full_vector_listener = PROTECT(VECTOR_ELT(LAZYVEC_DIAGNOSTICS(x), LAZYVEC_METHOD_FULL_VECTOR));
  
  SEXP stored_full_vec = LAZYVEC_FULL_VEC(x);
  
  // return dataptr of stored vector
  if (!Rf_isNull(stored_full_vec)) {
    UNPROTECT(3);
    return stored_full_vec;
  }

  // retrieve full vector
  SEXP full_vector = PROTECT(call_r_interface(full_vector_listener, user_data, calling_env));

  // add vector to user data
  LAZYVEC_SET_FULL_VEC(x, full_vector);

  UNPROTECT(4);

  return full_vector;
}


// generator source end: DuplicateEX
// generator source start: Coerce
SEXP lazyvec_ALTREP_TYPE_Coerce_method(SEXP x, int type)
{
  SEXP type_descriptor;

  switch (type)
  {
    case 10:  // LGLSXP
      type_descriptor = PROTECT(Rf_mkString("logical"));
      break;
    case 13:  // INTSXP
      type_descriptor = PROTECT(Rf_mkString("integer"));
      break;
    case 14:  // REALSXP
      type_descriptor = PROTECT(Rf_mkString("double"));
      break;
    case 15:  // CPLXSXP
      type_descriptor = PROTECT(Rf_mkString("complex"));
      break;
    case 16: // STRSXP
      type_descriptor = PROTECT(Rf_mkString("character"));
      break;
    case 19: // VECSXP
      type_descriptor = PROTECT(Rf_mkString("list"));
      break;
    case 24:  // RAWSXP
      type_descriptor = PROTECT(Rf_mkString("raw"));
      break;
    case 20:  // EXPRSXP
      type_descriptor = PROTECT(Rf_mkString("expression"));
      break;
    default:
      Rf_error("Undefined type requested from R");
  }

  // custom payload
  SEXP user_data = PROTECT(LAZYVEC_USER_DATA(x));

  // calling environment
  SEXP calling_env = PROTECT(LAZYVEC_PACKAGE_ENV(x));
  
  // coerce user method
  SEXP coerce_method = PROTECT(VECTOR_ELT(LAZYVEC_DIAGNOSTICS(x), LAZYVEC_METHOD_COERCE));

  // should return a coerced vector
  SEXP coerced_vec = call_dual_r_interface(
    coerce_method, user_data, type_descriptor, calling_env);

  UNPROTECT(4);  // type_descriptor, user_data, calling_env, coerce_method

  return coerced_vec;
}


// generator source end: Coerce
// generator source start: Extract_subset
SEXP lazyvec_ALTREP_TYPE_Extract_subset_method(SEXP x, SEXP indx, SEXP call)
{
  // custom payload
  SEXP user_data = PROTECT(LAZYVEC_USER_DATA(x));
  
  // calling environment
  SEXP calling_env = PROTECT(LAZYVEC_PACKAGE_ENV(x));
  
  // extract_subset user method
  SEXP extract_subset_listener = PROTECT(VECTOR_ELT(LAZYVEC_DIAGNOSTICS(x), LAZYVEC_METHOD_EXTRACT_SUBSET));

  // checks are for safety, remove later
  if (indx == NULL)
  {
    Rf_error("indx is_null");
  }

  if (call == NULL)
  {
    Rf_error("call is_null");
  }

  // should return a vector containing a subset of elements
  SEXP custom_elements = call_dual_r_interface(
    extract_subset_listener, user_data, indx, calling_env);

  UNPROTECT(3);  // extract_subset_listener, calling_env, user_data
  
  return custom_elements;
}


// generator source start: Unserialize
//
// On Win there is no Unserialize method exported, check with R-dev!
//
static SEXP lazyvec_ALTREP_TYPE_Unserialize_method(SEXP lazyvec_class, SEXP state)
{
  Rcpp::Environment pkgs = Rcpp::Environment::namespace_env("lazyvec");
  
  SEXP altrep_data1 = PROTECT(Rf_allocVector(VECSXP, 4));
  SET_VECTOR_ELT(altrep_data1, 0, VECTOR_ELT(state, 0));
  SET_VECTOR_ELT(altrep_data1, 1, VECTOR_ELT(state, 1));
  SET_VECTOR_ELT(altrep_data1, 2, VECTOR_ELT(state, 2));
  SET_VECTOR_ELT(altrep_data1, 3, pkgs);
  
  // unserialize listener method
  // SEXP unserialize_listener = PROTECT(VECTOR_ELT(VECTOR_ELT(state, 1), LAZYVEC_METHOD_UNSERIALIZE));
  
  // call_r_interface(unserialize_listener, state, LAZYVEC_PACKAGE_ENV(altrep_data1));
  
  // UNPROTECT(2);
  UNPROTECT(1);
  return lazyvec_ALTREP_TYPE_wrapper(altrep_data1);
}


// generator source end: Unserialize
// generator source start: UnserializeEX
//
// ALTREP_UNSERIALIZE_EX is not linking on linux due to uncommented hidden_attribute
// in declaration
//
SEXP lazyvec_ALTREP_TYPE_UnserializeEX_method(SEXP info, SEXP state, SEXP attr, int objf, int levs)
{
  // return ALTREP_UNSERIALIZE_EX_PROXY(info, state, attr, objf, levs);
  
  Rcpp::Environment pkgs = Rcpp::Environment::namespace_env("lazyvec");
  
  SEXP altrep_data1 = PROTECT(Rf_allocVector(VECSXP, 4));
  SET_VECTOR_ELT(altrep_data1, 0, VECTOR_ELT(state, 0));
  SET_VECTOR_ELT(altrep_data1, 1, VECTOR_ELT(state, 1));
  SET_VECTOR_ELT(altrep_data1, 2, VECTOR_ELT(state, 2));
  SET_VECTOR_ELT(altrep_data1, 3, pkgs);
  
  // SEXP unserialize_ex_listener = PROTECT(VECTOR_ELT(LAZYVEC_DIAGNOSTICS(altrep_data1),
  //   LAZYVEC_METHOD_UNSERIALIZE_EX));
  
  // Rf_PrintValue(state);
  // call_r_interface(unserialize_ex_listener, state, LAZYVEC_PACKAGE_ENV(altrep_data1));
  
  // UNPROTECT(2);
  UNPROTECT(1);
  return lazyvec_ALTREP_TYPE_wrapper(altrep_data1);
}


// generator source end: UnserializeEX
// generator source start: Serialized_state
SEXP lazyvec_ALTREP_TYPE_Serialized_state_method(SEXP x)
{
  // SEXP serialized_state_result = PROTECT(ALTREP_SERIALIZED_STATE_PROXY(LAZYVEC_PAYLOAD(x)));
  
  // length listener method
  // SEXP serialized_state_listener = PROTECT(VECTOR_ELT(LAZYVEC_DIAGNOSTICS(x), LAZYVEC_METHOD_SERIALIZED_STATE));
  
  // create serialization state
  SEXP serialized_state = PROTECT(Rf_allocVector(VECSXP, 2));
  SET_VECTOR_ELT(serialized_state, 0, LAZYVEC_PAYLOAD(x));
  SET_VECTOR_ELT(serialized_state, 1, LAZYVEC_DIAGNOSTICS(x));
  
  // if (serialized_state_result == NULL)
  // {
  //   call_r_interface(serialized_state_listener, R_NilValue, LAZYVEC_PACKAGE_ENV(x));
  // }
  // else
  // {
  //   call_r_interface(serialized_state_listener, serialized_state_result, LAZYVEC_PACKAGE_ENV(x));
  // }
  
  UNPROTECT(3);
  
  return serialized_state;
}


// generator source end: Extract_subset
// [[Rcpp::init]]
void register_lazyvec_ALTREP_TYPE_class(DllInfo *dll)
{
  lazyvec_ALTREP_TYPE_class = R_make_altALTREP_TYPE_class("lazyvec_ALTREP_TYPE", "lazyvec", dll);

  /* override ALTREP methods */
  CALL_LAZYVEC_SETTER(altrep, ALTREP_TYPE, UnserializeEX);     // codeline: UnserializeEX
  CALL_LAZYVEC_SETTER(altrep, ALTREP_TYPE, Unserialize);       // codeline: Unserialize
  CALL_LAZYVEC_SETTER(altrep, ALTREP_TYPE, Serialized_state);  // codeline: Serialized_state
  CALL_LAZYVEC_SETTER(altrep, ALTREP_TYPE, DuplicateEX);       // codeline: DuplicateEx
  CALL_LAZYVEC_SETTER(altrep, ALTREP_TYPE, Duplicate);         // codeline: Duplicate_
  CALL_LAZYVEC_SETTER(altrep, ALTREP_TYPE, Coerce);            // codeline: Coerce
  CALL_LAZYVEC_SETTER(altrep, ALTREP_TYPE, Inspect);           // codeline: Inspect
  CALL_LAZYVEC_SETTER(altrep, ALTREP_TYPE, Length);            // codeline: Length

  /* override ALTVEC methods */
  CALL_LAZYVEC_SETTER(altvec, ALTREP_TYPE, Dataptr);           // codeline: Dataptr
  CALL_LAZYVEC_SETTER(altvec, ALTREP_TYPE, Dataptr_or_null);   // codeline: Dataptr_or_null
  CALL_LAZYVEC_SETTER(altvec, ALTREP_TYPE, Extract_subset);    // codeline: Extract_subset

  /* override specific type methods */
  CALL_LAZYVEC_SETTER(ALT_METHOD, ALTREP_TYPE, Elt);           // codeline: Elt
  CALL_LAZYVEC_SETTER(ALT_METHOD, ALTREP_TYPE, Get_region);    // codeline: Get_region
  CALL_LAZYVEC_SETTER(ALT_METHOD, ALTREP_TYPE, Is_sorted);     // codeline: Is_sorted
  CALL_LAZYVEC_SETTER(ALT_METHOD, ALTREP_TYPE, No_NA);         // codeline: No_NA
  CALL_LAZYVEC_SETTER(ALT_METHOD, ALTREP_TYPE, Sum);           // codeline: Sum
  CALL_LAZYVEC_SETTER(ALT_METHOD, ALTREP_TYPE, Min);           // codeline: Min
  CALL_LAZYVEC_SETTER(ALT_METHOD, ALTREP_TYPE, Max);           // codeline: Max
}
