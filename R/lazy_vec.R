
#' Wrapper around an altrep interface
#'
#' @param altrep_interface altrep_interface object
#'
#' @return an altrep vector
#' @export
lazy_vec <- function(altrep_interface) {

  meta_data <- list(
    c(1L, 2L, 3L, 4L),  # state values
    list(  # interface methods
      lazy_vec_length
    )
  )

  lazy_vec_construct(meta_data)
}


lazy_vec_length <- function(x) {
  lazy_length(x)
}
