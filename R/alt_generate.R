
#' Generate source code for an altrep wrapper
#'
#' @param altrep_type A specific type of altrep vector; 'integer', 'real' or 'logical'
#'
#' @return a wrapper around the altrep vector which is an altrep vector itself
#' @export
alt_generate <- function(altrep_type, output_path) {

  altrep_type <- "integer"  # replace ALTREP_TYPE
  cpp_type <- "int"
  scalar_method <- "Rf_ScalarInteger"
  type_method <- "INTEGER"
  alt_method <- "altinteger"

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


# alt_generate("integer", "src/altrep_integer.cpp")
