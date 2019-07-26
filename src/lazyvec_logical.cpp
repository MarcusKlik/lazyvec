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
static R_altrep_class_t lazyvec_logical_class;


// [[Rcpp::export]]
SEXP lazyvec_logical_wrapper(SEXP data)
{
  return R_new_altrep(lazyvec_logical_class, data, NILSXP);
}


R_xlen_t lazyvec_logical_Length_method(SEXP x)
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


Rboolean lazyvec_logical_Inspect_method(SEXP x, int pre, int deep, int pvec,
  inspect_subtree_method subtree_method)
{
  return FALSE;
}


void* lazyvec_logical_Dataptr_method(SEXP x, Rboolean writeable)
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


const void *lazyvec_logical_Dataptr_or_null_method(SEXP x)
{
  SEXP stored_full_vec = LAZYVEC_FULL_VEC(x);
  
  // return dataptr of stored vector
  if (!Rf_isNull(stored_full_vec)) {
    return DATAPTR(stored_full_vec);
  }
  
  return NULL;
}


int lazyvec_logical_Elt_method(SEXP x, R_xlen_t i)
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

  // convert to int
  int element = SEXP_TO_INT(custom_element);

  UNPROTECT(5);
  
  return element;
}


R_xlen_t lazyvec_logical_Get_region_method(SEXP x, R_xlen_t i, R_xlen_t n, int *buf)
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
  int* elements = (int*)(LOGICAL(vec_elems));

  memcpy(buf, elements, n * sizeof(int));

  UNPROTECT(6);

  return (R_xlen_t) LENGTH(vec_elems);
}


int lazyvec_logical_Is_sorted_method(SEXP x)
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


int lazyvec_logical_No_NA_method(SEXP x)
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


SEXP lazyvec_logical_Sum_method(SEXP x, Rboolean na_rm)
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


SEXP lazyvec_logical_DuplicateEX_method(SEXP x, Rboolean deep)
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


SEXP lazyvec_logical_Coerce_method(SEXP x, int type)
{
  // length listener method
  SEXP listener_coerce = VECTOR_ELT(LAZYVEC_DIAGNOSTICS(x), LAZYVEC_METHOD_COERCE);

  // use default coercion
  if (Rf_isNull(listener_coerce)) {
    return NULL;
  }

  return  NULL;
}


SEXP lazyvec_logical_Extract_subset_method(SEXP x, SEXP indx, SEXP call)
{
  // custom payload
  SEXP user_data = PROTECT(LAZYVEC_USER_DATA(x));
  
  // calling environment
  SEXP calling_env = PROTECT(LAZYVEC_PACKAGE_ENV(x));
  
  // length listener method
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


//
// On Win there is no Unserialize method exported, check with R-dev!
//
static SEXP lazyvec_logical_Unserialize_method(SEXP lazyvec_class, SEXP state)
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
  return lazyvec_logical_wrapper(altrep_data1);
}


//
// ALTREP_UNSERIALIZE_EX is not linking on linux due to uncommented hidden_attribute
// in declaration
//
SEXP lazyvec_logical_UnserializeEX_method(SEXP info, SEXP state, SEXP attr, int objf, int levs)
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
  return lazyvec_logical_wrapper(altrep_data1);
}


SEXP lazyvec_logical_Serialized_state_method(SEXP x)
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


// [[Rcpp::init]]
void register_lazyvec_logical_class(DllInfo *dll)
{
  lazyvec_logical_class = R_make_altlogical_class("lazyvec_logical", "lazyvec", dll);

  /* override ALTREP methods */
  CALL_LAZYVEC_SETTER(altrep, logical, UnserializeEX);     // codeline: UnserializeEX
  CALL_LAZYVEC_SETTER(altrep, logical, Unserialize);       // codeline: Unserialize
  CALL_LAZYVEC_SETTER(altrep, logical, Serialized_state);  // codeline: Serialized_state
  CALL_LAZYVEC_SETTER(altrep, logical, DuplicateEX);       // codeline: DuplicateEx
  CALL_LAZYVEC_SETTER(altrep, logical, Coerce);            // codeline: Coerce
  CALL_LAZYVEC_SETTER(altrep, logical, Inspect);           // codeline: Inspect
  CALL_LAZYVEC_SETTER(altrep, logical, Length);            // codeline: Length

  /* override ALTVEC methods */
  CALL_LAZYVEC_SETTER(altvec, logical, Dataptr);           // codeline: Dataptr
  CALL_LAZYVEC_SETTER(altvec, logical, Dataptr_or_null);   // codeline: Dataptr_or_null
  CALL_LAZYVEC_SETTER(altvec, logical, Extract_subset);    // codeline: Extract_subset

  /* override specific type methods */
  CALL_LAZYVEC_SETTER(altlogical, logical, Elt);           // codeline: Elt
  CALL_LAZYVEC_SETTER(altlogical, logical, Get_region);    // codeline: Get_region
  CALL_LAZYVEC_SETTER(altlogical, logical, Is_sorted);     // codeline: Is_sorted
  CALL_LAZYVEC_SETTER(altlogical, logical, No_NA);         // codeline: No_NA
  CALL_LAZYVEC_SETTER(altlogical, logical, Sum);           // codeline: Sum
}
