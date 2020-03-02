// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// int_hash_file
String int_hash_file(String path);
RcppExport SEXP _ssdeepr_int_hash_file(SEXP pathSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< String >::type path(pathSEXP);
    rcpp_result_gen = Rcpp::wrap(int_hash_file(path));
    return rcpp_result_gen;
END_RCPP
}
// int_hash_buf
String int_hash_buf(std::vector < unsigned char > v);
RcppExport SEXP _ssdeepr_int_hash_buf(SEXP vSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector < unsigned char > >::type v(vSEXP);
    rcpp_result_gen = Rcpp::wrap(int_hash_buf(v));
    return rcpp_result_gen;
END_RCPP
}
// int_hash_cmp
IntegerVector int_hash_cmp(String h1, String h2);
RcppExport SEXP _ssdeepr_int_hash_cmp(SEXP h1SEXP, SEXP h2SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< String >::type h1(h1SEXP);
    Rcpp::traits::input_parameter< String >::type h2(h2SEXP);
    rcpp_result_gen = Rcpp::wrap(int_hash_cmp(h1, h2));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_ssdeepr_int_hash_file", (DL_FUNC) &_ssdeepr_int_hash_file, 1},
    {"_ssdeepr_int_hash_buf", (DL_FUNC) &_ssdeepr_int_hash_buf, 1},
    {"_ssdeepr_int_hash_cmp", (DL_FUNC) &_ssdeepr_int_hash_cmp, 2},
    {NULL, NULL, 0}
};

RcppExport void R_init_ssdeepr(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
