
context("constructor")

# sample class that wraps a native R vector
vec <- 1:100
nat_vec <- native_vec(vec)


test_that("constructor", {
  lazy_vec <- lazy_vec(nat_vec)
})


test_that("length", {
  vec_length <- length(lazy_vec(nat_vec))

  expect_equal(vec_length, 100)
})


test_that("subset", {
  vec <- lazy_vec(nat_vec)[1]

  expect_equal(vec, 5)
})
