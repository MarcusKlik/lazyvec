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


#' Test if object has altrep representation
#'
#' @param x the object to be tested
#'
#' @return TRUE if the object is an altrep vector
#' @export
is_altrep <- function(x) {
  is_altrep_vector(x) == 1
}


#' Retrieve the ALTREP class descriptor
#'
#' @param x ALTREP vector for which to determine the ALTREP class descriptor
#'
#' @return ALTREP class descriptor
#' @export
altrep_class <- function(x) {
  if (!is_altrep(x)) return(NULL)

  as.character(altrep_full_class(x)[[1]])
}


#' Retrieve the package in which a ALTREP vector is defined
#'
#' @param x ALTREP vector for which to determine the package
#'
#' @return package that contains the ALTREP class definition
#' @export
altrep_package <- function(x) {
  altrep_check(x)

  as.character(altrep_full_class(x)[[2]])
}


altrep_check <- function(x) {
  if (!is_altrep(x)) {
    stop("Vector is not an ALTREP vector")
  }
}
