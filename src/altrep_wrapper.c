
#include "api_helpers.h"

#include <R.h>
#include <Rinternals.h>


// get the payload with the ALTREP vector
#define ALTWRAP_PAYLOAD(x) VECTOR_ELT(R_altrep_data1(x), 0)
#define ALTWRAP_LISTENERS(x) VECTOR_ELT(R_altrep_data1(x), 1)
#define ALTWRAP_PARENT_ENV(x) VECTOR_ELT(R_altrep_data1(x), 2)


// altrep integer class definition
static R_altrep_class_t altwrap_int_class;


SEXP construct_altrep_wrapper(SEXP data)
{
  SEXP altrep_vec = R_new_altrep(altwrap_int_class, data, NILSXP);

  return altrep_vec;
}


static SEXP altwrap_Unserialize(SEXP altwrap_class, SEXP state)
{
  Rf_PrintValue(Rf_mkString("altwrap_Unserialize called"));

  return NULL;
}


static SEXP altwrap_Serialized_state(SEXP x)
{
  Rf_PrintValue(Rf_mkString("altwrap_Serialized_state called, null returned"));

  return ALTREP_SERIALIZED_STATE(ALTWRAP_PAYLOAD(x));
}


Rboolean altwrap_Inspect(SEXP x, int pre, int deep, int pvec,
  void (*inspect_subtree)(SEXP, int, int, int))
{
  Rf_PrintValue(Rf_mkString("altwrap_Inspect start"));

  return ALTREP_INSPECT(ALTWRAP_PAYLOAD(x), pre, deep, pvec, inspect_subtree);
}


static R_xlen_t altwrap_Length(SEXP x)
{
  R_xlen_t length_result = ALTREP_LENGTH(ALTWRAP_PAYLOAD(x));

  // length listener method
  SEXP length_listener = VECTOR_ELT(ALTWRAP_LISTENERS(x), 0);

  // call listener with integer length result
  // TODO: change to int64 result
  call_r_interface(length_listener, Rf_ScalarInteger(length_result), ALTWRAP_PARENT_ENV(x));

  return length_result;
}


static void *altwrap_Dataptr(SEXP x, Rboolean writeable)
{
  Rf_PrintValue(Rf_mkString("altwrap_Dataptr called"));

  /* get addr first to get error if the object has been unmapped */
  return DATAPTR(ALTWRAP_PAYLOAD(x));
}


static const void *altwrap_Dataptr_or_null(SEXP x)
{
  const void* pdata_or_null = DATAPTR_OR_NULL(ALTWRAP_PAYLOAD(x));

  // dataptr_or_null listener method
  SEXP dataptr_or_null_listener = VECTOR_ELT(ALTWRAP_LISTENERS(x), 1);

  int is_pointer = pdata_or_null == NULL;

  // call listener with integer result
  call_r_interface(dataptr_or_null_listener, Rf_ScalarLogical(is_pointer), ALTWRAP_PARENT_ENV(x));

  return pdata_or_null;
}


static int altwrap_integer_Elt(SEXP x, R_xlen_t i)
{
  Rf_PrintValue(Rf_mkString("altwrap_integer_Elt called"));

  return INTEGER_ELT(ALTWRAP_PAYLOAD(x), i);
}


static R_xlen_t altwrap_integer_Get_region(SEXP sx, R_xlen_t i, R_xlen_t n, int *buf)
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


void register_altwrap_integer_class(DllInfo *dll)
{
  R_altrep_class_t int_class = R_make_altinteger_class("altwrap_integer", "lazyvec", dll);
  altwrap_int_class = int_class;

  /* override ALTREP methods */
  R_set_altrep_Unserialize_method(int_class, altwrap_Unserialize);
  R_set_altrep_Serialized_state_method(int_class, altwrap_Serialized_state);
  R_set_altrep_Inspect_method(int_class, altwrap_Inspect);
  R_set_altrep_Length_method(int_class, altwrap_Length);

  /* override ALTVEC methods */
  R_set_altvec_Dataptr_method(int_class, altwrap_Dataptr);
  R_set_altvec_Dataptr_or_null_method(int_class, altwrap_Dataptr_or_null);

  /* override ALTINTEGER methods */
  R_set_altinteger_Elt_method(int_class, altwrap_integer_Elt);
  R_set_altinteger_Get_region_method(int_class, altwrap_integer_Get_region);
}
