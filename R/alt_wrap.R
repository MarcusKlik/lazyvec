
#' Wrap an altrep vector
#'
#' @param altrep_vec altrep vector
#'
#' @return a wrapper around the altrep vector which is an altrep vector itself
#' @export
alt_wrap <- function(altrep_vec) {

  meta_data <- list(
    altrep_vec
  )

  altrep_wrapper_construct(meta_data)
}
