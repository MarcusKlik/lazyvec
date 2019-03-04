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
