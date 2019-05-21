
context("triggers")


x <- 1:100


# general ALTREP methods


test_that("is ALTREP vector", {
  expect_true(is_altrep(x))
})


test_that("length trigger", {
  expect_equal(lazyvec:::altrep_trigger_length(x), 100)
})


test_that("duplicate_ex trigger", {
  res <- lazyvec:::altrep_trigger_duplicate_ex(x, FALSE)
  expect_false(is_altrep(res))

  res <- lazyvec:::altrep_trigger_duplicate_ex(x, TRUE)
  expect_false(is_altrep(res))
})


test_that("coerce_method trigger", {
  res <- lazyvec:::altrep_trigger_coerce(x, 10)  # to logical
  expect_null(res)
})


test_that("inspect_method trigger", {
  res <- capture.output(lazyvec:::altrep_trigger_inspect(x, 1, 10, 10))
  expect_equal(res, " 1 : 100 (compact)")
})


test_that("serialized_state trigger", {
  res <- lazyvec:::altrep_trigger_serialized_state(x)
  expect_equal(res, c(100, 1, 1))
})
