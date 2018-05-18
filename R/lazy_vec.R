
#' Create an altrep vector from an R interface
#'
#' @param altrep_interface altrep_interface object
#'
#' @return an altrep vector
#' @export
lazy_vec <- function(altrep_interface) {

  meta_data <- list(
    list(  # interface methods
      lazy_vec_length
    ),
    parent.env(environment()),
    altrep_interface
  )

  lazy_vec_construct(meta_data)
}


lazy_vec_length <- function(x) {
  print(paste("lazy_vec_length called in R with argument", x))

  altrep_length(x)
}


#' Call R method through c
#'
#' @param f function
#' @param x argument
#'
#' @return result
#' @export
call_R <- function(f, x) {
  call_r_method(f, x, parent.env(environment()))
}
