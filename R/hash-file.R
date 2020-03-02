#' Return CTP hash of one or more files
#'
#' @param path character vector of file paths
#' @return data frame
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
hash_file <- function(path) {

  path <- path.expand(path)

  lapply(path, function(.x) {

    if (file.exists(.x)) {
      hash <- int_hash_file(.x)
    } else {
      hash <- NA_character_
    }

    data.frame(
      path = .x,
      hash = hash,
      stringsAsFactors = FALSE
    )

  }) -> out

  out <- do.call(rbind.data.frame, out)

  class(out) <- c("tbl_df", "tbl", "data.frame")

  out

}