
#include "api_helpers.h"


// altrep integer class definition
static R_altrep_class_t altwrap_integer_class;

// [[Rcpp::export]]
SEXP construct_altrep_wrapper(SEXP data)
{
  SEXP altrep_vec = R_new_altrep(altwrap_integer_class, data, NILSXP);

  return altrep_vec;
}

static SEXP altwrap_integer_Unserialize_method(SEXP altwrap_class, SEXP state)
{
  Rf_PrintValue(Rf_mkString("altwrap_Unserialize called"));

  return NULL;
}


static SEXP altwrap_integer_Serialized_state_method(SEXP x)
{
  Rf_PrintValue(Rf_mkString("altwrap_Serialized_state called, null returned"));

  // TODO: ALTREP_SERIALIZED_STATE currently not correctly linked on Linux
  return NULL;
  //  return ALTREP_SERIALIZED_STATE(ALTWRAP_PAYLOAD(x));
}


Rboolean altwrap_integer_Inspect_method(SEXP x, int pre, int deep, int pvec,
  void (*inspect_subtree)(SEXP, int, int, int))
{
  Rf_PrintValue(Rf_mkString("altwrap_Inspect start"));

  // TODO: ALTREP_INSPECT currently not correctly linked on Linux (not exported correctly by R?)
  return TRUE;
  //  return ALTREP_INSPECT(ALTWRAP_PAYLOAD(x), pre, deep, pvec, inspect_subtree);
}


static R_xlen_t altwrap_integer_Length_method(SEXP x)
{
  R_xlen_t length_result = ALTREP_LENGTH(ALTWRAP_PAYLOAD(x));

  // length listener method
  SEXP length_listener = VECTOR_ELT(ALTWRAP_LISTENERS(x), 0);

  // call listener with integer length result
  // TODO: change to int64 result
  call_r_interface(length_listener, Rf_ScalarInteger(length_result), ALTWRAP_PARENT_ENV(x));

  return length_result;
}


static void *altwrap_integer_Dataptr_method(SEXP x, Rboolean writeable)
{
  // create structure with info
  SEXP arguments = Rf_allocVector(INTSXP, 3);
  PROTECT(arguments);

  int* parguments = INTEGER(arguments);

  void* pdata = DATAPTR(ALTWRAP_PAYLOAD(x));

  intptr_t address = (intptr_t) pdata;

  parguments[0] = (int) ((address >> 32) & 0xffffffff);
  parguments[1] = (int) (address & 0xffffffff);
  parguments[2] = (int) writeable;

  // call listener with info

  // dataptr_or_null listener method
  SEXP dataptr_listener = VECTOR_ELT(ALTWRAP_LISTENERS(x), 4);

  // call listener with integer result
  call_r_interface(dataptr_listener, arguments, ALTWRAP_PARENT_ENV(x));

  UNPROTECT(1);  // arguments

  return pdata;
}


static const void *altwrap_integer_Dataptr_or_null_method(SEXP x)
{
  const void* pdata_or_null = DATAPTR_OR_NULL(ALTWRAP_PAYLOAD(x));

  // dataptr_or_null listener method
  SEXP dataptr_or_null_listener = VECTOR_ELT(ALTWRAP_LISTENERS(x), 1);

  int is_pointer = pdata_or_null == NULL;

  // call listener with integer result
  call_r_interface(dataptr_or_null_listener, Rf_ScalarLogical(is_pointer), ALTWRAP_PARENT_ENV(x));

  return pdata_or_null;
}


static int altwrap_integer_Elt_method(SEXP sx, R_xlen_t i)
{
  int element = INTEGER_ELT(ALTWRAP_PAYLOAD(sx), i);
  
  SEXP arguments = Rf_allocVector(INTSXP, 1);
  PROTECT(arguments);
  
  int* parguments = INTEGER(arguments);
  parguments[0] = (int)(element);
  
  // retrieve is_sorted listener method
  SEXP is_sorted_listener = VECTOR_ELT(ALTWRAP_LISTENERS(sx), 3);
  
  // call listener with integer result
  call_r_interface(is_sorted_listener, arguments, ALTWRAP_PARENT_ENV(sx));
  
  UNPROTECT(1);
  
  return element;
}


static R_xlen_t altwrap_integer_Get_region_method(SEXP sx, R_xlen_t i, R_xlen_t n, int *buf)
{
  R_xlen_t length = INTEGER_GET_REGION(ALTWRAP_PAYLOAD(sx), i, n, buf);

  SEXP arguments = Rf_allocVector(INTSXP, 3);
  PROTECT(arguments);

  int* parguments = INTEGER(arguments);

  parguments[0] = (int)(i);
  parguments[1] = (int)(n);
  parguments[2] = (int)(length);

  // dataptr_or_null listener method
  SEXP get_region_listener = VECTOR_ELT(ALTWRAP_LISTENERS(sx), 2);

  // call listener with integer result
  call_r_interface(get_region_listener, arguments, ALTWRAP_PARENT_ENV(sx));

  UNPROTECT(1);

  return length;
}


int altwrap_integer_Is_sorted_method(SEXP sx)
{
  int is_sorted = INTEGER_IS_SORTED(ALTWRAP_PAYLOAD(sx));

  SEXP arguments = Rf_allocVector(INTSXP, 1);
  PROTECT(arguments);
  
  int* parguments = INTEGER(arguments);

  parguments[0] = (int)(is_sorted);

  // retrieve is_sorted listener method
  SEXP is_sorted_listener = VECTOR_ELT(ALTWRAP_LISTENERS(sx), 5);
  
  // call listener with integer result
  call_r_interface(is_sorted_listener, arguments, ALTWRAP_PARENT_ENV(sx));
  
  UNPROTECT(1);
  
  return is_sorted;
}


int altwrap_integer_No_NA_method(SEXP sx)
{
  int no_na = INTEGER_NO_NA(ALTWRAP_PAYLOAD(sx));
  
  SEXP arguments = Rf_allocVector(INTSXP, 1);
  PROTECT(arguments);
  
  int* parguments = INTEGER(arguments);
  
  parguments[0] = (int)(no_na);
  
  // retrieve no_na listener method
  SEXP no_na_listener = VECTOR_ELT(ALTWRAP_LISTENERS(sx), 6);
  
  // call listener with integer result
  call_r_interface(no_na_listener, arguments, ALTWRAP_PARENT_ENV(sx));
  
  UNPROTECT(1);
  
  return no_na;
}

// int (*R_altinteger_No_NA_method_t)(SEXP);
// SEXP (*R_altinteger_Sum_method_t)(SEXP, Rboolean); 
// SEXP (*R_altinteger_Min_method_t)(SEXP, Rboolean);
// SEXP (*R_altinteger_Max_method_t)(SEXP, Rboolean);


// [[Rcpp::init]]
void register_altrep_integer_class(DllInfo *dll)
{
  altwrap_integer_class = R_make_altinteger_class("altwrap_integer", "lazyvec", dll);

  /* override ALTREP methods */
  CALL_METHOD_SETTER(altrep, integer, Unserialize);
  CALL_METHOD_SETTER(altrep, integer, Serialized_state);
  CALL_METHOD_SETTER(altrep, integer, Inspect);
  CALL_METHOD_SETTER(altrep, integer, Length);

  /* override ALTVEC methods */
  CALL_METHOD_SETTER(altvec, integer, Dataptr);
  CALL_METHOD_SETTER(altvec, integer, Dataptr_or_null);
  
  /* override ALTINTEGER methods */
  CALL_METHOD_SETTER(altinteger, integer, Elt);
  CALL_METHOD_SETTER(altinteger, integer, Get_region);
  

  CALL_METHOD_SETTER(altinteger, integer, Is_sorted);
  CALL_METHOD_SETTER(altinteger, integer, No_NA);
  // CALL_METHOD_SETTER(altinteger, integer, Sum);
  // CALL_METHOD_SETTER(altinteger, integer, Min);
  // CALL_METHOD_SETTER(altinteger, integer, Max);
}
