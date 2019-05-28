// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// altrep_full_class
SEXP altrep_full_class(SEXP altrep_vec);
RcppExport SEXP _lazyvec_altrep_full_class(SEXP altrep_vecSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type altrep_vec(altrep_vecSEXP);
    rcpp_result_gen = Rcpp::wrap(altrep_full_class(altrep_vec));
    return rcpp_result_gen;
END_RCPP
}
// trigger_length
int trigger_length(SEXP x);
RcppExport SEXP _lazyvec_trigger_length(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(trigger_length(x));
    return rcpp_result_gen;
END_RCPP
}
// trigger_duplicate_ex
SEXP trigger_duplicate_ex(SEXP x, int deep);
RcppExport SEXP _lazyvec_trigger_duplicate_ex(SEXP xSEXP, SEXP deepSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< int >::type deep(deepSEXP);
    rcpp_result_gen = Rcpp::wrap(trigger_duplicate_ex(x, deep));
    return rcpp_result_gen;
END_RCPP
}
// trigger_serialized_state
SEXP trigger_serialized_state(SEXP x);
RcppExport SEXP _lazyvec_trigger_serialized_state(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(trigger_serialized_state(x));
    return rcpp_result_gen;
END_RCPP
}
// trigger_dataptr_or_null
SEXP trigger_dataptr_or_null(SEXP x);
RcppExport SEXP _lazyvec_trigger_dataptr_or_null(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(trigger_dataptr_or_null(x));
    return rcpp_result_gen;
END_RCPP
}
// trigger_get_region
SEXP trigger_get_region(SEXP x, SEXP pos, SEXP size);
RcppExport SEXP _lazyvec_trigger_get_region(SEXP xSEXP, SEXP posSEXP, SEXP sizeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type pos(posSEXP);
    Rcpp::traits::input_parameter< SEXP >::type size(sizeSEXP);
    rcpp_result_gen = Rcpp::wrap(trigger_get_region(x, pos, size));
    return rcpp_result_gen;
END_RCPP
}
// trigger_unserialize_ex
SEXP trigger_unserialize_ex(SEXP info, SEXP state, SEXP attr, int objf, int levs);
RcppExport SEXP _lazyvec_trigger_unserialize_ex(SEXP infoSEXP, SEXP stateSEXP, SEXP attrSEXP, SEXP objfSEXP, SEXP levsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type info(infoSEXP);
    Rcpp::traits::input_parameter< SEXP >::type state(stateSEXP);
    Rcpp::traits::input_parameter< SEXP >::type attr(attrSEXP);
    Rcpp::traits::input_parameter< int >::type objf(objfSEXP);
    Rcpp::traits::input_parameter< int >::type levs(levsSEXP);
    rcpp_result_gen = Rcpp::wrap(trigger_unserialize_ex(info, state, attr, objf, levs));
    return rcpp_result_gen;
END_RCPP
}
// trigger_inspect
void trigger_inspect(SEXP x, int pre, int deep, int pvec);
RcppExport SEXP _lazyvec_trigger_inspect(SEXP xSEXP, SEXP preSEXP, SEXP deepSEXP, SEXP pvecSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< int >::type pre(preSEXP);
    Rcpp::traits::input_parameter< int >::type deep(deepSEXP);
    Rcpp::traits::input_parameter< int >::type pvec(pvecSEXP);
    trigger_inspect(x, pre, deep, pvec);
    return R_NilValue;
END_RCPP
}
// trigger_coerce
SEXP trigger_coerce(SEXP x, int type);
RcppExport SEXP _lazyvec_trigger_coerce(SEXP xSEXP, SEXP typeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< int >::type type(typeSEXP);
    rcpp_result_gen = Rcpp::wrap(trigger_coerce(x, type));
    return rcpp_result_gen;
END_RCPP
}
// trigger_integer_Elt
int trigger_integer_Elt(SEXP x, int i);
RcppExport SEXP _lazyvec_trigger_integer_Elt(SEXP xSEXP, SEXP iSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< int >::type i(iSEXP);
    rcpp_result_gen = Rcpp::wrap(trigger_integer_Elt(x, i));
    return rcpp_result_gen;
END_RCPP
}
// trigger_integer_is_sorted
int trigger_integer_is_sorted(SEXP x);
RcppExport SEXP _lazyvec_trigger_integer_is_sorted(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(trigger_integer_is_sorted(x));
    return rcpp_result_gen;
END_RCPP
}
// trigger_integer_no_na
int trigger_integer_no_na(SEXP x);
RcppExport SEXP _lazyvec_trigger_integer_no_na(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(trigger_integer_no_na(x));
    return rcpp_result_gen;
END_RCPP
}
// trigger_integer_sum
SEXP trigger_integer_sum(SEXP x, int na_rm);
RcppExport SEXP _lazyvec_trigger_integer_sum(SEXP xSEXP, SEXP na_rmSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< int >::type na_rm(na_rmSEXP);
    rcpp_result_gen = Rcpp::wrap(trigger_integer_sum(x, na_rm));
    return rcpp_result_gen;
END_RCPP
}
// trigger_integer_min
SEXP trigger_integer_min(SEXP x, int na_rm);
RcppExport SEXP _lazyvec_trigger_integer_min(SEXP xSEXP, SEXP na_rmSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< int >::type na_rm(na_rmSEXP);
    rcpp_result_gen = Rcpp::wrap(trigger_integer_min(x, na_rm));
    return rcpp_result_gen;
END_RCPP
}
// trigger_integer_max
SEXP trigger_integer_max(SEXP x, int na_rm);
RcppExport SEXP _lazyvec_trigger_integer_max(SEXP xSEXP, SEXP na_rmSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< int >::type na_rm(na_rmSEXP);
    rcpp_result_gen = Rcpp::wrap(trigger_integer_max(x, na_rm));
    return rcpp_result_gen;
END_RCPP
}
// altrep_integer_wrapper
SEXP altrep_integer_wrapper(SEXP data);
RcppExport SEXP _lazyvec_altrep_integer_wrapper(SEXP dataSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type data(dataSEXP);
    rcpp_result_gen = Rcpp::wrap(altrep_integer_wrapper(data));
    return rcpp_result_gen;
END_RCPP
}
// altrep_logical_wrapper
SEXP altrep_logical_wrapper(SEXP data);
RcppExport SEXP _lazyvec_altrep_logical_wrapper(SEXP dataSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type data(dataSEXP);
    rcpp_result_gen = Rcpp::wrap(altrep_logical_wrapper(data));
    return rcpp_result_gen;
END_RCPP
}
// altrep_raw_wrapper
SEXP altrep_raw_wrapper(SEXP data);
RcppExport SEXP _lazyvec_altrep_raw_wrapper(SEXP dataSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type data(dataSEXP);
    rcpp_result_gen = Rcpp::wrap(altrep_raw_wrapper(data));
    return rcpp_result_gen;
END_RCPP
}
// altrep_real_wrapper
SEXP altrep_real_wrapper(SEXP data);
RcppExport SEXP _lazyvec_altrep_real_wrapper(SEXP dataSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type data(dataSEXP);
    rcpp_result_gen = Rcpp::wrap(altrep_real_wrapper(data));
    return rcpp_result_gen;
END_RCPP
}
// altrep_string_wrapper
SEXP altrep_string_wrapper(SEXP data);
RcppExport SEXP _lazyvec_altrep_string_wrapper(SEXP dataSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type data(dataSEXP);
    rcpp_result_gen = Rcpp::wrap(altrep_string_wrapper(data));
    return rcpp_result_gen;
END_RCPP
}
// is_altrep_vector
int is_altrep_vector(SEXP vec);
RcppExport SEXP _lazyvec_is_altrep_vector(SEXP vecSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type vec(vecSEXP);
    rcpp_result_gen = Rcpp::wrap(is_altrep_vector(vec));
    return rcpp_result_gen;
END_RCPP
}
// altrep_class
SEXP altrep_class(SEXP vec);
RcppExport SEXP _lazyvec_altrep_class(SEXP vecSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type vec(vecSEXP);
    rcpp_result_gen = Rcpp::wrap(altrep_class(vec));
    return rcpp_result_gen;
END_RCPP
}
// lazyvec_integer_wrapper
SEXP lazyvec_integer_wrapper(SEXP data);
RcppExport SEXP _lazyvec_lazyvec_integer_wrapper(SEXP dataSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type data(dataSEXP);
    rcpp_result_gen = Rcpp::wrap(lazyvec_integer_wrapper(data));
    return rcpp_result_gen;
END_RCPP
}
// lazyvec_logical_wrapper
SEXP lazyvec_logical_wrapper(SEXP data);
RcppExport SEXP _lazyvec_lazyvec_logical_wrapper(SEXP dataSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type data(dataSEXP);
    rcpp_result_gen = Rcpp::wrap(lazyvec_logical_wrapper(data));
    return rcpp_result_gen;
END_RCPP
}
// lazyvec_raw_wrapper
SEXP lazyvec_raw_wrapper(SEXP data);
RcppExport SEXP _lazyvec_lazyvec_raw_wrapper(SEXP dataSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type data(dataSEXP);
    rcpp_result_gen = Rcpp::wrap(lazyvec_raw_wrapper(data));
    return rcpp_result_gen;
END_RCPP
}
// lazyvec_real_wrapper
SEXP lazyvec_real_wrapper(SEXP data);
RcppExport SEXP _lazyvec_lazyvec_real_wrapper(SEXP dataSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type data(dataSEXP);
    rcpp_result_gen = Rcpp::wrap(lazyvec_real_wrapper(data));
    return rcpp_result_gen;
END_RCPP
}
// lazyvec_string_wrapper
SEXP lazyvec_string_wrapper(SEXP data);
RcppExport SEXP _lazyvec_lazyvec_string_wrapper(SEXP dataSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type data(dataSEXP);
    rcpp_result_gen = Rcpp::wrap(lazyvec_string_wrapper(data));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_lazyvec_altrep_full_class", (DL_FUNC) &_lazyvec_altrep_full_class, 1},
    {"_lazyvec_trigger_length", (DL_FUNC) &_lazyvec_trigger_length, 1},
    {"_lazyvec_trigger_duplicate_ex", (DL_FUNC) &_lazyvec_trigger_duplicate_ex, 2},
    {"_lazyvec_trigger_serialized_state", (DL_FUNC) &_lazyvec_trigger_serialized_state, 1},
    {"_lazyvec_trigger_dataptr_or_null", (DL_FUNC) &_lazyvec_trigger_dataptr_or_null, 1},
    {"_lazyvec_trigger_get_region", (DL_FUNC) &_lazyvec_trigger_get_region, 3},
    {"_lazyvec_trigger_unserialize_ex", (DL_FUNC) &_lazyvec_trigger_unserialize_ex, 5},
    {"_lazyvec_trigger_inspect", (DL_FUNC) &_lazyvec_trigger_inspect, 4},
    {"_lazyvec_trigger_coerce", (DL_FUNC) &_lazyvec_trigger_coerce, 2},
    {"_lazyvec_trigger_integer_Elt", (DL_FUNC) &_lazyvec_trigger_integer_Elt, 2},
    {"_lazyvec_trigger_integer_is_sorted", (DL_FUNC) &_lazyvec_trigger_integer_is_sorted, 1},
    {"_lazyvec_trigger_integer_no_na", (DL_FUNC) &_lazyvec_trigger_integer_no_na, 1},
    {"_lazyvec_trigger_integer_sum", (DL_FUNC) &_lazyvec_trigger_integer_sum, 2},
    {"_lazyvec_trigger_integer_min", (DL_FUNC) &_lazyvec_trigger_integer_min, 2},
    {"_lazyvec_trigger_integer_max", (DL_FUNC) &_lazyvec_trigger_integer_max, 2},
    {"_lazyvec_altrep_integer_wrapper", (DL_FUNC) &_lazyvec_altrep_integer_wrapper, 1},
    {"_lazyvec_altrep_logical_wrapper", (DL_FUNC) &_lazyvec_altrep_logical_wrapper, 1},
    {"_lazyvec_altrep_raw_wrapper", (DL_FUNC) &_lazyvec_altrep_raw_wrapper, 1},
    {"_lazyvec_altrep_real_wrapper", (DL_FUNC) &_lazyvec_altrep_real_wrapper, 1},
    {"_lazyvec_altrep_string_wrapper", (DL_FUNC) &_lazyvec_altrep_string_wrapper, 1},
    {"_lazyvec_is_altrep_vector", (DL_FUNC) &_lazyvec_is_altrep_vector, 1},
    {"_lazyvec_altrep_class", (DL_FUNC) &_lazyvec_altrep_class, 1},
    {"_lazyvec_lazyvec_integer_wrapper", (DL_FUNC) &_lazyvec_lazyvec_integer_wrapper, 1},
    {"_lazyvec_lazyvec_logical_wrapper", (DL_FUNC) &_lazyvec_lazyvec_logical_wrapper, 1},
    {"_lazyvec_lazyvec_raw_wrapper", (DL_FUNC) &_lazyvec_lazyvec_raw_wrapper, 1},
    {"_lazyvec_lazyvec_real_wrapper", (DL_FUNC) &_lazyvec_lazyvec_real_wrapper, 1},
    {"_lazyvec_lazyvec_string_wrapper", (DL_FUNC) &_lazyvec_lazyvec_string_wrapper, 1},
    {NULL, NULL, 0}
};

void register_altrep_integer_class(DllInfo *dll);
void register_altrep_logical_class(DllInfo *dll);
void register_altrep_raw_class(DllInfo *dll);
void register_altrep_real_class(DllInfo *dll);
void register_altrep_string_class(DllInfo *dll);
void register_lazyvec_integer_class(DllInfo *dll);
void register_lazyvec_logical_class(DllInfo *dll);
void register_lazyvec_raw_class(DllInfo *dll);
void register_lazyvec_real_class(DllInfo *dll);
void register_lazyvec_string_class(DllInfo *dll);
RcppExport void R_init_lazyvec(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
    register_altrep_integer_class(dll);
    register_altrep_logical_class(dll);
    register_altrep_raw_class(dll);
    register_altrep_real_class(dll);
    register_altrep_string_class(dll);
    register_lazyvec_integer_class(dll);
    register_lazyvec_logical_class(dll);
    register_lazyvec_raw_class(dll);
    register_lazyvec_real_class(dll);
    register_lazyvec_string_class(dll);
}
