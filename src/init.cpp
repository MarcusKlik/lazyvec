// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393


#include <Rcpp.h>

using namespace Rcpp;

// lazy_vec_construct
RcppExport SEXP _lazyvec_lazy_vec_construct(SEXP lazyvec_interfaceSEXP);
RcppExport SEXP _lazyvec_altrep_wrapper_construct(SEXP altrep_vecSEXP);
RcppExport SEXP _lazyvec_call_r_method(SEXP fSEXP, SEXP xSEXP, SEXP rhoSEXP);

RcppExport void register_integer_class(DllInfo *dll);
RcppExport void register_altwrap_integer_class(DllInfo *dll);


static const R_CallMethodDef CallEntries[] = {
    {"_lazyvec_lazy_vec_construct", (DL_FUNC) &_lazyvec_lazy_vec_construct, 1},
    {"_lazyvec_altrep_wrapper_construct", (DL_FUNC) &_lazyvec_altrep_wrapper_construct, 1},
    {"_lazyvec_call_r_method", (DL_FUNC) &_lazyvec_call_r_method, 3},
    {NULL, NULL, 0}
};


RcppExport void R_init_lazyvec(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);

    register_integer_class(dll);
    register_altwrap_integer_class(dll);
}
