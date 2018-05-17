
#' Wrapper around an altrep interface
#'
#' @param altrep_interface altrep_interface object
#'
#' @return an altrep vector
#' @export
lazy_vec <- function(altrep_interface) {

  state <- c(1L, 2L, 3L, 4L)
  lazy_vec_construct(state)
}
