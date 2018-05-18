

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


#' Generic function to emulate the altrep unserialize method
#'
#' @param x a state object
#' @param ...
#'
#' @return result of the altrep unserialize method
#' @export
altrep_unserialize.native_vec <- function (x, ...) {
  NULL
}


#' Generic function to emulate the altrep unserialize method
#'
#' @param x a state object
#' @param ...
#'
#' @return result of the altrep unserialize method
#' @export
altrep_serialized_state.native_vec <- function (x, ...) {
  NULL
}


#' Generic function to emulate the altrep inspect method
#'
#' @param x a state object
#' @param ...
#'
#' @return result of the altrep inspect method
#' @export
vec.altrep_inspect.native_vec <- function (x, ...) {
  NULL
}


#' Generic function to emulate the altrep length method
#'
#' @param x a state object
#' @param ...
#'
#' @return integer result of the altrep length method
#' @export
altrep_length.native_vec <- function (x, ...) {
  length(x)
}


#' Generic function to emulate the altrep dataptr method
#'
#' @param x a state object
#' @param ...
#'
#' @return result of the altrep dataptr method
#' @export
altrep_dataptr.native_vec <- function (x, ...) {
  NULL
}


#' Generic function to emulate the altrep element method
#'
#' @param x a state object
#' @param ...
#'
#' @return result of the altrep element method
#' @export
altrep_element.native_vec <- function (x, ...) {
  x
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
