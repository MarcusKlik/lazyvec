
#ifndef API_HELPERS_H
#define API_HELPERS_H

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include "R_ext/Altrep.h"

// altvec listeners
#define ALTREP_METHOD_LENGTH            0
#define ALTREP_METHOD_DATAPTR_OR_NULL   1
#define ALTREP_METHOD_GET_REGION        2
#define ALTREP_METHOD_ELT               3
#define ALTREP_METHOD_DATAPTR           4
#define ALTREP_METHOD_IS_SORTED         5
#define ALTREP_METHOD_NO_NA             6
#define ALTREP_METHOD_SUM               7
#define ALTREP_METHOD_MIN               8
#define ALTREP_METHOD_MAX               9
#define ALTREP_METHOD_INSPECT          10
#define ALTREP_METHOD_UNSERIALIZE_EX   11
#define ALTREP_METHOD_SERIALIZED_STATE 12
#define ALTREP_METHOD_DUPLICATE_EX     13
#define ALTREP_METHOD_COERCE           14
#define ALTREP_METHOD_EXTRACT_SUBSET   15
#define ALTREP_METHOD_UNSERIALIZE      16
#define ALTREP_METHOD_DUPLICATE        17

typedef void (*inspect_subtree_method)(SEXP, int, int, int);


// get meta data components from the ALTREP vector
#define ALTWRAP_PAYLOAD(x) VECTOR_ELT(R_altrep_data1(x), 0)
#define ALTWRAP_LISTENERS(x) VECTOR_ELT(R_altrep_data1(x), 1)
#define ALTWRAP_METADATA(x) VECTOR_ELT(R_altrep_data1(x), 2)
#define ALTWRAP_PARENT_ENV(x) VECTOR_ELT(R_altrep_data1(x), 3)

// override default altrep methods
#define CALL_METHOD_SETTER(CNAME, TNAME, MNAME) \
  R_set_##CNAME##_##MNAME##_method(altwrap_##TNAME##_class, altwrap_##TNAME##_##MNAME##_method)


// get meta data components from the ALTREP vector
#define LAZYVEC_PAYLOAD(x) VECTOR_ELT(R_altrep_data1(x), 0)
#define LAZYVEC_LISTENERS(x) VECTOR_ELT(R_altrep_data1(x), 1)
#define LAZYVEC_METADATA(x) VECTOR_ELT(R_altrep_data1(x), 2)
#define LAZYVEC_PARENT_ENV(x) VECTOR_ELT(R_altrep_data1(x), 3)

#define CALL_LAZYVEC_SETTER(CNAME, TNAME, MNAME) \
  R_set_##CNAME##_##MNAME##_method(lazyvec_##TNAME##_class, lazyvec_##TNAME##_##MNAME##_method)


// call a single argument R function from the C API
SEXP call_r_interface(SEXP f, SEXP x, SEXP rho);

int is_altrep_vector(SEXP vec);
  
#endif // API_HELPERS_H
