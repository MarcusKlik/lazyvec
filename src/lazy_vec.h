
#ifndef LAZYVEC_H
#define LAZYVEC_H

// [[Rcpp::export]]
SEXP lazy_vec_construct(SEXP lazyvec_interface);

// [[Rcpp::export]]
SEXP altrep_wrapper_construct(SEXP altrep_vec);

// [[Rcpp::export]]
SEXP call_r_method(SEXP f, SEXP x, SEXP rho);

#endif // LAZYVEC_H
