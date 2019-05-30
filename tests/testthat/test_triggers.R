
context("triggers")

# sample ALTREP vector
x <- 1:100
x_char <- as.character(x)
x_real <- as.numeric(x)


test_that("is ALTREP vector", {
  expect_true(is_altrep(x))

  expect_true(is_altrep(x_char))

  expect_true(is_altrep(x_real))

  expect_false(is_altrep(c(1, 3, 5)))
})


test_that("length trigger", {
  expect_equal(lazyvec:::trigger_length(x), 100)

  expect_equal(lazyvec:::trigger_length(x_char), 100)

  expect_equal(lazyvec:::trigger_length(x_real), 100)
})


test_that("get_region trigger", {
  expect_equal(lazyvec:::trigger_get_region(x, 2, 5), 3:7)

  expect_error(lazyvec:::trigger_get_region(x, 100, 5), "Position is outside vector boundaries")

  expect_error(lazyvec:::trigger_get_region(x, 10, 5000),
    "Size too large, resulting range is outside vector boundaries")

  expect_error(lazyvec:::trigger_get_region(x_char, 2, 5),
    "Method get_region cannot be called on a ALTREP vector of this type")

  expect_equal(lazyvec:::trigger_get_region(x_real, 2, 5), 3:7)

  expect_error(lazyvec:::trigger_get_region(x_real, 100, 5), "Position is outside vector boundaries")

  expect_error(lazyvec:::trigger_get_region(x_real, 10, 5000),
    "Size too large, resulting range is outside vector boundaries")
})


test_that("element trigger", {
  expect_equal(lazyvec:::trigger_element(x, 3), 4)

  expect_error(lazyvec:::trigger_element(x, 1000), "Position is outside vector boundaries")

  expect_equal(lazyvec:::trigger_element(x_char, 3), "4")

  expect_error(lazyvec:::trigger_element(x_char, 1000), "Position is outside vector boundaries")

  expect_equal(lazyvec:::trigger_element(x_real, 3), 4)

  expect_error(lazyvec:::trigger_element(x_real, 1000), "Position is outside vector boundaries")
})


test_that("is_sorted trigger", {
  expect_equal(lazyvec:::trigger_is_sorted(x), 1)

  expect_equal(lazyvec:::trigger_is_sorted(x_char), as.integer(NA))

  expect_equal(lazyvec:::trigger_is_sorted(x_real), 1)
})


test_that("no_na trigger", {
  expect_equal(lazyvec:::trigger_no_na(x), 1)

  expect_equal(lazyvec:::trigger_no_na(x_char), 1)

  expect_equal(lazyvec:::trigger_no_na(x_real), 1)
})


test_that("sum trigger", {
  expect_error(lazyvec:::trigger_sum(x, 3:8), "Please set na_rm using a logical value")

  expect_equal(lazyvec:::trigger_sum(x, FALSE), 5050)

  expect_error(lazyvec:::trigger_sum(x_char, FALSE), "cannot be called on a ALTREP vector of this type")

  expect_equal(lazyvec:::trigger_sum(x_real, FALSE), 5050)

  expect_equal(lazyvec:::trigger_sum(x, TRUE), 5050)

  expect_error(lazyvec:::trigger_sum(x_char, TRUE), "cannot be called on a ALTREP vector of this type")

  expect_equal(lazyvec:::trigger_sum(x_real, TRUE), 5050)
})


test_that("min trigger", {
  expect_error(lazyvec:::trigger_min(x, 3:8), "Please set na_rm using a logical value")

  expect_equal(lazyvec:::trigger_min(x, FALSE), NULL)

  expect_error(lazyvec:::trigger_min(x_char, FALSE), "cannot be called on a ALTREP vector of this type")

  expect_equal(lazyvec:::trigger_min(x_real, FALSE), NULL)

  expect_equal(lazyvec:::trigger_min(x, TRUE), NULL)

  expect_error(lazyvec:::trigger_min(x_char, TRUE), "cannot be called on a ALTREP vector of this type")

  expect_equal(lazyvec:::trigger_min(x_real, TRUE), NULL)
})


test_that("duplicate_ex trigger", {
  res <- lazyvec:::trigger_duplicate_ex(x, FALSE)
  expect_false(is_altrep(res))

  res <- lazyvec:::trigger_duplicate_ex(x, TRUE)
  expect_false(is_altrep(res))
})


test_that("coerce trigger", {
  res <- lazyvec:::trigger_coerce(x, 10)
  expect_null(res)
})


test_that("dataptr_or_null trigger", {
  res <- lazyvec:::trigger_dataptr_or_null(x)
  expect_null(res)
})


test_that("inspect_method trigger", {
  res <- capture.output(lazyvec:::trigger_inspect(x, 1, 10, 10))
  expect_equal(res[1], " 1 : 100 (compact)")
})


test_that("serialized_state trigger", {
  res <- lazyvec:::trigger_serialized_state(x)
  expect_equal(res, c(100, 1, 1))
})


test_that("extract_subset trigger", {
  expect_null(lazyvec:::trigger_extract_subset(x, c(1, 3, 5)))

  expect_error(lazyvec:::trigger_extract_subset(x, "incorrect index"), "Please use a numeric index")
})


# after this test, the vector will be in it's expanded form
test_that("dataptr trigger", {
  res <- lazyvec:::trigger_dataptr(x)
  expect_true(sum(res) > 0)
})


test_that("dataptr_or_null trigger", {
  res <- lazyvec:::trigger_dataptr_or_null(x)
  expect_true(sum(res) > 0)
  expect_true(is_altrep(x))
})
