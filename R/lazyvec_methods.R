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


#' Define a ALTREP interface
#'
#' With this method a complete ALTREP interface is defined using R functions. Calls to the custom
#' ALTREP vector will be diverted to these user functions.
#' 
#' @param lazyvec_init method to be called once upon deserialization (copying?) of a vector
#' @param method_length override for the ALTREP length method
#' @param method_dataptr_or_null  override for the ALTREP dataptr_or_null method
#' @param method_get_region override for the ALTREP get_region method
#' @param method_element override for the ALTREP element method
#' @param method_dataptr override for the ALTREP dataptr method
#' @param method_is_sorted override for the ALTREP is_sorted method
#' @param method_no_na override for the ALTREP no_na method
#' @param method_sum override for the ALTREP sum method
#' @param method_min override for the ALTREP min method
#' @param method_max override for the ALTREP max method
#' @param method_inspect override for the ALTREP inspect method
#' @param method_unserialize_ex override for the ALTREP unserialize_ex method
#' @param method_serialized_state override for the ALTREP serialized_state method
#' @param method_duplicate_ex override for the ALTREP duplicate_ex method
#' @param method_coerce override for the ALTREP coerce method
#' @param method_extract_subset override for the ALTREP extract_subset method
#'
#' @return object of type 'lazyvec_api' defining the set of methods to use for ALTREP calls
#' @export
lazyvec_methods <- function(lazyvec_init, method_length, method_dataptr_or_null, method_get_region,
  method_element, method_dataptr, method_is_sorted, method_no_na, method_sum, method_min,
  method_max, method_inspect, method_unserialize_ex, method_serialized_state,
  method_duplicate_ex, method_coerce, method_extract_subset) {

  # some checks on user function here
  
  methods <- list(
    method_length,
    method_dataptr_or_null,
    method_get_region,
    method_element,
    method_dataptr,
    method_is_sorted,
    method_no_na,
    method_sum,
    method_min,
    method_max,
    method_inspect,
    method_unserialize_ex,
    method_serialized_state,
    method_duplicate_ex,
    method_coerce,
    method_extract_subset,
    lazyvec_init
  )

  # some protection against arbitrary lists  
  class(methods) <- "lazyvec_api"
  
  methods
}


lazyvec_length <- function(x) {
  
  print(x)
  
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
