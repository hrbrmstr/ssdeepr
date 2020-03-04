#' Return CTP hash of one data collected from a connection
#'
#' This function has an advantage over the other ones as it does not require the caller to read in
#' the entire contents of a file or URL all at once, thus saving memory at a tiny hit to speed.
#'
#' @param con a [connection]
#' @param buffer_size `(int)` how big of a read buffer to use? This is the "chunk size" for each call to [readBin()].
#' @return data frame
#' @export
#' @examples
#' # All 3 shld be the same
#' hash_con(url("https://en.wikipedia.org/wiki/Donald_Knuth"))
#' hash_con(file(system.file("knuth", "local.html", package = "ssdeepr")))
#' hash_con(gzfile(system.file("knuth", "local.gz", package = "ssdeepr")))
hash_con <- function(con, buffer_size = 32768L) {

  stopifnot(inherits(con, "connection"))

  if(!isOpen(con)){
    on.exit(close(con)) # also destroy con if 'open' fails
    open(con, "rb")
  }

  buffer_size <- as.integer(buffer_size[1])

  fuz <- int_fuzzy_context()

  repeat {
    tmp <- readBin(con, "raw", n = 32768L)
    if (length(tmp) == 0) {
      break
    } else {
      fuz <- int_fuzzy_update(fuz, tmp)
    }
  }

  int_fuzzy_digest(fuz)

}