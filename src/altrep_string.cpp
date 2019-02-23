
#include <Rcpp.h>

#include "api_helpers.h"
#include <stdint.h>


// altrep integer class definition
static R_altrep_class_t altwrap_string_class;


// [[Rcpp::export]]
SEXP altrep_string_wrapper(SEXP data)
{
  return R_new_altrep(altwrap_string_class, data, NILSXP);
}


//
// On Win there is no Unserialize method exported, check with R-dev!
//
static SEXP altwrap_string_Unserialize_method(SEXP altwrap_class, SEXP state)
{
  SEXP altrep_data1 = PROTECT(Rf_allocVector(VECSXP, 4));
  SET_VECTOR_ELT(altrep_data1, 0, VECTOR_ELT(state, 0));
  SET_VECTOR_ELT(altrep_data1, 1, VECTOR_ELT(state, 1));
  SET_VECTOR_ELT(altrep_data1, 2, VECTOR_ELT(state, 2));
  SET_VECTOR_ELT(altrep_data1, 3, Rcpp::Environment::global_env());

  // unserialize listener method
  // SEXP unserialize_listener = PROTECT(VECTOR_ELT(VECTOR_ELT(state, 1), LISTENER_UNSERIALIZE));
  
  // call_r_interface(unserialize_listener, state, ALTWRAP_PARENT_ENV(altrep_data1));

  // UNPROTECT(2);
  UNPROTECT(2);
  return altrep_string_wrapper(altrep_data1);
}


//
// ALTREP_UNSERIALIZE_EX is not linking on linux due to uncommented hidden_attribute
// in declaration
//
SEXP altwrap_string_UnserializeEX_method(SEXP info, SEXP state, SEXP attr, int objf, int levs)
{
  // return ALTREP_UNSERIALIZE_EX(info, state, attr, objf, levs);

  SEXP altrep_data1 = PROTECT(Rf_allocVector(VECSXP, 4));
  SET_VECTOR_ELT(altrep_data1, 0, VECTOR_ELT(state, 0));
  SET_VECTOR_ELT(altrep_data1, 1, VECTOR_ELT(state, 1));
  SET_VECTOR_ELT(altrep_data1, 2, VECTOR_ELT(state, 2));
  SET_VECTOR_ELT(altrep_data1, 3, Rcpp::Environment::global_env());
  
  // SEXP unserialize_ex_listener = PROTECT(VECTOR_ELT(VECTOR_ELT(state, 1), LISTENER_UNSERIALIZE_EX));

  Rf_PrintValue(state);
  // call_r_interface(unserialize_ex_listener, state, ALTWRAP_PARENT_ENV(altrep_data1));
  
  // UNPROTECT(2);
  UNPROTECT(2);
  return altrep_string_wrapper(altrep_data1);
  
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


SEXP altwrap_string_Serialized_state_method(SEXP x)
{
  SEXP serialized_state_result = PROTECT(ALTREP_SERIALIZED_STATE(ALTWRAP_PAYLOAD(x)));

  // length listener method
  SEXP serialized_state_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(x), LISTENER_SERIALIZED_STATE));

  // create serialization state
  SEXP serialized_state = PROTECT(Rf_allocVector(VECSXP, 3));
  SET_VECTOR_ELT(serialized_state, 0, ALTWRAP_PAYLOAD(x));
  SET_VECTOR_ELT(serialized_state, 1, ALTWRAP_LISTENERS(x));
  SET_VECTOR_ELT(serialized_state, 2, ALTWRAP_METADATA(x));
  
  if (serialized_state_result == NULL)
  {
    call_r_interface(serialized_state_listener, R_NilValue, ALTWRAP_PARENT_ENV(x));
  }
  else
  {
    call_r_interface(serialized_state_listener, serialized_state_result, ALTWRAP_PARENT_ENV(x));
  }

  UNPROTECT(3);

  return serialized_state;
}


Rboolean altwrap_string_Inspect_method(SEXP x, int pre, int deep, int pvec,
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


R_xlen_t altwrap_string_Length_method(SEXP x)
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


void* altwrap_string_Dataptr_method(SEXP x, Rboolean writeable)
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


const void *altwrap_string_Dataptr_or_null_method(SEXP x)
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


SEXP altwrap_string_Elt_method(SEXP sx, R_xlen_t i)
{
  SEXP element = STRING_ELT(ALTWRAP_PAYLOAD(sx), i);

  // retrieve is_sorted listener method
  SEXP elt_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), LISTENER_ELT));

  // call listener with result with the correct ALTREP type
  call_r_interface(elt_listener, Rf_ScalarString(element), ALTWRAP_PARENT_ENV(sx));

  UNPROTECT(1);

  return element;
}


int altwrap_string_Is_sorted_method(SEXP sx)
{
  int is_sorted = STRING_IS_SORTED(ALTWRAP_PAYLOAD(sx));

  // retrieve is_sorted listener method
  SEXP is_sorted_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), LISTENER_IS_SORTED));

  // call listener with integer result
  call_r_interface(is_sorted_listener, Rf_ScalarInteger(is_sorted), ALTWRAP_PARENT_ENV(sx));

  UNPROTECT(1);

  return is_sorted;
}


int altwrap_string_No_NA_method(SEXP sx)
{
  int no_na = STRING_NO_NA(ALTWRAP_PAYLOAD(sx));

  // retrieve no_na listener method
  SEXP no_na_listener = PROTECT(VECTOR_ELT(ALTWRAP_LISTENERS(sx), LISTENER_NO_NA));

  // call listener with integer result
  call_r_interface(no_na_listener, Rf_ScalarInteger(no_na), ALTWRAP_PARENT_ENV(sx));

  UNPROTECT(1);

  return no_na;
}


SEXP altwrap_string_DuplicateEX_method(SEXP sx, Rboolean deep)
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


SEXP altwrap_string_Coerce_method(SEXP sx, int type)
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


SEXP altwrap_string_Extract_subset_method(SEXP sx, SEXP indx, SEXP call)
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
void register_altrep_string_class(DllInfo *dll)
{
  altwrap_string_class = R_make_altstring_class("altwrap_string", "lazyvec", dll);

  /* override ALTREP methods */
  CALL_METHOD_SETTER(altrep, string, UnserializeEX);     // codeline: UnserializeEX
  CALL_METHOD_SETTER(altrep, string, Unserialize);       // codeline: Unserialize
  CALL_METHOD_SETTER(altrep, string, Serialized_state);  // codeline: Serialized_state
  CALL_METHOD_SETTER(altrep, string, DuplicateEX);       // codeline: DuplicateEx
  CALL_METHOD_SETTER(altrep, string, Coerce);            // codeline: Coerce
  CALL_METHOD_SETTER(altrep, string, Inspect);           // codeline: Inspect
  CALL_METHOD_SETTER(altrep, string, Length);            // codeline: Length

  /* override ALTVEC methods */
  CALL_METHOD_SETTER(altvec, string, Dataptr);           // codeline: Dataptr
  CALL_METHOD_SETTER(altvec, string, Dataptr_or_null);   // codeline: Dataptr_or_null
  CALL_METHOD_SETTER(altvec, string, Extract_subset);    // codeline: Extract_subset

  /* override specific type methods */
  CALL_METHOD_SETTER(altstring, string, Elt);           // codeline: Elt
  CALL_METHOD_SETTER(altstring, string, Is_sorted);     // codeline: Is_sorted
  CALL_METHOD_SETTER(altstring, string, No_NA);         // codeline: No_NA
}
