
context("int_range")

# clean generated files
sample_path <- "sample_int_range.R"
unlink(sample_path, force = TRUE)

test_that("arguments", {
  expect_error(lazyvec_skeleton("bla"), "Invalid skeleton_id")
  expect_error(lazyvec_skeleton("int_range", "test_int_range.R"), "target path already exists")
  expect_error(lazyvec_skeleton("int_range", "incorrect_folder/1.R"), "target path points to a non-existing folder")
})


test_that("generate", {
  # explicitly set sample source directory
  lazyvec:::lazyvec_sample_copy("int_range", "../../inst/lazyvec_samples/", sample_path)

  expect_true(file.exists(sample_path))
})


# import generated implementation
source(sample_path)


test_that("ranges with different step size", {
  x <- int_range(3L, 12L, 1L)
  expect_equal(length(x), 10)

  x <- int_range(3L, 12L, 2L)
  expect_equal(length(x), 5)

  x <- int_range(3L, 12L, 3L)
  expect_equal(length(x), 4)
})
