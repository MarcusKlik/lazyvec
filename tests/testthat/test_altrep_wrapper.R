
require(data.table)

context("wrapper")

test_that("wrap altrep vector", {
  wrap_vec <- alt_wrap(1L:10L)

  expect_equal(wrap_vec, 1L:10L)
})


length_listener <- function(x) {
  length_res <<- x
  cat("length ")
}


dataptr_or_null_listener <- function(x) {
  dataptr_res <<- x
  cat("dataptr_or_null ")
}


get_region_listener <- function(x) {
  get_region_res <<- x
  cat("get_region_res ")
}


# define wrapper with custom methods
wrap_vec <- alt_wrap(1L:1000L, length_method = length_listener,
  dataptr_or_null_method = dataptr_or_null_listener,
  get_region_listener = get_region_listener)


# define global variables
dataptr_res <- NULL
get_region_res <- NULL
length_res <- NULL


test_that("length", {
  vec_length <- length(wrap_vec)

  expect_equal(length_res, 1000)
  expect_equal(vec_length, 1000)
})


test_that("max", {
  dataptr_res <<- NULL
  get_region_res <<- NULL
  vec_max <- max(wrap_vec)

  expect_equal(vec_max, 1000)
  expect_true(dataptr_res)
  expect_equal(length(get_region_res), 3)
})


test_that("min", {
  dataptr_res <<- NULL
  get_region_res <<- NULL
  vec_min <- min(wrap_vec)

  expect_equal(vec_min, 1)
  expect_true(dataptr_res)
  expect_equal(length(get_region_res), 3)
})
