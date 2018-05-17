
#' Create an altrep vector from an R interface
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
    ),
    parent.env(environment())
  )

  lazy_vec_construct(meta_data)
}


lazy_vec_length <- function(x) {
  print("lazy_vec_length called")

  1
}


#' Call R method through c
#'
#' @param f function
#' @param x argument
#' @param rho environment in which to evaluate the function
#'
#' @return result
#' @export
call_R <- function(f, x) {
  call_r_method(f, x, parent.env(environment()))
}
