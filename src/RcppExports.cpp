// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// construct_altrep_wrapper
SEXP construct_altrep_wrapper(SEXP data);
RcppExport SEXP _lazyvec_construct_altrep_wrapper(SEXP dataSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type data(dataSEXP);
    rcpp_result_gen = Rcpp::wrap(construct_altrep_wrapper(data));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_hello_world
List rcpp_hello_world();
RcppExport SEXP _lazyvec_rcpp_hello_world() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(rcpp_hello_world());
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_lazyvec_construct_altrep_wrapper", (DL_FUNC) &_lazyvec_construct_altrep_wrapper, 1},
    {"_lazyvec_rcpp_hello_world", (DL_FUNC) &_lazyvec_rcpp_hello_world, 0},
    {NULL, NULL, 0}
};

void register_altrep_integer_class(DllInfo *dll);
RcppExport void R_init_lazyvec(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
    register_altrep_integer_class(dll);
}
