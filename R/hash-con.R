#' Return CTP hash of one data collected from a connection
#'
#' @param con a [connection]
#' @return data frame
#' @export
#' @examples
#' # All 3 shld be the same
#' hash_con(url("https://en.wikipedia.org/wiki/Donald_Knuth"))
#' hash_con(file(system.file("knuth", "local.html", package = "ssdeepr")))
#' hash_con(gzfile(system.file("knuth", "local.gz", package = "ssdeepr")))
hash_con <- function(con) {

  stopifnot(inherits(con, "connection"))

  if(!isOpen(con)){
    on.exit(close(con)) # also destroy con if 'open' fails
    open(con, "rb")
  }

  out <- raw(0)

  repeat {
    tmp <- readBin(con, "raw", n = 32768L)
    if (length(tmp) == 0) {
      break
    } else {
      out <- c(out, tmp)
    }
  }

  hash_raw(out)

}