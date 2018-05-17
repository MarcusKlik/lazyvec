
context("constructor")

test_that("constructor", {
  lazy_vec <- lazy_vec()
})


test_that("length", {
  vec_length <- length(lazy_vec(6))

  expect_equal(vec_length, 3)
})


test_that("subset", {
  vec <- lazy_vec(6)[1]

  expect_equal(vec, 1)
})
