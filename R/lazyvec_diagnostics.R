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
    NULL,  # diagnostic_dataptr_or_null
    diagnostic_get_region,
    diagnostic_element,
    diagnostic_full_vec,
    diagnostic_is_sorted,
    diagnostic_no_na,
    diagnostic_sum,
    diagnostic_min,
    diagnostic_max,
    diagnostic_extract_subset,
    NULL,  # diagnostic_duplicate,
    diagnostic_inspect,
    diagnostic_unserialize_ex,
    diagnostic_serialized_state,
    diagnostic_coerce
  )
}


user_method_length           <- 1
user_method_dataptr_or_null  <- 2
user_method_get_region       <- 3
user_method_element          <- 4
user_method_full_vec         <- 5
user_method_is_sorted        <- 6
user_method_no_na            <- 7
user_method_sum              <- 8
user_method_min              <- 9
user_method_max              <- 10
user_method_extract_subset   <- 11
# user_method_duplicate removed at position 12
user_method_inspect          <- 13
user_method_unserialize_ex   <- 14
user_method_serialized_state <- 15
user_method_coerce           <- 16


run_user_method <- function(method_id, x) {

  # run user method
  result <- tryCatch(
    x$user_methods[[method_id]](x$user_data),
    error = function(e) { e },  # nolint
    warning = function(w) { w }  # nolint
  )

  if (is(result, "error")) stop("Error detected in user method: ", result$message)

  if (is(result, "warning")) stop("Warning detected in user method: ", result$message)

  result
}


run_user_method2 <- function(method_id, x, arg2) {

  # run user method
  result <- tryCatch(
    x$user_methods[[method_id]](x$user_data, arg2),
    error = function(e) { e },  # nolint
    warning = function(w) { w }  # nolint
  )

  if (is(result, "error")) stop("Error detected in user method: ", result$message)

  if (is(result, "warning")) stop("Warning detected in user method: ", result$message)

  result
}


run_user_method3 <- function(method_id, x, arg2, arg3) {

  # run user method
  result <- tryCatch(
    x$user_methods[[method_id]](x$user_data, arg2, arg3),
    error = function(e) { e },  # nolint
    warning = function(w) { w }  # nolint
  )

  if (is(result, "error")) stop("Error detected in user method: ", result$message)

  if (is(result, "warning")) stop("Warning detected in user method: ", result$message)

  result
}


check_type <- function(x, result, method_name) {
  if (typeof(result) != x$vec_type) stop("Method ", method_name, " generated a vector of type '",
    typeof(result), "', but the lazyvec is of type '", x$vec_type, "'")
}


check_type_logical <- function(result, method_name) {
  if (typeof(result) != "logical") stop("Method ", method_name, " generated a '",
    typeof(result), "' result where a 'logical' was expected")
}


check_fixed_length <- function(result, method_name, expected_length) {
  if (length(result) != expected_length) stop("Method ", method_name, " generated a result of length ",
    length(result), " where a length ", expected_length, " was expected")
}


check_length <- function(x, result, method_name) {
  vec_length <- run_user_method(user_method_length, x)

  if (vec_length != length(result)) stop("Method ", method_name, " generated a result of length ",
    length(result), " while method length() says the length should be ", vec_length)
}


diagnostic_length <- function(x) {

  result <- run_user_method(user_method_length, x)

  if (length(result) != 1) stop("Length method should return a length 1 integer vector")

  if (typeof(result) != "integer") stop("Length method should return an integer vector, not a ", typeof(result))

  # report result
  cat(crayon::italic(
    crayon::cyan(x$vec_id, ": length : result = ")),
    display_parameter(result), "\n", sep = "")

  result
}


diagnostic_full_vec <- function(x) {
  result <- run_user_method(user_method_full_vec, x)

  check_type(x, result, "full_vec")

  check_length(x, result, "full_vec")

  cat(crayon::italic(
    crayon::cyan(x$vec_id, ": full_vec result = ")),
    display_parameter(result), "\n", sep = "")

  result
}


diagnostic_inspect <- function(x) {

  cat(crayon::italic(
    crayon::cyan(x$vec_id, " inspect: result = ")),
      display_parameter(x[[1]]),
      crayon::italic(crayon::cyan(", pre =")),
      display_parameter(x[[2]]),
      crayon::italic(crayon::cyan(", deep =")),
      display_parameter(x[[3]]),
      crayon::italic(crayon::cyan(", pVec =")),
      display_parameter(x[[4]]), "\n", sep = "")
}


diagnostic_element <- function(x, i) {

  result <- run_user_method2(user_method_element, x, i)

  check_type(x, result, "element")

  vec_length <- run_user_method(user_method_length, x)

  if (i > vec_length) warning("Method element called with index larger than length()")

  cat(crayon::italic(
    crayon::cyan(x$vec_id, ": element : result = ")),
    display_parameter(result), "\n", sep = "")

  result
}


diagnostic_get_region <- function(x, i, n) {

  result <- run_user_method3(user_method_get_region, x, i, n)

  check_type(x, result, "get_region")

  vec_length <- run_user_method(user_method_length, x)

  if (i > vec_length) warning("Method element called with index larger than length()")

  if (i + n > vec_length) warning("Method element called with range outside the vector")

  cat(crayon::italic(
    crayon::cyan(x$vec_id, ": get_region : result = ")),
    display_parameter(result), "\n", sep = "")

  result
}


diagnostic_is_sorted <- function(x) {
  result <- run_user_method(user_method_is_sorted, x)

  check_type_logical(result, "is_sorted")
  check_fixed_length(result, "is_sorted", 1)

  cat(crayon::italic(
    crayon::cyan(x$vec_id, ": is_sorted : result = ")),
    display_parameter(result), "\n", sep = "")

  result
}


diagnostic_no_na <- function(x) {
  result <- run_user_method(user_method_no_na, x)

  check_type_logical(result, "no_na")
  check_fixed_length(result, "no_na", 1)

  cat(crayon::italic(
    crayon::cyan(x$vec_id, ": no_na : result = ")),
    display_parameter(result), "\n", sep = "")

  result
}


diagnostic_sum <- function(x, na_rm) {
  result <- run_user_method2(user_method_sum, x, na_rm)

  if (typeof(result) != "integer" & typeof(result) != "double") stop("Method sum generated a '",
    typeof(result), "' result where a double or integer was expected")

  check_fixed_length(result, "sum", 1)

  cat(crayon::italic(
    crayon::cyan(x$vec_id, ": sum : result = ")),
    display_parameter(result), "\n", sep = "")

  result
}


diagnostic_min <- function(x, na_rm) {
  result <- run_user_method2(user_method_min, x, na_rm)

  check_type(x, result, "min")
  check_fixed_length(result, "min", 1)

  cat(crayon::italic(
    crayon::cyan(x$vec_id, ": min : result = ")),
    display_parameter(result), "\n", sep = "")

  result
}


diagnostic_max <- function(x, na_rm) {
  result <- run_user_method2(user_method_max, x, na_rm)

  check_type(x, result, "max")
  check_fixed_length(result, "max", 1)

  cat(crayon::italic(
    crayon::cyan(x$vec_id, ": max : result = ")),
    display_parameter(result), "\n", sep = "")

  result
}


diagnostic_serialized_state <- function(x) {
  cat(crayon::italic(crayon::cyan(" serialized_state: result = ")),
      display_parameter(x), "\n", sep = "")
}


diagnostic_unserialize_ex <- function(x) {
  cat(crayon::italic(crayon::cyan(" unserialize_ex: altwrap_class = ")),
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
  cat(crayon::italic(crayon::cyan(" unserialize_ex: altwrap_class = ")),
      display_parameter(x[[1]]),
      crayon::italic(crayon::cyan(", state =")),
      display_parameter(x[[2]]))
}


#' Coerce vector to a different type
#'
#' @param x vector
#' @param type type to coerce to. Possible types are: 'logical', 'integer', 'double', 
#' 'complex', 'character', 'list', 'raw' and 'expression'
#'
#' @return coerced vector (which can  be an ALTREP)
diagnostic_coerce <- function(x, type) {
  result <- run_user_method2(user_method_coerce, x, type)

  # check result type
  if (typeof(result) != type) stop("Method coerce generated a '",
    typeof(result), "' result where a '", type, "' was expected")

  # check result length
  check_length(x, result, "coerce")

  # diagnostic message
  cat(crayon::italic(
    crayon::cyan(x$vec_id, ": coerce : result = ")),
    display_parameter(result), "\n", sep = "")

  result
}


diagnostic_extract_subset <- function(x, index) {
  if (length(index > 0)) {
    vec_length <- run_user_method(user_method_length, x)
    if (max(index) > vec_length) {
      warning("Method extract_subset called with index containing elements larger than the vector length")
    }
  }

  result <- run_user_method2(user_method_extract_subset, x, index)

  check_type(x, result, "full_vec")

  check_fixed_length(result, "extract_subset", length(index))

  cat(crayon::italic(
    crayon::cyan(x$vec_id, ": extract_subset result = ")),
    display_parameter(result), "\n", sep = "")

  result
}
