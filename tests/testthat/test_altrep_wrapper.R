
context("wrapper")

test_that("wrap altrep vector", {
  wrapped_vec <- altrep_wrapper(1L:10L)
})

wrapped_vec <- altrep_wrapper(1L:10L)

test_that("length", {
  vec_length <- length(wrapped_vec)

  expect_equal(vec_length, 1)
})
