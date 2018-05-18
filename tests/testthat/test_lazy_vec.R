
context("constructor")

# sample class that wraps a native R vector
vec <- 1:1e7
nat_vec <- native_vec(vec)
interface <- lazy_vec(nat_vec)

length(interface)

y <- interface[1000:1010]

mean(interface)

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
