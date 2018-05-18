

#' Generic function to emulate the altrep unserialize method
#'
#' @param x a state object
#' @param ...
#'
#' @return result of the altrep unserialize method
#' @export
altrep_unserialize <- function (x, ...) {
  UseMethod("altrep_unserialize", x)
}


#' Generic function to emulate the altrep unserialize method
#'
#' @param x a state object
#' @param ...
#'
#' @return result of the altrep unserialize method
#' @export
altrep_serialized_state <- function (x, ...) {
  UseMethod("altrep_serialized_state", x)
}


#' Generic function to emulate the altrep inspect method
#'
#' @param x a state object
#' @param ...
#'
#' @return result of the altrep inspect method
#' @export
altrep_inspect <- function (x, ...) {
  UseMethod("altrep_inspect", x)
}


#' Generic function to emulate the altrep length method
#'
#' @param x a state object
#' @param ...
#'
#' @return result of the altrep length method
#' @export
altrep_length <- function (x, ...) {
  UseMethod("altrep_length", x)
}


#' Generic function to emulate the altrep dataptr method
#'
#' @param x a state object
#' @param ...
#'
#' @return result of the altrep dataptr method
#' @export
altrep_dataptr <- function (x, ...) {
  UseMethod("altrep_dataptr", x)
}


#' Generic function to emulate the altrep element method
#'
#' @param x a state object
#' @param ...
#'
#' @return result of the altrep element method
#' @export
altrep_element <- function (x, ...) {
  UseMethod("altrep_element", x)
}


#' Generic function to emulate the altrep get_region method
#'
#' @param x a state object
#' @param ...
#'
#' @return result of the altrep get_region method
#' @export
altrep_get_region <- function (x, ...) {
  UseMethod("altrep_get_region", x)
}
