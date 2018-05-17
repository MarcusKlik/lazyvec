
#' Wrap an altrep vector
#'
#' @param altrep_vec altrep vector
#'
#' @return a wrapper around the altrep vector which is an altrep vector itself
#' @export
altrep_wrapper <- function(altrep_vec) {

  meta_data <- list(
    list(  # interface methods
      lazy_vec_length
    ),
    parent.env(environment()),
    altrep_vec
  )

  lazy_vec_construct(meta_data)
}
