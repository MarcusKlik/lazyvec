#  lazyvec - R package for creating, testing and deploying custom ALTREP vectors
#
#  Copyright (C) 2019-present, Mark AJ Klik
#
#  This file is part of the lazyvec R package.
#
#  The lazyvec R package is free software: you can redistribute it and/or modify it
#  under the terms of the GNU Affero General Public License version 3 as
#  published by the Free Software Foundation.
#
#  The lazyvec R package is distributed in the hope that it will be useful, but
#  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
#  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License
#  for more details.
#
#  You should have received a copy of the GNU Affero General Public License along
#  with the lazyvec R package. If not, see <http://www.gnu.org/licenses/>.
#
#  You can contact the author at:
#  - lazyvec R package source repository : https://github.com/fstpackage/lazyvec


altrep_listeners <- function() {
  c(
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
}

#' Add listeners to an ALTREP vector to eavesdrop on all internal ALTREP calls 
#' 
#' This method adds a set of listeners to an ALTREP vector that can be used to
#' track all internal ALTREP calls. Diagnostic information is shown on the specific
#' calls that are made from the R language and the data returned from the ALTREP vector.
#'
#' @param altrep_vec altrep vector
#' @param vec_id custom id of the ALTREP vector, used in diagnostic output
#'
#' @export
altrep_listener <- function(altrep_vec, vec_id) {

  if (!is_altrep(altrep_vec)) {
    stop("vector is not an ALTREP vector.")
  }

  meta_data <- list(

    # ALTREP payload
    altrep_vec,

    # package listener methods
    altrep_listeners(),

    # identifier, used in diagnostic output
    vec_id,

    # lazyvec package version
    lazyvec_version = lazyvec_version(),

    # parent environment in which to evaluate listeners
    parent.env(environment())
  )

  if (typeof(altrep_vec) == "integer") {
    return(altrep_integer_wrapper(meta_data))
  }

  if (typeof(altrep_vec) == "double") {
    return(altrep_real_wrapper(meta_data))
  }

  if (typeof(altrep_vec) == "logical") {
    return(altrep_logical_wrapper(meta_data))
  }

  if (typeof(altrep_vec) == "raw") {
    return(altrep_raw_wrapper(meta_data))
  }

  if (typeof(altrep_vec) == "character") {
    return(altrep_string_wrapper(meta_data))
  }
}


display_parameter <- function(x) {
  paste0(" ", crayon::magenta(short_types[typeof(x)]),
         crayon::magenta("["), crayon::magenta(length(x)),
         crayon::magenta("] "), paste0(x, collapse = " "))
}


listener_length <- function(x) {
  cat(crayon::italic(
    crayon::cyan(x[[1]], ": ALTREP length : result =")),
    display_parameter(x[[2]]), "\n", sep = "")
}


listener_dataptr_or_null <- function(x) {

  cat(crayon::italic(
    crayon::cyan(x[[1]], ": ALTREP dataptr_or_null, null returned: ")),
    display_parameter(x[[2]]), "\n", sep = "")
}


listener_get_region <- function(x) {
  cat(crayon::italic(
    crayon::cyan(x[[1]], ": ALTREP get_region : result =")),
      display_parameter(x[[4]]),
      crayon::italic(crayon::cyan(", start =")),
      display_parameter(x[[2]]),
      crayon::italic(crayon::cyan(", length =")),
      display_parameter(x[[3]]), "\n", sep = "")
}


listener_element <- function(x) {
  cat(crayon::italic(
    crayon::cyan(x[[1]], ": ALTREP element : result =")),
      display_parameter(x[[2]]), "\n", sep = "")
}


listener_is_sorted <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP is_sorted: result =")),
      display_parameter(x == 1), "\n", sep = "")
}


listener_no_na <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP no_na: result =")),
    display_parameter(x == 1), "\n", sep = "")
}


listener_sum <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP sum: na.rm =")),
    display_parameter(x[[2]] == 1),
    crayon::italic(crayon::cyan(", result: ")),
    display_parameter(x[[1]]), "\n", sep = "")
}


listener_min <- function(x) {
  cat(crayon::italic(
    crayon::cyan(x[[1]], ": ALTREP min: result =")),
    display_parameter(x[[2]]), "\n", sep = "")
}


listener_max <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP max: result =")),
    display_parameter(x), "\n", sep = "")
}


listener_inspect <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP inspect: result =")),
    display_parameter(x[[1]]),
    crayon::italic(crayon::cyan(", pre = ")),
    display_parameter(x[[2]]),
    crayon::italic(crayon::cyan(", deep = ")),
    display_parameter(x[[3]]),
    crayon::italic(crayon::cyan(", pVec = ")),
    display_parameter(x[[4]]), "\n", sep = "")
}


listener_serialized_state <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP serialized_state: result =")),
    display_parameter(x), "\n", sep = "")
}


listener_unserialize_ex <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP unserialize_ex: result = ")),
    display_parameter(x), "\n", sep = "")
}


listener_dataptr <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP dataptr: result =")),
      format(as.hexmode(x[1]), width = 8),  # high address bytes
      format(as.hexmode(x[2]), width = 8),  # low bytes of address
      ", writable = ", as.logical(x[3]), "\n", sep = "")
}


listener_duplicate_ex <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP duplicate_ex: result = ?")),
    # crayon::italic(crayon::cyan(", altwrap_class = ")),
    # display_parameter(x[[1]]),
    # crayon::italic(crayon::cyan(", state = ")),
    # display_parameter(x[[2]]),
    # crayon::italic(crayon::cyan(", attr = ")),
    # display_parameter(x[[3]]),
    # crayon::italic(crayon::cyan(", objf = ")),
    # display_parameter(x[[4]]),
    crayon::italic(crayon::cyan(", levs = ")),
    display_parameter(x[[5]]))
}


listener_coerce <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP coerce: result =")),
    display_parameter(x), "\n", sep = "")
}


listener_extract_subset <- function(x) {
  subset_result <- x[[1]]
  if (is.null(subset_result)) subset_result <- "NULL"
  cat(crayon::italic(crayon::cyan("ALTREP extract_subset:  result =")),
    display_parameter(subset_result),
    crayon::italic(crayon::cyan(", indx = ")),
    display_parameter(x[[2]]),
    crayon::italic(crayon::cyan(", call = ")),
    display_parameter(str(x[[3]])),
    "\n", sep = "")
}
