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
static R_altrep_class_t altwrap_ALTREP_TYPE_class;


// [[Rcpp::export]]
SEXP altrep_ALTREP_TYPE_wrapper(SEXP data)
{
  return R_new_altrep(altwrap_ALTREP_TYPE_class, data, NILSXP);
}


// generator source start: Unserialize
static SEXP altwrap_ALTREP_TYPE_Unserialize_method(SEXP altwrap_class, SEXP state)
{
  Rcpp::Environment pkgs = Rcpp::Environment::namespace_env("lazyvec");

  SEXP altrep_data1 = PROTECT(Rf_allocVector(VECSXP, 4));
  SET_VECTOR_ELT(altrep_data1, 0, VECTOR_ELT(state, 0));
  SET_VECTOR_ELT(altrep_data1, 1, VECTOR_ELT(state, 1));
  SET_VECTOR_ELT(altrep_data1, 2, VECTOR_ELT(state, 2));
  SET_VECTOR_ELT(altrep_data1, 3, pkgs);

  // unserialize listener method
  // SEXP unserialize_listener = PROTECT(VECTOR_ELT(VECTOR_ELT(state, 1), ALTREP_METHOD_UNSERIALIZE));
  
  // call_r_interface(unserialize_listener, state, ALTWRAP_PARENT_ENV(altrep_data1));

  // UNPROTECT(2);
  UNPROTECT(1);
  return altrep_ALTREP_TYPE_wrapper(altrep_data1);
}


// generator source end: Unserialize
// generator source start: UnserializeEX
SEXP altwrap_ALTREP_TYPE_UnserializeEX_method(SEXP altwrap_class, SEXP state, SEXP attr, int objf, int levs)
{
  Rcpp::Environment pkgs = Rcpp::Environment::namespace_env("lazyvec");

  // SEXP unserialize_ex_result = PROTECT(ALTREP_UNSERIALIZE_EX_PROXY(altwrap_class, state, attr, objf, levs));
  // SEXP info = PROTECT(ATTRIB(ALTREP_CLASS(VECTOR_ELT(state, 0))));

  SEXP altrep_data1 = PROTECT(Rf_allocVector(VECSXP, 5));
  SET_VECTOR_ELT(altrep_data1, 0, VECTOR_ELT(state, 0));
  SET_VECTOR_ELT(altrep_data1, 1, VECTOR_ELT(state, 1));
  SET_VECTOR_ELT(altrep_data1, 2, VECTOR_ELT(state, 2));
  SET_VECTOR_ELT(altrep_data1, 3, Rf_ScalarInteger(LAZYVEC_VERSION));
  SET_VECTOR_ELT(altrep_data1, 4, pkgs);
  
  // create a new wrapper using the current lazyvec implementation
  SEXP altwrap_integer = PROTECT(ALTVEC_WRAPPER(altrep_data1));

  // get current listeners
  SEXP listeners = PROTECT(ALTWRAP_LISTENERS(altwrap_integer));
  SET_VECTOR_ELT(altrep_data1, 1, listeners);

  // now use the (updated) listener to display info
  SEXP unserialize_ex_listener = PROTECT(VECTOR_ELT(listeners, ALTREP_METHOD_UNSERIALIZE_EX));
  
  SEXP altrep_info = PROTECT(Rf_allocVector(VECSXP, 5));
  SET_VECTOR_ELT(altrep_info, 0, sexp_or_null(altwrap_class));
  SET_VECTOR_ELT(altrep_info, 1, sexp_or_null(state));
  SET_VECTOR_ELT(altrep_info, 2, sexp_or_null(attr));
  SET_VECTOR_ELT(altrep_info, 3, Rf_ScalarInteger(objf));
  SET_VECTOR_ELT(altrep_info, 4, Rf_ScalarInteger(levs));
  
  call_r_interface(unserialize_ex_listener, altrep_info, pkgs);
  
  UNPROTECT(5);  // altrep_data1, altwrap_integer, unserialize_ex_listener, altrep_info, listeners
  
  return altwrap_integer;
}


// generator source end: UnserializeEX
// generator source start: Serialized_state
SEXP altwrap_ALTREP_TYPE_Serialized_state_method(SEXP x)
{
  SEXP serialized_state_result = PROTECT(ALTREP_SERIALIZED_STATE_PROXY(ALTWRAP_PAYLOAD(x)));
  
  // length listener method
  SEXP serialized_state_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(x), ALTREP_METHOD_SERIALIZED_STATE));

  // create serialization state
  SEXP serialized_state = PROTECT(Rf_allocVector(VECSXP, 5));
  SET_VECTOR_ELT(serialized_state, 0, ALTWRAP_PAYLOAD(x));
  SET_VECTOR_ELT(serialized_state, 1, ALTWRAP_LISTENERS(x));
  SET_VECTOR_ELT(serialized_state, 2, ALTWRAP_METADATA(x));
  SET_VECTOR_ELT(serialized_state, 3, ALTWRAP_VERSION(x));
  
  if (!serialized_state_result)
  {
    SET_VECTOR_ELT(serialized_state, 4, serialized_state_result);
    call_r_interface(serialized_state_listener, R_NilValue, ALTWRAP_PARENT_ENV(x));
  }
  else
  {
    SET_VECTOR_ELT(serialized_state, 4, R_NilValue);
    call_r_interface(serialized_state_listener, serialized_state_result, ALTWRAP_PARENT_ENV(x));
  }
  
  UNPROTECT(3);
  
  return serialized_state;
}


// generator source end: Serialized_state
// generator source start: Inspect
Rboolean altwrap_ALTREP_TYPE_Inspect_method(SEXP x, int pre, int deep, int pvec,
  inspect_subtree_method subtree_method)
{
  Rboolean inspect_result = ALTREP_INSPECT_PROXY(ALTWRAP_PAYLOAD(x), pre, deep, pvec, subtree_method);

  SEXP arguments = PROTECT(Rf_allocVector(VECSXP, 4));

  SET_VECTOR_ELT(arguments, 0, Rf_ScalarInteger(inspect_result));
  SET_VECTOR_ELT(arguments, 1, Rf_ScalarInteger(pre));
  SET_VECTOR_ELT(arguments, 2, Rf_ScalarInteger(deep));
  SET_VECTOR_ELT(arguments, 3, Rf_ScalarInteger(pvec));

  // length listener method
  SEXP inspect_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(x), ALTREP_METHOD_INSPECT));

  // call inspect listener
  call_r_interface(inspect_listener, arguments, ALTWRAP_PARENT_ENV(x));

  UNPROTECT(2);

  return inspect_result;
}


// generator source end: Inspect
// generator source start: Length
R_xlen_t altwrap_ALTREP_TYPE_Length_method(SEXP x)
{
  R_xlen_t length_result = ALTREP_LENGTH(ALTWRAP_PAYLOAD(x));

  SEXP arguments = PROTECT(Rf_allocVector(VECSXP, 2));
  SET_VECTOR_ELT(arguments, 0, ALTWRAP_METADATA(x));
  SET_VECTOR_ELT(arguments, 1, Rf_ScalarInteger(length_result));

  // length listener method
  SEXP length_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(x), ALTREP_METHOD_LENGTH));

  // call listener with integer length result
  // TODO: change to int64 result
  call_r_interface(length_listener, arguments, ALTWRAP_PARENT_ENV(x));

  UNPROTECT(2);

  return length_result;
}


// generator source end: Length
// generator source start: Dataptr
void* altwrap_ALTREP_TYPE_Dataptr_method(SEXP x, Rboolean writeable)
{
  // create structure with info
  SEXP arguments = PROTECT(Rf_allocVector(INTSXP, 3));

  int* parguments = INTEGER(arguments);
  void* pdata = ALTVEC_DATAPTR(ALTWRAP_PAYLOAD(x));

  intptr_t address = (intptr_t) pdata;

  parguments[0] = (int) ((address >> 32) & 0xffffffff);
  parguments[1] = (int) (address & 0xffffffff);
  parguments[2] = (int) writeable;

  // call listener with info

  // dataptr_or_null listener method
  SEXP dataptr_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(x), ALTREP_METHOD_DATAPTR));

  // call listener with integer result
  call_r_interface(dataptr_listener, arguments, ALTWRAP_PARENT_ENV(x));

  UNPROTECT(2);  // arguments

  return pdata;
}


// generator source end: Dataptr
// generator source start: Dataptr_or_null
const void *altwrap_ALTREP_TYPE_Dataptr_or_null_method(SEXP x)
{
  const void* pdata_or_null = DATAPTR_OR_NULL(ALTWRAP_PAYLOAD(x));
  int is_pointer = pdata_or_null == NULL;

  // dataptr_or_null listener method
  SEXP dataptr_or_null_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(x), ALTREP_METHOD_DATAPTR_OR_NULL));

  SEXP arguments = PROTECT(Rf_allocVector(VECSXP, 2));
  SET_VECTOR_ELT(arguments, 0, ALTWRAP_METADATA(x));
  SET_VECTOR_ELT(arguments, 1, Rf_ScalarLogical(is_pointer));
  
  // call listener with integer result
  call_r_interface(dataptr_or_null_listener, arguments, ALTWRAP_PARENT_ENV(x));

  UNPROTECT(2);

  return pdata_or_null;
}


// generator source end: Dataptr_or_null
// generator source start: Elt
CPP_TYPE altwrap_ALTREP_TYPE_Elt_method(SEXP sx, R_xlen_t i)
{
  CPP_TYPE element = TYPE_METHOD_ELT(ALTWRAP_PAYLOAD(sx), i);

  // retrieve is_sorted listener method
  SEXP elt_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), ALTREP_METHOD_ELT));

  // arguments vector
  SEXP arguments = PROTECT(Rf_allocVector(VECSXP, 2));
  SET_VECTOR_ELT(arguments, 0, ALTWRAP_METADATA(sx));
  SET_VECTOR_ELT(arguments, 1, RF_SCALAR_TYPE(element));

  // call listener with result with the correct ALTREP type
  call_r_interface(elt_listener, arguments, ALTWRAP_PARENT_ENV(sx));

  UNPROTECT(2);

  return element;
}


// generator source end: Elt
// generator source start: Get_region
R_xlen_t altwrap_ALTREP_TYPE_Get_region_method(SEXP sx, R_xlen_t i, R_xlen_t n, CPP_TYPE *buf)
{
  R_xlen_t length = TYPE_METHOD_GET_REGION(ALTWRAP_PAYLOAD(sx), i, n, buf);

  SEXP arguments = PROTECT(Rf_allocVector(VECSXP, 4));
  SET_VECTOR_ELT(arguments, 0, ALTWRAP_METADATA(sx));
  SET_VECTOR_ELT(arguments, 1, Rf_ScalarInteger(i));
  SET_VECTOR_ELT(arguments, 2, Rf_ScalarInteger(n));
  SET_VECTOR_ELT(arguments, 3, Rf_ScalarInteger(length));

  // dataptr_or_null listener method
  SEXP get_region_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), ALTREP_METHOD_GET_REGION));

  // call listener with integer result
  call_r_interface(get_region_listener, arguments, ALTWRAP_PARENT_ENV(sx));

  UNPROTECT(2);

  return length;
}


// generator source end: Get_region
// generator source start: Is_sorted
int altwrap_ALTREP_TYPE_Is_sorted_method(SEXP sx)
{
  int is_sorted = TYPE_METHOD_IS_SORTED(ALTWRAP_PAYLOAD(sx));

  // retrieve is_sorted listener method
  SEXP is_sorted_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), ALTREP_METHOD_IS_SORTED));

  // call listener with integer result
  call_r_interface(is_sorted_listener, Rf_ScalarInteger(is_sorted), ALTWRAP_PARENT_ENV(sx));

  UNPROTECT(1);

  return is_sorted;
}


// generator source end: Is_sorted
// generator source start: No_NA
int altwrap_ALTREP_TYPE_No_NA_method(SEXP sx)
{
  int no_na = TYPE_METHOD_NO_NA(ALTWRAP_PAYLOAD(sx));

  // retrieve no_na listener method
  SEXP no_na_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), ALTREP_METHOD_NO_NA));

  // call listener with integer result
  call_r_interface(no_na_listener, Rf_ScalarInteger(no_na), ALTWRAP_PARENT_ENV(sx));

  UNPROTECT(1);

  return no_na;
}


// generator source end: No_NA
// generator source start: Sum
SEXP altwrap_ALTREP_TYPE_Sum_method(SEXP sx, Rboolean na_rm)
{
  SEXP sum = PROTECT(ALTTYPE_METHOD_SUM(ALTWRAP_PAYLOAD(sx), na_rm));

  // retrieve sum listener method
  SEXP sum_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), ALTREP_METHOD_SUM));

  SEXP arguments = PROTECT(Rf_allocVector(VECSXP, 2));
  SET_VECTOR_ELT(arguments, 1, Rf_ScalarInteger(na_rm));

  if (sum == NULL)
  {
    SET_VECTOR_ELT(arguments, 0, R_NilValue);

    // call listener with integer result
    call_r_interface(sum_listener, arguments, ALTWRAP_PARENT_ENV(sx));

    UNPROTECT(3);

    return sum;
  }

  SET_VECTOR_ELT(arguments, 0, sum);

  // call listener with integer result
  call_r_interface(sum_listener, arguments, ALTWRAP_PARENT_ENV(sx));

  UNPROTECT(3);

  return sum;
}


// generator source end: Sum
// generator source start: Min
SEXP altwrap_ALTREP_TYPE_Min_method(SEXP sx, Rboolean na_rm)
{
  SEXP result_min = PROTECT(ALTTYPE_METHOD_MIN(ALTWRAP_PAYLOAD(sx), na_rm));

  SEXP arguments = PROTECT(Rf_allocVector(VECSXP, 2));
  SET_VECTOR_ELT(arguments, 0, ALTWRAP_METADATA(sx));
  SET_VECTOR_ELT(arguments, 1, result_min == NULL ? R_NilValue : result_min);
  
  // retrieve sum listener method
  SEXP min_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), ALTREP_METHOD_MIN));

  // call listener with SEXP result
  call_r_interface(min_listener, arguments, ALTWRAP_PARENT_ENV(sx));
  UNPROTECT(3);

  return result_min;
}


// generator source end: Min
// generator source start: Max
SEXP altwrap_ALTREP_TYPE_Max_method(SEXP sx, Rboolean na_rm)
{
  SEXP result_max = PROTECT(ALTTYPE_METHOD_MAX(ALTWRAP_PAYLOAD(sx), na_rm));

  // retrieve sum listener method
  SEXP max_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), ALTREP_METHOD_MAX));

  if (result_max == NULL)
  { 
    // call listener with SEXP result
    call_r_interface(max_listener, R_NilValue, ALTWRAP_PARENT_ENV(sx));
    UNPROTECT(2);

    return result_max;
  }

  // call listener with SEXP result
  call_r_interface(max_listener, result_max, ALTWRAP_PARENT_ENV(sx));
  UNPROTECT(2);

  return result_max;
}


// generator source end: Max
// generator source start: Duplicate_
SEXP altwrap_ALTREP_TYPE_Duplicate_method(SEXP sx, Rboolean deep)
{
  SEXP result_duplicate = PROTECT(ALTREP_DUPLICATE(ALTWRAP_PAYLOAD(sx), deep));
  
  // retrieve duplicateEX listener method
  SEXP duplicate_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), ALTREP_METHOD_DUPLICATE));
  
  if (result_duplicate == NULL)
  { 
    // call listener with SEXP result
    call_r_interface(duplicate_listener, R_NilValue, ALTWRAP_PARENT_ENV(sx));
    UNPROTECT(2);
    
    return result_duplicate;
  }
  
  // call listener with SEXP result
  call_r_interface(duplicate_listener, result_duplicate, ALTWRAP_PARENT_ENV(sx));
  UNPROTECT(2);
  
  return result_duplicate;
}


// generator source end: Duplicate_
// generator source start: DuplicateEX
SEXP altwrap_ALTREP_TYPE_DuplicateEX_method(SEXP sx, Rboolean deep)
{
  SEXP result_duplicate_ex = PROTECT(ALTREP_DUPLICATE_EX_PROXY(ALTWRAP_PAYLOAD(sx), deep));

  // retrieve duplicateEX listener method
  SEXP duplicate_ex_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), ALTREP_METHOD_DUPLICATE_EX));

  if (result_duplicate_ex == NULL)
  { 
    // call listener with SEXP result
    call_r_interface(duplicate_ex_listener, R_NilValue, ALTWRAP_PARENT_ENV(sx));
    UNPROTECT(2);

    return result_duplicate_ex;
  }

  // call listener with SEXP result
  call_r_interface(duplicate_ex_listener, result_duplicate_ex, ALTWRAP_PARENT_ENV(sx));
  UNPROTECT(2);

  return result_duplicate_ex;
}


// generator source end: DuplicateEX
// generator source start: Coerce
SEXP altwrap_ALTREP_TYPE_Coerce_method(SEXP sx, int type)
{
  SEXP result_coerce = PROTECT(ALTREP_COERCE_PROXY(ALTWRAP_PAYLOAD(sx), type));

  SEXP arguments = PROTECT(Rf_allocVector(VECSXP, 2));
  SET_VECTOR_ELT(arguments, 1, Rf_ScalarInteger(type));

  // retrieve coerce listener method
  SEXP coerce_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), ALTREP_METHOD_COERCE));

  if (result_coerce == NULL)
  {
    SET_VECTOR_ELT(arguments, 0, R_NilValue);

    // call listener with integer result
    call_r_interface(coerce_listener, arguments, ALTWRAP_PARENT_ENV(sx));

    UNPROTECT(3);
    return result_coerce;
  }

  SET_VECTOR_ELT(arguments, 0, result_coerce);

  // call listener with integer result
  call_r_interface(coerce_listener, arguments, ALTWRAP_PARENT_ENV(sx));

  UNPROTECT(3);
  return result_coerce;
}


// generator source end: Coerce
// generator source start: Extract_subset
SEXP altwrap_ALTREP_TYPE_Extract_subset_method(SEXP sx, SEXP indx, SEXP call)
{
  SEXP result_extract_subset = PROTECT(ALTVEC_EXTRACT_SUBSET_PROXY(ALTWRAP_PAYLOAD(sx), indx, call));

  SEXP arguments = PROTECT(Rf_allocVector(VECSXP, 3));

  if (result_extract_subset == NULL)
  {
    SET_VECTOR_ELT(arguments, 0, R_NilValue);
  } else
  {
    SET_VECTOR_ELT(arguments, 0, result_extract_subset);
  }

  if (indx == NULL)
  {
    SET_VECTOR_ELT(arguments, 1, R_NilValue);
  } else
  {
    SET_VECTOR_ELT(arguments, 1, indx);
  }

  if (call == NULL)
  {
    SET_VECTOR_ELT(arguments, 2, R_NilValue);
  } else
  {
    SET_VECTOR_ELT(arguments, 2, call);
  }

  // retrieve coerce listener method
  SEXP extract_subset_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), ALTREP_METHOD_EXTRACT_SUBSET));

  // call listener with arguments and result
  call_r_interface(extract_subset_listener, arguments, ALTWRAP_PARENT_ENV(sx));

  UNPROTECT(3);

  return result_extract_subset;
}


// generator source end: Extract_subset
// [[Rcpp::init]]
void register_altrep_ALTREP_TYPE_class(DllInfo *dll)
{
  altwrap_ALTREP_TYPE_class = R_make_altALTREP_TYPE_class("altwrap_ALTREP_TYPE", "lazyvec", dll);

  /* override ALTREP methods */
  CALL_METHOD_SETTER(altrep, ALTREP_TYPE, UnserializeEX);     // codeline: UnserializeEX
  CALL_METHOD_SETTER(altrep, ALTREP_TYPE, Unserialize);       // codeline: Unserialize
  CALL_METHOD_SETTER(altrep, ALTREP_TYPE, Serialized_state);  // codeline: Serialized_state
  CALL_METHOD_SETTER(altrep, ALTREP_TYPE, DuplicateEX);       // codeline: DuplicateEx
  CALL_METHOD_SETTER(altrep, ALTREP_TYPE, Duplicate);         // codeline: Duplicate_
  CALL_METHOD_SETTER(altrep, ALTREP_TYPE, Coerce);            // codeline: Coerce
  CALL_METHOD_SETTER(altrep, ALTREP_TYPE, Inspect);           // codeline: Inspect
  CALL_METHOD_SETTER(altrep, ALTREP_TYPE, Length);            // codeline: Length

  /* override ALTVEC methods */
  CALL_METHOD_SETTER(altvec, ALTREP_TYPE, Dataptr);           // codeline: Dataptr
  CALL_METHOD_SETTER(altvec, ALTREP_TYPE, Dataptr_or_null);   // codeline: Dataptr_or_null
  CALL_METHOD_SETTER(altvec, ALTREP_TYPE, Extract_subset);    // codeline: Extract_subset

  /* override specific type methods */
  CALL_METHOD_SETTER(ALT_METHOD, ALTREP_TYPE, Elt);           // codeline: Elt
  CALL_METHOD_SETTER(ALT_METHOD, ALTREP_TYPE, Get_region);    // codeline: Get_region
  CALL_METHOD_SETTER(ALT_METHOD, ALTREP_TYPE, Is_sorted);     // codeline: Is_sorted
  CALL_METHOD_SETTER(ALT_METHOD, ALTREP_TYPE, No_NA);         // codeline: No_NA
  CALL_METHOD_SETTER(ALT_METHOD, ALTREP_TYPE, Sum);           // codeline: Sum
  CALL_METHOD_SETTER(ALT_METHOD, ALTREP_TYPE, Min);           // codeline: Min
  CALL_METHOD_SETTER(ALT_METHOD, ALTREP_TYPE, Max);           // codeline: Max
}
