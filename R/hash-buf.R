#' Return CTP hash of a raw vector
#'
#' @note Length 1 character vectors will be auto-converted to a raw vectors
#' @param x raw vector or length 1 character vector
#' @return character(1)
#' @export
#' @examples
#' ltrs <- paste0(c(letters, LETTERS), collapse="")
#' hash_raw(ltrs)
hash_raw <- function(x) {

  stopifnot(is.raw(x) ||((length(x) == 1) && is.character(x)))

  if (is.character(x[1])) x <- rawToChar(x[1])

  int_hash_buf(x)

}