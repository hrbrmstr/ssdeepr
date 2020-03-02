#' Compare two hashes
#'
#' @param sig1,sig2 character signatures created with one of the hash generation functions
#' @return integer(1)
#' @export
#' @examples
#' system.file("extdat", package="ssdeepr") %>%
#' list.files(full.names = TRUE, pattern = "html$", include.dirs = FALSE) %>%
#'   hash_file() -> hashes
#'
#' hash_compare(hashes$hash[1], hashes$hash[1])
#' hash_compare(hashes$hash[1], hashes$hash[2])
#' hash_compare(hashes$hash[1], hashes$hash[3])
#' hash_compare(hashes$hash[1], hashes$hash[4])
hash_compare <- function(sig1, sig2) {

  stopifnot(is.character(sig1) && is.character(sig2))

  if (is.na(sig1[1]) || is.na(sig2[1])) {
    return(NA_integer_)
  } else {
    int_hash_cmp(sig1[1], sig2[1])
  }

}