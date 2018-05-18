
#' Generic function to emulate the altrep length method
#'
#' @param x a state object
#' @param ... additional arguments, ignored
#'
#' @return result of the altrep length method
#' @export
altrep_length <- function (x, ...) {
  UseMethod("altrep_length", x)
}


#' Retrieve a single element from a vector
#'
#' @param x a state object
#' @param i index of the element to retrieve
#' @param ... additional arguments, ignored
#'
#' @return result of the altrep element method
#' @export
altrep_element <- function (x, i, ...) {
  UseMethod("altrep_element")
}


#' Generic function to emulate the altrep get_region method
#'
#' @param x a state object
#' @param i starting index of the vector region to retrieve
#' @param nr_of_elements number of elements to retrieve
#' @param ... additional arguments, ignored
#'
#' @return result of the altrep get_region method
#' @export
altrep_get_region <- function (x, i, nr_of_elements, ...) {
  UseMethod("altrep_get_region", x)
}
