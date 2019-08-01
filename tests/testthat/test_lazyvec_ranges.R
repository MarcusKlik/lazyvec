
require(testthat)

context("lazyvec_ranges")

# clean generated files
sample_path <- "sample_integer_range.R"
unlink(sample_path, force = TRUE)

sample_char_path <- "sample_character_range.R"
unlink(sample_char_path, force = TRUE)


test_that("arguments", {
  expect_error(lazyvec_skeleton("bla"), "Invalid skeleton_id")
  expect_error(lazyvec_skeleton("integer_range", "test_lazyvec_ranges.R"), "target path already exists")
  expect_error(lazyvec_skeleton("integer_range", "incorrect_folder/1.R"), "target path points to a non-existing folder")
})


test_that("generate", {
  # when testing interactively
  if (dir.exists("../../inst/lazyvec_samples/")) {
    lazyvec:::lazyvec_sample_copy("integer_range", "../../inst/lazyvec_samples/", sample_path)
    lazyvec:::lazyvec_sample_copy("character_range", "../../inst/lazyvec_samples/", sample_char_path)
  } else {
    lazyvec::lazyvec_skeleton("integer_range", sample_path)
    lazyvec::lazyvec_skeleton("character_range", sample_char_path)
  }

  expect_true(file.exists(sample_path))
})


# import generated implementations
source(sample_path)
source(sample_char_path)


test_that("ranges with different step size", {
  x <- integer_range(3L, 12L, 1L)
  y <- character_range(3L, 12L, 1L)

  expect_equal(length(x), 10)
  expect_equal(length(y), 10)

  x <- integer_range(3L, 12L, 2L)
  y <- character_range(3L, 12L, 2L)

  expect_equal(length(x), 5)
  expect_equal(length(y), 5)

  x <- integer_range(3L, 12L, 3L)
  y <- character_range(3L, 12L, 3L)

  expect_equal(length(x), 4)
  expect_equal(length(y), 4)
})


# sample vectors
x <- integer_range(3L, 12L, 2L)
y <- character_range(3L, 12L, 2L)


test_that("trigger dataptr_or_null", {
  expect_null(lazyvec:::trigger_dataptr_or_null(x))

  expect_null(lazyvec:::trigger_dataptr_or_null(y))
})


test_that("element", {
  expect_equal(x[5], 11)
  expect_equal(y[5], "11")
})


test_that("full_vector", {
  expect_equal(x, c(3, 5, 7, 9, 11))
  dataptr <- lazyvec:::trigger_dataptr(x)
  expect_length(dataptr, 2)
  expect_equal(lazyvec:::trigger_dataptr_or_null(x), dataptr)

  expect_equal(y, as.character(c(3, 5, 7, 9, 11)))
  dataptr <- lazyvec:::trigger_dataptr(x)
  expect_length(dataptr, 2)
  expect_equal(lazyvec:::trigger_dataptr_or_null(x), dataptr)
})


test_that("get_region", {
  expect_equal(lazyvec:::trigger_get_region(x, 2, 2), c(7, 9))
  lazyvec:::lazyvec_deexpand(x)
  expect_equal(lazyvec:::trigger_get_region(x, 2, 2), c(7, 9))

  # size too large
  expect_error(lazyvec:::trigger_get_region(x, 4, 4), "Size too large, resulting range is outside vector boundaries")

  # index too large
  expect_error(lazyvec:::trigger_get_region(x, 8, 4), "Index is outside vector boundaries")
})


test_that("is_sorted", {
  expect_equal(lazyvec:::trigger_is_sorted(x), 1)
  expect_equal(lazyvec:::trigger_is_sorted(y), 1)
})


test_that("no_na", {
  expect_equal(lazyvec:::trigger_no_na(x), 1)
  expect_equal(lazyvec:::trigger_no_na(y), 1)
})


test_that("sum", {
  expect_equal(sum(x), 35)

  expect_equal(lazyvec:::trigger_sum(x, FALSE), 35)
  y <- lazyvec:::trigger_sum(x, TRUE)
  expect_equal(y, 35)

  expect_type(y, "double")
})


test_that("max", {
  expect_equal(max(x), 11)
  expect_equal(lazyvec:::trigger_max(x, FALSE), 11)
  y <- lazyvec:::trigger_max(x, TRUE)
  expect_equal(y, 11)

  expect_type(y, "integer")
})


test_that("min", {
  expect_equal(min(x), 3)
  expect_equal(lazyvec:::trigger_min(x, FALSE), 3)
  y <- lazyvec:::trigger_min(x, TRUE)
  expect_equal(y, 3)

  expect_type(y, "integer")
})


test_that("extract_subset", {
  expect_false(lazyvec:::lazyvec_is_expanded(x))
  expect_false(lazyvec:::lazyvec_is_expanded(y))

  expect_equal(x[c(1, 3, 5)], c(3, 7, 11))  # no copy yet
  expect_equal(y[c(1, 3, 5)], as.character(c(3, 7, 11)))  # no copy yet

  expect_equal(x[c(-2)], c(3, 7, 9, 11))  # no copy yet
  expect_equal(y[c(-2)], as.character(c(3, 7, 9, 11)))  # no copy yet

  expect_equal(x[c(-2, -3)], c(3, 9, 11))  # no copy yet
  expect_equal(y[c(-2, -3)], as.character(c(3, 9, 11)))  # no copy yet

  expect_equal(x[0], integer(0))  # no copy yet
  expect_equal(y[0], character(0))  # no copy yet

  expect_warning(x[7], "called with index containing elements larger than the vector length")
  expect_warning(y[7], "called with index containing elements larger than the vector length")
})


test_that("duplicate", {
  expect_false(lazyvec:::lazyvec_is_expanded(x))
  expect_false(lazyvec:::lazyvec_is_expanded(y))

  z1 <- x  # no copy yet
  z2 <- y  # no copy yet

  expect_false(lazyvec:::lazyvec_is_expanded(x))
  expect_false(lazyvec:::lazyvec_is_expanded(y))

  z1[1] <- 1  # expanded copy assigned to z
  z2[1] <- 1  # expanded copy assigned to z

  expect_true(is_altrep(x))
  expect_false(is_altrep(z1))
  expect_true(lazyvec:::lazyvec_is_expanded(x))

  expect_true(is_altrep(y))
  expect_false(is_altrep(z2))
  expect_true(lazyvec:::lazyvec_is_expanded(y))
})


test_that("coerce", {
  lazyvec:::lazyvec_deexpand(x)
  lazyvec:::lazyvec_deexpand(y)

  z1 <- as.character(x)  # coercion per element
  z2 <- as.integer(y)

  expect_type(z1, "character")
  expect_type(z2, "integer")

  expect_true(is_altrep(z1))
  expect_true(is_altrep(z2))
})
