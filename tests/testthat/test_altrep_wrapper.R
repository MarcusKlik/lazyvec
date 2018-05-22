
context("wrapper")

test_that("wrap altrep vector", {
  wrap_vec <- alt_wrap(1L:10L)
})


wrap_vec <- alt_wrap(1L:1000L)

test_that("length", {
  vec_length <- length(wrap_vec)

  expect_equal(vec_length, 1000)
})


test_that("max", {
  vec_max <- max(wrap_vec)

  expect_equal(vec_max, 1000)
})
