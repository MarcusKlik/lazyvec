
#' Generate source code for an altrep wrapper
#'
#' @param altrep_type A specific type of altrep vector; 'integer', 'real' or 'logical'
#'
#' @return a wrapper around the altrep vector which is an altrep vector itself
#' @export
alt_generate <- function(altrep_type, cpp_type, scalar_method, type_method,
  alt_method, output_path, exclude_methods = NULL) {

  # read default source file
  source_file <- readLines("altrep_implementation.cpp")

  # replace altrep type
  source_file <- gsub("ALTREP_TYPE", altrep_type, source_file)
  source_file <- gsub("CPP_TYPE", cpp_type, source_file)
  source_file <- gsub("RF_SCALAR_TYPE", scalar_method, source_file)
  source_file <- gsub("TYPE_METHOD", type_method, source_file)
  source_file <- gsub("ALT_METHOD", alt_method, source_file)

  for (exclude_method in exclude_methods) {

    # remove single code lines
    hits <- regexpr(paste0("  // codeline: ", exclude_method), source_file, fixed = TRUE) != -1
    source_file <- source_file[!hits]

    # remove code block
    start <- which(regexpr(paste0("// generator source start: ", exclude_method),
      source_file, fixed = TRUE) != -1)

    if (length(start) == 0) {
      stop("source method not found")
    }

    end <- which(regexpr(paste0("// generator source end: ", exclude_method),
      source_file, fixed = TRUE) != -1)

    source_file <- source_file[c(1:(start - 1), (end + 1):length(source_file))]
  }

  writeLines(source_file, output_path)
}


# generate int wrapper
alt_generate(
  altrep_type = "integer",
  cpp_type = "int",
  scalar_method = "Rf_ScalarInteger",
  type_method = "INTEGER",
  alt_method = "altinteger",
  "../src/altrep_integer.cpp")


# generate real wrapper
alt_generate(
  altrep_type = "real",
  cpp_type = "double",
  scalar_method = "Rf_ScalarReal",
  type_method = "REAL",
  alt_method = "altreal",
  "../src/altrep_real.cpp")


# generate logical wrapper
alt_generate(
  altrep_type = "logical",
  cpp_type = "int",
  scalar_method = "Rf_ScalarLogical",
  type_method = "LOGICAL",
  alt_method = "altlogical",
  "../src/altrep_logical.cpp",
  c("Min", "Max"))
