
#' Generate source code for an altrep wrapper
#'
#' @param altrep_type specific type of ALTREP vector; 'integer', 'real', 'logical', 'raw'
#' or `string`
#' @param source_path path to the source file used for code generation
#' @param cpp_type C++ type corresponding to ALTREP type
#' @param scalar_method method from R API to generate a scalar SEXP value
#' @param type_method method from R API to access vector data
#' @param alt_method name use in ALTREP API for specific ALTREP type generation
#' @param output_path path to generated output file
#' @param exclude_methods methods to remove from source before generation (for most ALTREP
#' vectors only a subset of the ALTREP API is needed)
#'
#' @return a wrapper around the altrep vector which is an altrep vector itself
#' @export
alt_generate <- function(source_path, altrep_type, cpp_type, scalar_method, type_method,
  alt_method, sexp_to_cpp, altvec_wrapper, output_path, exclude_methods = NULL) {

  # read default source file
  source_file <- readLines(source_path)

  # replace altrep type
  source_file <- gsub("ALTREP_TYPE", altrep_type, source_file)
  source_file <- gsub("CPP_TYPE", cpp_type, source_file)
  source_file <- gsub("RF_SCALAR_TYPE", scalar_method, source_file)
  source_file <- gsub("TYPE_METHOD", type_method, source_file)
  source_file <- gsub("ALT_METHOD", alt_method, source_file)
  source_file <- gsub("SEXP_TO_CPP", sexp_to_cpp, source_file)
  source_file <- gsub("ALTVEC_WRAPPER", altvec_wrapper, source_file)

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

  # remove all code markers
  hits <- regexpr("// generator source ", source_file, fixed = TRUE) != -1
  source_file <- source_file[!hits]


  writeLines(source_file, output_path)
}


###################################################################################################
# Generators for ALTREP API used by alt_wrap()                                                    #
###################################################################################################

# generate int wrapper
alt_generate(
  source_path    = "altwrap_implementation.cpp",
  altrep_type    = "integer",
  cpp_type       = "int",
  scalar_method  = "Rf_ScalarInteger",
  type_method    = "INTEGER",
  alt_method     = "altinteger",
  sexp_to_cpp    = "not_needed",
  altvec_wrapper = "altrep_integer_wrapper",
  "../src/altwrap_integer.cpp",
  "Duplicate_")

# generate real wrapper
alt_generate(
  source_path    = "altwrap_implementation.cpp",
  altrep_type    = "real",
  cpp_type       = "double",
  scalar_method  = "Rf_ScalarReal",
  type_method    = "REAL",
  alt_method     = "altreal",
  sexp_to_cpp    = "not_needed",
  altvec_wrapper = "altrep_real_wrapper",
  "../src/altwrap_real.cpp",
  "Duplicate_")


# generate logical wrapper
alt_generate(
  source_path    = "altwrap_implementation.cpp",
  altrep_type    = "logical",
  cpp_type       = "int",
  scalar_method  = "Rf_ScalarLogical",
  type_method    = "LOGICAL",
  alt_method     = "altlogical",
  sexp_to_cpp    = "not_needed",
  altvec_wrapper = "altrep_logical_wrapper",
  "../src/altwrap_logical.cpp",
  c("Min", "Max", "Duplicate_"))


# generate raw wrapper
alt_generate(
  source_path    = "altwrap_implementation.cpp",
  altrep_type    = "raw",
  cpp_type       = "Rbyte",
  scalar_method  = "Rf_ScalarRaw",
  type_method    = "RAW",
  alt_method     = "altraw",
  sexp_to_cpp    = "not_needed",
  altvec_wrapper = "altrep_raw_wrapper",
  "../src/altwrap_raw.cpp",
  c("Min", "Max", "Is_sorted", "No_NA", "Sum", "Duplicate_"))


# generate string wrapper
alt_generate(
  source_path    = "altwrap_implementation.cpp",
  altrep_type    = "string",
  cpp_type       = "SEXP",
  scalar_method  = "Rf_ScalarString",
  type_method    = "STRING",
  alt_method     = "altstring",
  sexp_to_cpp    = "not_needed",
  altvec_wrapper = "altrep_string_wrapper",
  "../src/altwrap_string.cpp",
  c("Min", "Max", "Sum", "Get_region", "Duplicate_"))


###################################################################################################
# Generators for ALTREP API used by lazyvec()                                                     #
###################################################################################################

# generate int wrapper
alt_generate(
  source_path    = "lazyvec_implementation.cpp",
  altrep_type    = "integer",
  cpp_type       = "int",
  scalar_method  = "Rf_ScalarInteger",
  type_method    = "INTEGER",
  alt_method     = "altinteger",
  sexp_to_cpp    = "SEXP_TO_INT",
  altvec_wrapper = "not_needed",
  "../src/lazyvec_integer.cpp",
  "Duplicate_")

# generate real wrapper
alt_generate(
  source_path    = "lazyvec_implementation.cpp",
  altrep_type    = "real",
  cpp_type       = "double",
  scalar_method  = "Rf_ScalarReal",
  type_method    = "REAL",
  alt_method     = "altreal",
  sexp_to_cpp    = "SEXP_TO_DOUBLE",
  altvec_wrapper = "not_needed",
  "../src/lazyvec_real.cpp",
  "Duplicate_")


# generate logical wrapper
alt_generate(
  source_path    = "lazyvec_implementation.cpp",
  altrep_type    = "logical",
  cpp_type       = "int",
  scalar_method  = "Rf_ScalarLogical",
  type_method    = "LOGICAL",
  alt_method     = "altlogical",
  sexp_to_cpp    = "SEXP_TO_INT",
  altvec_wrapper = "not_needed",
  "../src/lazyvec_logical.cpp",
  c("Min", "Max", "Duplicate_"))


# generate raw wrapper
alt_generate(
  source_path    = "lazyvec_implementation.cpp",
  altrep_type    = "raw",
  cpp_type       = "Rbyte",
  scalar_method  = "Rf_ScalarRaw",
  type_method    = "RAW",
  alt_method     = "altraw",
  sexp_to_cpp    = "SEXP_TO_RBYTE",
  altvec_wrapper = "not_needed",
  "../src/lazyvec_raw.cpp",
  c("Min", "Max", "Is_sorted", "No_NA", "Sum", "Duplicate_"))


# generate string wrapper
alt_generate(
  source_path    = "lazyvec_implementation.cpp",
  altrep_type    = "string",
  cpp_type       = "SEXP",
  scalar_method  = "Rf_ScalarString",
  type_method    = "STRING",
  alt_method     = "altstring",
  sexp_to_cpp    = "SEXP_TO_CHARXP",
  altvec_wrapper = "not_needed",
  "../src/lazyvec_string.cpp",
  c("Min", "Max", "Sum", "Get_region", "Duplicate_"))
