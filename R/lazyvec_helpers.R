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


#' Diagnostic methods to check boundaries and validity of return values of the
#' user lazyvecdefined API,
#'
#' @return list of diagnostic functions
diagnostics <- function() {
  list(
    diagnostic_length,
    diagnostic_dataptr_or_null,
    diagnostic_get_region,
    diagnostic_element,
    diagnostic_dataptr,
    diagnostic_is_sorted,
    diagnostic_no_na,
    diagnostic_sum,
    diagnostic_min,
    diagnostic_max,
    diagnostic_inspect,
    diagnostic_unserialize_ex,
    diagnostic_serialized_state,
    diagnostic_duplicate_ex,
    diagnostic_coerce,
    diagnostic_extract_subset
  )
}


diagnostic_length <- function(x) {
  cat(crayon::italic(
    crayon::cyan(x[[1]], ": ALTREP length : result =")),
    display_parameter(x[[2]]), "\n", sep = "")
}


diagnostic_dataptr_or_null <- function(x) {
  cat(crayon::italic(
    crayon::cyan(x[[1]], ": ALTREP dataptr_or_null, null returned: ")),
    display_parameter(x[[2]]), "\n", sep = "")
}


diagnostic_get_region <- function(x) {
  cat(crayon::italic(
    crayon::cyan(x[[1]], ": ALTREP get_region : result =")),
    display_parameter(x[[4]]),
    crayon::italic(crayon::cyan(", start =")),
    display_parameter(x[[2]]),
    crayon::italic(crayon::cyan(", length =")),
    display_parameter(x[[3]]), "\n", sep = "")
}


diagnostic_element <- function(x) {
  cat(crayon::italic(
    crayon::cyan(x[[1]], ": ALTREP element : result =")),
    display_parameter(x[[2]]), "\n", sep = "")
}


diagnostic_is_sorted <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP is_sorted: result =")),
      display_parameter(x == 1), "\n", sep = "")
}


diagnostic_no_na <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP no_na: result =")),
      display_parameter(x == 1), "\n", sep = "")
}


diagnostic_sum <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP sum: na.rm =")),
      display_parameter(x[[2]] == 1),
      crayon::italic(crayon::cyan(", result: ")),
      display_parameter(x[[1]]), "\n", sep = "")
}


diagnostic_min <- function(x) {
  cat(crayon::italic(
    crayon::cyan(x[[1]], ": ALTREP min: result =")),
    display_parameter(x[[2]]), "\n", sep = "")
}


diagnostic_max <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP max: result =")),
      display_parameter(x), "\n", sep = "")
}


diagnostic_inspect <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP inspect: result =")),
      display_parameter(x[[1]]),
      crayon::italic(crayon::cyan(", pre =")),
      display_parameter(x[[2]]),
      crayon::italic(crayon::cyan(", deep =")),
      display_parameter(x[[3]]),
      crayon::italic(crayon::cyan(", pVec =")),
      display_parameter(x[[4]]), "\n", sep = "")
}


diagnostic_serialized_state <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP serialized_state: result =")),
      display_parameter(x), "\n", sep = "")
}


diagnostic_unserialize_ex <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP unserialize_ex: altwrap_class =")),
      display_parameter(x[[1]]),
      crayon::italic(crayon::cyan(", state =")),
      display_parameter(x[[2]]),
      crayon::italic(crayon::cyan(", attr =")),
      display_parameter(x[[3]]),
      crayon::italic(crayon::cyan(", objf =")),
      display_parameter(x[[4]]),
      crayon::italic(crayon::cyan(", levs =")),
      display_parameter(x[[5]]))
}


diagnostic_unserialize <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP unserialize_ex: altwrap_class =")),
      display_parameter(x[[1]]),
      crayon::italic(crayon::cyan(", state =")),
      display_parameter(x[[2]]))
}


diagnostic_dataptr <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP dataptr: result =")),
      format(as.hexmode(x[1]), width = 8),  # high address bytes
      format(as.hexmode(x[2]), width = 8),  # low bytes of address
      ", writable = ", as.logical(x[3]), "\n", sep = "")
}


diagnostic_duplicate_ex <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP duplicate_ex: result = ?")),
      # crayon::italic(crayon::cyan(", altwrap_class = ")),
      # display_parameter(x[[1]]),
      # crayon::italic(crayon::cyan(", state = ")),
      # display_parameter(x[[2]]),
      # crayon::italic(crayon::cyan(", attr = ")),
      # display_parameter(x[[3]]),
      # crayon::italic(crayon::cyan(", objf = ")),
      # display_parameter(x[[4]]),
      crayon::italic(crayon::cyan(", levs =")),
      display_parameter(x[[5]]))
}


diagnostic_coerce <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP coerce: result =")),
      display_parameter(x), "\n", sep = "")
}


diagnostic_extract_subset <- function(x) {
  subset_result <- x[[1]]
  if (is.null(subset_result)) subset_result <- "NULL"
  cat(crayon::italic(crayon::cyan("ALTREP extract_subset:  result =")),
      display_parameter(subset_result),
      crayon::italic(crayon::cyan(", indx =")),
      display_parameter(x[[2]]),
      crayon::italic(crayon::cyan(", call =")),
      display_parameter(str(x[[3]])),
      "\n", sep = "")
}
