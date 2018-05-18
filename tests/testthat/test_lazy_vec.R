
context("constructor")

# sample class that wraps a native R vector
nat_vec <- lazyvec::native_vec(c(1, 5, 7, 2, 6, 10))


test_that("constructor", {
  lazy_vec <- lazy_vec()
})


test_that("length", {
  vec_length <- length(lazy_vec(nat_vec))

  expect_equal(vec_length, 3)
})


test_that("subset", {
  vec <- lazy_vec(6)[1]

  expect_equal(vec, 1)
})
