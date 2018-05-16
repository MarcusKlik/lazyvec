
#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Altrep.h>


static R_altrep_class_t altvec_int_class;
// static R_altrep_class_t altvec_real_class;


SEXP construct_lazy_vec(SEXP data)
{
  SEXP state = Rf_mkString("this is a state object");
/*
  int* external_pointer = malloc(20 * * sizeof(int));

  // initialize values
  for (int count = 0; count < 20; count++)
  {
    external_pointer[count] = count;
  }

  SEXP eptr = PROTECT(R_MakeExternalPtr(external_pointer, R_NilValue, state));
  register_mmap_eptr(eptr);
*/

  return R_new_altrep(altvec_int_class, Rf_mkString("data1"), state);
}


static SEXP altvec_Unserialize(SEXP altvec_class, SEXP state)
{
  Rf_PrintValue(Rf_mkString("altvec_Unserialize called"));

  return Rf_ScalarLogical(1);
}


static SEXP altvec_Serialized_state(SEXP x)
{
  return NULL;
}


Rboolean altvec_Inspect(SEXP x, int pre, int deep, int pvec,
  void (*inspect_subtree)(SEXP, int, int, int))
{
  return TRUE;
}


static R_xlen_t altvec_Length(SEXP x)
{
  return 1;
}


static void *altvec_Dataptr(SEXP x, Rboolean writeable)
{
  /* get addr first to get error if the object has been unmapped */
  return NULL;
}


static const void *altvec_Dataptr_or_null(SEXP x)
{
  return NULL;
}



static int altvec_integer_Elt(SEXP x, R_xlen_t i)
{
  return 1;
}


static R_xlen_t altvec_integer_Get_region(SEXP sx, R_xlen_t i, R_xlen_t n, int *buf)
{
  return 1;
}


void register_integer_class(DllInfo *dll)
{
  R_altrep_class_t int_class = R_make_altinteger_class("altvec_integer", "lazyvec", dll);
  altvec_int_class = int_class;

  /* override ALTREP methods */
  R_set_altrep_Unserialize_method(int_class, altvec_Unserialize);
  R_set_altrep_Serialized_state_method(int_class, altvec_Serialized_state);
  R_set_altrep_Inspect_method(int_class, altvec_Inspect);
  R_set_altrep_Length_method(int_class, altvec_Length);

  /* override ALTVEC methods */
  R_set_altvec_Dataptr_method(int_class, altvec_Dataptr);
  R_set_altvec_Dataptr_or_null_method(int_class, altvec_Dataptr_or_null);

  /* override ALTINTEGER methods */
  R_set_altinteger_Elt_method(int_class, altvec_integer_Elt);
  R_set_altinteger_Get_region_method(int_class, altvec_integer_Get_region);

  Rf_PrintValue(Rf_mkString("altvec_integer class registered"));
}
