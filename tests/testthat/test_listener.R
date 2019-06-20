
context("linstener")

# sample ALTREP vector
x <- 1:100

# general ALTREP methods

test_that("is ALTREP vector", {
  expect_true(is_altrep(x))
})


test_that("non ALTREP vector", {
  expect_error(altrep_listener(c(1, 5)), "vector is not an ALTREP vector")

  y <- altrep_listener(x, "x")  # no error
})


y <- altrep_listener(x, "x")  # no error


test_that("length listener", {
  text <- paste(capture.output(lazyvec:::trigger_length(y)), collapse = " ")
  expect_match(text, "x : ALTREP length : result = int[1] 100", fixed = TRUE)
})


test_that("dataptr_or_null listener", {
  expect_null(lazyvec:::trigger_dataptr_or_null(y))
})


test_that("duplicate_ex listener", {
  res <- lazyvec:::trigger_duplicate_ex(x, FALSE)
  expect_false(is_altrep(res))

  res <- lazyvec:::trigger_duplicate_ex(x, TRUE)
  expect_false(is_altrep(res))
})


test_that("coerce_method listener", {
  res <- lazyvec:::trigger_coerce(x, 10)  # to logical
  expect_null(res)
})


test_that("inspect_method listener", {
  res <- capture.output(lazyvec:::trigger_inspect(x, 1, 10, 10))
  expect_equal(res[1], " 1 : 100 (compact)")
})


test_that("serialized_state listener", {
  res <- lazyvec:::trigger_serialized_state(x)
  expect_equal(res, c(100, 1, 1))
})
