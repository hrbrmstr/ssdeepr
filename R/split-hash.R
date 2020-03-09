#' Splits an ssdeep hash string into component parts
#'
#' ssdeep hashes consists of three parts, separated by `:`:
#' - chunk size : size of the chunks in rest of the hash
#' - chunk : where each character represents a part of the file of length "chunk size"
#' - double chunk : hash computation where "chunk size" = 2 * "chunk size"
#' This function splits the single has string into three component parts.
#'
#' @param x character vector of ssdeep hashes
#' @return data frame
#' @export
#' @examples
#' split_hash(hash_con(url("https://en.wikipedia.org/wiki/Donald_Knuth")))
split_hash <- function(x) {

  components <- strsplit(x, ":", fixed = TRUE)
  lapply(components, function(.x) {
    as.data.frame(as.list(setNames(.x, c("chunk_size", "chunk", "double_chunk"))), stringsAsFactors = FALSE)
  }) -> out

  out <- do.call(rbind.data.frame, out)
  class(out) <- c("tbl_df", "tbl", "data.frame")

  out[["chunk_size"]] <- as.integer(out[["chunk_size"]])

  out

}