
#include "api_helpers.h"

#include <stdint.h>


// altrep integer class definition
static R_altrep_class_t altwrap_integer_class;


// [[Rcpp::export]]
SEXP construct_altrep_integer_wrapper(SEXP data)
{
  SEXP altrep_vec = R_new_altrep(altwrap_integer_class, data, NILSXP);

  return altrep_vec;
}


// There is no ALTREP_UNSERIALIZE method on Windows
// 
// static SEXP altwrap_integer_Unserialize_method(SEXP altwrap_class, SEXP state)
// {
//   SEXP unserialize_result = AL  ALTREP_U _INSPECT(ALTWRAP_PAYLOAD(x), pre, deep, pvec, subtree_method);
// 
//   // length listener method
//   SEXP inspect_listener = VECTOR_ELT(ALTWRAP_LISTENERS(x), LISTENER_INSPECT);
// 
//   // call listener with integer length result
//   // TODO: change to int64 result
//   call_r_interface(inspect_listener, Rf_ScalarInteger(inspect_result), ALTWRAP_PARENT_ENV(x));
// 
//   return inspect_result;
// }


// ALTREP_UNSERIALIZE_EX((SEXP info, SEXP state, SEXP attr, int objf, int levs)
// is not linking on linux
//
SEXP altwrap_integer_UnserializeEX_method(SEXP info, SEXP state, SEXP attr, int objf, int levs)
{
  return ALTREP_UNSERIALIZE_EX(info, state, attr, objf, levs);

  // SEXP payload = PROTECT(ALTWRAP_PAYLOAD(x));

  // get attributes from original altrep object
  // SEXP payload_attr = PROTECT(ATTRIB(payload));
  // int payload_objf = OBJECT(payload);
  // int payload_levs = LEVELS(payload);

  // UNPROTECT(2);

  // SEXP unserialize_ex_result = PROTECT(ALTREP_UNSERIALIZE_EX(ALTWRAP_PAYLOAD(x), state, attr, objf, levs));
  // return ALTREP_UNSERIALIZE_EX(payload, state, payload_attr, payload_objf, payload_levs);

  // SEXP arguments = PROTECT(Rf_allocVector(VECSXP, 5));

  // if (unserialize_ex_result == NULL)
  // {
  //   SET_VECTOR_ELT(arguments, 0, R_NilValue);
  // }
  // else
  // {
  //   SET_VECTOR_ELT(arguments, 0, unserialize_ex_result);
  // }
  // 
  // if (state == NULL)
  // {
  //   SET_VECTOR_ELT(arguments, 1, R_NilValue);
  // }
  // else
  // {
  //   SET_VECTOR_ELT(arguments, 1, state);
  // }
  // 
  // if (attr == NULL)
  // {
  //   SET_VECTOR_ELT(arguments, 2, R_NilValue);
  // }
  // else
  // {
  //   SET_VECTOR_ELT(arguments, 2, attr);
  // }
  // 
  // SET_VECTOR_ELT(arguments, 3, Rf_ScalarInteger(objf));
  // SET_VECTOR_ELT(arguments, 4, Rf_ScalarInteger(levs));

  // if (unserialize_ex_result == NULL) Rf_error("stop immediately!");

  // length listener method
  // SEXP unserialize_ex_listener = VECTOR_ELT(ALTWRAP_LISTENERS(x), LISTENER_UNSERIALIZE_EX);

  // call listener
  // call_r_interface(unserialize_ex_listener, arguments, ALTWRAP_PARENT_ENV(x));

  // UNPROTECT(2);

  // return unserialize_ex_result;
}


SEXP altwrap_integer_Serialized_state_method(SEXP x)
{
  SEXP serialized_state_result = PROTECT(ALTREP_SERIALIZED_STATE(ALTWRAP_PAYLOAD(x)));

  // length listener method
  SEXP serialized_state_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(x), LISTENER_SERIALIZED_STATE));

  if (serialized_state_result == NULL)
  {
    call_r_interface(serialized_state_listener, R_NilValue, ALTWRAP_PARENT_ENV(x));
    UNPROTECT(2);
    return serialized_state_result;
  }

  call_r_interface(serialized_state_listener, serialized_state_result, ALTWRAP_PARENT_ENV(x));
  UNPROTECT(2);
  return serialized_state_result;
}


Rboolean altwrap_integer_Inspect_method(SEXP x, int pre, int deep, int pvec,
  inspect_subtree_method subtree_method)
{
  Rboolean inspect_result = ALTREP_INSPECT(ALTWRAP_PAYLOAD(x), pre, deep, pvec, subtree_method);

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
  SEXP inspect_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(x), LISTENER_INSPECT));

  // call inspect listener
  call_r_interface(inspect_listener, arguments, ALTWRAP_PARENT_ENV(x));

  UNPROTECT(2);

  return inspect_result;
}


R_xlen_t altwrap_integer_Length_method(SEXP x)
{
  R_xlen_t length_result = ALTREP_LENGTH(ALTWRAP_PAYLOAD(x));

  SEXP arguments = PROTECT(Rf_allocVector(VECSXP, 2));
  SET_VECTOR_ELT(arguments, 0, ALTWRAP_METADATA(x));
  SET_VECTOR_ELT(arguments, 1, Rf_ScalarInteger(length_result));

  // length listener method
  SEXP length_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(x), LISTENER_LENGTH));

  // call listener with integer length result
  // TODO: change to int64 result
  call_r_interface(length_listener, arguments, ALTWRAP_PARENT_ENV(x));

  UNPROTECT(2);

  return length_result;
}


void* altwrap_integer_Dataptr_method(SEXP x, Rboolean writeable)
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
  SEXP dataptr_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(x), LISTENER_DATAPTR));

  // call listener with integer result
  call_r_interface(dataptr_listener, arguments, ALTWRAP_PARENT_ENV(x));

  UNPROTECT(2);  // arguments

  return pdata;
}


const void *altwrap_integer_Dataptr_or_null_method(SEXP x)
{
  const void* pdata_or_null = DATAPTR_OR_NULL(ALTWRAP_PAYLOAD(x));

  // dataptr_or_null listener method
  SEXP dataptr_or_null_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(x), LISTENER_DATAPTR_OR_NULL));

  int is_pointer = pdata_or_null == NULL;

  // call listener with integer result
  call_r_interface(dataptr_or_null_listener, Rf_ScalarLogical(is_pointer), ALTWRAP_PARENT_ENV(x));

  UNPROTECT(1);

  return pdata_or_null;
}


int altwrap_integer_Elt_method(SEXP sx, R_xlen_t i)
{
  int element = INTEGER_ELT(ALTWRAP_PAYLOAD(sx), i);

  // retrieve is_sorted listener method
  SEXP is_sorted_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), LISTENER_ELT));

  // call listener with integer result
  call_r_interface(is_sorted_listener, Rf_ScalarInteger(element), ALTWRAP_PARENT_ENV(sx));

  UNPROTECT(1);

  return element;
}


R_xlen_t altwrap_integer_Get_region_method(SEXP sx, R_xlen_t i, R_xlen_t n, int *buf)
{
  R_xlen_t length = INTEGER_GET_REGION(ALTWRAP_PAYLOAD(sx), i, n, buf);

  SEXP arguments = PROTECT(Rf_allocVector(INTSXP, 3));
  int* parguments = INTEGER(arguments);

  parguments[0] = (int)(i);
  parguments[1] = (int)(n);
  parguments[2] = (int)(length);

  // dataptr_or_null listener method
  SEXP get_region_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), LISTENER_GET_REGION));

  // call listener with integer result
  call_r_interface(get_region_listener, arguments, ALTWRAP_PARENT_ENV(sx));

  UNPROTECT(2);

  return length;
}


int altwrap_integer_Is_sorted_method(SEXP sx)
{
  int is_sorted = INTEGER_IS_SORTED(ALTWRAP_PAYLOAD(sx));

  // retrieve is_sorted listener method
  SEXP is_sorted_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), LISTENER_IS_SORTED));

  // call listener with integer result
  call_r_interface(is_sorted_listener, Rf_ScalarInteger(is_sorted), ALTWRAP_PARENT_ENV(sx));

  UNPROTECT(1);

  return is_sorted;
}


int altwrap_integer_No_NA_method(SEXP sx)
{
  int no_na = INTEGER_NO_NA(ALTWRAP_PAYLOAD(sx));

  // retrieve no_na listener method
  SEXP no_na_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), LISTENER_NO_NA));

  // call listener with integer result
  call_r_interface(no_na_listener, Rf_ScalarInteger(no_na), ALTWRAP_PARENT_ENV(sx));

  UNPROTECT(1);

  return no_na;
}

SEXP altwrap_integer_Sum_method(SEXP sx, Rboolean na_rm)
{
  SEXP sum = PROTECT(ALTINTEGER_SUM(ALTWRAP_PAYLOAD(sx), na_rm));

  // retrieve sum listener method
  SEXP sum_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), LISTENER_SUM));

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


SEXP altwrap_integer_Min_method(SEXP sx, Rboolean na_rm)
{
  SEXP result_min = PROTECT(ALTINTEGER_MIN(ALTWRAP_PAYLOAD(sx), na_rm));

  // retrieve sum listener method
  SEXP min_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), LISTENER_MIN));

  if (result_min == NULL)
  { 
    // call listener with SEXP result
    call_r_interface(min_listener, R_NilValue, ALTWRAP_PARENT_ENV(sx));
    UNPROTECT(2);

    return result_min;
  }

  // call listener with SEXP result
  call_r_interface(min_listener, result_min, ALTWRAP_PARENT_ENV(sx));
  UNPROTECT(2);

  return result_min;
}


SEXP altwrap_integer_Max_method(SEXP sx, Rboolean na_rm)
{
  SEXP result_max = PROTECT(ALTINTEGER_MAX(ALTWRAP_PAYLOAD(sx), na_rm));

  // retrieve sum listener method
  SEXP max_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), LISTENER_MAX));

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


SEXP altwrap_integer_DuplicateEX_method(SEXP sx, Rboolean deep)
{
  SEXP result_duplicate_ex = PROTECT(ALTREP_DUPLICATE_EX(ALTWRAP_PAYLOAD(sx), deep));

  // retrieve duplicateEX listener method
  SEXP duplicate_ex_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), LISTENER_DUPLICATE_EX));

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


SEXP altwrap_integer_Coerce_method(SEXP sx, int type)
{
  SEXP result_coerce = PROTECT(ALTREP_COERCE(ALTWRAP_PAYLOAD(sx), type));

  SEXP arguments = PROTECT(Rf_allocVector(VECSXP, 2));
  SET_VECTOR_ELT(arguments, 1, Rf_ScalarInteger(type));

  // retrieve coerce listener method
  SEXP coerce_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), LISTENER_COERCE));

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


SEXP altwrap_integer_Extract_subset_method(SEXP sx, SEXP indx, SEXP call)
{
  SEXP result_extract_subset = PROTECT(ALTVEC_EXTRACT_SUBSET(ALTWRAP_PAYLOAD(sx), indx, call));

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
  SEXP extract_subset_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), LISTENER_EXTRACT_SUBSET));

  // call listener with arguments and result
  call_r_interface(extract_subset_listener, arguments, ALTWRAP_PARENT_ENV(sx));

  UNPROTECT(3);

  return result_extract_subset;
}


// [[Rcpp::init]]
void register_altrep_integer_class(DllInfo *dll)
{
  altwrap_integer_class = R_make_altinteger_class("altwrap_integer", "lazyvec", dll);

  /* override ALTREP methods */
  CALL_METHOD_SETTER(altrep, integer, Serialized_state);
  CALL_METHOD_SETTER(altrep, integer, Inspect);
  CALL_METHOD_SETTER(altrep, integer, Length);
  CALL_METHOD_SETTER(altrep, integer, DuplicateEX);
  CALL_METHOD_SETTER(altrep, integer, Coerce);

  // CALL_METHOD_SETTER(altrep, integer, Unserialize);
  // CALL_METHOD_SETTER(altrep, integer, UnserializeEX);
  // CALL_METHOD_SETTER(altrep, Duplicate);  // not found

  /* override ALTVEC methods */
  CALL_METHOD_SETTER(altvec, integer, Dataptr);
  CALL_METHOD_SETTER(altvec, integer, Dataptr_or_null);
  CALL_METHOD_SETTER(altvec, integer, Extract_subset);

  /* override ALTINTEGER methods */
  CALL_METHOD_SETTER(altinteger, integer, Elt);
  CALL_METHOD_SETTER(altinteger, integer, Get_region);
  CALL_METHOD_SETTER(altinteger, integer, Is_sorted);
  CALL_METHOD_SETTER(altinteger, integer, No_NA);
  CALL_METHOD_SETTER(altinteger, integer, Sum);
  CALL_METHOD_SETTER(altinteger, integer, Min);
  CALL_METHOD_SETTER(altinteger, integer, Max);
}
