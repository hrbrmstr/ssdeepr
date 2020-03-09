#include <Rcpp.h>
#include "fuzzy.h"

using namespace Rcpp;

//' Test whether an object is an external pointer
//'
//' @param x object to test
//' @keywords internal
// [[Rcpp::export]]
void check_is_xptr(SEXP s) {
  if (TYPEOF(s) != EXTPTRSXP) {
    Rf_error("expected an externalptr");
  }
}

//' Test whether an external pointer is null
//'
//' @param x object to test
//' @keywords internal
// [[Rcpp::export]]
SEXP is_null_xptr_(SEXP s) {
  check_is_xptr(s);
  void *r = (void *)R_ExternalPtrAddr(s);
  return wrap(r == NULL);
}

static void sctx_finalizer(SEXP ptr) {
  if(!R_ExternalPtrAddr(ptr)) return;
  fuzzy_state *ctxt = (fuzzy_state *)R_ExternalPtrAddr(ptr);
  if (ptr) fuzzy_free(ctxt);
  R_ClearExternalPtr(ptr); /* not really needed */
}

// [[Rcpp::export]]
SEXP int_fuzzy_context() {

  SEXP ptr;
  fuzzy_state *stxt = fuzzy_new();

  if (stxt != NULL) {
    ptr = R_MakeExternalPtr(stxt, Rf_install("sctx"), R_NilValue);
    R_RegisterCFinalizerEx(ptr, sctx_finalizer, TRUE);
    Rf_setAttrib(ptr, Rf_install("class"), Rf_mkString("sctx"));
    return(ptr);
  } else {
    return(R_NilValue);
  }

}

// [[Rcpp::export]]
SEXP int_fuzzy_update(SEXP sctx, std::vector < unsigned char > v) {

  check_is_xptr(sctx);

  fuzzy_state *fctx = (fuzzy_state *)R_ExternalPtrAddr(sctx);

  if ((sctx == NULL) || (fctx == NULL)) return(R_NilValue);

  int res = fuzzy_update(fctx, &v[0], v.size());

  if (res < 0) Rcpp::warning("An error occurred updating the hash context.");

  return(sctx);

}

// [[Rcpp::export]]
String int_fuzzy_digest(SEXP sctx) {

  check_is_xptr(sctx);

  fuzzy_state *fctx = (fuzzy_state *)R_ExternalPtrAddr(sctx);

  if ((sctx == NULL) || (fctx == NULL)) return(R_NilValue);

  char hash[FUZZY_MAX_RESULT];
  int res = fuzzy_digest(fctx, &hash[0], 0);

  if (res < 0) Rcpp::warning("An error occurred updating the hash context.");

  return(
    (res == 0) ? String(hash) : NA_STRING
  );

}


// [[Rcpp::export]]
String int_hash_file(String path) {

  char hash[FUZZY_MAX_RESULT];
  int res = fuzzy_hash_filename(path.get_cstring(), &hash[0]);

  return(
    (res == 0) ? String(hash) : NA_STRING
  );

}


// [[Rcpp::export]]
String int_hash_buf(std::vector < unsigned char > v) {

  char hash[FUZZY_MAX_RESULT];
  const unsigned char *p_buf = (unsigned char *)&*v.begin();
  int res = fuzzy_hash_buf(p_buf, v.size(), &hash[0]);

  return(
    (res == 0) ? String(hash) : NA_STRING
  );

}


// [[Rcpp::export]]
IntegerVector int_hash_cmp(String h1, String h2) {

  int res = fuzzy_compare(h1.get_cstring(), h2.get_cstring());

  return(
    (res >= 0) ? IntegerVector::create(res) : NA_INTEGER
  );

}

