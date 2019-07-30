
lazyvec_length <- function(x) {
  x[[4]]
}


lazyvec_full_vector <- function(x) {
  as.character(seq.int(x$from, x$to, x$step))
}


lazyvec_element <- function(x, i) {
  as.character(x[[1]] + (i - 1L) * x[[3]])
}


lazyvec_is_sorted <- function(x) {
  TRUE
}


lazyvec_no_na <- function(x) {
  TRUE
}


lazyvec_extract_subset <- function(x, index) {
  as.character(x$from + (index - 1L) * x$step)
}


# define int_range ALTREP API
character_range_api <- lazyvec_methods(
  lazyvec_length,
  lazyvec_full_vector,
  lazyvec_element,
  lazyvec_is_sorted,
  lazyvec_no_na,
  lazyvec_extract_subset
)


# constructor for an custom integer range
character_range <- function(from, to, step) {

  # alternative representation
  alt_pres <- list(
    from = as.integer(from),                       # range start
    to = as.integer(to),                           # range end
    step = as.integer(step),                       # range step
    length = as.integer(1L + (to - from) / step)   # vector length
  )

  # return custom ALTREP vector
  lazyvec(alt_pres, "character", character_range_api)
}
