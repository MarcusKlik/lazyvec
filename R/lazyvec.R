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


#' Define a custom ALTREP vector
#' 
#' This method creates a user-defined ALTREP vector with the complete ALTREP API created
#' in R instead of C/C++ sources.
#'
#' @param altrep_vec altrep vector
#' @param vec_id id of the custom ALTREP vector
#'
#' @return a user-defined ALTREP vector
#' @export
lazyvec <- function(altrep_vec, vec_id) {

  if (!is_altrep(altrep_vec)) {
    stop("vector is not an ALTREP vector.")
  }

  meta_data <- list(

    # ALTREP payload
    altrep_vec,

    # package listener methods
    c(
      lazyvec_length,
      lazyvec_dataptr_or_null,
      lazyvec_get_region,
      lazyvec_element,
      lazyvec_dataptr,
      lazyvec_is_sorted,
      lazyvec_no_na,
      lazyvec_sum,
      lazyvec_min,
      lazyvec_max,
      lazyvec_inspect,
      lazyvec_unserialize_ex,
      lazyvec_serialized_state,
      lazyvec_duplicate_ex,
      lazyvec_coerce,
      lazyvec_extract_subset
    ),

    # identifyer, used in diagnostic output
    vec_id,

    # parent environment in which to evaluate listeners
    parent.env(environment())
  )

  if (typeof(altrep_vec) == "integer") {
    return(lazyvec_integer_wrapper(meta_data))
  }

  if (typeof(altrep_vec) == "double") {
    return(lazyvec_real_wrapper(meta_data))
  }

  if (typeof(altrep_vec) == "logical") {
    return(lazyvec_logical_wrapper(meta_data))
  }

  if (typeof(altrep_vec) == "raw") {
    return(lazyvec_raw_wrapper(meta_data))
  }

  if (typeof(altrep_vec) == "character") {
    return(lazyvec_string_wrapper(meta_data))
  }
}


lazyvec_length <- function(x) {
  cat(crayon::italic(
    crayon::cyan(x[[1]], ": ALTREP length : result =")),
    display_parameter(x[[2]]), "\n", sep = "")

  5L
}


lazyvec_dataptr_or_null <- function(x) {

  cat(crayon::italic(
    crayon::cyan(x[[1]], ": ALTREP dataptr_or_null called, null returned: ")),
    display_parameter(x[[2]]), "\n", sep = "")
}


lazyvec_get_region <- function(x) {
  cat(crayon::italic(
    crayon::cyan(x[[1]], ": ALTREP get_region : result =")),
    display_parameter(x[[4]]),
    crayon::italic(crayon::cyan(", start =")),
    display_parameter(x[[2]]),
    crayon::italic(crayon::cyan(", length =")),
    display_parameter(x[[3]]), "\n", sep = "")
}


lazyvec_element <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP element : result =")),
      display_parameter(x), "\n", sep = "")
}


lazyvec_is_sorted <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP is_sorted : result =")),
      display_parameter(x == 1), "\n", sep = "")
}


lazyvec_no_na <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP no_na : result =")),
      display_parameter(x == 1), "\n", sep = "")
}


lazyvec_sum <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP sum called, na.rm = ")),
      display_parameter(x[[2]] == 1),
      crayon::italic(crayon::cyan(", result: ")),
      display_parameter(x[[1]]), "\n", sep = "")
}


lazyvec_min <- function(x) {
  cat(crayon::italic(
    crayon::cyan(x[[1]], ": ALTREP min : result =")),
    display_parameter(x[[2]]), "\n", sep = "")
}


lazyvec_max <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP max : result =")),
      display_parameter(x), "\n", sep = "")
}


lazyvec_inspect <- function(x) {

  print(x)

  cat(crayon::italic(crayon::cyan("ALTREP inspect : result =")),
      display_parameter(x[[1]]),
      crayon::italic(crayon::cyan(", x = ")),
      display_parameter(x[[2]]),
      crayon::italic(crayon::cyan(", pre = ")),
      display_parameter(x[[3]]),
      crayon::italic(crayon::cyan(", deep = ")),
      display_parameter(x[[4]]),
      crayon::italic(crayon::cyan(", pVec = ")),
      display_parameter(x[[5]]), "\n", sep = "")
}


lazyvec_serialized_state <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP serialized_state : result =")),
      display_parameter(x), "\n", sep = "")
}


lazyvec_unserialize_ex <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP unserialize_ex : result =")),
      display_parameter(x), "\n", sep = "")
}


lazyvec_dataptr <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP dataptr : result =")),
      format(as.hexmode(x[1]), width = 8),  # high address bytes
      format(as.hexmode(x[2]), width = 8),  # low bytes of address
      ", writable = ", as.logical(x[3]), "\n", sep = "")
}


lazyvec_duplicate_ex <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP duplicate_ex : result =")),
      display_parameter(x), "\n", sep = "")
}


lazyvec_coerce <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP coerce : result =")),
      display_parameter(x), "\n", sep = "")
}


lazyvec_extract_subset <- function(x) {
  subset_result <- x[[1]]
  if (is.null(subset_result)) subset_result <- "NULL"
  cat(crayon::italic(crayon::cyan("ALTREP extract_subset :\n  result =")),
      display_parameter(subset_result),
      crayon::italic(crayon::cyan("\n    indx = ")),
      display_parameter(x[[2]]),
      crayon::italic(crayon::cyan("\n    call = ")),
      display_parameter(str(x[[3]])),
      "\n", sep = "")
}
