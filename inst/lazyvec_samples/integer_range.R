
lazyvec_length <- function(x) {
  x[[4]]
}


lazyvec_full_vector <- function(x) {
  seq.int(x$from, x$to, x$step)
}


lazyvec_get_region <- function(x, i, n) {
  x[[1]] + ( (i - 1L) : (i + n - 2) ) * x[[3]]
}


lazyvec_element <- function(x, i) {
  x[[1]] + (i - 1L) * x[[3]]
}


lazyvec_is_sorted <- function(x) {
  TRUE
}


lazyvec_no_na <- function(x) {
  TRUE
}


# result is a double to avoid integer overflows
lazyvec_sum <- function(x, na_rm) {
  if (x$length %% 2 == 0) {
    sum_element <- (2 * x$from + (x$length - 1) * x$step) * x$length / 2
  } else {
    half_length <- (x$length - 1L) / 2L
    sum_element <- (2 * x$from + (x$length - 1) * x$step) * half_length
    sum_element <- sum_element + x$from + half_length * x$step;
  }

  sum_element
}


lazyvec_min <- function(x, na_rm) {
  x$from
}


lazyvec_max <- function(x, na_rm) {
  x$from + (x$length - 1L) * x$step
}


lazyvec_extract_subset <- function(x, index) {
  x$from + (index - 1L) * x$step
}


lazyvec_coerce <- function(x, type) {
  if (type != "character") return(NULL);

  character_range(x$from, x$to, x$step)
}


# define int_range ALTREP API
integer_range_api <- lazyvec_methods(
  lazyvec_length,
  lazyvec_full_vector,
  lazyvec_element,
  lazyvec_is_sorted,
  lazyvec_no_na,
  lazyvec_extract_subset,
  lazyvec_coerce,
  lazyvec_get_region,
  lazyvec_sum,
  lazyvec_min,
  lazyvec_max
)


# constructor for an custom integer range
integer_range <- function(from, to, step) {

  # alternative representation
  alt_pres <- list(
    from = as.integer(from),                       # range start
    to = as.integer(to),                           # range end
    step = as.integer(step),                       # range step
    length = as.integer(1L + (to - from) / step)   # vector length
  )

  # return custom ALTREP vector
  lazyvec(alt_pres, "integer", integer_range_api)
}
