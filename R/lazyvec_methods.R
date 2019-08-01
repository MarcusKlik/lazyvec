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


#' Define the lazyvec interface
#'
#' With this method a complete ALTREP interface is defined using R functions. Calls to the custom
#' ALTREP vector will be diverted to these user functions.
#' 
#' @param method_length override for the ALTREP length method
#' @param method_full_vector generates the full expanded vector
#' @param method_get_region override for the ALTREP get_region method
#' @param method_element override for the ALTREP element method
#' @param method_is_sorted override for the ALTREP is_sorted method
#' @param method_no_na override for the ALTREP no_na method
#' @param method_sum override for the ALTREP sum method
#' @param method_min override for the ALTREP min method
#' @param method_max override for the ALTREP max method
#' @param method_duplicate_ex override for the ALTREP duplicate method
#' @param method_inspect override for the ALTREP inspect method
#' @param method_unserialize_ex override for the ALTREP unserialize_ex method
#' @param method_serialized_state override for the ALTREP serialized_state method
#' @param method_coerce override for the ALTREP coerce method
#' @param method_extract_subset override for the ALTREP extract_subset method
#' @param method_init init your vector after deserialization
#'
#' @return object of type 'lazyvec_api' defining the set of methods to use for ALTREP calls
#' @export
lazyvec_methods <- function(
  method_length,
  method_full_vector = NULL,
  method_element = NULL,
  method_is_sorted = NULL,
  method_no_na = NULL,
  method_extract_subset = NULL,
  method_coerce = NULL,
  method_get_region = NULL,
  method_sum = NULL,
  method_min = NULL,
  method_max = NULL,
  method_duplicate = NULL,
  method_init = NULL,
  method_inspect = NULL,
  method_unserialize_ex = NULL,
  method_serialized_state = NULL) {

  # some checks on user functions here

  methods <- list(
    method_length,
    NULL, # method_dataptr_or_null
    method_get_region,
    method_element,
    method_full_vector,
    method_is_sorted,
    method_no_na,
    method_sum,
    method_min,
    method_max,
    method_extract_subset,
    method_duplicate,
    method_inspect,
    method_unserialize_ex,
    method_serialized_state,
    method_coerce,
    method_init
  )

  # some protection against arbitrary lists
  class(methods) <- "lazyvec_api"

  methods
}
