
#' Generate source code for an altrep wrapper
#'
#' @param altrep_type A specific type of altrep vector; 'integer', 'real' or 'logical'
#'
#' @return a wrapper around the altrep vector which is an altrep vector itself
#' @export
alt_generate <- function(altrep_type) {

  altrep_type <- "integer"  # replace ALTREP_TYPE

  # read default source file
  source_file <- readLines(paste0(
    path.package("lazyvec"), "/altrep_sources/altrep_implementation.cpp"))

  # replace altrep type  
  source_file <- sub("ALTREP_TYPE", altrep_type, source_file)
}
