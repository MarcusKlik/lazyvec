
context("wrapper")

test_that("wrap altrep vector", {
  wrap_vec <- alt_wrap(1L:10L)
})

wrap_vec <- alt_wrap(1L:100L)

test_that("length", {
  vec_length <- length(wrap_vec)

  expect_equal(vec_length, 100)
})
