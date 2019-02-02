
#' Wrap an altrep vector
#'
#' @param altrep_vec altrep vector
#' @param length_method optional override for the length diagnostic method
#' @param dataptr_or_null_method optional override for the dataptr_or_null diagnostic method
#' @param get_region_listener optional override for the get_region diagnostic method
#' @param element_method optional override for the element diagnostic method
#' @param dataptr_listener optional override for the dataptr diagnostic method
#'
#' @return a wrapper around the altrep vector which is an altrep vector itself
#' @export
alt_wrap <- function(altrep_vec) {

  # package listener methods
  listeners <- c(
    listener_length,
    listener_dataptr_or_null,
    listener_get_region,
    listener_element,
    listener_dataptr,
    listener_is_sorted
  )
  
  meta_data <- list(

    # ALTREP payload
    altrep_vec,

    # package listener methods
    listeners,

    # parent environment in which to evaluate listeners
    parent.env(environment())
  )

  construct_altrep_wrapper(meta_data)
}


listener_length <- function(x) {

  cat(crayon::italic(crayon::cyan("ALTREP length called: ")), x, "\n")
}


listener_dataptr_or_null <- function(is_non_null_pointer) {

  cat(crayon::italic(crayon::cyan("ALTREP dataptr_or_null called, null returned: ")), is_non_null_pointer, "\n")
}


listener_get_region <- function(arguments) {

  cat(crayon::italic(crayon::cyan("ALTREP get_region called: ")),
    "[ start: ", arguments[1],
    ", length: ", arguments[2],
    ", length result: ", arguments[3], "]\n")
}


listener_element <- function(x) {

  cat(crayon::italic(crayon::cyan("ALTREP element called: ")), x, "\n")
}


listener_is_sorted <- function(x) {
  
  cat(crayon::italic(crayon::cyan("ALTREP is_sorted called: ")), x, "\n")
}


listener_dataptr <- function(x) {

  cat(crayon::italic(crayon::cyan("ALTREP dataptr called: ")),
      format(as.hexmode(x[1]), width = 8),  # high address bytes
      format(as.hexmode(x[2]), width = 8),  # low bytes of address
      as.logical(x[3]), "\n")
}
