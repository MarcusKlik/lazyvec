
display_parameter <- function(x) {
  paste0(" ", crayon::magenta(typeof(x)),
         crayon::magenta("["), crayon::magenta(length(x)),
         crayon::magenta("] "), paste0(x, collapse = " "))
}

lazyvec_length <- function(x) {

  cat(crayon::italic(
    crayon::cyan("ALTREP length : result =")),
    display_parameter(x[2]), "\n", sep = "")

  x[2]
}


lazyvec_dataptr_or_null <- function(x) {

  cat(crayon::italic(
    crayon::cyan(x[[1]], ": ALTREP dataptr_or_null called, null returned: ")),
    display_parameter(x[[2]]), "\n", sep = "")
}


lazyvec_get_region <- function(x) {
  cat(crayon::italic(
    crayon::cyan(x[[1]], ": ALTREP get_region : result =")),
    display_parameter(x[[4]]),
    crayon::italic(crayon::cyan(", start =")),
    display_parameter(x[[2]]),
    crayon::italic(crayon::cyan(", length =")),
    display_parameter(x[[3]]), "\n", sep = "")
}


lazyvec_element <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP element : result =")),
      display_parameter(x), "\n", sep = "")
}


lazyvec_is_sorted <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP is_sorted : result =")),
      display_parameter(x == 1), "\n", sep = "")
}


lazyvec_no_na <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP no_na : result =")),
      display_parameter(x == 1), "\n", sep = "")
}


lazyvec_sum <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP sum called, na.rm = ")),
      display_parameter(x[[2]] == 1),
      crayon::italic(crayon::cyan(", result: ")),
      display_parameter(x[[1]]), "\n", sep = "")
}


lazyvec_min <- function(x) {
  cat(crayon::italic(
    crayon::cyan(x[[1]], ": ALTREP min : result =")),
    display_parameter(x[[2]]), "\n", sep = "")
}


lazyvec_max <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP max : result =")),
      display_parameter(x), "\n", sep = "")
}


lazyvec_inspect <- function(x) {

  print(x)

  cat(crayon::italic(crayon::cyan("ALTREP inspect : result =")),
      display_parameter(x[[1]]),
      crayon::italic(crayon::cyan(", x = ")),
      display_parameter(x[[2]]),
      crayon::italic(crayon::cyan(", pre = ")),
      display_parameter(x[[3]]),
      crayon::italic(crayon::cyan(", deep = ")),
      display_parameter(x[[4]]),
      crayon::italic(crayon::cyan(", pVec = ")),
      display_parameter(x[[5]]), "\n", sep = "")
}


lazyvec_serialized_state <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP serialized_state : result =")),
      display_parameter(x), "\n", sep = "")
}


lazyvec_unserialize_ex <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP unserialize_ex : result =")),
      display_parameter(x), "\n", sep = "")
}


lazyvec_dataptr <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP dataptr : result =")),
      format(as.hexmode(x[1]), width = 8),  # high address bytes
      format(as.hexmode(x[2]), width = 8),  # low bytes of address
      ", writable = ", as.logical(x[3]), "\n", sep = "")
}


lazyvec_duplicate_ex <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP duplicate_ex : result =")),
      display_parameter(x), "\n", sep = "")
}


lazyvec_coerce <- function(x) {
  cat(crayon::italic(crayon::cyan("ALTREP coerce : result =")),
      display_parameter(x), "\n", sep = "")
}


lazyvec_extract_subset <- function(x) {
  subset_result <- x[[1]]
  if (is.null(subset_result)) subset_result <- "NULL"
  cat(crayon::italic(crayon::cyan("ALTREP extract_subset :\n  result =")),
      display_parameter(subset_result),
      crayon::italic(crayon::cyan("\n    indx = ")),
      display_parameter(x[[2]]),
      crayon::italic(crayon::cyan("\n    call = ")),
      display_parameter(str(x[[3]])),
      "\n", sep = "")
}


# define lazyvec API
lazyvec_api <- lazyvec_methods(
  lazyvec_length,
  lazyvec_dataptr_or_null,
  lazyvec_get_region,
  lazyvec_element,
  lazyvec_dataptr,
  lazyvec_is_sorted,
  lazyvec_no_na,
  lazyvec_sum,
  lazyvec_min,
  lazyvec_max,
  lazyvec_inspect,
  lazyvec_unserialize_ex,
  lazyvec_serialized_state,
  lazyvec_duplicate_ex,
  lazyvec_coerce,
  lazyvec_extract_subset
)


# create custom ALTREP vector
my_altrep_vec <- lazyvec(c(1L, 20L, 2L), "integer", lazyvec_api)

length(my_altrep_vec)

       