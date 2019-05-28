
context("triggers")

# sample ALTREP vector
x <- 1:100


# general ALTREP methods

test_that("is ALTREP vector", {
  expect_true(is_altrep(x))
})


test_that("length trigger", {
  expect_equal(lazyvec:::trigger_length(x), 100)
})


test_that("get_region trigger", {
  expect_equal(lazyvec:::trigger_get_region(x, 2, 5), 3:7)
})


test_that("duplicate_ex trigger", {
  res <- lazyvec:::trigger_duplicate_ex(x, FALSE)
  expect_false(is_altrep(res))

  res <- lazyvec:::trigger_duplicate_ex(x, TRUE)
  expect_false(is_altrep(res))
})


test_that("coerce_method trigger", {
  res <- lazyvec:::trigger_coerce(x, 10)  # to logical
  expect_null(res)
})


test_that("inspect_method trigger", {
  res <- capture.output(lazyvec:::trigger_inspect(x, 1, 10, 10))
  expect_equal(res, " 1 : 100 (compact)")
})


test_that("serialized_state trigger", {
  res <- lazyvec:::trigger_serialized_state(x)
  expect_equal(res, c(100, 1, 1))
})


# nolint start

# x <- 1:100
# y <- altrep_listener(x, "x")
# tmp_file <- tempfile()
# saveRDS(y, tmp_file)
# z <- readRDS(tmp_file)
# file.remove(tmp_file)
# 
# is_altrep(z)

# nolint end
