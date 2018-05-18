
#include "api_helpers.h"
#include "Altrep.h"

#include <R.h>
#include <Rinternals.h>


static R_altrep_class_t altwrap_int_class;


#define ALTREP_PAYLOAD(x) VECTOR_ELT(R_altrep_data1(x), 0)


SEXP construct_altrep_wrapper(SEXP data)
{
  SEXP state2 = Rf_mkString("data1");
  PROTECT(state2);

  SEXP altrep_vec = R_new_altrep(altwrap_int_class, data, state2);

  UNPROTECT(1);  // state1, state2

  return altrep_vec;
}


static SEXP altwrap_Unserialize(SEXP altwrap_class, SEXP state)
{
  Rf_PrintValue(Rf_mkString("altwrap_Unserialize called"));

  return NULL;
}


static SEXP altwrap_Serialized_state(SEXP x)
{
  return ALTREP_SERIALIZED_STATE(ALTREP_PAYLOAD(x));
}


Rboolean altwrap_Inspect(SEXP x, int pre, int deep, int pvec,
  void (*inspect_subtree)(SEXP, int, int, int))
{
  Rf_PrintValue(Rf_mkString("altwrap_Inspect start"));

  return ALTREP_INSPECT(ALTREP_PAYLOAD(x), pre, deep, pvec, inspect_subtree);
}


static R_xlen_t altwrap_Length(SEXP x)
{
  Rf_PrintValue(Rf_mkString("altwrap_Length called"));

  return ALTREP_LENGTH(ALTREP_PAYLOAD(x));
}


static void *altwrap_Dataptr(SEXP x, Rboolean writeable)
{
  Rf_PrintValue(Rf_mkString("altwrap_Dataptr called"));

  /* get addr first to get error if the object has been unmapped */
  return DATAPTR(ALTREP_PAYLOAD(x));
}


static const void *altwrap_Dataptr_or_null(SEXP x)
{
  Rf_PrintValue(Rf_mkString("altwrap_Dataptr_or_null called"));

  const void* pdata_or_null = DATAPTR_OR_NULL(ALTREP_PAYLOAD(x));

  return pdata_or_null;
}


static int altwrap_integer_Elt(SEXP x, R_xlen_t i)
{
  Rf_PrintValue(Rf_mkString("altwrap_integer_Elt called"));

  return INTEGER_ELT(ALTREP_PAYLOAD(x), i);
}


static R_xlen_t altwrap_integer_Get_region(SEXP sx, R_xlen_t i, R_xlen_t n, int *buf)
{
  Rf_PrintValue(Rf_mkString("altwrap_integer_Get_region called"));

  return INTEGER_GET_REGION(ALTREP_PAYLOAD(sx), i, n, buf);
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

  Rf_PrintValue(Rf_mkString("altwrap_integer class registered"));
}