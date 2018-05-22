
#' Wrap an altrep vector
#'
#' @param altrep_vec altrep vector
#' @param length_method optional override for the length diagnostic method
#' @param element_method optional override for the element diagnostic method
#' @param get_region_method optional override for the get_region diagnostic method
#'
#' @return a wrapper around the altrep vector which is an altrep vector itself
#' @export
alt_wrap <- function(altrep_vec, length_method = NULL, dataptr_or_null_method = NULL, get_region_listener = NULL,
  element_method = NULL) {

  # package listener methods
  listeners <- list()

  # lengh method
  if (!is.null(length_method)) {
    listeners <- c(listeners, length_method)
  } else {
    listeners <- c(listeners, listener_length)
  }

  # dataptr_or_null method
  if (!is.null(dataptr_or_null_method)) {
    listeners <- c(listeners, dataptr_or_null_method)
  } else {
    listeners <- c(listeners, listener_dataptr_or_null)
  }

  # get_region listener
  if (!is.null(get_region_listener)) {
    listeners <- c(listeners, get_region_listener)
  } else {
    listeners <- c(listeners, listener_get_region)
  }

  # element method
  if (!is.null(element_method)) {
    listeners <- c(listeners, element_method)
  } else {
    listeners <- c(listeners, listener_element)
  }

  meta_data <- list(

    # ALTREP payload
    altrep_vec,

    # package listener methods
    listeners,

    # parent environment in which to evaluate listeners
    parent.env(environment())
  )

  altrep_wrapper_construct(meta_data)
}


listener_length <- function(x) {

  print(paste("ALTREP length called:", x))
}


listener_dataptr_or_null <- function(is_non_null_pointer) {

  print(paste("ALTREP dataptr_or_null called:", is_non_null_pointer))
}


listener_get_region <- function(arguments) {

  print(paste0("ALTREP get_region called: [", paste(arguments, collapse = ", "), "]"))
}


listener_element <- function(x) {

  element <- altrep_element(x)

  print(paste("Element returned:", element))

  if (!is.integer(element) | length(element) != 1) {
    stop("generic method lazy_vec_element should return a length 1 integer value")
  }

  element
}
