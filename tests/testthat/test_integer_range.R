
require(testthat)

context("integer_range")

# clean generated files
sample_path <- "sample_integer_range.R"
unlink(sample_path, force = TRUE)

test_that("arguments", {
  expect_error(lazyvec_skeleton("bla"), "Invalid skeleton_id")
  expect_error(lazyvec_skeleton("integer_range", "test_integer_range.R"), "target path already exists")
  expect_error(lazyvec_skeleton("integer_range", "incorrect_folder/1.R"), "target path points to a non-existing folder")
})


test_that("generate", {
  # when testing interactively
  if (dir.exists("../../inst/lazyvec_samples/")) {
    lazyvec:::lazyvec_sample_copy("integer_range", "../../inst/lazyvec_samples/", sample_path)
  } else {
    lazyvec::lazyvec_skeleton("integer_range", sample_path)
  }

  expect_true(file.exists(sample_path))
})


# import generated implementation
source(sample_path)


test_that("ranges with different step size", {
  x <- integer_range(3L, 12L, 1L)
  expect_equal(length(x), 10)

  x <- integer_range(3L, 12L, 2L)
  expect_equal(length(x), 5)

  x <- integer_range(3L, 12L, 3L)
  expect_equal(length(x), 4)
})


# sample integer vector
x <- integer_range(3L, 12L, 2L)


test_that("trigger dataptr_or_null", {
  expect_null(lazyvec:::trigger_dataptr_or_null(x))
})


test_that("element", {1
  expect_equal(x[5], 11)
})


test_that("full_vector", {1
  expect_equal(x, c(3, 5, 7, 9, 11))
})

x[5]

y <- altrep_listener(x, "x")

y[5]

x = 1:10

