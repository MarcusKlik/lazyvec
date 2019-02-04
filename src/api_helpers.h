
#ifndef API_HELPERS_H
#define API_HELPERS_H

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include "R_ext/Altrep.h"


// R listeners
#define LISTENER_LENGTH            0
#define LISTENER_DATAPTR_OR_NULL   1
#define LISTENER_GET_REGION        2
#define LISTENER_ELT               3
#define LISTENER_DATAPTR           4
#define LISTENER_IS_SORTED         5
#define LISTENER_NO_NA             6
#define LISTENER_SUM               7
#define LISTENER_MIN               8
#define LISTENER_MAX               9
#define LISTENER_INSPECT          10
#define LISTENER_UNSERIALIZE_EX   11
#define LISTENER_SERIALIZED_STATE 12

typedef void (*inspect_subtree_method)(SEXP, int, int, int);


// get the payload with the ALTREP vector
#define ALTWRAP_PAYLOAD(x) VECTOR_ELT(R_altrep_data1(x), 0)
#define ALTWRAP_LISTENERS(x) VECTOR_ELT(R_altrep_data1(x), 1)
#define ALTWRAP_PARENT_ENV(x) VECTOR_ELT(R_altrep_data1(x), 2)

#define CALL_METHOD_SETTER(CNAME, TNAME, MNAME) \
  R_set_##CNAME##_##MNAME##_method(altwrap_##TNAME##_class, altwrap_##TNAME##_##MNAME##_method)

// call a single argument R function from the C API
SEXP call_r_interface(SEXP f, SEXP x, SEXP rho);

#endif // API_HELPERS_H
