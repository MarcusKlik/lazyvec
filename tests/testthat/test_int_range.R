
context("int_range")

source("../../inst/implement/lazyvec_int_range.R")

x <- int_range(3L, 12L, 2L)
y <- int_range(3L, 13L, 3L)

test_that("int_range length", {
  expect_equal(length(x), 5)
  expect_equal(length(y), 4)
})
