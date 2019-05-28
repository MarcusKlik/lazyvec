
context("triggers")

# sample ALTREP vector
x <- 1:100
x_char <- as.character(x)
x_real <- as.numeric(x)
x_logical <- c(TRUE, FALSE, NA, TRUE, FALSE, NA)

# general ALTREP methods

test_that("is ALTREP vector", {
  expect_true(is_altrep(x))

  expect_true(is_altrep(x_char))

  expect_true(is_altrep(x_real))
  
  expect_false(is_altrep(x_logical))
})


test_that("length trigger", {
  expect_equal(lazyvec:::trigger_length(x), 100)

  expect_equal(lazyvec:::trigger_length(x_char), 100)

  expect_equal(lazyvec:::trigger_length(x_real), 100)
})


test_that("get_region trigger", {
  expect_equal(lazyvec:::trigger_get_region(x, 2, 5), 3:7)
  
  expect_error(lazyvec:::trigger_get_region(x, 100, 5), "Position is outside vector boundaries")

  expect_error(lazyvec:::trigger_get_region(x, 10, 5000), "Size too large, resulting range is outside vector boundaries")
  
  expect_error(lazyvec:::trigger_get_region(x_char, 2, 5), "Method get_region cannot be called on a ALTREP vector of this type")
  
  expect_equal(lazyvec:::trigger_get_region(x_real, 2, 5), 3:7)

  expect_error(lazyvec:::trigger_get_region(x_real, 100, 5), "Position is outside vector boundaries")
  
  expect_error(lazyvec:::trigger_get_region(x_real, 10, 5000), "Size too large, resulting range is outside vector boundaries")
  
})


test_that("element trigger", {
  expect_equal(lazyvec:::trigger_element(x, 3), 4)
  
  expect_error(lazyvec:::trigger_element(x, 1000), "Position is outside vector boundaries")

  expect_equal(lazyvec:::trigger_element(x_char, 3), "4")
  
  expect_error(lazyvec:::trigger_element(x_char, 1000), "Position is outside vector boundaries")
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
