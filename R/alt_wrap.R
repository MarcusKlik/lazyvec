
#' Wrap an altrep vector
#'
#' @param altrep_vec altrep vector
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
    listener_is_sorted,
    listener_no_na,
    listener_sum,
    listener_min,
    listener_max,
    listener_inspect,
    listener_unserialize_ex,
    listener_serialized_state,
    listener_duplicate_ex,
    listener_coerce,
    listener_extract_subset
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


display_parameter <- function(x) {
  paste0(" ", crayon::magenta(typeof(x)),
         crayon::magenta("["), crayon::magenta(length(x)),
         crayon::magenta("] "), paste0(x, collapse = " "))
}


listener_length <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP length called: result = ")), display_parameter(x), "\n", sep = "")
}


listener_dataptr_or_null <- function(is_non_null_pointer) {

  cat(crayon::italic(crayon::cyan("ALTREP dataptr_or_null called, null returned: ")),
    display_parameter(is_non_null_pointer), "\n", sep = "")
}


listener_get_region <- function(arguments) {
  cat(crayon::italic(crayon::cyan("ALTREP get_region called: result = ")), display_parameter(arguments[3]),
      crayon::italic(crayon::cyan(", start = ")), display_parameter(arguments[1]),
      crayon::italic(crayon::cyan(", length = ")), display_parameter(arguments[2]), "\n", sep = "")
}


listener_element <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP element called: result = ")), display_parameter(x), "\n", sep = "")
}


listener_is_sorted <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP is_sorted called: result = ")), display_parameter(x == 1), "\n", sep = "")
}


listener_no_na <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP no_na called: result = ")), display_parameter(x == 1), "\n", sep = "")
}


listener_sum <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP sum called, na.rm = ")), display_parameter(x[[2]] == 1),
    crayon::italic(crayon::cyan(", result: ")), display_parameter(x[[1]]), "\n", sep = "")
}


listener_min <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP min called: result = ")), display_parameter(x), "\n", sep = "")
}


listener_max <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP max called: result = ")), display_parameter(x), "\n", sep = "")
}


listener_inspect <- function(x) {
  
  print(x)
  
  cat(crayon::italic(crayon::cyan("ALTREP inspect called: result = ")), display_parameter(x[[1]]),
    crayon::italic(crayon::cyan(", x = ")), display_parameter(x[[2]]),
    crayon::italic(crayon::cyan(", pre = ")), display_parameter(x[[3]]),
    crayon::italic(crayon::cyan(", deep = ")), display_parameter(x[[4]]),
    crayon::italic(crayon::cyan(", pVec = ")), display_parameter(x[[5]]), "\n", sep = "")
}


listener_serialized_state <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP serialized_state called: result = ")), display_parameter(x), "\n", sep = "")
}


listener_unserialize_ex <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP unserialize_ex called: result = ")), display_parameter(x), "\n", sep = "")
}


listener_dataptr <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP dataptr called: result = ")),
      format(as.hexmode(x[1]), width = 8),  # high address bytes
      format(as.hexmode(x[2]), width = 8),  # low bytes of address
      ", writable = ", as.logical(x[3]), "\n", sep = "")
}


listener_duplicate_ex <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP duplicate_ex called: result = ")), display_parameter(x), "\n", sep = "")
}


listener_coerce <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP coerce called: result = ")), display_parameter(x), "\n", sep = "")
}


listener_extract_subset <- function(x) {
  subset_result <- x[[1]]
  if (is.null(subset_result)) subset_result <- "NULL"
  cat(crayon::italic(crayon::cyan("ALTREP extract_subset called:\n  result = ")), display_parameter(subset_result),
    crayon::italic(crayon::cyan("\n    indx = ")), display_parameter(x[[2]]),
    crayon::italic(crayon::cyan("\n    call = ")), display_parameter(format(x[[3]])),
    "\n", sep = "")
}
