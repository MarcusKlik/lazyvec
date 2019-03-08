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
  
  // call_r_interface(unserialize_listener, state, LAZYVEC_PARENT_ENV(altrep_data1));

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
  // return ALTREP_UNSERIALIZE_EX(info, state, attr, objf, levs);

  Rcpp::Environment pkgs = Rcpp::Environment::namespace_env("lazyvec");

  SEXP altrep_data1 = PROTECT(Rf_allocVector(VECSXP, 4));
  SET_VECTOR_ELT(altrep_data1, 0, VECTOR_ELT(state, 0));
  SET_VECTOR_ELT(altrep_data1, 1, VECTOR_ELT(state, 1));
  SET_VECTOR_ELT(altrep_data1, 2, VECTOR_ELT(state, 2));
  SET_VECTOR_ELT(altrep_data1, 3, pkgs);

  // SEXP unserialize_ex_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(altrep_data1),
  //   LAZYVEC_METHOD_UNSERIALIZE_EX));

  // Rf_PrintValue(state);
  // call_r_interface(unserialize_ex_listener, state, LAZYVEC_PARENT_ENV(altrep_data1));
  
  // UNPROTECT(2);
  UNPROTECT(1);
  return lazyvec_ALTREP_TYPE_wrapper(altrep_data1);
}


// generator source end: UnserializeEX
// generator source start: Serialized_state
SEXP lazyvec_ALTREP_TYPE_Serialized_state_method(SEXP x)
{
  SEXP serialized_state_result = PROTECT(ALTREP_SERIALIZED_STATE(LAZYVEC_PAYLOAD(x)));

  // length listener method
  SEXP serialized_state_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(x), LAZYVEC_METHOD_SERIALIZED_STATE));

  // create serialization state
  SEXP serialized_state = PROTECT(Rf_allocVector(VECSXP, 3));
  SET_VECTOR_ELT(serialized_state, 0, LAZYVEC_PAYLOAD(x));
  SET_VECTOR_ELT(serialized_state, 1, LAZYVEC_LISTENERS(x));
  SET_VECTOR_ELT(serialized_state, 2, LAZYVEC_METADATA(x));
  
  // if (serialized_state_result == NULL)
  // {
  //   call_r_interface(serialized_state_listener, R_NilValue, LAZYVEC_PARENT_ENV(x));
  // }
  // else
  // {
  //   call_r_interface(serialized_state_listener, serialized_state_result, LAZYVEC_PARENT_ENV(x));
  // }

  UNPROTECT(3);

  return serialized_state;
}


// generator source end: Serialized_state
// generator source start: Inspect
Rboolean lazyvec_ALTREP_TYPE_Inspect_method(SEXP x, int pre, int deep, int pvec,
  inspect_subtree_method subtree_method)
{
  return FALSE;
}


// generator source end: Inspect
// generator source start: Length
R_xlen_t lazyvec_ALTREP_TYPE_Length_method(SEXP x)
{
  // custom payload
  SEXP user_data = PROTECT(LAZYVEC_USER_DATA(x));

  // calling environment
  SEXP calling_env = PROTECT(LAZYVEC_PARENT_ENV(x));
  
  // length listener method
  SEXP length_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(x), LAZYVEC_METHOD_LENGTH));

  // call ALTREP override
  SEXP custom_length = PROTECT(call_r_interface(length_listener, user_data, calling_env));

  // type and length checking is done on R side
  R_xlen_t res_length = (R_xlen_t)(*INTEGER(custom_length));
  
  UNPROTECT(4);

  return res_length;
}


// generator source end: Length
// generator source start: Dataptr
void* lazyvec_ALTREP_TYPE_Dataptr_method(SEXP x, Rboolean writeable)
{
  // custom payload
  SEXP user_data = PROTECT(LAZYVEC_USER_DATA(x));

  // calling environment
  SEXP calling_env = PROTECT(LAZYVEC_PARENT_ENV(x));

  // length listener method
  SEXP full_vector_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(x), LAZYVEC_METHOD_DATAPTR));

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
  
  Rprintf("dataptr_or_null called");
  
  // return dataptr of stored vector
  if (!Rf_isNull(stored_full_vec)) {
    UNPROTECT(3);
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
  SEXP calling_env = PROTECT(LAZYVEC_PARENT_ENV(x));
  
  // length listener method
  SEXP elt_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(x), LAZYVEC_METHOD_ELT));

  // i argument
  SEXP i_arg = PROTECT(Rf_ScalarInteger((int)(i + 1)));
  
  // ALTREP override
  // should return a length 1 vector containing the element
  SEXP custom_element = PROTECT(call_dual_r_interface(elt_listener, user_data, i_arg, calling_env));

  // convert to CPP_TYPE
  CPP_TYPE element = SEXP_TO_CPP(custom_element);

  UNPROTECT(5);
  
  return element;
}


// generator source end: Elt
// generator source start: Get_region
R_xlen_t lazyvec_ALTREP_TYPE_Get_region_method(SEXP sx, R_xlen_t i, R_xlen_t n, CPP_TYPE *buf)
{
  R_xlen_t length = TYPE_METHOD_GET_REGION(LAZYVEC_PAYLOAD(sx), i, n, buf);

  SEXP arguments = PROTECT(Rf_allocVector(VECSXP, 4));
  SET_VECTOR_ELT(arguments, 0, LAZYVEC_METADATA(sx));
  SET_VECTOR_ELT(arguments, 1, Rf_ScalarInteger(i));
  SET_VECTOR_ELT(arguments, 2, Rf_ScalarInteger(n));
  SET_VECTOR_ELT(arguments, 3, Rf_ScalarInteger(length));

  // dataptr_or_null listener method
  SEXP get_region_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(sx), LAZYVEC_METHOD_GET_REGION));

  // call listener with integer result
  call_r_interface(get_region_listener, arguments, LAZYVEC_PARENT_ENV(sx));

  UNPROTECT(2);

  return length;
}


// generator source end: Get_region
// generator source start: Is_sorted
int lazyvec_ALTREP_TYPE_Is_sorted_method(SEXP x)
{
  // custom payload
  SEXP user_data = PROTECT(LAZYVEC_USER_DATA(x));
  
  // calling environment
  SEXP calling_env = PROTECT(LAZYVEC_PARENT_ENV(x));
  
  // length listener method
  SEXP is_sorted_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(x), LAZYVEC_METHOD_IS_SORTED));
  
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
  SEXP calling_env = PROTECT(LAZYVEC_PARENT_ENV(x));

  // length listener method
  SEXP no_na_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(x), LAZYVEC_METHOD_NO_NA));

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
  SEXP calling_env = PROTECT(LAZYVEC_PARENT_ENV(x));
  
  // length listener method
  SEXP sum_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(x), LAZYVEC_METHOD_SUM));
  
  // na_rm argument
  SEXP na_rm_arg = PROTECT(Rf_ScalarInteger(na_rm));
  
  // ALTREP override
  // should return a length 1 vector containing the element
  SEXP custom_element = PROTECT(call_dual_r_interface(sum_listener, user_data, na_rm_arg, calling_env));
  
  UNPROTECT(5);  // last PROTECT could be removed
  
  return custom_element;
}


// generator source end: Sum
// generator source start: Min
SEXP lazyvec_ALTREP_TYPE_Min_method(SEXP x, Rboolean na_rm)
{
  // custom payload
  SEXP user_data = PROTECT(LAZYVEC_USER_DATA(x));
  
  // calling environment
  SEXP calling_env = PROTECT(LAZYVEC_PARENT_ENV(x));
  
  // length listener method
  SEXP min_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(x), LAZYVEC_METHOD_MIN));
  
  // na_rm argument
  SEXP na_rm_arg = PROTECT(Rf_ScalarInteger(na_rm));
  
  // ALTREP override
  // should return a length 1 vector containing the element
  SEXP custom_element = PROTECT(call_dual_r_interface(min_listener, user_data, na_rm_arg, calling_env));
  
  UNPROTECT(5);  // last PROTECT could be removed
  
  return custom_element;
}


// generator source end: Min
// generator source start: Max
SEXP lazyvec_ALTREP_TYPE_Max_method(SEXP x, Rboolean na_rm)
{
  // custom payload
  SEXP user_data = PROTECT(LAZYVEC_USER_DATA(x));
  
  // calling environment
  SEXP calling_env = PROTECT(LAZYVEC_PARENT_ENV(x));
  
  // length listener method
  SEXP max_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(x), LAZYVEC_METHOD_MAX));
  
  // na_rm argument
  SEXP na_rm_arg = PROTECT(Rf_ScalarInteger(na_rm));
  
  // ALTREP override
  // should return a length 1 vector containing the element
  SEXP custom_element = PROTECT(call_dual_r_interface(max_listener, user_data, na_rm_arg, calling_env));
  
  UNPROTECT(5);  // last PROTECT could be removed
  
  return custom_element;
}


// generator source end: Max
// generator source start: Duplicate_
SEXP lazyvec_ALTREP_TYPE_Duplicate_method(SEXP sx, Rboolean deep)
{
  SEXP result_duplicate = PROTECT(ALTREP_DUPLICATE(LAZYVEC_PAYLOAD(sx), deep));
  
  // // retrieve duplicateEX listener method
  // SEXP duplicate_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(sx), LAZYVEC_METHOD_DUPLICATE));
  // 
  // if (result_duplicate == NULL)
  // {
  //   // call listener with SEXP result
  //   call_r_interface(duplicate_listener, R_NilValue, LAZYVEC_PARENT_ENV(sx));
  //   UNPROTECT(2);
  // 
  //   return result_duplicate;
  // }
  // 
  // // call listener with SEXP result
  // call_r_interface(duplicate_listener, result_duplicate, LAZYVEC_PARENT_ENV(sx));
  // UNPROTECT(2);

  UNPROTECT(1);
  
  return result_duplicate;
}


// generator source end: Duplicate_
// generator source start: DuplicateEX
SEXP lazyvec_ALTREP_TYPE_DuplicateEX_method(SEXP sx, Rboolean deep)
{
  SEXP result_duplicate_ex = PROTECT(ALTREP_DUPLICATE_EX(LAZYVEC_PAYLOAD(sx), deep));

  // retrieve duplicateEX listener method
  SEXP duplicate_ex_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(sx), LAZYVEC_METHOD_DUPLICATE_EX));

  if (result_duplicate_ex == NULL)
  { 
    // call listener with SEXP result
    call_r_interface(duplicate_ex_listener, R_NilValue, LAZYVEC_PARENT_ENV(sx));
    UNPROTECT(2);

    return result_duplicate_ex;
  }

  // call listener with SEXP result
  call_r_interface(duplicate_ex_listener, result_duplicate_ex, LAZYVEC_PARENT_ENV(sx));
  UNPROTECT(2);

  return result_duplicate_ex;
}


// generator source end: DuplicateEX
// generator source start: Coerce
SEXP lazyvec_ALTREP_TYPE_Coerce_method(SEXP x, int type)
{
  // length listener method
  SEXP listener_coerce = VECTOR_ELT(LAZYVEC_LISTENERS(x), LAZYVEC_METHOD_COERCE);

  // use default coercion
  if (Rf_isNull(listener_coerce)) {
    return NULL;
  }

  return  NULL;
}


// generator source end: Coerce
// generator source start: Extract_subset
SEXP lazyvec_ALTREP_TYPE_Extract_subset_method(SEXP x, SEXP indx, SEXP call)
{
  // custom payload
  SEXP user_data = PROTECT(LAZYVEC_USER_DATA(x));
  
  // calling environment
  SEXP calling_env = PROTECT(LAZYVEC_PARENT_ENV(x));
  
  // length listener method
  SEXP listener_extract_subset = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(x), LAZYVEC_METHOD_EXTRACT_SUBSET));

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
  SEXP custom_elements = PROTECT(call_dual_r_interface(
    listener_extract_subset, user_data, indx, calling_env));

  UNPROTECT(4);  // last PROTECT could be removed
  
  return custom_elements;
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
