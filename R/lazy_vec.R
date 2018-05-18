
#' Create an altrep vector from an R interface
#'
#' @param altrep_interface altrep_interface object
#'
#' @return an altrep vector
#' @export
lazy_vec <- function(altrep_interface) {

  meta_data <- list(
    list(  # interface methods
      lazy_vec_length,
      lazy_vec_element
    ),
    parent.env(environment()),
    altrep_interface
  )

  lazy_vec_construct(meta_data)
}


lazy_vec_element <- function(x) {

  element <- altrep_element(x)

  print(paste("Element returned:", element))

  if (!is.integer(element) | length(element) != 1) {
    stop("generic method lazy_vec_element should return a length 1 integer value")
  }

  element
}

lazy_vec_length <- function(x) {

  vec_length <- altrep_length(x)

  if (!is.integer(vec_length) | length(vec_length) != 1) {
    stop("generic method lazy_vec_length should return a length 1 integer value")
  }

  vec_length
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
