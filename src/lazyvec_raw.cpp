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
static R_altrep_class_t lazyvec_raw_class;


// [[Rcpp::export]]
SEXP lazyvec_raw_wrapper(SEXP data)
{
  return R_new_altrep(lazyvec_raw_class, data, NILSXP);
}


//
// On Win there is no Unserialize method exported, check with R-dev!
//
static SEXP lazyvec_raw_Unserialize_method(SEXP lazyvec_class, SEXP state)
{
  Rcpp::Environment pkgs = Rcpp::Environment::namespace_env("lazyvec");

  SEXP altrep_data1 = PROTECT(Rf_allocVector(VECSXP, 4));
  SET_VECTOR_ELT(altrep_data1, 0, VECTOR_ELT(state, 0));
  SET_VECTOR_ELT(altrep_data1, 1, VECTOR_ELT(state, 1));
  SET_VECTOR_ELT(altrep_data1, 2, VECTOR_ELT(state, 2));
  SET_VECTOR_ELT(altrep_data1, 3, pkgs);

  // unserialize listener method
  // SEXP unserialize_listener = PROTECT(VECTOR_ELT(VECTOR_ELT(state, 1), ALTREP_METHOD_UNSERIALIZE));
  
  // call_r_interface(unserialize_listener, state, LAZYVEC_PARENT_ENV(altrep_data1));

  // UNPROTECT(2);
  UNPROTECT(1);
  return lazyvec_raw_wrapper(altrep_data1);
}


//
// ALTREP_UNSERIALIZE_EX is not linking on linux due to uncommented hidden_attribute
// in declaration
//
SEXP lazyvec_raw_UnserializeEX_method(SEXP info, SEXP state, SEXP attr, int objf, int levs)
{
  // return ALTREP_UNSERIALIZE_EX(info, state, attr, objf, levs);

  Rcpp::Environment pkgs = Rcpp::Environment::namespace_env("lazyvec");

  SEXP altrep_data1 = PROTECT(Rf_allocVector(VECSXP, 4));
  SET_VECTOR_ELT(altrep_data1, 0, VECTOR_ELT(state, 0));
  SET_VECTOR_ELT(altrep_data1, 1, VECTOR_ELT(state, 1));
  SET_VECTOR_ELT(altrep_data1, 2, VECTOR_ELT(state, 2));
  SET_VECTOR_ELT(altrep_data1, 3, pkgs);

  // SEXP unserialize_ex_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(altrep_data1),
  //   ALTREP_METHOD_UNSERIALIZE_EX));

  // Rf_PrintValue(state);
  // call_r_interface(unserialize_ex_listener, state, LAZYVEC_PARENT_ENV(altrep_data1));
  
  // UNPROTECT(2);
  UNPROTECT(1);
  return lazyvec_raw_wrapper(altrep_data1);
}


SEXP lazyvec_raw_Serialized_state_method(SEXP x)
{
  SEXP serialized_state_result = PROTECT(ALTREP_SERIALIZED_STATE(LAZYVEC_PAYLOAD(x)));

  // length listener method
  SEXP serialized_state_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(x), ALTREP_METHOD_SERIALIZED_STATE));

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


Rboolean lazyvec_raw_Inspect_method(SEXP x, int pre, int deep, int pvec,
  inspect_subtree_method subtree_method)
{
  Rboolean inspect_result = ALTREP_INSPECT(LAZYVEC_PAYLOAD(x), pre, deep, pvec, subtree_method);

  SEXP arguments = PROTECT(Rf_allocVector(VECSXP, 5));

  if (x == NULL)
  {
    SET_VECTOR_ELT(arguments, 1, R_NilValue);
  }
  else
  {
    SET_VECTOR_ELT(arguments, 1, x);
  }

  SET_VECTOR_ELT(arguments, 0, Rf_ScalarInteger(inspect_result));
  SET_VECTOR_ELT(arguments, 2, Rf_ScalarInteger(pre));
  SET_VECTOR_ELT(arguments, 3, Rf_ScalarInteger(deep));
  SET_VECTOR_ELT(arguments, 4, Rf_ScalarInteger(pvec));

  // length listener method
  SEXP inspect_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(x), ALTREP_METHOD_INSPECT));

  // call inspect listener
  call_r_interface(inspect_listener, arguments, LAZYVEC_PARENT_ENV(x));

  UNPROTECT(2);

  return inspect_result;
}


R_xlen_t lazyvec_raw_Length_method(SEXP x)
{
  // custom payload
  SEXP user_data = PROTECT(LAZYVEC_USER_DATA(x));

  // calling environment
  SEXP calling_env = PROTECT(LAZYVEC_PARENT_ENV(x));
  
  // length listener method
  SEXP length_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(x), ALTREP_METHOD_LENGTH));

  // call ALTREP override
  SEXP custom_length = PROTECT(call_r_interface(length_listener, user_data, calling_env));

  // type and length checking is done on R side
  R_xlen_t res_length = (R_xlen_t)(*INTEGER(custom_length));
  
  UNPROTECT(4);

  return res_length;
}


void* lazyvec_raw_Dataptr_method(SEXP x, Rboolean writeable)
{
  // custom payload
  SEXP user_data = PROTECT(LAZYVEC_USER_DATA(x));

  // calling environment
  SEXP calling_env = PROTECT(LAZYVEC_PARENT_ENV(x));

  // length listener method
  SEXP full_vector_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(x), ALTREP_METHOD_DATAPTR));

  SEXP stored_full_vec = LAZYVEC_FULL_VEC(x);

  // return dataptr of stored vector
  if (!Rf_isNull(stored_full_vec)) {
    Rprintf("not is_null");
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


const void *lazyvec_raw_Dataptr_or_null_method(SEXP x)
{
  const void* pdata_or_null = DATAPTR_OR_NULL(LAZYVEC_PAYLOAD(x));
  int is_pointer = pdata_or_null == NULL;

  // dataptr_or_null listener method
  SEXP dataptr_or_null_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(x), ALTREP_METHOD_DATAPTR_OR_NULL));

  SEXP arguments = PROTECT(Rf_allocVector(VECSXP, 2));
  SET_VECTOR_ELT(arguments, 0, LAZYVEC_METADATA(x));
  SET_VECTOR_ELT(arguments, 1, Rf_ScalarLogical(is_pointer));

  // call listener with integer result
  // call_r_interface(dataptr_or_null_listener, arguments, LAZYVEC_PARENT_ENV(x));

  UNPROTECT(2);

  return pdata_or_null;
}


Rbyte lazyvec_raw_Elt_method(SEXP x, R_xlen_t i)
{
  // custom payload
  SEXP user_data = PROTECT(LAZYVEC_USER_DATA(x));
  
  // calling environment
  SEXP calling_env = PROTECT(LAZYVEC_PARENT_ENV(x));
  
  // length listener method
  SEXP elt_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(x), ALTREP_METHOD_ELT));

  // i argument
  SEXP i_arg = PROTECT(Rf_ScalarInteger((int)(i + 1)));
  
  // ALTREP override
  // should return a length 1 vector containing the element
  SEXP custom_element = PROTECT(call_dual_r_interface(elt_listener, user_data, i_arg, calling_env));

  // convert to Rbyte
  Rbyte element = SEXP_TO_RBYTE(custom_element);

  UNPROTECT(5);
  
  return element;
}


R_xlen_t lazyvec_raw_Get_region_method(SEXP sx, R_xlen_t i, R_xlen_t n, Rbyte *buf)
{
  R_xlen_t length = RAW_GET_REGION(LAZYVEC_PAYLOAD(sx), i, n, buf);

  SEXP arguments = PROTECT(Rf_allocVector(VECSXP, 4));
  SET_VECTOR_ELT(arguments, 0, LAZYVEC_METADATA(sx));
  SET_VECTOR_ELT(arguments, 1, Rf_ScalarInteger(i));
  SET_VECTOR_ELT(arguments, 2, Rf_ScalarInteger(n));
  SET_VECTOR_ELT(arguments, 3, Rf_ScalarInteger(length));

  // dataptr_or_null listener method
  SEXP get_region_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(sx), ALTREP_METHOD_GET_REGION));

  // call listener with integer result
  call_r_interface(get_region_listener, arguments, LAZYVEC_PARENT_ENV(sx));

  UNPROTECT(2);

  return length;
}


SEXP lazyvec_raw_DuplicateEX_method(SEXP sx, Rboolean deep)
{
  SEXP result_duplicate_ex = PROTECT(ALTREP_DUPLICATE_EX(LAZYVEC_PAYLOAD(sx), deep));

  // retrieve duplicateEX listener method
  SEXP duplicate_ex_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(sx), ALTREP_METHOD_DUPLICATE_EX));

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


SEXP lazyvec_raw_Coerce_method(SEXP sx, int type)
{
  SEXP result_coerce = PROTECT(ALTREP_COERCE(LAZYVEC_PAYLOAD(sx), type));

  SEXP arguments = PROTECT(Rf_allocVector(VECSXP, 2));
  SET_VECTOR_ELT(arguments, 1, Rf_ScalarInteger(type));

  // retrieve coerce listener method
  SEXP coerce_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(sx), ALTREP_METHOD_COERCE));

  if (result_coerce == NULL)
  {
    SET_VECTOR_ELT(arguments, 0, R_NilValue);

    // call listener with integer result
    call_r_interface(coerce_listener, arguments, LAZYVEC_PARENT_ENV(sx));

    UNPROTECT(3);
    return result_coerce;
  }

  SET_VECTOR_ELT(arguments, 0, result_coerce);

  // call listener with integer result
  call_r_interface(coerce_listener, arguments, LAZYVEC_PARENT_ENV(sx));

  UNPROTECT(3);
  return result_coerce;
}


SEXP lazyvec_raw_Extract_subset_method(SEXP sx, SEXP indx, SEXP call)
{
  SEXP result_extract_subset = PROTECT(ALTVEC_EXTRACT_SUBSET(LAZYVEC_PAYLOAD(sx), indx, call));

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
  SEXP extract_subset_listener = PROTECT(VECTOR_ELT(LAZYVEC_LISTENERS(sx), ALTREP_METHOD_EXTRACT_SUBSET));

  // call listener with arguments and result
  call_r_interface(extract_subset_listener, arguments, LAZYVEC_PARENT_ENV(sx));

  UNPROTECT(3);

  return result_extract_subset;
}


// [[Rcpp::init]]
void register_lazyvec_raw_class(DllInfo *dll)
{
  lazyvec_raw_class = R_make_altraw_class("lazyvec_raw", "lazyvec", dll);

  /* override ALTREP methods */
  CALL_LAZYVEC_SETTER(altrep, raw, UnserializeEX);     // codeline: UnserializeEX
  CALL_LAZYVEC_SETTER(altrep, raw, Unserialize);       // codeline: Unserialize
  CALL_LAZYVEC_SETTER(altrep, raw, Serialized_state);  // codeline: Serialized_state
  CALL_LAZYVEC_SETTER(altrep, raw, DuplicateEX);       // codeline: DuplicateEx
  CALL_LAZYVEC_SETTER(altrep, raw, Coerce);            // codeline: Coerce
  CALL_LAZYVEC_SETTER(altrep, raw, Inspect);           // codeline: Inspect
  CALL_LAZYVEC_SETTER(altrep, raw, Length);            // codeline: Length

  /* override ALTVEC methods */
  CALL_LAZYVEC_SETTER(altvec, raw, Dataptr);           // codeline: Dataptr
  CALL_LAZYVEC_SETTER(altvec, raw, Dataptr_or_null);   // codeline: Dataptr_or_null
  CALL_LAZYVEC_SETTER(altvec, raw, Extract_subset);    // codeline: Extract_subset

  /* override specific type methods */
  CALL_LAZYVEC_SETTER(altraw, raw, Elt);           // codeline: Elt
  CALL_LAZYVEC_SETTER(altraw, raw, Get_region);    // codeline: Get_region
}
