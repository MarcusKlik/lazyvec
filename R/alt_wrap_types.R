
listeners <- function() {

  # package listener methods
  c(
    listener_length,
    listener_dataptr_or_null,
    listener_get_region,
    listener_element,
    listener_dataptr,
    listener_is_sorted,
    listener_no_na,
    listener_sum,
    listener_min,
    listener_max,
    listener_inspect,
    listener_unserialize_ex,
    listener_serialized_state,
    listener_duplicate_ex,
    listener_coerce,
    listener_extract_subset
  )
}


alt_wrap_integer <- function(altrep_vec, vec_id) {

  if (!is_altrep(altrep_vec)) {
    stop("vector is not an ALTREP vector.")
  }

  meta_data <- list(

    # ALTREP payload
    altrep_vec,

    # package listener methods
    listeners(),

    # parent environment in which to evaluate listeners
    parent.env(environment()),

    # identifyer, used in diagnostic output
    vec_id
  )

  altrep_integer_wrapper(meta_data)
}


alt_wrap_real <- function(altrep_vec, vec_id) {

  if (!is_altrep(altrep_vec)) {
    stop("vector is not an ALTREP vector.")
  }

  meta_data <- list(

    # ALTREP payload
    altrep_vec,

    # package listener methods
    listeners(),

    # parent environment in which to evaluate listeners
    parent.env(environment()),

    # identifyer, used in diagnostic output
    vec_id
  )

  altrep_real_wrapper(meta_data)
}


alt_wrap_logical <- function(altrep_vec, vec_id) {

  if (!is_altrep(altrep_vec)) {
    stop("vector is not an ALTREP vector.")
  }

  meta_data <- list(

    # ALTREP payload
    altrep_vec,

    # package listener methods
    listeners(),

    # parent environment in which to evaluate listeners
    parent.env(environment()),

    # identifyer, used in diagnostic output
    vec_id
  )

  altrep_logical_wrapper(meta_data)
}


alt_wrap_raw <- function(altrep_vec, vec_id) {

  if (!is_altrep(altrep_vec)) {
    stop("vector is not an ALTREP vector.")
  }

  meta_data <- list(

    # ALTREP payload
    altrep_vec,

    # package listener methods
    listeners(),

    # parent environment in which to evaluate listeners
    parent.env(environment()),

    # identifyer, used in diagnostic output
    vec_id
  )

  altrep_raw_wrapper(meta_data)
}


alt_wrap_string <- function(altrep_vec, vec_id) {

  if (!is_altrep(altrep_vec)) {
    stop("vector is not an ALTREP vector.")
  }

  meta_data <- list(

    # ALTREP payload
    altrep_vec,

    # package listener methods
    listeners(),

    # parent environment in which to evaluate listeners
    parent.env(environment()),

    # identifyer, used in diagnostic output
    vec_id
  )

  altrep_string_wrapper(meta_data)
}
