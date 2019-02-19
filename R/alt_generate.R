
#' Generate source code for an altrep wrapper
#'
#' @param altrep_type A specific type of altrep vector; 'integer', 'real' or 'logical'
#'
#' @return a wrapper around the altrep vector which is an altrep vector itself
#' @export
alt_generate <- function(altrep_type, cpp_type, scalar_method, type_method, alt_method, output_path) {

  # read default source file
  source_file <- readLines(paste0(
    path.package("lazyvec"), "/altrep_sources/altrep_implementation.cpp"))

  # replace altrep type
  source_file <- gsub("ALTREP_TYPE", altrep_type, source_file)
  source_file <- gsub("CPP_TYPE", cpp_type, source_file)
  source_file <- gsub("RF_SCALAR_TYPE", scalar_method, source_file)
  source_file <- gsub("TYPE_METHOD", type_method, source_file)
  source_file <- gsub("ALT_METHOD", alt_method, source_file)

  writeLines(source_file, output_path)
}


# alt_generate(
#   altrep_type = "integer",
#   cpp_type = "int",
#   scalar_method = "Rf_ScalarInteger",
#   type_method = "INTEGER",
#   alt_method = "altinteger",
#   "src/altrep_integer.cpp")

# alt_generate(
#   altrep_type = "real",
#   cpp_type = "double",
#   scalar_method = "Rf_ScalarReal",
#   type_method = "REAL",
#   alt_method = "altreal",
#   "src/altrep_real.cpp")

# alt_generate(
#   altrep_type = "logical",
#   cpp_type = "int",
#   scalar_method = "Rf_ScalarLogical",
#   type_method = "LOGICAL",
#   alt_method = "altlogical",
#   "src/altrep_logical.cpp")
