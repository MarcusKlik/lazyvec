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


#' Generate a fully functional lazyvec implementation from a selection of examples
#'
#' With this method you can generate a single-file sample implementation of a lazyvec.
#' This sample implementation can be used as a starting point for custom implementations.
#' For a detailed description of the sample implementations, please see the corresponding
#' vignette.
#' 
#' The following sample implementations are available:
#' * _int_range_: an integer range with a custom step size
#' * _real_range_: a range of double's with a custom step size
#' * _logical_compressed_: a compressed logical vector
#' * _raw_ondisk_: a file based out-of-memory raw vector
#' * _character_range_: the character vector equivalent of an integers range n:m
#'
#' @param skeleton_id id of the sample implementation. Valid id's are:
#' @param path path to the target file
#'
#' @export
#'
#' @md
lazyvec_skeleton <- function(skeleton_id, path) {
  valid_ids <- c("int_range", "real_range", "logical_compressed", "raw_ondisk", "character_range")

  if (!(skeleton_id %in% valid_ids)) {
    stop("Invalid skeleton_id. Please select one of the following id's: '",
      paste(valid_ids[1:length(valid_ids) - 1], collapse = "', '"), "' or '", tail(valid_ids, 1), "'.")
  }

  if (file.exists(path)) {
    stop("target path already exists, please select a path to a non-existing file")
  }

  if (!dir.exists(dirname(path))) {
    stop("target path points to a non-existing folder, please create the folder first")
  }

  sample_path <- paste0(path.package("lazyvec"), "/lazyvec_samples/", skeleton_id, ".R")
  
  file.copy(sample_path, path)
  
  invisible(NULL)
}
