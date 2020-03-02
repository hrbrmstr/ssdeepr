#include <Rcpp.h>
#include <fuzzy.h>

using namespace Rcpp;

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

