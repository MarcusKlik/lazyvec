

#' Create a altrep interface object of class 'native_vec'
#'
#' @param vec an ordinary R vector
#'
#' @return object of class 'native_vec' for which the altrep generics are implemented
#' @export
native_vec <- function(vec) {

  native_vec_object <- list(
    native_vec = vec
  )

  class(native_vec_object) <- "native_vec"

  native_vec_object
}

#' Generic function to emulate the altrep length method
#'
#' @param x a state object
#' @param ...
#'
#' @return integer result of the altrep length method
#' @export
altrep_length.native_vec <- function (x, ...) {

  length(x$native_vec)
}


#' Generic function to emulate the altrep element method
#'
#' @param x a state object
#' @param ...
#'
#' @return result of the altrep element method
#' @export
altrep_element.native_vec <- function (x, ...) {

  x$native_vec[5]
}


#' Generic function to emulate the altrep get_region method
#'
#' @param x a state object
#' @param ...
#'
#' @return result of the altrep get_region method
#' @export
altrep_get_region.native_vec <- function (x, ...) {
  NULL
}
