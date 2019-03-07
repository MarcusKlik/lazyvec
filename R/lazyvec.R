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
#' @param metadata custom metadata stored alongside the generated ALTREP vector.
#' @param vec_type data type required for the ALTREP vector, options are 'integer', 'double',
#' 'logical', 'raw' and 'character'. 
#' @param altrep_methods user-defined methods used by the resulting ALTREP vector.
#'
#' @return a user-defined ALTREP vector
#' @export
lazyvec <- function(metadata, vec_type, altrep_methods) {

  if (class(altrep_methods) != "lazyvec_api") {
    stop("Please use lazyvec_methods() to define the ALTREP methods for this vector")
  }

  payload <- list(

    # ALTREP payload for testing (remove later)
    1:10,

    # altrep API
    altrep_methods,

    # identifyer, used in diagnostic output
    "sample_range",

    # parent environment in which to evaluate listeners
    parent.env(environment()),

    # user-defined metadata
    metadata,

    NULL
  )

  if (vec_type == "integer") {
    return(lazyvec_integer_wrapper(payload))
  }

  if (vec_type == "double") {
    return(lazyvec_real_wrapper(payload))
  }

  if (vec_type == "logical") {
    return(lazyvec_logical_wrapper(payload))
  }

  if (vec_type == "raw") {
    return(lazyvec_raw_wrapper(payload))
  }

  if (vec_type == "character") {
    return(lazyvec_string_wrapper(payload))
  }
}
