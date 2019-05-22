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


#' @useDynLib lazyvec, .registration = TRUE
#' @importFrom Rcpp evalCpp
#' @importFrom crayon italic
#' @importFrom crayon cyan
#' @importFrom utils str
#' @importFrom utils tail
#' @importFrom utils packageVersion
NULL


#' Return lazyvec version identifier
#' 
#' The version is calculated as: `256 * major_version + 16 * minor_version + patch_version`
lazyvec_version <- function() {
  17
}
