
#' Test if object has altrep representation
#'
#' @param x the object to be tested
#'
#' @return TRUE if the object is an altrep vector
#' @export
is_altrep <- function(x) {
  is_altrep_vector(x) == 1
}
