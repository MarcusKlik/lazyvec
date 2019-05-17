
context("int_range")

# clean generated files
unlink("int_range.R", force = TRUE)

test_that("arguments", {
  expect_error(lazyvec_skeleton("bla"), "Invalid skeleton_id")
  expect_error(lazyvec_skeleton("int_range", "test_int_range.R"), "target path already exists")
  expect_error(lazyvec_skeleton("int_range", "incorrect_folder/1.R"), "target path points to a non-existing folder")
})


# use for sample implementation
tmpfile <- tempfile(fileext = ".R")


test_that("generate", {
  lazyvec_skeleton("int_range", tmpfile)

  expect_true(file.exists(tmpfile))
})


# import generated implementation
source(tmpfile)


test_that("ranges with different step size", {
  x <- int_range(3L, 12L, 1L)
  expect_equal(length(x), 10)

  x <- int_range(3L, 12L, 2L)
  expect_equal(length(x), 5)

  x <- int_range(3L, 12L, 3L)
  expect_equal(length(x), 4)
})
