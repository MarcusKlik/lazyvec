
diagnostic_message <- function(show, ...) {
  named_args <- list(...)

  # do not show messages
  if (!show) return()

  func_name <- named_args[[1]]
  res <- named_args[[2]]

  args <- ""

  if (length(named_args) > 2) {
    func_args <- named_args[3:length(named_args)]
    args <- paste0(paste(names(func_args), "=", func_args), collapse = ", ")
  }

  if (length(res) > 1) {
    res <- paste0("c(", paste0(res, collapse = ", "), ")")
  }

  cat(crayon::italic(crayon::cyan(
    paste0(func_name, "(", args, "): ", res, "\n")
  )))
}


lazyvec_length <- function(x) {
  x$message(x$diagnostics, "length", x[[4]])
  x[[4]]
}


lazyvec_full_vector <- function(x) {
  full_vec <- seq.int(x$from, x$to, x$step)
  x$message(x$diagnostics, "full_vector", full_vec)

  full_vec
}


lazyvec_get_region <- function(x) {
  x$message(x$diagnostics, "get_region", x[[4]], start = x[[2]], length = x[[3]])
}


lazyvec_element <- function(x, i) {
  res <- x[[1]] + (i - 1L) * x[[3]]
  x$message(x$diagnostics, "element", res, i = i)
  res
}


lazyvec_is_sorted <- function(x) {
  x$message(x$diagnostics, "is_sorted", TRUE)
  TRUE
}


lazyvec_no_na <- function(x) {
  x$message(x$diagnostics, "no_na", TRUE)
  TRUE
}


lazyvec_sum <- function(x, na_rm) {
  if (x$length %% 2 == 0) {
    sum_element <- (2 * x$from + (x$length - 1) * x$step) * x$length / 2
  } else {
    half_length <- (x$length - 1) / 2
    sum_element <- (2 * x$from + (x$length - 1) * x$step) * half_length
    sum_element <- sum_element + x$from + half_length * x$step;
  }

  x$message(x$diagnostics, "sum", sum_element)

  sum_element
}


lazyvec_min <- function(x, na_rm) {
  min_element <- x$from  # from
  x$message(x$diagnostics, "min", min_element)
  min_element
}


lazyvec_max <- function(x, na_rm) {
  max_element <- x$to  # from
  x$message(x$diagnostics, "max", max_element)
  max_element
}


lazyvec_extract_subset <- function(x, indx) {
  x$message(x$diagnostics, "extract_subset", NULL, indx = indx)
  x$from + (indx - 1L) * x$step
}


# define int_range ALTREP API
lazyvec_api <- lazyvec_methods(
  function(){},  # nolint
  lazyvec_length,
  lazyvec_full_vector,
  lazyvec_get_region,
  lazyvec_element,
  lazyvec_full_vector,
  lazyvec_is_sorted,
  lazyvec_no_na,
  lazyvec_sum,
  lazyvec_min,
  lazyvec_max,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  lazyvec_extract_subset
)


# constructor for an custom integer range
int_range <- function(from, to, step, diagnostics = FALSE) {

  # alternative representation
  alt_pres <- list(
    from = as.integer(from),                       # range start
    to = as.integer(to),                           # range end
    step = as.integer(step),                       # range step
    length = as.integer(1L + (to - from) / step),  # vector length
    diagnostics = diagnostics,                     # show diagnostics
    message = diagnostic_message                   # output diagnostic message
  )

  # return custom ALTREP vector
  lazyvec(alt_pres, "integer", lazyvec_api)
}
